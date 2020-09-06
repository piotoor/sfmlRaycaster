#include "Assets.h"

std::map<std::string, std::unique_ptr<sf::Image>> Assets::textures;

Assets::Assets() {

}

Assets::~Assets() {

}

sf::Image* Assets::getTexture(std::string name)
{
    return textures[name].get();
}

void Assets::loadTextures(std::string assetsFolder)
{
    assetsFolder.append("/");
    std::cout << "Loading textures..." << std::endl;
    bool successfull = true;
    textures["bluestone"] = std::make_unique<sf::Image>();
    if (!textures["bluestone"]->loadFromFile(assetsFolder + "bluestone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["colorstone"] = std::make_unique<sf::Image>();
    if (!textures["colorstone"]->loadFromFile(assetsFolder + "colorstone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["eagle"] = std::make_unique<sf::Image>();
    if (!textures["eagle"]->loadFromFile(assetsFolder + "eagle.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["greystone"] = std::make_unique<sf::Image>();
    if (!textures["greystone"]->loadFromFile(assetsFolder + "greystone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["mossy"] = std::make_unique<sf::Image>();
    if (!textures["mossy"]->loadFromFile(assetsFolder + "mossy.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["purplestone"] = std::make_unique<sf::Image>();
    if (!textures["purplestone"]->loadFromFile(assetsFolder + "purplestone.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["redbrick"] = std::make_unique<sf::Image>();
    if (!textures["redbrick"]->loadFromFile(assetsFolder + "redbrick.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    textures["wood"] = std::make_unique<sf::Image>();
    if (!textures["wood"]->loadFromFile(assetsFolder + "wood.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    if (successfull) {
        std::cout << "Textures loaded successfully" << std::endl;
    }
}
