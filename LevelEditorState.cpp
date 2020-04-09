#include "LevelEditorState.h"
#include "LevelEditorMenuState.hpp"
#include "MainMenuState.hpp"

#include <fstream>


LevelEditorState::LevelEditorState(std::shared_ptr<gameData> data):
    _data(data)
{
        fieldType = BLOCK;
        this->_data->asset.loadTexture("hero","img/hero.png");

        int currentX{0},currentY{0};
        int blockNumberX{0}, blockNumberY{0};

        while(currentY < this->_data->height){
            currentX=0;
            blockNumberX=0;

            while(currentX < this->_data->width){
                sf::RectangleShape tmpRectangle(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
                tmpRectangle.setFillColor(sf::Color::Black);
                tmpRectangle.setPosition(blockNumberX*(BLOCK_SIZE+1),blockNumberY*(BLOCK_SIZE+1));

                field tmpField;
                tmpField.rec = tmpRectangle;
                tmpField.type = EMPTY;
                tmpField.posX = blockNumberX*(BLOCK_SIZE+1);
                tmpField.posY = blockNumberY*(BLOCK_SIZE+1);


                this->_rectangles.push_back(tmpField);

                ++blockNumberX;
                currentX+=BLOCK_SIZE;
            }

            ++blockNumberY;
            currentY+=BLOCK_SIZE;
        }
}

void LevelEditorState::init()
{
}

void LevelEditorState::handleInput()
{
    sf::Event event;

    while(this->_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            this->_data->window.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        fieldType=BLOCK;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        fieldType=PLAYER;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        fieldType=DESTINATION;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        this->_data->machine.addState(std::unique_ptr<State>(std::make_unique<LevelEditorMenuState>(this->_data,_rectangles)),false);
    }
}

void LevelEditorState::update(float dt)
{
    _mousePosition = sf::Mouse::getPosition(this->_data->window);

    for(int i=0; i < this->_rectangles.size(); ++i){
        sf::IntRect tmpRec(this->_rectangles[i].rec.getPosition().x,this->_rectangles[i].rec.getPosition().y,
        this->_rectangles[i].rec.getGlobalBounds().width,this->_rectangles[i].rec.getGlobalBounds().height);

        if(tmpRec.contains(_mousePosition)){
            _rectangles[i].rec.setFillColor(sf::Color(60,60,60));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                switch (fieldType){
                    case BLOCK:
                        _rectangles[i].type=BLOCK;
                        break;

                    case PLAYER:
                        _rectangles[i].type=PLAYER;
                        for(int j=0; j < this->_rectangles.size(); ++j){
                            if(i==j)
                                continue;
                            if(_rectangles[j].type==PLAYER)
                                _rectangles[j].type=EMPTY;
                        }
                        break;

                    case DESTINATION:
                        _rectangles[i].type=DESTINATION;
                        for(int j=0; j < this->_rectangles.size(); ++j){
                            if(i==j)
                                continue;
                            if(_rectangles[j].type==DESTINATION)
                                _rectangles[j].type=EMPTY;
                        }
                        break;
                }
            }
        }
        else
            _rectangles[i].rec.setFillColor(sf::Color(20,20,20));

        if(_rectangles[i].type==BLOCK)
            _rectangles[i].rec.setFillColor(sf::Color(100,100,100));

        if(_rectangles[i].type==PLAYER)
            _rectangles[i].rec.setFillColor(sf::Color(0,255,255));

        if(_rectangles[i].type==DESTINATION)
            _rectangles[i].rec.setFillColor(sf::Color(0,255,0));
    }
}

void LevelEditorState::draw(float dt)
{
    this->_data->window.clear(sf::Color(100,100,100));

    for(int i=0; i<this->_rectangles.size(); ++i){
        this->_data->window.draw(this->_rectangles[i].rec);
    }

    this->_data->window.display();
}
