#include "renderer.h"
#include "chipmunk/chipmunk.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


class Renderer
{
public:
    sf::Texture texture;

    Renderer()
    {
        texture.loadFromFile("box.png");
    }
private:
    void drawer(cpBody *body, sf::RenderWindow *window)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.SetOrigin(16.f, 16.f);
    }

    void basic(cpSpace *space, sf::RenderWindow *window)
    {
        cpSpaceEachBody(space, drawer, (void *) window);
    }
};



