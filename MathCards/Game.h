#pragma once
#include <iostream>

#include "StateMachine.h"
#include "GameState.h"
#include "MenuState.h"

class Game
{
private:
	sf::Font font;
	sf::VideoMode videoMode;
	sf::RenderWindow *window;
	std::shared_ptr<StateMachine> stateMachine;
	//StateMachine stateMachine;

	void InitVariables();
public:
	Game();
	~Game();

	void Run();
	const sf::Font GetFont() const;
};

