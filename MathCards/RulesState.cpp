#include "RulesState.h"

RulesState::RulesState(sf::RenderWindow& window, sf::Font& font, std::shared_ptr<StateMachine> stateMachine)
{
	this->window = &window;
	this->font = font;
	this->stateMachine = stateMachine;

	this->InitButton();
}

RulesState::~RulesState()
{

}

void RulesState::InitButton()
{
	this->returnButtonShape.setSize(sf::Vector2f(350, 100));
	sf::FloatRect spriteRect = this->returnButtonShape.getLocalBounds();
	this->returnButtonShape.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height);
	this->returnButtonShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f + 400.f));
	this->returnButtonShape.setFillColor(sf::Color::Cyan);

	this->returnButtonText.setFont(font);
	this->returnButtonText.setCharacterSize(40);
	this->returnButtonText.setFillColor(sf::Color::Yellow);
	this->returnButtonText.setStyle(sf::Text::Bold);
	this->returnButtonText.setString(readFileAsString("Rules/rules.txt"));//"MathCards Game Rules\n1.Player creates equasion in Reverse Polish Notation");
	sf::FloatRect textRect = this->returnButtonText.getLocalBounds();
	this->returnButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->returnButtonText.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2 - 100.f));

	this->rulesExplainedText.setFont(font);
	this->rulesExplainedText.setCharacterSize(100);
	this->rulesExplainedText.setFillColor(sf::Color::Yellow);
	this->rulesExplainedText.setStyle(sf::Text::Bold);
	this->rulesExplainedText.setString("RETURN");
	sf::FloatRect textRect1 = this->rulesExplainedText.getLocalBounds();
	this->rulesExplainedText.setOrigin(textRect1.left + textRect1.width / 2.0f,
		textRect1.top + textRect1.height / 2.0f);
	this->rulesExplainedText.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2 + 350.f));
}

std::string RulesState::readFileAsString(const std::string& filePath) //funkcja odczytuj¹ca zawartoœæ pliku / napisana przez chatGPT
{
	std::ifstream file(filePath);
	std::string content((std::istreambuf_iterator<char>(file)), //iterator oznaczaj¹cy pocz¹tek pliku
		(std::istreambuf_iterator<char>())); //iterator przypisany na koniec pliku
	return content;
}

void RulesState::Update()
{

}

void RulesState::HandleInput()
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

			if (this->ev.key.code == sf::Keyboard::Space)
			{
				this->stateMachine->PopState();
			}
			break;
		}
	}
}

void RulesState::Draw()
{
	this->window->clear();

	this->window->draw(returnButtonShape);
	this->window->draw(returnButtonText);
	this->window->draw(rulesExplainedText);

	this->window->display();
}
