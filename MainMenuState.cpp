#include "MainMenuState.hpp"
#include "LevelState.hpp"
#include "LevelEditorState.h"

MainMenuState::MainMenuState(std::shared_ptr<gameData> data):
    _data(data)
{
    _data->asset.loadTexture("playMenu","img/play.png");
    _data->asset.loadTexture("editorMenu","img/editor.png");
    _data->asset.loadTexture("exitMenu","img/chest.png");
    _data->asset.loadTexture("background","img/background.png");

    _background.setTexture(_data->asset.getTexture("background"));
    _background.setPosition(0,0);

    _playButton.init(_data->width/2,(_data->height/2)-_data->height/3,_data->asset.getTexture("playMenu"));
    _editButton.init(_data->width/2,(_data->height/2),_data->asset.getTexture("editorMenu"));
    _exitButton.init(_data->width/2,(_data->height/2)+_data->height/3,_data->asset.getTexture("exitMenu"));
}

void MainMenuState::init()
{
}

void MainMenuState::handleInput()
{
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            _data->window.close();
        }
    }
}

void MainMenuState::update(float dt)
{
    if(_playButton.hover(_data->window))
        _playButton.setTexture(_data->asset.getTexture("playMenu"));
    else
        _playButton.setTexture(_data->asset.getTexture("playMenu"));

    if(_editButton.hover(_data->window))
        _editButton.setTexture(_data->asset.getTexture("editorMenu"));
    else
        _editButton.setTexture(_data->asset.getTexture("editorMenu"));

    if(_exitButton.hover(_data->window))
        _exitButton.setTexture(_data->asset.getTexture("exitMenu"));
    else
        _exitButton.setTexture(_data->asset.getTexture("exitMenu"));

    if(_exitButton.pressed(_data->window,sf::Mouse::Left))
            _data->window.close();
    if(_playButton.pressed(_data->window,sf::Mouse::Left))
            _data->machine.addState(std::unique_ptr<State>(std::make_unique<LevelState>(_data)));
    if(_editButton.pressed(_data->window,sf::Mouse::Left))
            _data->machine.addState(std::unique_ptr<State>(std::make_unique<LevelEditorState>(_data)));
}

void MainMenuState::draw(float dt)
{
    _data->window.clear();
    _data->window.draw(_background);

    _playButton.draw(_data->window);
    _editButton.draw(_data->window);
    _exitButton.draw(_data->window);

    _data->window.display();
}
