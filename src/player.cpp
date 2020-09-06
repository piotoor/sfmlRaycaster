#include "player.h"
#include <cmath>

Player::Player(double posX, double posY, double dirX, double dirY, double playerSize, GameMap *gameMapPtr):
    posX(posX),
    posY(posY),
    dirX(dirX),
    dirY(dirY),
    planeX(0),
    planeY(0.66),
    playerSize(playerSize),
    gameMapPtr(gameMapPtr) {
}

Player::~Player() {

}

void Player::rotateRight(double rotationSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(-rotationSpeed) - dirY * sin(-rotationSpeed);
    dirY = oldDirX * sin(-rotationSpeed) + dirY * cos(-rotationSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rotationSpeed) - planeY * sin(-rotationSpeed);
    planeY = oldPlaneX * sin(-rotationSpeed) + planeY * cos(-rotationSpeed);
}

void Player::rotateLeft(double rotationSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(rotationSpeed) - dirY * sin(rotationSpeed);
    dirY = oldDirX * sin(rotationSpeed) + dirY * cos(rotationSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotationSpeed) - planeY * sin(rotationSpeed);
    planeY = oldPlaneX * sin(rotationSpeed) + planeY * cos(rotationSpeed);
}

void Player::moveForward(double moveSpeed) {
    int posXi = static_cast<int>(posX + dirX * moveSpeed);
    int posYi = static_cast<int>(posY);
    if ((*gameMapPtr)(posXi, posYi) == 0) {
        posX += dirX * moveSpeed;
    }
    posXi = static_cast<int>(posX);
    posYi = static_cast<int>(posY + dirY * moveSpeed);
    if ((*gameMapPtr)(posXi, posYi) == 0) {
        posY += dirY * moveSpeed;
    }
}

void Player::moveBack(double moveSpeed) {
    int posXi = static_cast<int>(posX - dirX * moveSpeed);
    int posYi = static_cast<int>(posY);
    if ((*gameMapPtr)(posXi, posYi) == 0) {
        posX -= dirX * moveSpeed;
    }
    posXi = static_cast<int>(posX);
    posYi = static_cast<int>(posY - dirY * moveSpeed);
    if ((*gameMapPtr)(posXi, posYi) == 0) {
        posY -= dirY * moveSpeed;
    }
}

void Player::moveLeft(double moveSpeed) {

}

void Player::moveRight(double moveSpeed) {

}

double Player::getPosX() const {
    return posX;
}

double Player::getPosY() const {
    return posY;
}

double Player::getDirX() const {
    return dirX;
}

double Player::getDirY() const {
    return dirY;
}

double Player::getPlayerSize() const {
    return playerSize;
}

double Player::getPlaneX() const {
    return planeX;
}

double Player::getPlaneY() const {
    return planeY;
}
