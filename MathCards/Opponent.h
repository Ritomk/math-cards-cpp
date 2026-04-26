#pragma once
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <functional>

#include "Parser.h"
#include "Card.h"
#include "Parser.h"


class Opponent
{
private:
	sf::Font font; //zmienna czci¹ki
	std::vector<std::string> cards; //"karty" w rêce przeciwnika
	std::vector<std::string> cardsOnTable; //karty umieszczone na aktualnie uk³adanym przez przeciwnika stole
	std::vector<std::string> symbols; //dostêpna "lista" symboli

	Parser parser; //klasa parser

	int highlightedCardIndex; //odpowiada za wybranie karty do umieszczenia
	int tableLength; //mówi przeciwnikowi jaka ma byæ d³ugoœæ nastêpnego wygenerowanego ci¹gu ruchów

	float highestValue; //nawiêksza wartoœæ wygenerowanego przez niego ci¹gu
	std::vector<std::string> highestExpression; //kolejka umieszczaj¹ca ci¹g z najwiêksz¹ wartoœci¹

	int tableIndexX; //zmienna odpowidaj¹ca za wskazanie sto³u w przestrzeni X
	int tableIndexY; //zmienna odpowiadaj¹ca za wskazanie sto³u w przestrzeni Y

	bool cantPlaceMoreCards; //przeciwnik stwierdza, ¿e nie op³aca siê mu generowaæ kolejnych ci¹gów

	void generateCombinations(std::vector<std::string> elements, std::vector<std::string> combination, int length); //generuje wszystkie kombinacje ci¹gów znaków
	void compare(float value, std::vector<std::string> expression); //porównuje i zwraca ci¹g z nawiêksz¹ wartoœci¹
public:
	Opponent(sf::Font&); //konsturktor
	~Opponent(); //dekonstruktor

	void GenerateCardSymbol(); //generowanie symbolu odpowiadaj¹cego karcie

	const int GetTableIndexX() const; //zwraca zmienna tableIndexX
	const int GetTableIndexY() const; //zwraca zmienna tableIndexY
	void DeleteCard(); //usuwa karte

	const Card InstantizeNewCard(); //tworzy nowy obiekt karty przy umieszczeniu na stole
	void ReturnCardsToDeck();

	void ClearPlacingOrder(const std::string); //czysci kolejke kart i zmusza przeciwnika do wygenerowania nowej po umieszczeniu przez gracza karty na stole przeciwnika
	void GenerateCardPlacingOrder(); //pilnuje aby wygenerowany ciag znakow byl w ONP, przeciwnik generowa³ coraz d³u¿szy ci¹g, przeciwnik nie przegenerowa³ (ci¹g d³u¿szy ni¿ 9)
	bool CanPlaceCard(); //wbiera karte do umieszczenia oraz decyduje czy mozna ja polozyc (dla randomowego bota)

	void EndRound(); //fragment kontroli logiki przeciwnika umieszczony w GameState (sprawdza czy ró¿nica wartoœci na sto³ach nie przekracza 500)

	bool MakeMove(bool, const std::vector<std::string>); //ca³a logika przeciwnika z taktyk¹
};

