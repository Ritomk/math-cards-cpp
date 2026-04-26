#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void HandleInput() = 0;
};
