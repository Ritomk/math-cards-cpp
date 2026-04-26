#include "StateMachine.h"

StateMachine::StateMachine()
{
	this-> popState = false;
}

StateMachine::~StateMachine()
{
	while(!states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void StateMachine::PushState(State* state)
{
	this->states.push(state);
}

void StateMachine::PopState()
{
	this-> popState = true;
}

void StateMachine::ChangeState(State* state)
{
	if (!this->states.empty())
	{
		PopState();
	}
	PushState(state);
}

State* StateMachine::GetCurrent()
{
	if (this->states.empty())
	{
		return nullptr;
	}
	return this->states.top();
}

void StateMachine::ProcessStateChange()
{
	if (popState)
	{
		if (!states.empty())
		{
			delete this->states.top();
			this->states.pop();
			this->popState = false;
		}
	}
}