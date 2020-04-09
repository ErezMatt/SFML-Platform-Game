#include "Button.hpp"

Button::Button()
{
}

void Button::init(int posX, int posY, sf::Texture &texture)
{
    _button.setTexture(texture);
    _button.setPosition(posX-(_button.getGlobalBounds().width/2),posY-(_button.getGlobalBounds().height/2));
}

void Button::setTexture(const sf::Texture &texture)
{
    _button.setTexture(texture);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(_button);
}

bool Button::hover(sf::RenderWindow &window)
{
    sf::IntRect tmpRec(_button.getPosition().x,_button.getPosition().y,_button.getGlobalBounds().width,_button.getGlobalBounds().height);
    return tmpRec.contains(sf::Mouse::getPosition(window));
}

bool Button::pressed(sf::RenderWindow &window, sf::Mouse::Button button)
{
    if(sf::Mouse::isButtonPressed(button) && this->hover(window))
        return true;
    return false;
}

Button::~Button()
{
}
