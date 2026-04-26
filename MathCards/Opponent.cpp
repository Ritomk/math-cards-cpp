#include "Opponent.h"

Opponent::Opponent(sf::Font& font) : font(font)
{
	this->tableIndexX = 0;
	this->tableIndexY = 0;

	this->cantPlaceMoreCards = false;
	this->tableLength = 3;
	this->highlightedCardIndex = 0;
	this->highestValue = -21370;
	this->symbols = {
	"1","1","2","2","3","3",
	"4","4","5","5","6","6",
	"7","7","8","8","9","9",
	"+","+","+","-","-","-",
	"*","*","*","/","/","/" };

	for (int i = 0; i < 15; i++)
	{
		GenerateCardSymbol();
		std::cout << cards.back();
	}
	std::cout << std::endl;
}

Opponent::~Opponent()
{

}

void Opponent::GenerateCardSymbol()
{
	if (symbols.size() < 1)
	{
		return;
	}

	int random = 0;
	srand(time(NULL));

	random = rand() % this->symbols.size();

	std::string returnSymbol = this->symbols[random];

	this->symbols.erase(this->symbols.begin() + random);
	this->cards.emplace_back(std::string(returnSymbol));
}

void Opponent::generateCombinations(std::vector<std::string> elements, std::vector<std::string> combination, int length) {
	if (combination.size() == length) //sprawdza czy podana kombinacja ma porz¹dan¹ d³ugoœæ 
	{
		if (this->parser.IsRPN(combination) == 1) //jeœli kombinacja jest równa 1, czyli jest w rpn to sprawdzane jest czy jest wieksza od tej z najwieksza wartosci¹
		{
			compare(parser.RpnEval(combination), combination);
		}
		return;
	}

	for (int i = 0; i < elements.size(); i++) 
	{
		std::vector<std::string> newElements = elements;
		std::vector<std::string> newCombination = combination; //nowa zmienna otrzymuje wartoœci poprzednich kombinacji

		newCombination.push_back(newElements[i]); //do nowych kombinacji jest umieszczany element z pozycji i
		newElements.erase(newElements.begin() + i); //nowy element na tej pozycji zostaje usuniety

		generateCombinations(newElements, newCombination, length); //przekazanie nowych zmiennych do rekurencji
	}
}

void Opponent::compare(float value, std::vector<std::string> expression)
{
	if (value > this->highestValue && value < 21370)
	{
		this->highestValue = value;
		this->highestExpression = expression;
	}
}

const int Opponent::GetTableIndexX() const
{
	return this->tableIndexX;
}

const int Opponent::GetTableIndexY() const
{
	return this->tableIndexY;
}

void Opponent::DeleteCard()
{
	this->cards.erase(this->cards.begin() + this->highlightedCardIndex);
}

const Card Opponent::InstantizeNewCard()
{
	return Card(this->cards[this->highlightedCardIndex], this->font);
}

void Opponent::ReturnCardsToDeck()
{
	while (this->cards.size() > 0)
	{
		this->symbols.push_back(this->cards[0]);
		this->cards.erase(this->cards.begin());
	}
	this->cardsOnTable.clear();
	this->highestExpression.clear();
	this->highestValue = -21370;
	this->tableLength = 3;
	this->cantPlaceMoreCards = false;
}

void Opponent::ClearPlacingOrder(const std::string playersPlacedSybol)
{
	if (this->tableLength > this->cardsOnTable.size() + 3) //opdpowiada za wzgledy optymalizacyjne
	{
		this->tableLength -= 2; //dla optymalizacji
		this->highestValue = -2137; //aby opponent mial szanse wygenerowac nowy ciag znakow jesli ten jest duzo gorszy od poprzedniego
	}

	for (int i = 0; i < highestExpression.size(); i++) //pêtla wykonuje siê a¿ i nie osi¹gnie wartoœci wielkoœci highestExpression
	{
		cardsOnTable.pop_back(); //nadwy¿szka wygenerowanych elementów jest usuwana
	}
	cardsOnTable.push_back(playersPlacedSybol); //wstawiony przez gracza element trafia do vectora elementów na stole
	highestExpression.clear(); //kolejka umieszczania elementów jest usuwana
}

void Opponent::GenerateCardPlacingOrder()
{
	std::cout << ":::::Generowanie:::::" << std::endl;
	std::cout << "Taka jest docelowa dlugosc kart na stole: " << tableLength << std::endl;
	std::cout << "Takie karty mam umieszczone w kolejce: ";
	for (auto& s : highestExpression)
	{
		std::cout << s;
	}
	std::cout << std::endl;
	std::cout << "Takie karty leza na moim stole: ";
	for (auto& s : cardsOnTable)
	{
		std::cout << s;
	}
	std::cout << std::endl;
	int cardsOnTableSizeBegin = this->cardsOnTable.size(); //zmienna sprawdzaj¹ca czy pod koniec wykoniania funkcji zwiêkszy³a siê liczba kart na stole

	if (cards.size() > 0)
	{
		generateCombinations(this->cards, this->cardsOnTable, this->tableLength); //wygenerowanie ci¹gu znaków o podanej d³ugoœci i uwzglêdniaj¹c pocz¹tkowe elementy cardsOnTable
	}
	else //jeœli nie ma dostêpnych kart przeciwnik koñczy rundê
	{
		this->cantPlaceMoreCards = true;
		std::cout << "Koncze runde 0 cards" << std::endl;
		return;
	}

	for (auto& s : this->highestExpression)
	{
		std::cout << s;
	}
	std::cout << std::endl;

	if (parser.IsRPN(highestExpression) != 1) //s³u¿y g³ównie do zakoñczenia rundy, gdy przeciwnik nie znajdzie lepszego wyniku (s³u¿y równie¿ jako kontrola b³êdów, jeœli przeciwnik wygeneruje wadliw¹ kolejkê, wtedy jest ona porzucona)
	{
		this->cantPlaceMoreCards = true; //zmienna zakoñczenia rundy
		std::cout << "Koncze runde highestExpression" << std::endl;
		highestExpression.clear(); //wyczyszczenie kolejki
		std::cout << highestExpression.size() << std::endl;
		return;
	}

	if (this->cardsOnTable.size() > 0) //ten fragment pilnuje aby po wygenerowaniu nowej kolejki (która zawiera w sobie karty ju¿ umieszczone) karty umieszczone na stole zosta³y z niej usuniête
	{
		for (int i = 0; i < this->cardsOnTable.size(); i++)
		{
			if (this->highestExpression.size() == 0) //sprawdza czy wielkoœæ highestExpression jest równa 0 jeœli tak przerywa pêtle
			{
				break;
			}
			if (this->cardsOnTable[i] == this->highestExpression[0]) //jeœli karta znajduje siê na stole wtedy jest usuwana z kolejki
			{
				this->highestExpression.erase(this->highestExpression.begin());
			}
		}
	}
	this->cardsOnTable.insert(this->cardsOnTable.end(), this->highestExpression.begin(), this->highestExpression.end()); //do kart na stole zostaje umieszczona aktualna kolejka

	if (this->tableLength < 9) //sprawdza czy przeciwnik osi¹gna³ maksymaln¹ liczbê kart na stole, jeœli tak koñczy rundê
	{
		this->tableLength += 4; //zwiêkszenie rozmiaru kolejnej generacji znaków

		if (this->tableLength > 9) //jeœli przeciwnik osi¹gn¹³ maksymalny rozmiar, wtedy nadmiar zostaje usuniêty
		{
			this->tableLength = this->tableLength - this->tableLength % 9;
		}

		if (cardsOnTable.size() == cardsOnTableSizeBegin) //jeœli rozmiar kart na stole siê nie zwiêkszy³ funkcja zostaje uruchomiona ponownie
		{
			this->GenerateCardPlacingOrder();
		}
	}
	else
	{
		this->cantPlaceMoreCards = true; //zakoñczenie rundy
		std::cout << cards.size() << std::endl;
		std::cout << "Koncze runde koniec" << std::endl;
	}
}

bool Opponent::CanPlaceCard()
{
	while (this->highestExpression.size() > 0)
	{
		if (this->cards.size() > 0)
		{
			for (int i = 0; i < this->cards.size(); i++)
			{
				if (this->cards[i] == this->highestExpression[0])
				{
					this->highestExpression.erase(this->highestExpression.begin());
					this->highlightedCardIndex = i;
					return true;
				}
			}
		}
	}
	return false;
}

void Opponent::EndRound()
{
	cantPlaceMoreCards = true;
}

bool Opponent::MakeMove(bool playerHasAnyCards, const std::vector<std::string> symbolsOnPlayerAttackTable)
{
	if (this->cantPlaceMoreCards && this->highestExpression.size() > 0)
	{
		std::cout << "Jeszcze klade ostatnie karty" << std::endl;
		this->CanPlaceCard();
		return true;

	}
	else if (this->cantPlaceMoreCards)
	{
		std::cout << "Skonczylem runde" << std::endl;
		return false;
	}

	if (playerHasAnyCards) //jeœli gracz ma jescze karty przeciwnik tylko siê broni
	{
		this->tableIndexX = 1;
		this->tableIndexY = 0;

		if (symbolsOnPlayerAttackTable.size() == 5 || symbolsOnPlayerAttackTable.size() == 6) //jeœli na stole gracza znajduje siê 5 lub 6 symboli przeciwnik mu dokuczy
		{
			std::cout << "Wielkosc symboli na stola atakGracza" <<symbolsOnPlayerAttackTable.size() << std::endl;
			int countA = std::count(cards.begin(), cards.end(), "/") 
				- std::count(highestExpression.begin(), highestExpression.end(), "/"); //sprawdza czy przeciwnik ma nadmiar znaków / poza wygenerowanym ci¹giem
			int countB = std::count(cards.begin(), cards.end(), "-")
				- std::count(highestExpression.begin(), highestExpression.end(), "-"); //tak samo dla -

			if (countB > 0) //jeœli przeciwnik ma nadmiar symboli - próbuje go po³o¿yæ u gracza na stole
			{
				std::cout << "Moge polozyc karte na gracza stole -" << std::endl;
				std::vector<std::string> temp = symbolsOnPlayerAttackTable;
				temp.push_back("-"); //stworzenie tymczasowej zmiennej aby ustaliæ czy po po³o¿eniu karty nadal bêdzie to ONP

				if (parser.IsRPN(temp))
				{
					this->tableIndexX = 0;
					this->tableIndexY = 1; //ustawienie kart na atakuj¹cy stó³ gracza

					this->highestExpression.insert(this->highestExpression.begin(), "-"); //umieszczenie "karty" w kolejce
					this->CanPlaceCard(); //wybranie indeksu karty do umieszczenia

					return true; //zezwolenie na umieszczenie karty
				}
			}
			else if (countA > 0) //to samo tylko dla / (przeciwnik uznaje, ¿e karta "-" jest du¿o bardziej destrukcyjna od "/")
			{
				std::cout << "Moge polozyc karte na gracza stole /" << std::endl;
				std::vector<std::string> temp = symbolsOnPlayerAttackTable;
				temp.push_back("/");

				if (parser.IsRPN(temp))
				{
					this->tableIndexX = 0;
					this->tableIndexY = 1;

					this->highestExpression.insert(this->highestExpression.begin(), "/");
					this->CanPlaceCard();
					return true;
				}
			}
		}
	}
	else //ustawianie kart na stó³ atakuj¹cy
	{
		this->tableIndexX = 0;
		this->tableIndexY = 0;
	}

	if (this->highestExpression.size() == 0) //jeœli przeciwnik nie ma wygenerowanego ci¹gu ruchów, generuje je
	{
		std::cout << "Nie mam wygenerowanych ruchow :: Generuje" << std::endl;
		//std::thread generateThread(GenerateCardPlacingOrder);
		this->GenerateCardPlacingOrder();
	}

	if(highestExpression.size() > 0) //jeœli przeciwnik ju¿ ma ci¹g k³adzie kartê na stole
	{
		std::cout << "Wiem jaki ruch wykonac klade karte" << std::endl;
		this->CanPlaceCard();
		return true; //zezwolenie na umieszczenie karty
	}
	return false; //tak dla pewnoœci, choæ nigdy siê nie wykona przez resztê kontroli i zabezpieczeñ programu
}
