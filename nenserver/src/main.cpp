// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include "env.h"
#include "server.h"

static sf::Texture texture;

static void basicDraw(cpBody *body, void *data)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(16.f, 16.f);

    //TODO: improve efficiency here
    sprite.setPosition(cpBodyGetPosition(body).x, cpBodyGetPosition(body).y);
    cpFloat angle = cpvtoangle(cpBodyGetRotation(body)) * pi / 180.0;
    sprite.setRotation(angle);

    sf::RenderWindow *window = (sf::RenderWindow *)data;
    window->draw(sprite);
}

void renderingThread(sf::RenderWindow* window, cpSpace *space)
{
    texture.loadFromFile("box.png");
    // activate the window's context
    window->setActive(true);

    // the rendering loop
    while (window->isOpen())
    {
        // draw...
        cpSpaceEachBody(space, basicDraw, (void *)window);
        // end the current frame
        window->display();
    }
}

int main(void)
{
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");

    // deactivate its OpenGL context
    window.setActive(false);

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    // the event/logic/whatever loop
    while (window.isOpen())
    {

    }

    return 0;
}
