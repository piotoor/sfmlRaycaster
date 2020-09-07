#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <string>
#include <memory>

class Assets
{
    public:
        Assets();
        virtual ~Assets();
        static sf::Texture* getTexture(std::string name);
        static void loadTextures(const std::string assetsFolder);

    protected:
        static std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;

};

#endif // ASSETS_H
