#pragma once
#include "State.h"
#include "StateMachine.h"
#include "GameState.h"
#include "RulesState.h"


class MenuState :
    public State
{
private:
    sf::RenderWindow* window;
    sf::Font font;
    std::shared_ptr<StateMachine> stateMachine;
    sf::Event ev;

    sf::Text gameTitle;
    sf::Text playButtonText;
    sf::RectangleShape playButtonShape;
    sf::Text exitButtonText;
    sf::RectangleShape exitButtonShape;
    sf::Text rulesButtonText;
    sf::RectangleShape rulesButtonShape;

    bool playButtonHighlighted;
    bool rulesButtonHighlighted;
    bool exitButtonHighlighted;

    int highlightedButtonIndex;

    void InitVariables();
    void InitShape();
    void InitText();
public:
    MenuState(sf::RenderWindow&, sf::Font&, std::shared_ptr<StateMachine>);
    ~MenuState();

    void ButtonPressed();

    void Update() override;
    void HandleInput() override;
    void Draw() override;
};

