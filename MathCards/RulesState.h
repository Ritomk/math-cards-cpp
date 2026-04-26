#pragma once
#include "State.h"
#include "StateMachine.h"
#include <fstream>
#include <string>

class RulesState :
    public State
{
private:
    sf::RenderWindow* window;
    sf::Font font;
    std::shared_ptr<StateMachine> stateMachine;
    sf::Event ev;

    sf::Text returnButtonText;
    sf::Text rulesExplainedText;
    sf::RectangleShape returnButtonShape;

    void InitButton();
    std::string readFileAsString(const std::string&);

public:
    RulesState(sf::RenderWindow&, sf::Font&, std::shared_ptr<StateMachine>);
    ~RulesState();

    void Update() override;
    void HandleInput() override;
    void Draw() override;
};

