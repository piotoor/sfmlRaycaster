#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <memory>

class Assets
{
    public:
        Assets();
        virtual ~Assets();
        static sf::Image* getTexture(int textureIndex);
        static void loadTextures(const std::string assetsFolder);

    protected:
        static std::map<int, std::unique_ptr<sf::Image>> textures;

};

#endif // ASSETS_H
