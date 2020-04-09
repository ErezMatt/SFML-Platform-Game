#include "Block.hpp"

Block::Block()
{
}

void Block::init(int posX, int posY, sf::Texture &texture)
{
    _block.setTexture(texture);
    _block.setPosition(posX,posY);
}

void Block::setTexture(sf::Texture &texture)
{
    _block.setTexture(texture);
}

void Block::draw(sf::RenderWindow &window)
{
    window.draw(this->_block);
}

float Block::right() const
{
    return _block.getPosition().x + _block.getGlobalBounds().width;
}

float Block::left() const
{
    return _block.getPosition().x;
}

float Block::down() const
{
    return _block.getPosition().y + _block.getGlobalBounds().height;
}

float Block::up() const
{
    return _block.getPosition().y;
}

sf::FloatRect Block::getGlobalBounds()
{
    return _block.getGlobalBounds();
}

Block::~Block()
{
}
