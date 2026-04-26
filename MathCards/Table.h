#pragma once
#include "Parser.h"
#include "Card.h"

class Table
{
private:
	Parser parser;
	float nextShift;
	int nextIndex;

protected:
	sf::RectangleShape tableShape;
	sf::Vector2f tablePosition;
	std::vector<Card> cardsOnTable;
	float parsedValue;

	void InitShape();
	void InitVariables();

public:
	Table(const sf::Vector2f, const sf::Color);
	~Table();

	const std::vector<std::string> GetCards() const;
	void EnableOutline(bool);
	float EvaulateEquasion();
	void NewCardPlaced(const Card&);
	void Clear();

	void DrawTable(sf::RenderTarget&);

	bool canPlaceCard(const Card&);
};

