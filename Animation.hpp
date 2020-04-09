#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include "Block.hpp"

#include <SFML/Graphics.hpp>

class Animation
{
public:
    enum Direction{LEFT,RIGHT,STAY};
    Animation();
    virtual ~Animation();
    void init(int cols, int rows, int width, int height, const sf::Texture& texture,sf::Sprite& sprite);
    void applyToSprite(sf::Sprite& sprite);
    void update(float dt,Direction dir);

    void setScale(sf::Vector2f scale,sf::Sprite& sprite);

private:
    const float HOLD_TIME{0.05f};
    int _framesX{0};
    int _framesY{0};
    int _currentX{0};
    int _currentY{0};
    int _width{0};
    int _height{0};
    float time{0.0f};
    sf::Texture texture;
};
