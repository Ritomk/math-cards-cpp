#include "Table.h"

Table::Table(const sf::Vector2f position, const sf::Color color)
{
	this->tablePosition = position;
	this->tableShape.setPosition(position);
	this->tableShape.setFillColor(color);
	this->InitVariables();
	this->InitShape();
}

Table::~Table()
{

}

void Table::InitVariables()
{
	this->nextShift = 0;
	this->nextIndex = 0;
	this->parsedValue = 0;
}

void Table::InitShape()
{
	this->tableShape.setSize(sf::Vector2f(820, 200));
	this->tableShape.setOutlineColor(sf::Color::Yellow);
	this->tableShape.setOutlineThickness(0);
	sf::FloatRect shapeRect = this->tableShape.getLocalBounds();
	this->tableShape.setOrigin(shapeRect.left + 50,
		shapeRect.top + shapeRect.height / 2.0f);
}

const std::vector<std::string> Table::GetCards() const
{
	std::vector<std::string> temp;
	for (auto& card : cardsOnTable)
	{
		temp.push_back(card.getSymbolOnCard());
	}

	return temp;
}

void Table::EnableOutline(bool enable)
{
	if (enable)
	{
		this->tableShape.setOutlineThickness(10);
	}
	else
	{
		this->tableShape.setOutlineThickness(0);
	}
}

float Table::EvaulateEquasion()
{
	std::vector<std::string> temp;
	if (this->cardsOnTable.size() > 0)
	{
		for (auto& card : this->cardsOnTable)
		{
			temp.push_back(card.getSymbolOnCard());
		}

		std::cout << this->parser.IsRPN(temp) << std::endl;
		if (this->parser.IsRPN(temp) == 1)
		{
			this->parsedValue = this->parser.RpnEval(temp);
		}
		else
		{
			std::cout << "This is not RPN" << std::endl;
			return 0;
		}
	}
	return parsedValue;
}

void Table::NewCardPlaced(const Card &card)
{
	this->cardsOnTable.emplace_back(card);
	this->cardsOnTable[this->nextIndex].setCardScale(0.8f);
	this->cardsOnTable[this->nextIndex].setCardPosition(sf::Vector2f(this->tablePosition.x + this->nextShift, this->tablePosition.y));
	this->cardsOnTable[this->nextIndex].setCardColor(sf::Color::White);
	this->nextShift += 90;
	this->nextIndex++;
}

void Table::Clear()
{
	if (cardsOnTable.size() > 0)
	{
		cardsOnTable.clear();
		this->nextShift = 0;
		this->nextIndex = 0;
	}
	this->parsedValue = 0;
}

void Table::DrawTable(sf::RenderTarget& target)
{
	target.draw(this->tableShape);
	if (this->cardsOnTable.size() > 0)
	{
		for (auto& card : this->cardsOnTable)
		{
			card.DrawCard(target);
		}
	}
}

bool Table::canPlaceCard(const Card& checkedCard)
{
	if (cardsOnTable.size() < 2 && (isdigit(checkedCard.getSymbolOnCard()[0]) || checkedCard.getSymbolOnCard().size() > 1))
	{
		return true;
	}
	else if (cardsOnTable.size() >= 2 && cardsOnTable.size() <8)
	{
		std::vector<std::string> temp;
		for (auto& card : this->cardsOnTable)
		{
			temp.push_back(card.getSymbolOnCard());
		}
		temp.push_back(checkedCard.getSymbolOnCard());
		if (this->parser.IsRPN(temp) < 4 && this->parser.IsRPN(temp) > 0)
		{
			return true;
		}
	}
	else if (cardsOnTable.size() == 8 && !isdigit(checkedCard.getSymbolOnCard()[0]))
	{
		return true;
	}
	return false;
}
