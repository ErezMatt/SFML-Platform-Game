#include "AssetManager.h"

AssetManager::AssetManager()
{
}

void AssetManager::loadTexture(const std::string &name,const std::string &fileName)
{
    sf::Texture tmpTexture;

    if(tmpTexture.loadFromFile(fileName)){
        this->_textures[name]=tmpTexture;
    }
}

sf::Texture &AssetManager::getTexture(const std::string &name)
{
    return this->_textures.at(name);
}

void AssetManager::loadFont(const std::string &fileName)
{
    sf::Font tmpFont;

    if(tmpFont.loadFromFile(fileName)){
        this->_font=tmpFont;
    }
}

sf::Font &AssetManager::getFont()
{
    return this->_font;
}

AssetManager::~AssetManager()
{
}
