#pragma once
#include <iostream>

#include "Player.h"
#include "State.h"
#include "StateMachine.h"
#include "Table.h"
#include "Opponent.h"

class GameState :
	public State
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	std::shared_ptr<StateMachine> stateMachine;
	sf::Event ev;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	Parser parser;
	Player player;
	Opponent opponent;
	Table *table[2][2];

	int highlightedTableIndexX;
	int highlightedTableIndexY;
	bool tableChanged;
	int round;

	bool playerHasAnyCards;
	bool playerMadeMove;
	bool playerPlacedCardsOnOpponentTable;
	bool playerEndedRound;
	bool opponentEndedRound;

	int playerHealth;
	sf::Text playerHealthText;
	sf::Text roundText;
	int opponentHealth;
	sf::Text opponentHealthText;
	sf::Text gameoverText;
	bool gameover;

	void InitVariables();
	void InitBackground();
	void InitHealthText();
	void HandleInput();

public:
	GameState(sf::RenderWindow&, sf::Font&, std::shared_ptr<StateMachine>);
	~GameState();

	const bool GameRunning() const;
	void Update();
	void Draw();

	void ControlRoundOver();
	void ControlWinLose();
	void StartNextRound();
};

