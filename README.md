# MathCards

A **turn-based card game** built in C++ with SFML, where players construct mathematical expressions in **Reverse Polish Notation (RPN)** to deal damage to an opponent controlled by AI. Developed as a university project for the *C++ Programming* course.

> **This is the first iteration of the concept.** The game has since been expanded into a fully-featured Unity project as part of an engineering thesis — check out the evolved version here: **[MathCards Unity](https://github.com/Ritomk/math-cards)**

---

## Gameplay Overview

Each player (human and AI) holds a hand of cards bearing **numbers (1–9)** and **mathematical operators (+, −, ×, ÷)**. The battlefield consists of four tables arranged in a 2×2 grid:

| | Player's Table | Opponent's Table |
|---|---|---|
| **Attack** | Build your offensive expression | Sabotage the opponent's defense |
| **Defense** | Defend against the opponent's attack | AI builds its offensive expression |

### Core Mechanics
- **Card Placement** — Cards are placed on tables to form expressions written in **Reverse Polish Notation** (e.g., `3 4 + 2 *` = 14)
- **Damage Calculation** — At the end of each round, damage dealt equals the difference between the attacker's expression value and the defender's expression value
- **Sabotage System** — Players can place operator cards on the opponent's defense table to weaken their defensive expression
- **Penalty for Invalid RPN** — If a defense table doesn't contain a valid RPN expression, the attacker deals **double damage**
- **Win Condition** — Reduce the opponent's HP to 0, or have more HP after 10 rounds

### Controls
| Key | Action |
|---|---|
| `A` / `D` | Navigate cards in hand / Select table column |
| `W` / `S` | Select table row |
| `Space` | Pick up card / Place card on table / Confirm |
| `LCtrl` | Return picked card to hand |
| `Enter` | End current round |
| `Escape` | Return to menu |

---

## Architecture & Technical Highlights

### State Machine Pattern
The application is built around a **stack-based state machine** that manages game flow through distinct states:

```
StateMachine (stack<State*>)
├── MenuState    — Main menu with navigation
├── GameState    — Core gameplay loop
└── RulesState   — Rules display screen
```

Each state implements a pure virtual `State` interface with `Update()`, `HandleInput()`, and `Draw()` methods, providing clean separation of concerns and enabling seamless transitions between game screens. The state machine supports **push, pop, and change** operations, allowing states to be stacked (e.g., returning from Rules back to Menu).

### RPN Expression Parser
A custom **Reverse Polish Notation parser** (`Parser`) handles:
- **Validation** (`IsRPN`) — Uses a valence-based algorithm to verify expression correctness in O(n) time
- **Evaluation** (`RpnEval`) — Stack-based evaluation supporting `+`, `−`, `×`, `÷`, and `^` operators
- **Operator Priority** — Proper precedence handling for expression processing

### AI Opponent with Strategic Decision-Making
The `Opponent` class implements a non-trivial AI system:
- **Combinatorial Generation** — Recursively generates all valid card combinations up to a target length, evaluating them against the current board state
- **Greedy Optimization** — Selects the expression yielding the highest value from all valid RPN permutations
- **Adaptive Strategy** — Dynamically adjusts target expression length (3 → 5 → 7 → 9 cards) across the round
- **Sabotage Tactics** — When the player's attack table has 5–6 symbols, the AI prioritizes placing `−` or `÷` operators on the player's attack table to reduce incoming damage
- **Resource Management** — Tracks available cards, returns cards to the deck between rounds, and gracefully handles depletion

### Object-Oriented Design
- **Encapsulation** — Each game entity (`Card`, `Player`, `Opponent`, `Table`) manages its own state, rendering, and logic
- **Polymorphism** — State system leverages virtual dispatch for clean game-loop integration
- **Separation of Concerns** — Rendering (`Draw`), logic (`Update`), and input (`HandleInput`) are clearly separated at every level
- **Manual Memory Management** — Raw pointers with explicit `new`/`delete` for game objects (states, tables, positions), demonstrating understanding of C++ memory ownership semantics

---

## Tech Stack

| Component | Technology |
|---|---|
| **Language** | C++17 |
| **Graphics & Input** | [SFML 2.x](https://www.sfml-dev.org/) |
| **Build System** | Visual Studio / MSBuild |
| **Platform** | Windows (x64) |

---

## Project Structure

```
MathCards/
├── main.cpp              # Entry point
├── Game.h/.cpp           # Application bootstrap & main loop
├── State.h               # Abstract state interface
├── StateMachine.h/.cpp   # Stack-based state manager
├── MenuState.h/.cpp      # Main menu UI & navigation
├── GameState.h/.cpp      # Core gameplay orchestration
├── RulesState.h/.cpp     # Rules display screen
├── Card.h/.cpp           # Card entity (shape, symbol, rendering)
├── Player.h/.cpp         # Player hand management & input
├── Opponent.h/.cpp       # AI logic & strategy
├── Table.h/.cpp          # Table entity & RPN card validation
├── Parser.h/.cpp         # RPN expression validator & evaluator
├── Font/                 # Font assets
├── Sprites/              # Texture assets (Hand.png, Table.png)
└── Rules/                # Game rules text file
```

---

## Building & Running

### Prerequisites
- **Visual Studio 2019+** with C++ Desktop Development workload
- **SFML 2.x** (included in `External/` directory)

### Build Steps
1. Clone the repository
   ```bash
   git clone https://github.com/Ritomk/MathCards.git
   ```
2. Open `MathCards.sln` in Visual Studio
3. Set build configuration to **x64** (Debug or Release)
4. Build and run (`F5`)

> SFML runtime DLLs are included in the project directory for convenience.

---

## Evolution — From C++ Prototype to Unity Thesis

This project served as the **proof of concept** that validated the core game mechanics — RPN-based combat, the sabotage system, and AI expression optimization. The lessons learned here directly shaped the architecture of the full Unity version, developed as an **engineering thesis**.

### What carried over (and scaled up)
| C++ Prototype | Unity Version |
|---|---|
| Stack-based state machine (3 states) | Generic dual state machine — `StateMachine<TStateEnum>` with 8 game states + 10 player states, coroutine transitions, queue-based processing, and state history with rollback |
| Recursive RPN combo generator | Async expression optimizer (`Task.Run()`) with backtracking, running off the main thread |
| AI sabotage (place `−`/`÷` on player's table) | Full behaviour tree (NodeCanvas) with probabilistic sabotage, escalating chance, and adaptive attack/defense priorities |
| `Parser::RpnEval` stack evaluator | `RpnExpressionHelper` with multiple evaluation modes + animated card-by-card RPN visualization |
| Direct function calls between systems | ScriptableObject event bus (7 event channels) — fully decoupled, inspector-wired architecture |

### What's new in Unity
- **3D environment** — cards, tables, and chests as 3D models with custom materials
- **6 custom ShaderGraph shaders** — dissolve, highlight rain, distortion, dithering post-process
- **Card merge mechanic** — combine two cards in an animated chest to create multi-digit numbers (e.g., `8` + `9` → `89`)
- **Spline-based hand layout** — cards fan along a configurable Unity Spline with duplicate grouping
- **Custom coroutine framework** — centralized `CoroutineHelper` with pause/resume, ID tracking, and `WaitForSecondsPauseable`
- **Unity Input System** — action maps with hold interactions and context-sensitive state filtering

**[Check out the Unity version →](https://github.com/Ritomk/math-cards-unity)**

---

## License

University project — feel free to explore the code and use it as reference material.
