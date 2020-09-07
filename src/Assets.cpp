#include "Assets.h"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> Assets::textures;
std::unordered_map<std::string, std::unique_ptr<sf::Font>> Assets::fonts;

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


sf::Font* Assets::getFont(std::string name)
{
    return fonts[name].get();
}

void Assets::loadFonts(std::string assetsFolder)
{
    assetsFolder.append("/");
    std::cout << "Loading fonts..." << std::endl;
    fonts["doom"] = std::make_unique<sf::Font>();
    bool successfull = true;
    if (fonts["doom"]->loadFromFile(assetsFolder + "DooM.ttf")) {
        std::cout << "Error loading font file" << std::endl;
        successfull = false;
    }
    if (successfull) {
        std::cout << "Fonts loaded successfully" << std::endl;
    }
}
