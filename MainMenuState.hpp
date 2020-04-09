#pragma once
#include "Game.hpp"
#include "Button.hpp"

class MainMenuState : public State
{
    public:
        MainMenuState(std::shared_ptr<gameData> data);

        void init();

        void handleInput();
        void update(float dt);
        void draw(float dt);
    private:
        std::shared_ptr<gameData> _data;

        Button _playButton;
        Button _editButton;
        Button _exitButton;
        sf::Sprite _background;

        sf::Clock _clock;
};
