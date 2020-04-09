#include "LevelState.hpp"
#include "LevelEditorState.h"
#include "Splash.hpp"
#include "MainMenuState.hpp"
#include "VictoryScreenState.hpp"

#include <fstream>
#include <string>
#include <sstream>


LevelState::LevelState(std::shared_ptr<gameData> data):
    _data(data)
{
    int field{0};
    int posX{0};
    int posY{0};
    _data->asset.loadTexture("hero","img/hero.png");
    _data->asset.loadTexture("heroA","img/champ.png");
    _data->asset.loadTexture("block","img/block.png");
    _data->asset.loadTexture("background","img/background.png");
    _data->asset.loadTexture("destination","img/destination.png");
    _background.setTexture(_data->asset.getTexture("background"));
    _background.setPosition(0,0);
    std::fstream testFile;

    std::ostringstream level;
    level << _currentLevel;

    testFile.open( "level/level"+ level.str() +".txt", std::ios::in );
    while( testFile>>field){
        Block block;
        switch(field){
            case PLAYER:
                testFile>>posX;
                testFile>>posY;
                _player.init(posX,posY,_data->asset.getTexture("heroA"),_data->PlayerAnimationData.cols, _data->PlayerAnimationData.rows, _data->PlayerAnimationData.width, _data->PlayerAnimationData.height);
                _player.setScale(sf::Vector2f(0.4f,0.4f));
                _player.setWorldWidth(_data->width);
                _player.setWorldHeight(_data->height);
                break;
            case BLOCK:
                testFile>>posX;
                testFile>>posY;
                block.init(posX,posY,_data->asset.getTexture("block"));
                _blocks.push_back(block);
                break;
            case DESTINATION:
                testFile>>posX;
                testFile>>posY;
                _destination.init(posX,posY,_data->asset.getTexture("destination"));
                break;
        }
    }
    testFile.close();
}

void LevelState::init()
{

}

void LevelState::handleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            this->_data->window.close();
        }
        if (event.type == sf::Event::KeyPressed){

            if (event.key.code == sf::Keyboard::Return){
                changeLevel(_currentLevel+1);
            }
        }
    }
    _player.handleInput();
}

void LevelState::update(float dt)
{
    for(int i=0; i<_blocks.size(); ++i)
        _player.colisionBlock(_blocks[i]);

    if(levelComplete())
        changeLevel(_currentLevel+1);

    if(_player.dead())
        changeLevel(_currentLevel);

    _mousePosition = sf::Mouse::getPosition(this->_data->window);
    _player.update(dt);

}

void LevelState::draw(float dt)
{
    this->_data->window.clear(sf::Color::Yellow);

    this->_data->window.draw(_background);
    _player.draw( this->_data->window);
    _destination.draw(this->_data->window);

    for(int i=0; i<_blocks.size(); ++i)
        _blocks[i].draw(this->_data->window);
    this->_data->window.display();
}

void LevelState::changeLevel(int nLevel)
{

    std::fstream testFile;
    testFile.open("level/levels.txt", std::ios::in );
    int maxLevel;
    testFile >> maxLevel;
    if(nLevel>maxLevel){
        this->_data->machine.addState(std::unique_ptr<State>(std::make_unique<VictoryScreenState>(this->_data)));
        return;
    }

    _blocks.clear();

    _currentLevel=nLevel;

    std::ostringstream level;
    testFile.close();
    int field{0};
    int posX{0};
    int posY{0};
    level << nLevel;

    testFile.open( "level/level"+ level.str() +".txt", std::ios::in );
    while( testFile>>field){
        Block block;
        switch(field){
            case PLAYER:
                testFile>>posX;
                testFile>>posY;
                _player.init(posX,posY,this->_data->asset.getTexture("heroA"),_data->PlayerAnimationData.cols, _data->PlayerAnimationData.rows, _data->PlayerAnimationData.width, _data->PlayerAnimationData.height);
                _player.setWorldWidth(_data->width);
                _player.setWorldHeight(_data->height);
                break;
            case BLOCK:
                testFile>>posX;
                testFile>>posY;
                block.init(posX,posY,this->_data->asset.getTexture("block"));
                _blocks.push_back(block);
                break;
            case DESTINATION:
                testFile>>posX;
                testFile>>posY;
                _destination.init(posX,posY,this->_data->asset.getTexture("destination"));
                break;
        }
    }

    testFile.close();
}

bool LevelState::levelComplete()
{
    if(_player.getGlobalBounds().intersects(_destination.getGlobalBounds()))
        return true;
    return false;
}
