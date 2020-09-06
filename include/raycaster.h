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
            LOADED_TESTURES,
            GENERATED_TEXTURES
        };

        Raycaster(int screenWidth, int screenHeight, Player *playerPtr, GameMap *gameMapPtr, Raycaster::RaycasterType raycasterType = Raycaster::RaycasterType::NO_TEXTURES);
        virtual ~Raycaster();
        void update();
        void changeRaycasterType(Raycaster::RaycasterType raycasterType);


    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int screenWidth;
        int screenHeight;
        Player *playerPtr;
        GameMap *gameMapPtr;
        RaycasterType raycasterType;
        sf::VertexArray mVertices;
        sf::VertexArray mLines;
};

#endif // RAYCASTER
