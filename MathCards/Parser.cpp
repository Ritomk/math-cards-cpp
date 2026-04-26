#include "Parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

int Parser::Priority(char token)
{
	if (strchr("+-", token)) return 1;
	else if (strchr("*/", token)) return 2;
	else if (strchr("^", token)) return 3;
	else return 0;
}

float Parser::Calculate(float a, float b, char symbol)
{
	switch (symbol)
	{
	case'+':
		return a + b;
	case'-':
		return a - b;
	case'*':
		return a * b;
	case'/':
		return a / b;
	case'^':
		return pow(a, b);
	default:
		return 0;
	}
}

void Parser::ReverseStack()
{
	if (expStack.empty()) return;
	std::stack<std::string> s;

	s = this->expStack; //przypisanie stosu expression do s

	while (!this->expStack.empty()) //opró¿nienie stosu expression
	{
		this->expStack.pop();
	}
	while (!s.empty()) //umieszczenie wartoœci stosu s na stos expression
	{
		this->expStack.push(s.top());
		s.pop();
	}
}

void Parser::PutOnStack()
{
	while (!this->exp.empty())
	{
		expStack.push(exp[0]);
		exp.erase(exp.begin());
	}
}

int Parser::Valence(std::string token) {
	if (token.size() > 1)
	{
		return 1;
	}
	else
	{
		if (std::isdigit(token[0]))
			return 1;
		if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
			return -1;
	}
	return 0;
}

float Parser::RpnEval(std::vector<std::string> expression)
{
	if (expression.empty())
	{
		std::cout << "Error: String is empty" << std::endl;
		return 0;
	}

	this->exp = expression;
	this->PutOnStack();
	this->ReverseStack();

	std::stack<float> result;
	while (!this->expStack.empty()) //wykonywanie dopóki stos nie jest pusty
	{
		if (isdigit(this->expStack.top()[0])) //sprawdzenie czy na górze stosu znajduje siê liczba
		{
			result.push(stod(this->expStack.top())); //umieszczenie na górze stosu result
			this->expStack.pop();
		}
		else if (!isdigit(this->expStack.top()[0])) //sprawdzenie czy na górze stosu nie znajduje siê liczba
		{
			float right = result.top();
			result.pop();
			float left = result.top();
			result.pop();

			result.push(this->Calculate(left, right, this->expStack.top()[0])); //policzenie ostatnich 2 elementy stosu w jeden
			this->expStack.pop();
		}
	}
	return result.top();
}

int Parser::IsRPN(const std::vector<std::string> expression) {
	int stack_size = 0;
	for (const auto& c : expression) {
		stack_size += this->Valence(c);
		if (stack_size <= 0)
			return 0;
	}
	if (stack_size < 1)
	{
		return 0;
	}
	return stack_size;
}