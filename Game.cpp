#include "Game.hpp"
#include "Splash.hpp"

#include <fstream>

Game::Game(int width, int height, const std::string &title)
{
    _data->window.create(sf::VideoMode(width,height),title);
    _data->width=width;
    _data->height=height;
    _data->machine.addState(std::unique_ptr<State>(std::make_unique<Splash>(_data)));

    std::fstream testFile;
    testFile.open("PlayerAnimationData.txt", std::ios::in );
    testFile>>  _data->PlayerAnimationData.cols;
    testFile>>  _data->PlayerAnimationData.rows;
    testFile>>  _data->PlayerAnimationData.width;
    testFile>>  _data->PlayerAnimationData.height;
    testFile.close();
}

void Game::run()
{
    float currentTime;
    float deltaTime;
    float lastTime = _clock.getElapsedTime().asSeconds();
    float sum = 0.0f;

    while(_data->window.isOpen()){
        _data->machine.update();

        currentTime = _clock.getElapsedTime().asSeconds();

        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sum += deltaTime;

        while(sum >=DT){
            _data->machine.getState()->handleInput();
            _data->machine.getState()->update(DT);
            sum-=DT;
        }
        _data->machine.getState()->draw(DT);
    }
}

Game::~Game()
{
}
