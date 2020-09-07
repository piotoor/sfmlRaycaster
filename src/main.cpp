#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "raycaster.h"
#include "Assets.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;


int main() {
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(60);

    sf::Font font;
    sf::Text fpsText;
    bool fpsAvailable = true;

    Assets::loadTextures("../assets/textures");
    GameMap gameMap;
    Player player(12, 12, -1, 0, 0.5, &gameMap);
    Raycaster raycaster(screenWidth, screenHeight, &player, &gameMap, Raycaster::RaycasterType::LOADED_TEXTURES);

    std::cout << "Loading fonts..." << std::endl;
    if (font.loadFromFile("../assets/fonts/DooM.ttf")) {
        std::cout << "DooM.ttf loaded successfully" << std::endl;
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::Green);
    } else {
        std::cout << "Error loading DooM.ttf" << std::endl;
        fpsAvailable = false;
    }

    while (window.isOpen()) {
        window.clear(sf::Color(40, 40, 40));
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        double fps = 1000000.0 / static_cast<double>(elapsed.asMicroseconds());
        if (fpsAvailable) {
            fpsText.setString(std::to_string(fps));

        }

        raycaster.update();

        double moveSpeed = elapsed.asMilliseconds() / 1000.0 * 5.0;
        double rotateSpeed = elapsed.asMilliseconds() / 1000.0 * 3.0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.rotateLeft(rotateSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player.rotateRight(rotateSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.moveForward(moveSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.moveBack(moveSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            raycaster.changeRaycasterType(Raycaster::RaycasterType::LOADED_TEXTURES);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            raycaster.changeRaycasterType(Raycaster::RaycasterType::NO_TEXTURES);
        }

        window.draw(raycaster);
        window.draw(fpsText);
        window.display();
    }

    return 0;
}

