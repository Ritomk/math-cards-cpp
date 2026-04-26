#include "Card.h"

Card::Card()
{
	symbol = '\0';
}

Card::Card(std::string sign, sf::Font& font)
{
	this->InitShape();
	this->InitText(sign, font);
}

Card::~Card()
{

}

void Card::InitShape() //Inicjalizacja kszta³tu karty
{
	this->cardSize = sf::Vector2f(100, 200);
	this->cardShape.setSize(this->cardSize);
	this->cardShape.setFillColor(sf::Color::White);
	sf::FloatRect shapeRect = this->cardShape.getLocalBounds();	//ustawienie pozycji kszta³tu na œrodek
	this->cardShape.setOrigin(shapeRect.left + shapeRect.width / 2.0f,
		shapeRect.top + shapeRect.height / 2.0f);
}

void Card::InitText(std::string sign, sf::Font &font)
{
	this->symbol = sign;

	this->text.setFont(font);
	this->text.setCharacterSize(100);
	this->text.setFillColor(sf::Color::Red);
	this->text.setStyle(sf::Text::Bold);
	this->text.setString(this->symbol);
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void Card::setCardColor(sf::Color color)
{
	this->cardShape.setFillColor(color);
}

void Card::setCardPosition(sf::Vector2f position)
{
	this->cardShape.setPosition(position);
	this->text.setPosition(
		this->cardShape.getGlobalBounds().left + (this->cardShape.getGlobalBounds().width / 2),
		this->cardShape.getGlobalBounds().top + (this->cardShape.getGlobalBounds().height / 2));
}

void Card::setCardScale(float scale)
{
	cardShape.scale(sf::Vector2f(scale, scale));
}

void Card::setSymbolOnCard(std::string sign)
{
	this->symbol = sign;
}

const std::string Card::getSymbolOnCard() const
{
	return this->symbol;
}

sf::RectangleShape Card::getCardShape()
{
	return this->cardShape;
}

sf::Text Card::getCardText()
{
	return this->text;
}

void Card::DrawCard(sf::RenderTarget &target)
{
	target.draw(this->cardShape);
	target.draw(this->text);
}