#pragma once
#include "Game.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include <vector>


class LevelState : public State
{
    public:
        LevelState(std::shared_ptr<gameData> data);

        void init();

        void handleInput();
        void update(float dt);
        void draw(float dt);
        void changeLevel(int nLevel);

        bool levelComplete();

    private:
        std::shared_ptr<gameData> _data;
        Player _player;
        std::vector<Block>  _blocks;
        Block _destination;
        sf::Vector2i _mousePosition;
        sf::Sprite _background;
        sf::Clock _clock;
        int _currentLevel{1};
};

