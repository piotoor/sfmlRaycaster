#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "player.h"
#include "gameMap.h"

class Raycaster : public sf::Drawable, public sf::Transformable {
    public:
        enum class RaycasterType {
            NO_TEXTURES,
            LOADED_TEXTURES,
            GENERATED_TEXTURES
        };

        Raycaster(int screenWidth,
                  int screenHeight,
                  Player *playerPtr,
                  GameMap *gameMapPtr,
                  Raycaster::RaycasterType raycasterType = Raycaster::RaycasterType::NO_TEXTURES,
                  int textureWidth = 64,
                  int textureHeight = 64);

        virtual ~Raycaster();

        void update();
        void changeRaycasterType(Raycaster::RaycasterType raycasterType);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int             screenWidth;
        int             screenHeight;
        Player          *playerPtr;
        GameMap         *gameMapPtr;
        RaycasterType   raycasterType;
        int             textureWidth;
        int             textureHeight;
        sf::VertexArray mVertices;
        sf::VertexArray mLines;
};

#endif // RAYCASTER
