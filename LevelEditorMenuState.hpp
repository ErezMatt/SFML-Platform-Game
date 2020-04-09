#pragma once
#include "Game.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "LevelEditorState.h"

class LevelEditorMenuState : public State
{
public:
    LevelEditorMenuState(std::shared_ptr<gameData> data);
    LevelEditorMenuState(std::shared_ptr<gameData> data, std::vector<field>& vec);

    void init();

    void handleInput();
    void update(float dt);
    void draw(float dt);
private:
    std::shared_ptr<gameData> _data;
    sf::Vector2i _mousePosition;
    std::vector<field> _rectangles;
    sf::Clock _clock;
    Button _continue;
    Button _saveAndExitButton;
    Button _exitButton;
};

