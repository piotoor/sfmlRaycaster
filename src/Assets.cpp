#include "Assets.h"

std::map<int, std::unique_ptr<sf::Image>> Assets::textures;

Assets::Assets() {

}

Assets::~Assets() {

}

sf::Image* Assets::getTexture(int textureIndex)
{
    return textures[textureIndex].get();
}

void Assets::loadTextures(std::string assetsFolder)
{
    assetsFolder.append("/");
    std::cout << "Loading textures..." << std::endl;
    bool successfull = true;
    textures[0] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "bluestone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[1] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "colorstone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[2] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "eagle.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[3] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "greystone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[4] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "mossy.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[5] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "purplestone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[6] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "redbrick.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures[7] = std::make_unique<sf::Image>();
    if (!textures[0]->loadFromFile(assetsFolder + "wood.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    if (successfull) {
        std::cout << "Textures loaded successfully" << std::endl;
    }
}
