#pragma once

#include "Game.hpp"

class Splash : public State
{
public:
    Splash(std::shared_ptr<gameData> data);

    void init();

    void handleInput();
    void update(float dt);
    void draw(float dt);
private:
    std::shared_ptr<gameData> _data;

    sf::Clock _clock;
};
