#include "Game.h"

Game::Game()
{
	this->stateMachine = std::make_shared<StateMachine>();
	this->InitVariables();
}

Game::~Game()
{

}

void Game::InitVariables()
{
	this->videoMode = sf::VideoMode(1800, 900);
	this->window = new sf::RenderWindow(this->videoMode, "MathCards", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	if (!this->font.loadFromFile("Font/ArialTh.ttf"))
	{
		std::cout << "Error: Could not load font file ArialTh.ttf" << std::endl;
		return;
	}

	stateMachine->PushState(new MenuState(*window, font, stateMachine));
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		this->stateMachine->GetCurrent()->Update();
		this->stateMachine->GetCurrent()->HandleInput();
		this->stateMachine->GetCurrent()->Draw();
		this->stateMachine->ProcessStateChange();
	}
}

const sf::Font Game::GetFont() const
{
	return font;
}
