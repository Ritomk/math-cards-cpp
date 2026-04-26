#include "Player.h"
#include <iostream>


Player::Player(sf::Font& font) : font(font)
{
	this->InitVariables();
	this->InitHand();
}

Player::~Player()
{

}

void Player::InitVariables()
{
	this->cardPicked = false;
	this->cardsInHand = 0;
	this->highlightedCardIndex = 0;
	this->symbols = {
		"1","1","2","2","3","3",
		"4","4","5","5","6","6",
		"7","7","8","8","9","9",
		"+","+","+","-","-","-",
		"*","*","*","/","/","/" };
	this->centerPosition = new sf::Vector2f(900, 400);
	this->cardsPositions = new sf::Vector2f[5]{
		sf::Vector2f(500,800), sf::Vector2f(700,700),
		sf::Vector2f(900,600), sf::Vector2f(1100,700),
		sf::Vector2f(1300,800) };
}

void Player::InitHand()
{
	this->InitHandTexture();

	this->handSprite.setTexture(this->handTexture);
	this->handSprite.setScale(0.5, 0.5);
	sf::FloatRect spriteRect = this->handSprite.getLocalBounds();
	this->handSprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height);
	this->handSprite.setPosition(sf::Vector2f(1800 / 2.0f, 900));

	this->handText.setFont(this->font);
	this->handText.setString(std::to_string(this->cardsInHand));
	this->handText.setCharacterSize(80);
	this->handText.setFillColor(sf::Color::Blue);
	this->handText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = this->handText.getLocalBounds();
	this->handText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->handText.setPosition(
		this->handSprite.getGlobalBounds().left + (this->handSprite.getGlobalBounds().width / 1.7f),
		this->handSprite.getGlobalBounds().top + (this->handSprite.getGlobalBounds().height / 1.3f));
}

void Player::InitHandTexture()
{
	if (!this->handTexture.loadFromFile("Sprites/Hand.png"))
	{
		std::cout << "Error, while trying to load Hand texture" << std::endl;
		return;
	}
}

void Player::IncreaseDisplayedIndex()
{
	if (this->cards.size() > 5)
	{
		this->cards.insert(this->cards.begin(), this->cards.back());
		this->cards.erase(this->cards.end() - 1);
	}
}

void Player::DecreaseDisplayedIndex()
{
	if (this->cards.size() > 5)
	{
		this->cards.insert(this->cards.end(), this->cards[0]);
		this->cards.erase(this->cards.begin());
	}
}

const bool Player::HasAnyCards() const
{
	if ((this->symbols.size() + this->cards.size()) < 15)
	{
		return false;
	}
	else
	{
		return true;
	}
}

const bool Player::GetCardPicked() const
{
	return this->cardPicked;
}

const Card& Player::GetCard() const
{
	return this->cards[this->highlightedCardIndex];
}

void Player::DeleteCard()
{
	this->cards.erase(this->cards.begin() + this->highlightedCardIndex);
	this->Update();
	cardPicked = false;
}

void Player::IncreaseHighlightedIndex()
{
	if (this->cards.size() > 0)
	{
		this->cards[this->highlightedCardIndex].setCardColor(sf::Color::White);

		if (this->highlightedCardIndex == 4)
		{
			DecreaseDisplayedIndex();
			this->cards[this->highlightedCardIndex].setCardColor(sf::Color::Yellow);
		}
		else
		{
			this->highlightedCardIndex++;
			this->highlightedCardIndex > cards.size() - 1 ? this->highlightedCardIndex = this->cards.size() - 1 : this->highlightedCardIndex;
			this->cards[this->highlightedCardIndex].setCardColor(sf::Color::Yellow);
		}
	}
}

void Player::DecreaseHighlightedIndex()
{
	if (this->cards.size() > 0)
	{
		this->cards[this->highlightedCardIndex].setCardColor(sf::Color::White);

		if (this->highlightedCardIndex == 0)
		{
			IncreaseDisplayedIndex();
			this->cards[this->highlightedCardIndex].setCardColor(sf::Color::Yellow);
		}
		else
		{
			this->highlightedCardIndex--;
			this->highlightedCardIndex < 0 ? this->highlightedCardIndex = 0 : this->highlightedCardIndex;
			this->cards[this->highlightedCardIndex].setCardColor(sf::Color::Yellow);
		}
	}
}

void Player::PickFirstFivePosition()
{
	this->cardPosistionIndex++;
}

void Player::Update()
{
	if (cards.size() > 0)
	{
		this->highlightedCardIndex < 0 ? this->highlightedCardIndex = 0 : this->highlightedCardIndex;
		this->highlightedCardIndex > cards.size() - 1 ? this->highlightedCardIndex = this->cards.size() - 1 : this->highlightedCardIndex;
		this->cards[this->highlightedCardIndex].setCardColor(sf::Color::Yellow);
	}

	this->cardsInHand = this->cards.size();
	this->handText.setString(std::to_string(this->cardsInHand));
}

void Player::InstantizeNewCard()
{
	if (this->symbols.size() < 1)
	{
		return;
	}

	this->cards.emplace_back(Card(GenerateSymbol(), this->font));
	PickFirstFivePosition();

	this->Update();

	if (cards.size()==1)
	{
		this->cards[0].setCardColor(sf::Color::Yellow);
	}
}

void Player::ReturnCardsToDeck()
{
	while (cards.size() > 0)
	{
		symbols.push_back(cards[0].getSymbolOnCard());
		cards.erase(cards.begin());
	}
}

std::string Player::GenerateSymbol()
{

	int random = 0;
	srand(time(NULL));

	random = rand() % this->symbols.size();

	std::string returnSymbol = this->symbols[random];

	this->symbols.erase(this->symbols.begin() + random);
	return returnSymbol;
}


bool Player::PickCard()
{
	if (this->cards.empty()) return false;
	this->cardPicked = true;
	this->cards[this->highlightedCardIndex].setCardPosition(*this->centerPosition);
	this->cards[this->highlightedCardIndex].setCardScale(1.25);
	return true;
}

void Player::PutCard()
{
	this->cardPicked = false;
	this->cards[this->highlightedCardIndex].setCardScale(0.8f);
}

void Player::DrawCards(sf::RenderTarget& target)
{
	for (int i = 0; i < 5; i++)
	{
		if (this->cards.size() > i)
		{
			if (!cardPicked || highlightedCardIndex != i)
			{
				this->cards[i].setCardPosition(this->cardsPositions[i]);
			}
			this->cards[i].DrawCard(target);
		}
	}
}

void Player::DrawHand(sf::RenderWindow& window)
{
	window.draw(this->handSprite);
	window.draw(this->handText);
}