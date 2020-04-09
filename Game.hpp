#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include "StateMachine.hpp"

#include <SFML/Graphics.hpp>

struct gameData
{
    StateMachine machine;
    AssetManager asset;
    sf::RenderWindow window;
    int width;
    int height;
    struct
    {
        int cols; //Columns in graphics file
        int rows;  //Rows in graphics file
        int width;
        int height;
    }PlayerAnimationData;
};

class Game
{
    public:
        Game(int width, int height, const std::string &title="Game");
        virtual ~Game();

        void run();

    private:
        const float DT = 1.0f/60.0f;
        sf::Clock _clock;

        std::shared_ptr<gameData> _data = std::make_shared<gameData>();
};


