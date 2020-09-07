#include "Assets.h"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> Assets::textures;

Assets::Assets() {

}

Assets::~Assets() {

}

sf::Texture* Assets::getTexture(std::string name)
{
    return textures[name].get();
}

void Assets::loadTextures(std::string assetsFolder)
{
    assetsFolder.append("/");
    std::cout << "Loading textures..." << std::endl;
    bool successfull = true;
    textures["walls"] = std::make_unique<sf::Texture>();
    if (!textures["walls"]->loadFromFile(assetsFolder + "walls.png"))
    {
        std::cout << "Error loading texture" << std::endl;
        successfull = false;
    }

    if (successfull) {
        std::cout << "Textures loaded successfully" << std::endl;
    }
}
