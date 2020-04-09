#pragma once

#include <map>

#include <SFML/Graphics.hpp>

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        void loadTexture(const std::string &name, const std::string &fileName);
        sf::Texture &getTexture(const std::string &name);

        void loadFont(const std::string &fileName);
        sf::Font &getFont();

    private:
        std::map<std::string,sf::Texture> _textures;
        sf::Font _font;
};
