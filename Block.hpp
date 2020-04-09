#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include <SFML/Graphics.hpp>

class Block
{
    public:
        Block();
        void init(int posX, int posY, sf::Texture &texture);
        virtual ~Block();

        void setTexture(sf::Texture &texture);
        void draw(sf::RenderWindow &window);

        float right() const;
        float left() const;
        float down() const;
        float up() const;
        sf::FloatRect getGlobalBounds();
    private:
        sf::Sprite _block;
        int _width;
        int _height;
};

