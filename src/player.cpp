#include "player.h"
#include <cmath>
#include <SFML/Graphics.hpp>


MovableObject::MovableObject(double posX, double posY, double dirX, double dirY, double movementSpeedMultiplier, double rotationSpeedMultiplier, double objectBoxSize, GameMap *gameMapPtr):
    posX(posX),
    posY(posY),
    dirX(dirX),
    dirY(dirY),
    planeX(0), // compute properly
    planeY(0.66), // compute
    movementSpeedMultiplier(movementSpeedMultiplier),
    rotationSpeedMultiplier(rotationSpeedMultiplier),
    objectBoxSize(objectBoxSize),
    gameMapPtr(gameMapPtr) {

}

MovableObject::~MovableObject() {
}

void MovableObject::rotateRight(int32_t dt) {
    double rotateSpeed = dt / 1000.0 * rotationSpeedMultiplier;
    double oldDirX = dirX;
    dirX = dirX * cos(-rotateSpeed) - dirY * sin(-rotateSpeed);
    dirY = oldDirX * sin(-rotateSpeed) + dirY * cos(-rotateSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rotateSpeed) - planeY * sin(-rotateSpeed);
    planeY = oldPlaneX * sin(-rotateSpeed) + planeY * cos(-rotateSpeed);
}

void MovableObject::rotateLeft(int32_t dt) {
    double rotateSpeed = dt / 1000.0 * rotationSpeedMultiplier;
    double oldDirX = dirX;
    dirX = dirX * cos(rotateSpeed) - dirY * sin(rotateSpeed);
    dirY = oldDirX * sin(rotateSpeed) + dirY * cos(rotateSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotateSpeed) - planeY * sin(rotateSpeed);
    planeY = oldPlaneX * sin(rotateSpeed) + planeY * cos(rotateSpeed);
}

void MovableObject::moveForward(int32_t dt) {
    double moveSpeed = dt / 1000.0 * movementSpeedMultiplier;
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

void MovableObject::moveBack(int32_t dt) {
    double moveSpeed = dt / 1000.0 * movementSpeedMultiplier;
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


double MovableObject::getPosX() const {
    return posX;
}

double MovableObject::getPosY() const {
    return posY;
}

double MovableObject::getDirX() const {
    return dirX;
}

double MovableObject::getDirY() const {
    return dirY;
}

double MovableObject::getObjectBoxSize() const {
    return objectBoxSize;
}

double MovableObject::getPlaneX() const {
    return planeX;
}

double MovableObject::getPlaneY() const {
    return planeY;
}



Player::Player(double posX, double posY, double dirX, double dirY, double movementSpeedMultiplier, double rotationSpeedMultiplier, double objectBoxSize, GameMap *gameMapPtr):
    MovableObject(posX, posY, dirX, dirY, movementSpeedMultiplier, rotationSpeedMultiplier, objectBoxSize, gameMapPtr){
}

Player::~Player() {

}

void Player::keyboardInput(uint32_t dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        rotateLeft(dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        rotateRight(dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        moveForward(dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        moveBack(dt);
    }
}
