#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "raycaster.h"
#include "Assets.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

uint8_t bgColor = 16;
int main() {
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(60);

    Assets::loadTextures("../assets/textures");
    Assets::loadFonts("../assets/fonts");

    GameMap gameMap;
    Player player(22, 22, -1, 0, 0.5, &gameMap);
    Raycaster raycaster(screenWidth, screenHeight, &player, &gameMap, Raycaster::RaycasterType::LOADED_TEXTURES);

    sf::Text fpsText;
    fpsText.setFont(*(Assets::getFont("doom")));
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        window.clear(sf::Color(bgColor, bgColor, bgColor));
        //window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        double fps = 1000000.0 / static_cast<double>(elapsed.asMicroseconds());
        fpsText.setString(std::to_string(fps));

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            bgColor = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            bgColor = 16;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            bgColor = 32;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            bgColor = 48;
        }

        window.draw(raycaster);
        window.draw(fpsText);
        window.display();
    }

    return 0;
}

