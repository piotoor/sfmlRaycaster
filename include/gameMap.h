#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <SFML/Graphics.hpp>

class gameMap : public sf::Drawable, public sf::Transformable
{
    public:
        gameMap();
        virtual ~gameMap();

    protected:

    private:
};

#endif // GAMEMAP_H
