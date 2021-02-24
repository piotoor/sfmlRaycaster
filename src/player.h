#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "gameMap.h"


class MovableObject {
    public:
        MovableObject(double posX, double posY, double dirX, double dirY, double movementSpeedMultiplier, double rotationSpeedMultiplier, double objectBoxSize, GameMap *gameMapPtr);
        virtual ~MovableObject();

        void rotateRight    (int32_t dt);
        void rotateLeft     (int32_t dt);
        void moveForward    (int32_t dt);
        void moveBack       (int32_t dt);
        void moveLeft       (int32_t dt);
        void moveRight      (int32_t dt);

        double getPosX() const;
        double getPosY() const;
        double getDirX() const;
        double getDirY() const;
        double getObjectBoxSize() const;
        double getPlaneX() const;
        double getPlaneY() const;
        double getMovementSpeed() const;
        double getRotationSpeed() const;
        void setMovementSpeed(double movementSpeedMultiplier);
        void setRotationSpeed(double rotationSpeedMultiplier);

    private:
        double posX;
        double posY;
        double dirX;
        double dirY;
        double planeX;
        double planeY;
        double movementSpeedMultiplier;
        double rotationSpeedMultiplier;
        double objectBoxSize;

        GameMap *gameMapPtr;
};

class GameActor {


    private:
        uint16_t health;
        uint16_t ammo;
        uint16_t firepower;

        // player only?
        uint16_t frags;
        uint16_t deaths;

        /*
    implement state machine
    states:
    idle
    takingDamage
    taunting
    walking
    attacking
    dying
    dead
    */
};

class Player: public MovableObject, public GameActor {
    public:
        Player(double posX, double posY, double dirX, double dirY, double movementSpeedMultiplier, double rotationSpeedMultiplier, double objectBoxSize, GameMap *gameMapPtr);
        virtual ~Player();

        void keyboardInput(uint32_t dt);
};

class Enemy: public MovableObject, public GameActor {

    // draw
    // animation

};

#endif // PLAYER_H
