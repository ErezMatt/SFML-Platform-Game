#include "Chest.hpp"
namespace Engine
{
    Chest::Chest()
    {
        //ctor
    }

      void Chest::init(int posX, int posY, sf::Texture &texture)
    {
        _block.setTexture(texture);
        _block.setPosition(posX,posY);
    }

    void Chest::setTexture(sf::Texture &texture)
    {
        _block.setTexture(texture);
    }

    void Chest::draw(sf::RenderWindow &window)
    {
        window.draw(this->_block);
    }
    float Chest::right() const
    {
        return _block.getPosition().x + _block.getGlobalBounds().width;
    }
    float Chest::left() const
    {
        return _block.getPosition().x;
    }
    float Chest::down() const
    {
        return _block.getPosition().y + _block.getGlobalBounds().height;
    }
    float Chest::up() const
    {
        return _block.getPosition().y;
    }
    sf::FloatRect Chest::getGlobalBounds()
    {
        return _block.getGlobalBounds();
    }





    void Chest::setWorldWidth(int width)
    {
        _worldWidth=width;
    }

    void Chest::setWorldHeight(int height)
    {
        _worldHeight=height;
    }



         void Chest::update(float dt, Player player)
    {
        this->_speed.x=0;


        if(_block.getPosition().x<=0){
           _lBlocked=true;
        }

        if(_block.getPosition().x+_block.getGlobalBounds().width>=_worldWidth){
           _rBlocked=true;
        }

        if(_block.getGlobalBounds().intersects(player.getGlobalBounds()))
            if(player.getPosition().y+(9*player.getGlobalBounds().height/10) >= this->up() &&
                   player.getPosition().y-(9*player.getGlobalBounds().height/10) <= this->down() ){

                    if(player.getPosition().x+player.getGlobalBounds().width>=this->left() &&
                       player.getPosition().x+player.getGlobalBounds().width<this->right()){
                           if(_rBlocked ==_lBlocked)
                        this->_speed.x=player.getSpeedX();
                    }else if(player.getPosition().x<=this->right()){
                          if(_rBlocked ==_lBlocked)
                         this->_speed.x=player.getSpeedX();
                    }
                }




        if(_floor)
            this->_speed.y=0;
        else
            this->_speed.y+=_gravity;

       _block.move(this->_speed);

       _floor=false;
       _rBlocked=false;
       _lBlocked=false;
    }


    void Chest::blocked(){
    std::cout<<"Prawo: "<<_rBlocked<<" Lewo: "<<_lBlocked<<std::endl;

    }


    bool Chest::colisionBlock(Block &block)
    {

        if(_block.getGlobalBounds().intersects(block.getGlobalBounds())){
            //Down/Up path blocked
            if(_block.getPosition().x+_block.getGlobalBounds().width>block.left()+(_block.getGlobalBounds().width/8)
               &&_block.getPosition().x<block.right()-(_block.getGlobalBounds().width/8)){
                if(!_floor && _block.getPosition().y<=block.down() && _block.getPosition().y+_block.getGlobalBounds().height>block.down()){
                    this->_speed.y=2;
                }else if(_block.getPosition().y+_block.getGlobalBounds().height>=block.up()){
                    _floor=true;
                    _block.setPosition(_block.getPosition().x,(block.up()-_block.getGlobalBounds().height));
                }
            }

            //Left/Right path blocked
            if(_block.getPosition().y+(9*_block.getGlobalBounds().height/10) >= block.up() &&
               _block.getPosition().y-(9*_block.getGlobalBounds().height/10) <= block.down() ){

                if(_block.getPosition().x+_block.getGlobalBounds().width>=block.left() &&
                   _block.getPosition().x+_block.getGlobalBounds().width<block.right()){
                    _rBlocked=true;

                }else if(_block.getPosition().x<=block.right()){
                    _lBlocked=true;
                }
            }
        }
        return false;
    }



    Chest::~Chest()
    {
        //dtor
    }
}
