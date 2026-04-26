#pragma once

#include <stack>

#include "State.h"


//przy tworzeniu mocno opiera³em siê na implementacji tego algorytmu z tych stron:
//https://www.binpress.com/creating-city-building-game-with-sfml-state-manager/
//https://github.com/ufrshubham/2D-Snake-Game

class StateMachine
{
private:
	std::stack<State*> states;
	bool popState;

public:
	StateMachine();
	~StateMachine();

	void PushState(State* state);
	void PopState();
	void ChangeState(State* state);
	void ProcessStateChange();
	State* GetCurrent();
};

