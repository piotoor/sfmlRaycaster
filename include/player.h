#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "gameMap.h"


class Player {
    public:
        Player(double posX, double posY, double dirX, double dirY, double playerSize, GameMap *gameMapPtr);
        virtual ~Player();

        void rotateRight    (double rotationSpeed);
        void rotateLeft     (double rotationSpeed);
        void moveForward    (double moveSpeed);
        void moveBack       (double moveSpeed);
        void moveLeft       (double moveSpeed);
        void moveRight      (double moveSpeed);

        double getPosX() const;
        double getPosY() const;
        double getDirX() const;
        double getDirY() const;
        double getPlayerSize() const;
        double getPlaneX() const;
        double getPlaneY() const;

    private:
        double posX;
        double posY;
        double dirX;
        double dirY;
        double planeX;
        double planeY;
        double playerSize;

        GameMap *gameMapPtr;
};

#endif // PLAYER_H
