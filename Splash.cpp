#include "Splash.hpp"
#include <iostream>
#include "MainMenuState.hpp"

Splash::Splash(std::shared_ptr<gameData> data):
    _data(data)
{
}

void Splash::init()
{
}

void Splash::handleInput()
{
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            _data->window.close();
        }
    }
}

void Splash::update(float dt)
{
    if(_clock.getElapsedTime().asSeconds()>3)
        _data->machine.addState(std::unique_ptr<State>(std::make_unique<MainMenuState>(_data)));
}

void Splash::draw(float dt)
{
    _data->window.clear();

    _data->window.display();
}
