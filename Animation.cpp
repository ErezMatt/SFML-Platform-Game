#include "Animation.hpp"

Animation::Animation()
{
}

void Animation::init(int cols, int rows, int width, int height, const sf::Texture& texture,sf::Sprite& sprite)
{
    _framesX=cols;
    _framesY=rows;
    _width=width;
    _height=height;
    this->texture=texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(_width*_currentX,_height*_currentY,_width,_height));
}

void Animation::applyToSprite(sf::Sprite& sprite)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(_width*_currentX,_height*_currentY,_width,_height));
}

void Animation::update(float dt,Direction dir)
{
    time+=dt;
    if(time>=HOLD_TIME){
        time=0;
        ++_currentX;
        if(_currentX>(_framesX-1)){
            _currentX=0;
        }
        if(dir==LEFT){
            _currentY=1;
        }else if(dir==RIGHT){
            _currentY=2;
        }else{
            _currentY=3;
            _currentX=0;
        }
    }
}

void Animation::setScale(sf::Vector2f scale,sf::Sprite& sprite)
{
    sprite.setScale(scale);
}

Animation::~Animation()
{
}
