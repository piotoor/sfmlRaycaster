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
        static sf::Image* getTexture(std::string name);
        static void loadTextures(const std::string assetsFolder);

    protected:
        static std::map<std::string, std::unique_ptr<sf::Image>> textures;

};

#endif // ASSETS_H
