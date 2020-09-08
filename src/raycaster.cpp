#include "raycaster.h"
#include <cmath>
#include <iostream>
#include "Assets.h"

Raycaster::Raycaster(int screenWidth, int screenHeight, Player *playerPtr, GameMap *gameMapPtr,  Raycaster::RaycasterType raycasterType, int textureWidth, int textureHeight):
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    playerPtr(playerPtr),
    gameMapPtr(gameMapPtr),
    raycasterType(raycasterType),
    textureWidth(textureWidth),
    textureHeight(textureHeight),
    mQuads(sf::Quads, screenWidth * 4),
    mLines(sf::Lines, screenWidth * 2),
    mFloorQuad(sf::Quads, 4) {

    mFloorQuad[0].position = sf::Vector2f(0, screenHeight / 2);
    mFloorQuad[1].position = sf::Vector2f(screenWidth - 1, screenHeight / 2);
    mFloorQuad[2].position = sf::Vector2f(screenWidth - 1, screenHeight - 1);
    mFloorQuad[3].position = sf::Vector2f(0, screenHeight - 1);
    for (int i = 0; i < 4; ++i) {
        mFloorQuad[i].color = sf::Color(64, 64, 64);
    }
}

Raycaster::~Raycaster() {

}


 void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::LOADED_TEXTURES) {
        target.draw(mFloorQuad, states);
        states.texture = Assets::getTexture("walls");
        target.draw(mQuads, states);
    } else {
        states.texture = NULL;
        target.draw(mLines, states);
    }
}

void Raycaster::update() {
    // walls
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
        int lineStart = screenHeight / 2 - lineHeight / 2;
        int lineEnd = screenHeight / 2 + lineHeight / 2;
        if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::NO_TEXTURES) {
            lineStart = std::max(0, lineStart);
            lineEnd = std::min(lineEnd, screenHeight - 1);
        }


        if (raycasterType == RaycasterType::GENERATED_TEXTURES or raycasterType == RaycasterType::LOADED_TEXTURES) {
            double wallX;
            if (horizontal) {
                wallX = playerPtr->getPosY() + perpendicularDistance * rayDirY;
            } else {
                wallX = playerPtr->getPosX() + perpendicularDistance * rayDirX;
            }

            wallX -= std::floor(wallX);

            int texX = int(wallX * textureWidth);
            if (horizontal and rayDirX > 0) {
                texX = textureWidth - texX - 1;
            }
            if (!horizontal and rayDirY < 0) {
                texX = textureWidth - texX - 1;
            }

            int textureInd = (*gameMapPtr)(mapX, mapY);

            if (horizontal and rayDirX > 0) {
                textureInd >>= 12;
            } else if (horizontal and rayDirX <= 0) {
                textureInd = (textureInd & 0x00F0) >> 4;
            } else if (!horizontal and rayDirY > 0) {
                textureInd = textureInd & 0x000f;
            } else {
                textureInd = (textureInd & 0x0F00) >> 8;
            }


            texX += textureInd * textureWidth;

            int quadInd = 4 * w;
            mQuads[quadInd].position =      sf::Vector2f(w, lineStart);
            mQuads[quadInd + 1].position =  sf::Vector2f(w + 1, lineStart);
            mQuads[quadInd + 2].position =  sf::Vector2f(w + 1, lineEnd);
            mQuads[quadInd + 3].position =  sf::Vector2f(w, lineEnd);

            int offscreen = 0;
            mQuads[quadInd].texCoords =     sf::Vector2f(texX, offscreen);
            mQuads[quadInd + 1].texCoords = sf::Vector2f(texX + 1, offscreen);
            mQuads[quadInd + 2].texCoords = sf::Vector2f(texX + 1, textureHeight - offscreen);
            mQuads[quadInd + 3].texCoords = sf::Vector2f(texX, textureHeight - offscreen);

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
                case 6: {
                    color = sf::Color::Magenta;
                    break;
                }
                case 7: {
                    color = sf::Color(10, 112, 201);
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
