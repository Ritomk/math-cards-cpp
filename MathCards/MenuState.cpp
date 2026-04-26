#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window, sf::Font& font, std::shared_ptr<StateMachine> stateMachine)
{
	this->stateMachine = stateMachine;
	this->window = &window;
	this->font = font;
	this->InitVariables();
	this->InitShape();
	this->InitText();
}

MenuState::~MenuState()
{
	//delete window;
}

void MenuState::InitVariables()
{
	this->highlightedButtonIndex = 0;
	this->playButtonHighlighted = false;
	this->rulesButtonHighlighted = false;
	this->exitButtonHighlighted = false;
}

void MenuState::InitShape()
{
	this->playButtonShape.setSize(sf::Vector2f(350, 100));
	sf::FloatRect spriteRect = this->playButtonShape.getLocalBounds();
	this->playButtonShape.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height);
	this->playButtonShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f + 50.f));
	this->playButtonShape.setFillColor(sf::Color::Magenta);

	this->rulesButtonShape.setSize(sf::Vector2f(350, 100));
	sf::FloatRect spriteRect1 = this->rulesButtonShape.getLocalBounds();
	this->rulesButtonShape.setOrigin(spriteRect1.left + spriteRect1.width / 2.0f,
		spriteRect1.top + spriteRect1.height);
	this->rulesButtonShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f + 225.f));
	this->rulesButtonShape.setFillColor(sf::Color::Green);

	this->exitButtonShape.setSize(sf::Vector2f(350, 100));
	sf::FloatRect spriteRect2 = this->exitButtonShape.getLocalBounds();
	this->exitButtonShape.setOrigin(spriteRect2.left + spriteRect2.width / 2.0f,
		spriteRect2.top + spriteRect2.height);
	this->exitButtonShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f + 400.f));
	this->exitButtonShape.setFillColor(sf::Color::Cyan);
}

void MenuState::InitText()
{
	this->playButtonText.setFont(font);
	this->playButtonText.setCharacterSize(100);
	this->playButtonText.setFillColor(sf::Color::Yellow);
	this->playButtonText.setStyle(sf::Text::Bold);
	this->playButtonText.setString("PLAY");
	sf::FloatRect textRect = this->playButtonText.getLocalBounds();
	this->playButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->playButtonText.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f));

	this->rulesButtonText.setFont(font);
	this->rulesButtonText.setCharacterSize(100);
	this->rulesButtonText.setFillColor(sf::Color::Yellow);
	this->rulesButtonText.setStyle(sf::Text::Bold);
	this->rulesButtonText.setString("RULES");
	sf::FloatRect textRect1 = this->rulesButtonText.getLocalBounds();
	this->rulesButtonText.setOrigin(textRect1.left + textRect1.width / 2.0f,
		textRect1.top + textRect1.height / 2.0f);
	this->rulesButtonText.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f + 175.f));

	this->exitButtonText.setFont(font);
	this->exitButtonText.setCharacterSize(100);
	this->exitButtonText.setFillColor(sf::Color::Yellow);
	this->exitButtonText.setStyle(sf::Text::Bold);
	this->exitButtonText.setString("EXIT");
	sf::FloatRect textRect2 = this->exitButtonText.getLocalBounds();
	this->exitButtonText.setOrigin(textRect2.left + textRect2.width / 2.0f,
		textRect2.top + textRect2.height / 2.0f);
	this->exitButtonText.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2 + 350.f));

	this->gameTitle.setFont(font);
	this->gameTitle.setCharacterSize(160);
	this->gameTitle.setFillColor(sf::Color::Yellow);
	this->gameTitle.setStyle(sf::Text::Bold);
	this->gameTitle.setString("MathCards");
	sf::FloatRect textRect4 = this->gameTitle.getLocalBounds();
	this->gameTitle.setOrigin(textRect4.left + textRect4.width / 2.0f,
		textRect4.top + textRect4.height / 2.0f);
	this->gameTitle.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f - 250.f));
}

void MenuState::ButtonPressed()
{
	if (playButtonHighlighted)
	{
		this->stateMachine->PushState(new GameState(*window, font, stateMachine));
	}
	else if (rulesButtonHighlighted)
	{
		this->stateMachine->PushState(new RulesState(*window, font, stateMachine));
	}
	else if (exitButtonHighlighted)
	{
		this->window->close();
	}
}

void MenuState::Update()
{
	switch (this->highlightedButtonIndex)
	{
	case 0:
		this->playButtonHighlighted = true;
		this->rulesButtonHighlighted = false;
		this->exitButtonHighlighted = false;
		break;

	case 1:
		this->playButtonHighlighted = false;
		this->rulesButtonHighlighted = true;
		this->exitButtonHighlighted = false;
		break;

	case 2:
		this->playButtonHighlighted = false;
		this->rulesButtonHighlighted = false;
		this->exitButtonHighlighted = true;
		break;
	}
}

void MenuState::HandleInput()
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
				this->window->close();
			}

			if (this->ev.key.code == sf::Keyboard::W)
			{
				if (this->highlightedButtonIndex > 0)
				{
					highlightedButtonIndex--;
				}
			}
			else if (this->ev.key.code == sf::Keyboard::S)
			{
				if (this->highlightedButtonIndex < 2)
				{
					highlightedButtonIndex++;
				}
			}

			if (this->ev.key.code == sf::Keyboard::Space)
			{
				this->ButtonPressed();
			}
		}
	}
}

void MenuState::Draw()
{
	this->window->clear();

	if (playButtonHighlighted)
	{
		this->window->draw(playButtonShape);
	}
	else if (rulesButtonHighlighted)
	{
		this->window->draw(rulesButtonShape);
	}
	else if (exitButtonHighlighted)
	{
		this->window->draw(exitButtonShape);
	}

	this->window->draw(playButtonText);
	this->window->draw(rulesButtonText);
	this->window->draw(exitButtonText);
	this->window->draw(gameTitle);

	this->window->display();
}
