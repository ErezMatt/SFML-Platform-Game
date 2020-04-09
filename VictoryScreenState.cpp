#include "VictoryScreenState.hpp"

#include "LevelEditorMenuState.hpp"
#include "MainMenuState.hpp"

#include <fstream>


VictoryScreenState::VictoryScreenState(std::shared_ptr<gameData> data):
    _data(data)
{
    this->_data->asset.loadTexture("victory","img/victory.png");
    _victoryInfo.setTexture(this->_data->asset.getTexture("victory"));
    _victoryInfo.setOrigin(_victoryInfo.getGlobalBounds().width/2,_victoryInfo.getGlobalBounds().height/2);
    _victoryInfo.setPosition(this->_data->width/2,this->_data->height/2);

    this->_data->asset.loadTexture("background","img/background.png");
    this->_background.setTexture(this->_data->asset.getTexture("background"));
    this->_background.setPosition(0,0);
}

void VictoryScreenState::init()
{
}

void VictoryScreenState::handleInput()
{
    sf::Event event;
    while(this->_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            this->_data->window.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        this->_data->machine.addState(std::unique_ptr<State>(std::make_unique<MainMenuState>(this->_data)));
    }
}

void VictoryScreenState::update(float dt)
{
}

void VictoryScreenState::draw(float dt)
{
    this->_data->window.clear(sf::Color(100,100,100));
    this->_data->window.draw(_background);
    this->_data->window.draw(_victoryInfo);
    this->_data->window.display();
}
