#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Animation.hpp"

class Player
{
public:
    Player();
    void init(int posX, int posY, sf::Texture &texture,int cols, int rows, int width, int height);
    virtual ~Player();

    void setTexture(sf::Texture &texture);
    void setTextureRect(sf::IntRect rect);
    void setScale(sf::Vector2f scale);
    void setWorldWidth(int width);
    void setWorldHeight(int height);
    void draw(sf::RenderWindow &window);

    void handleInput();
    void update(float dt);
    bool colisionBlock(Block &block);
    sf::FloatRect getGlobalBounds();

    bool dead();

private:
    sf::Sprite _player;
    Animation _animation;
    int _width;
    int _height;
    int _worldWidth{0};
    int _worldHeight{0};

    const float HERO_SPEED{3.0f};
    const float JUMP_SPEED{15.0f};
    sf::Vector2f _speed{0,0};
    bool _floor{false};
    bool _lBlocked{false};
    bool _rBlocked{false};
    float _gravity{0.5f};

    float angle;
    float diffX=0;
    float diffY=0;
    const float RAD_TO_DEG=57.3248407643;
    enum {NONE,LEFT,RIGHT,JUMP}directionX,directionY;
    Animation::Direction _moveDirection{Animation::Direction::STAY};
};
