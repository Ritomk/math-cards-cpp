#pragma once
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Card
{
private:
	sf::RectangleShape cardShape; // podstawowy krzta³t karty
	sf::Vector2f cardSize; // wielkoœæ karty
	std::string symbol; // symbol znajduj¹cy siê na karcie (wykorzystywany przez parser)
	sf::Text text; // wizualne przedstawienie symbolu karty

public:
	Card(); //konstruktor domyœlny ze wzglêdu ¿e nie jest mo¿liwa inicjalizacja domyœlnej wartoœci sf::Font
	Card(std::string, sf::Font&); //konsturktor, który jest u¿ywany
	~Card(); //dekonstruktor
	void InitShape(); //inicjalizacja kszta³tu
	void InitText(std::string, sf::Font&); //inicjalizacja tekstu
	void setCardColor(sf::Color); //ustawienie koloru tekstu
	void setCardPosition(sf::Vector2f); //ustawia pozycjê karty oraz tekstu
	void setCardScale(float);
	void setSymbolOnCard(std::string); //ustawia symbol karty
	const std::string getSymbolOnCard() const; //pobiera symbol karty (dla parsera)
	sf::Text getCardText(); //pobiera zmienna text graficznie przedstawiaj¹c¹ symbol karty
	sf::RectangleShape getCardShape(); //pobiera zmienna cardShape graficznie przedstawiaj¹c¹ kszta³t prostok¹ta
	void DrawCard(sf::RenderTarget&); //metoda uzywana do wyswietalania karty
};

