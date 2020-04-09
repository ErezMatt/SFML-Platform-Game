#include "Player.hpp"

Player::Player()
{
}

void Player::init(int posX, int posY, sf::Texture &texture,int cols, int rows, int width, int height)
{
    _player.setTexture(texture);
    _animation.init(cols, rows, width, height, texture,_player);
    _player.setPosition(posX,posY);
}

void Player::setTexture(sf::Texture &texture)
{
    _player.setTexture(texture);
}

void Player::setTextureRect(sf::IntRect rect)
{
    _player.setTextureRect(rect);
}

void Player::setScale(sf::Vector2f scale)
{
    _animation.setScale(scale,_player);
}

void Player::setWorldWidth(int width)
{
    _worldWidth=width;
}

void Player::setWorldHeight(int height)
{
    _worldHeight=height;
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(this->_player);
}

void Player::handleInput()
{
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        directionY=JUMP;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        directionX=RIGHT;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        directionX=LEFT;
    }
}

void Player::update(float dt)
{
    this->_speed.x=0;
    _moveDirection=Animation::Direction::STAY;
    if(_player.getPosition().x<=0){
        _lBlocked=true;
    }

    if(_player.getPosition().x+_player.getGlobalBounds().width>=_worldWidth){
        _rBlocked=true;
    }

    if(directionX==LEFT && !_lBlocked){
        this->_speed.x=-HERO_SPEED;
        _moveDirection=Animation::Direction::LEFT;
    }
    else if(directionX==RIGHT && !_rBlocked){
        this->_speed.x=HERO_SPEED;
        _moveDirection=Animation::Direction::RIGHT;
    }
    if(_floor && directionY==JUMP){
        _floor=false;
        this->_speed.y=-JUMP_SPEED;
    }
    _animation.update(dt,_moveDirection);
    _animation.applyToSprite(_player);
    if(_floor)
        this->_speed.y=0;
    else
        this->_speed.y+=_gravity;

    directionX=NONE;
    directionY=NONE;

    _player.move(this->_speed);

    _floor=false;
    _rBlocked=false;
    _lBlocked=false;
}

bool Player::colisionBlock(Block &block)
{
    if(_player.getGlobalBounds().intersects(block.getGlobalBounds())){
        //Down/Up path blocked
        if(_player.getPosition().x+_player.getGlobalBounds().width>block.left()+(_player.getGlobalBounds().width/8)
            &&_player.getPosition().x<block.right()-(_player.getGlobalBounds().width/8)){
            if(!_floor && _player.getPosition().y<=block.down() && _player.getPosition().y+_player.getGlobalBounds().height>block.down()){
                directionY=NONE;
                this->_speed.y=2;
            }else if(_player.getPosition().y+_player.getGlobalBounds().height>=block.up()){
                _floor=true;
                _player.setPosition(_player.getPosition().x,(block.up()-_player.getGlobalBounds().height));
            }
        }

        //Left/Right path blocked
        if(_player.getPosition().y+(9*_player.getGlobalBounds().height/10) >= block.up() &&
            _player.getPosition().y-(9*_player.getGlobalBounds().height/10) <= block.down() ){

            if(_player.getPosition().x+_player.getGlobalBounds().width>=block.left() &&
                _player.getPosition().x+_player.getGlobalBounds().width<block.right()){
                _rBlocked=true;

            }else if(_player.getPosition().x<=block.right()){
                _lBlocked=true;
            }
        }
    }
    return false;
}

sf::FloatRect Player::getGlobalBounds()
{
    return _player.getGlobalBounds();
}

bool Player::dead()
{
    if(_player.getPosition().y>=_worldHeight)
        return true;
    return false;
}

Player::~Player()
{
}
