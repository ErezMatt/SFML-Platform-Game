#pragma once
#include "Game.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "LevelEditorState.h"


class VictoryScreenState : public State
{
public:
    VictoryScreenState (std::shared_ptr<gameData> data);

    void init();

    void handleInput();
    void update(float dt);
    void draw(float dt);
private:
    std::shared_ptr<gameData> _data;
    sf::Vector2i _mousePosition;

    sf::Sprite _victoryInfo;
    sf::Sprite _background;

    sf::Clock _clock;
};
