#pragma once

#include <memory>
#include <string>

#include "AssetManager.h"
#include "Player.hpp"
#include "Block.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

namespace Engine
{
    class Chest
    {
        public:
            Chest();
            virtual ~Chest();



            void init(int posX, int posY, sf::Texture &texture);

            void setTexture(sf::Texture &texture);
            void draw(sf::RenderWindow &window);

            float right() const;
            float left() const;
            float down() const;
            float up() const;
            sf::FloatRect getGlobalBounds();

        void blocked();


            void setWorldWidth(int width);
            void setWorldHeight(int height);
            void update(float dt, Player player);

            bool colisionBlock(Block &block);


            private:

             sf::Sprite _block;
            int _width;
            int _height;

            int _worldWidth{0};
            int _worldHeight{0};

            const float CHEST_SPEED{3.0f};

            float _gravity{0.5f};

            sf::Vector2f _speed{0,0};
            bool _floor{false};
            bool _lBlocked{false};
            bool _rBlocked{false};
    };
}
