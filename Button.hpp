#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include <SFML/Graphics.hpp>


class Button
{
    public:
        Button();
        void init(int posX, int posY, sf::Texture &texture);
        virtual ~Button();

        void setTexture(const sf::Texture &texture);
        void draw(sf::RenderWindow &window);

        bool hover(sf::RenderWindow &window);
        bool pressed(sf::RenderWindow &window, sf::Mouse::Button button);

    private:
        sf::Sprite _button;
};

