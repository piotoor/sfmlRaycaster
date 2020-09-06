#include "raycaster.h"
#include <cmath>
#include <iostream>

Raycaster::Raycaster(int screenWidth, int screenHeight, Player *playerPtr, GameMap *gameMapPtr,  Raycaster::RaycasterType raycasterType, int textureWidth, int textureHeight):
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    playerPtr(playerPtr),
    gameMapPtr(gameMapPtr),
    raycasterType(raycasterType),
    textureWidth(textureWidth),
    textureHeight(textureHeight),
    mVertices(sf::Points, screenWidth * screenHeight),
    mLines(sf::Lines, screenWidth * 2) {

    if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::LOADED_TEXTURES) {
        for (int j = 0; j < screenWidth; ++j) {
            for (int i = 0; i < screenHeight; ++i) {
                mVertices[j * screenHeight + i].position.x = j;
                mVertices[j * screenHeight + i].position.y = i;
                mVertices[j * screenHeight + i].color = sf::Color::Black;
            }
        }



    }
}

Raycaster::~Raycaster() {

}


 void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = NULL;

    if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::LOADED_TEXTURES) {
        target.draw(mVertices, states);
    } else {
        target.draw(mLines, states);
    }
}

void Raycaster::update() {
    for (int w = 0; w < screenWidth; ++w) {
        double cameraX = 2 * w / static_cast<double>(screenWidth) - 1;
        double rayDirX = playerPtr->getDirX() + playerPtr->getPlaneX() * cameraX;
        double rayDirY = playerPtr->getDirY() + playerPtr->getPlaneY() * cameraX;
        int mapX = static_cast<int>(playerPtr->getPosX());
        int mapY = static_cast<int>(playerPtr->getPosY());
        double dx = rayDirX == 1 ? 0 : std::abs(1.0 / rayDirX);
        double dy = rayDirY == 1 ? 0 : std::abs(1.0 / rayDirY);
        int stepX = 0;
        int stepY = 0;
        double initDistX = 0;
        double initDistY = 0;

        if (rayDirX >= 0) {
                initDistX = (1 - playerPtr->getPosX() + mapX) * dx;
                stepX = 1;
        } else {
                initDistX = (playerPtr->getPosX() - mapX) * dx;
                stepX = -1;
        }

        if (rayDirY >= 0) {
                initDistY = (1 - playerPtr->getPosY() + mapY) * dy;
                stepY = 1;
        } else {
                initDistY = (playerPtr->getPosY() - mapY) * dy;
                stepY = -1;
        }

        bool hit = false;
        bool horizontal = true;

        while (!hit) {
            if (initDistX <= initDistY) {
                horizontal = true;
                initDistX += dx;
                mapX += stepX;
            } else {
                horizontal = false;
                initDistY += dy;
                mapY += stepY;
            }
            if ((*gameMapPtr)(mapX, mapY) > 0) {
                hit = true;
            }
        }

        double perpendicularDistance = 0;

        if (horizontal) {
            double distX = mapX - playerPtr->getPosX() + (1 - stepX) / 2;
            perpendicularDistance = rayDirX == 0 ? distX : distX / rayDirX;
        } else {
            double distY = mapY - playerPtr->getPosY() + (1 - stepY) / 2;
            perpendicularDistance = rayDirY == 0 ? distY : distY / rayDirY;
        }

        int lineHeight = screenHeight / perpendicularDistance;
        int lineStart = std::max(0, screenHeight / 2 - lineHeight / 2);
        int lineEnd = std::min(screenHeight / 2 + lineHeight / 2, screenHeight - 1);

        if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::LOADED_TEXTURES) {
            double wallX;
            if (horizontal) {
                wallX = playerPtr->getPosY() + perpendicularDistance * rayDirY;
            } else {
                wallX = playerPtr->getPosX() + perpendicularDistance * rayDirX;
            }

            wallX -= std::floor(wallX);
        } else {
            sf::Color color;
            switch ((*gameMapPtr)(mapX, mapY)) {
                case 1: {
                    color = sf::Color::Red;
                    break;
                }
                case 2: {
                    color = sf::Color::Green;
                    break;
                }
                case 3: {
                    color = sf::Color::Blue;
                    break;
                }
                case 4: {
                    color = sf::Color::White;
                    break;
                }
                case 5: {
                    color = sf::Color::Cyan;
                    break;
                }
                default: {
                    color = sf::Color::Yellow;
                    break;
                }
            }

            int vertLineInd = 2 * w;
            mLines[vertLineInd].position = sf::Vector2f(w, lineStart);
            mLines[vertLineInd + 1].position = sf::Vector2f(w, lineEnd);

            if (horizontal) {
                color.a = color.a / 2;
            }

            double colorModifier = std::max(1.0, (double)screenHeight / (double)lineHeight);
            color.a /= colorModifier;

            mLines[vertLineInd].color = color;
            mLines[vertLineInd + 1].color = color;
        }
    }
}

void Raycaster::changeRaycasterType( Raycaster::RaycasterType raycasterType) {
    this->raycasterType = raycasterType;
}
