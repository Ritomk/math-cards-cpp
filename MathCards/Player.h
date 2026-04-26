#pragma once
#include "Card.h"
#include "Table.h"

class Player
{
private:
	std::vector<Card> cards; //vector przechowuj¹cy array klas Card
	std::vector <std::string> symbols; //vector przechowuj¹cy wszystkie dostêpne symbole (string poniewa¿ przechowuje równie¿ "0.5","-2" itp.)
	const sf::Vector2f *cardsPositions; //pozycje w jakich mog¹ znajdowaæ siê karty
	const sf::Vector2f *centerPosition; //pozycja w której znajdzie siê karta po wybraniu przez gracza
	sf::Texture handTexture; //zmienna przechowuj¹ca texturê dla sprite'a
	sf::Sprite handSprite; //zmienna przechowuj¹ca kszta³t dla textury
	sf::Text handText; //zmienna przechowój¹ca text graficznie
	int cardsInHand; //liczba kart posiadan¹ przez gracza w rêce
	int cardPosistionIndex; //pozycja dla pierwszych 5 kart - PickFirstFivePosition()
	int highlightedCardIndex; //index aktualnie podœwietlonej karty
	bool cardPicked; //zmienna sprawdza czy karta zosta³a podniesiona do umieszczenia na stole

	std::string GenerateSymbol(); //wygenerowanie symbolu dla nowej karty uzywa - InstNewCard()
	void InitVariables(); //inicializacja zmiennych
	void InitHand(); //inicjalizacja sprite'a oraz tekstu rêki
	void InitHandTexture(); //inicalizacja textury rêki

	void IncreaseDisplayedIndex(); //umieszenie ostatniego elementu na pierwszej pozycji i usuniêcie go z koñca vectora cards
	void DecreaseDisplayedIndex(); //umieszenie pierwszego elementu na ostatniej pozycji i usuniêcie go z pocz¹tku vectora cards

	sf::Font font;

public:
	Player(sf::Font&);
	~Player();

	const bool HasAnyCards() const;
	const bool GetCardPicked() const;
	const Card& GetCard() const; //pobranie karty
	void DeleteCard(); //usuniêcie karty

	void IncreaseHighlightedIndex(); //zmiana podœwietlenia karty o pozycjê "w górê"
	void DecreaseHighlightedIndex(); //zmiana podœwietlenia karty o pozycjê "w dó³"

	void PickFirstFivePosition(); //dobranie kart "od œrodka"
	void Update(); //zaktualizowanie tekstu o liczbe kart znajduj¹cych siê w rêce
	void InstantizeNewCard(); //inicjalizacja nowego elementu clasy Card
	void ReturnCardsToDeck();

	bool PickCard(); //podniesienie karty do umieszczenia na stole
	void PutCard(); //ponowne umieszczenie karty w rêce

	void DrawCards(sf::RenderTarget&); //rysowanie wszystkich kart z vectora cards
	void DrawHand(sf::RenderWindow&); //rysowanie rêki
};

