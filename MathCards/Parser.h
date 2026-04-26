#pragma once
#include <stack>
#include <string>
#include <math.h>
#include <cctype>
#include <iostream>
#include <vector>

class Parser
{
private:
	std::stack<std::string> expStack;
	std::vector<std::string> exp;
	std::string oldExp;

	int Priority(char);
	float Calculate(float, float, char);
	void ReverseStack();
	void PutOnStack();

	int Valence(std::string);
public:
	Parser();
	~Parser();

	float RpnEval(std::vector<std::string>);
	int IsRPN(const std::vector<std::string>);
};

