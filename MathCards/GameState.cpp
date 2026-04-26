#include "GameState.h"
#include <thread>
#include <chrono>

GameState::GameState(sf::RenderWindow& window, sf::Font& font, std::shared_ptr<StateMachine> stateMachine) : player(font), opponent(font),
	table{new Table(sf::Vector2f(60, 250),sf::Color(128, 0, 0, 180)),
	new Table(sf::Vector2f(1020, 250),sf::Color(0, 0, 128, 180)),
	new Table(sf::Vector2f(60, 475),sf::Color(255, 0, 0, 180)),
	new Table(sf::Vector2f(1020, 475),sf::Color(0, 0, 255, 180))}
{
	this->stateMachine = stateMachine;
	this->window = &window;
	this->font = font;

	this->InitVariables();
	this->InitBackground();
	this->InitHealthText();

	this->StartNextRound();
}

GameState::~GameState()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (this->table[i] != nullptr)
			{
				delete this->table[i][j];
			}
		}
	}
}

void GameState::InitVariables()
{
	this->playerHealth = 1000;
	this->opponentHealth = 1000;
	this->gameover = false;

	this->playerHasAnyCards = true;
	this->playerPlacedCardsOnOpponentTable = false;
	this->playerMadeMove = false;

	this->playerEndedRound = false;
	this->opponentEndedRound = false;

	this->highlightedTableIndexX = 0;
	this->highlightedTableIndexY = 1;
	this->tableChanged = false;
}

void GameState::InitBackground()
{
	if (!this->backgroundTexture.loadFromFile("Sprites/Table.png"))
	{
		std::cout << "Error: Could not open texture file Table.png" << std::endl;
		return;
	}
	this->backgroundSprite.setTexture(this->backgroundTexture);
}

void GameState::InitHealthText()
{
	this->playerHealthText.setFont(this->font);
	this->playerHealthText.setString("Player Health\n\t   " + std::to_string(this->playerHealth));
	this->playerHealthText.setCharacterSize(70);
	this->playerHealthText.setFillColor(sf::Color::Red);
	this->playerHealthText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = this->playerHealthText.getLocalBounds();
	this->playerHealthText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->playerHealthText.setPosition(sf::Vector2f(1620, 810));

	this->roundText.setFont(this->font);
	this->roundText.setString("Round: 0");
	this->roundText.setCharacterSize(100);
	this->roundText.setFillColor(sf::Color::White);
	this->roundText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect2 = this->roundText.getLocalBounds();
	this->roundText.setOrigin(textRect2.left + textRect2.width / 2.0f,
		textRect2.top + textRect2.height / 2.0f);
	this->roundText.setPosition(sf::Vector2f(160, 800));

	this->opponentHealthText.setFont(this->font);
	this->opponentHealthText.setString("Opponent Health\n\t\t " + std::to_string(this->opponentHealth));
	this->opponentHealthText.setCharacterSize(60);
	this->opponentHealthText.setFillColor(sf::Color::Red);
	this->opponentHealthText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect1 = this->opponentHealthText.getLocalBounds();
	this->opponentHealthText.setOrigin(textRect1.left + textRect1.width / 2.0f,
		textRect1.top + textRect1.height / 2.0f);
	this->opponentHealthText.setPosition(sf::Vector2f(180, 70));

	this->gameoverText.setFont(this->font);
	this->gameoverText.setString("");
	this->gameoverText.setCharacterSize(120);
	this->gameoverText.setFillColor(sf::Color::White);
	this->gameoverText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect3 = this->gameoverText.getLocalBounds();
	this->gameoverText.setOrigin(textRect3.left + textRect3.width / 2.0f,
		textRect3.top + textRect3.height / 2.0f);
	this->gameoverText.setPosition(sf::Vector2f(700, 350));
}

void GameState::HandleInput()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:

			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->stateMachine->PopState();
			}

			if (this->playerEndedRound)
			{
				return;
			}
			else if (this->gameover)
			{
				if (this->ev.key.code == sf::Keyboard::Space)
				{
					this->stateMachine->PopState();
				}
				return;
			}

			if (!this->player.GetCardPicked())
			{
				if (this->ev.key.code == sf::Keyboard::A)
				{
					this->player.DecreaseHighlightedIndex();
				}
				else if (this->ev.key.code == sf::Keyboard::D)
				{
					this->player.IncreaseHighlightedIndex();
				}
				else if (this->ev.key.code == sf::Keyboard::Space)
				{
					if (this->player.PickCard())
					{
						this->table[highlightedTableIndexY][highlightedTableIndexX]->EnableOutline(true);
					}
				}

				if (this->ev.key.code == sf::Keyboard::Enter)
				{
					this->playerEndedRound = true;
				}
			}
			else
			{
				this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->EnableOutline(false);

				if (this->ev.key.code == sf::Keyboard::A && this->highlightedTableIndexX != 0)
				{
					this->highlightedTableIndexX--;
				}
				else if (this->ev.key.code == sf::Keyboard::D && this->highlightedTableIndexX != 1)
				{
					this->highlightedTableIndexX++;
				}
				else if (this->ev.key.code == sf::Keyboard::W && this->highlightedTableIndexY != 0)
				{
					this->highlightedTableIndexY--;
				}
				else if (this->ev.key.code == sf::Keyboard::S && highlightedTableIndexY != 1)
				{
					this->highlightedTableIndexY++;
				}
				this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->EnableOutline(true);



				if (this->ev.key.code == sf::Keyboard::LControl)
				{
					this->player.PutCard();
					this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->EnableOutline(false);
				}



				if (this->ev.key.code == sf::Keyboard::Space)
				{
					if (this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->canPlaceCard(player.GetCard()))
					{
						if (this->highlightedTableIndexY == this->opponent.GetTableIndexY() && this->highlightedTableIndexX == this->opponent.GetTableIndexX())
						{
							this->opponent.ClearPlacingOrder(this->player.GetCard().getSymbolOnCard());
						}
						this->player.PutCard();
						this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->NewCardPlaced(this->player.GetCard());
						this->player.DeleteCard();
						this->table[this->highlightedTableIndexY][this->highlightedTableIndexX]->EnableOutline(false);

						this->playerMadeMove = true;
					}
				}
			}
			break;
		}
	}
}

const bool GameState::GameRunning() const
{
	return this->window->isOpen();
}

void GameState::Update()
{
	if (this->gameover)
	{
		return;
	}

	if (this->playerEndedRound && this->opponentEndedRound)
	{
		this->ControlWinLose();
		this->ControlRoundOver();
		return;
	}

	if (this->playerMadeMove || this->playerEndedRound)
	{
		if (playerEndedRound)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		if (this->opponent.MakeMove(this->playerHasAnyCards, table[1][0]->GetCards()))
		{
			if (this->playerHasAnyCards)
			{
				if (this->table[0][0]->EvaulateEquasion() - this->table[1][1]->EvaulateEquasion() > 500)
				{
					this->opponent.EndRound();
					this->opponentEndedRound = true;
				}
				else if (this->table[1][0]->EvaulateEquasion() - this->table[0][1]->EvaulateEquasion() < -500
					|| (this->table[1][0]->EvaulateEquasion() - this->table[0][1]->EvaulateEquasion() < 0 && this->playerEndedRound))
				{
					this->opponent.EndRound();
					this->opponentEndedRound = true;
				}
			}

			if (!this->opponentEndedRound)
			{
				this->table[this->opponent.GetTableIndexY()][this->opponent.GetTableIndexX()]->NewCardPlaced(this->opponent.InstantizeNewCard());
				this->opponent.DeleteCard();
			}
		}
		else
		{
			this->opponentEndedRound = true;
		}
		this->playerMadeMove = false;
	}
}

void GameState::Draw()
{
	this->window->clear();

	this->window->draw(this->backgroundSprite);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			this->table[i][j]->DrawTable(*this->window);
		}
	}

	this->player.DrawHand(*this->window);
	this->player.DrawCards(*this->window);

	this->window->draw(this->playerHealthText);
	this->window->draw(this->opponentHealthText);

	this->window->draw(this->roundText);

	if (this->gameover)
	{
		this->window->draw(this->gameoverText);
	}

	this->window->display();
}

void GameState::ControlRoundOver()
{
	if (this->parser.IsRPN(this->table[1][1]->GetCards())) //gracz broni
	{
		this->playerHealth -= (this->table[0][0]->EvaulateEquasion() - this->table[1][1]->EvaulateEquasion());

		if (this->playerHealth > 1000) this->playerHealth = 1000;
	}
	else
	{
		this->playerHealth -= (this->table[0][0]->EvaulateEquasion() * 2);
	}


	if (this->parser.IsRPN(this->table[0][1]->GetCards())) //przeciwnik broni
	{
		this->opponentHealth -= (this->table[1][0]->EvaulateEquasion() - this->table[0][1]->EvaulateEquasion());

		if (this->opponentHealth > 1000) this->opponentHealth = 1000;
	}
	else
	{
		this->opponentHealth -= (this->table[1][0]->EvaulateEquasion() * 2);
	}

	this->playerHealthText.setString("Player Health\n\t\t" + std::to_string(playerHealth));
	this->opponentHealthText.setString("Opponent Health\n\t\t" + std::to_string(opponentHealth));

	this->StartNextRound();
}

void GameState::ControlWinLose()
{
	this->round++;
	this->roundText.setString("Round: " + std::to_string(this->round));

	if (this->playerHealth == 0)
	{
		this->gameoverText.setString("YOU LOST...");
	}
	else if(this->opponentHealth == 0)
	{
		this->gameoverText.setString("YOU WON!!!");
		this->gameover = true;
	}
	else if (this->round == 10)
	{
		if (this->playerHealth > this->opponentHealth)
		{
			this->gameoverText.setString("YOU WON!!!");
		}
		else
		{
			this->gameoverText.setString("YOU LOST...");
		}
		this->gameover = true;
	}
}

void GameState::StartNextRound()
{
	this->playerEndedRound = false;
	this->opponentEndedRound = false;

	this->playerHasAnyCards = this->player.HasAnyCards();
	std::cout << this->player.HasAnyCards() << std::endl;

	this->player.ReturnCardsToDeck();
	this->opponent.ReturnCardsToDeck();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			this->table[i][j]->Clear();
		}
	}

	for (int i = 0; i < 15; i++)
	{
		this->opponent.GenerateCardSymbol();
		this->player.InstantizeNewCard();
	}
}
