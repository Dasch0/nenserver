// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "env.h"
#include "server.h"

#define PPM 64.0f
#define RAD_TO_DEG 57.2958

static sf::Texture texture;

static void
update(cpSpace *space, double dt)
{
    cpSpaceStep(space, dt);
}

static void basicDraw(cpBody *body, void *data)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(16.f, 16.f);

    //TODO: improve efficiency here
    sprite.setPosition(PPM * cpBodyGetPosition(body).x, PPM * cpBodyGetPosition(body).y);
    cpFloat angle = cpvtoangle(cpBodyGetRotation(body)) * RAD_TO_DEG;
    sprite.setRotation(angle);

    sf::RenderWindow *window = (sf::RenderWindow *)data;
    window->draw(sprite);
}

void renderingThread(sf::RenderWindow* window)
{
    texture.loadFromFile("box.png");
    // activate the window's context
    window->setActive(true);


    // Create a rouge body to control the planet manually.
    cpSpace *space = cpSpaceNew();
    cpSpaceSetIterations(space, 20);
    cpSpaceSetGravity(space, cpv(5,0));
    cpSpaceSetDamping(space, 1.0);

    addSat(space, 50, 10, cpvzero);

    // the rendering loop
    while (window->isOpen())
    {
        // draw...
        update(space, 1.0/600.0);
        cpSpaceEachBody(space, basicDraw, (void *)window);
        // end the current frame
        window->display();
    }
}

int main(void)
{

    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "nenbody", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    texture.loadFromFile("box.png");
    texture.setSmooth(true);
    // activate the window's context
    window.setActive(true);

    cpSpace *space = cpSpaceNew();
    cpSpaceSetIterations(space, 20);
    cpSpaceSetGravity(space, cpv(1,0));

    bool clicked = false;
    // the rendering loop
    while (window.isOpen())
    {
        // draw...
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (!clicked) {
                        int MouseX = sf::Mouse::getPosition(window).x / PPM;
                        int MouseY = sf::Mouse::getPosition(window).y / PPM;

                        addSat(space, 16.f / PPM , 16.f / PPM, cpv(MouseX, MouseY));

                        clicked = true;
                    }
                }
        else clicked = false;
        update(space, 1.0/60.0);

        window.clear(sf::Color(255, 255, 255, 255));
        cpSpaceEachBody(space, basicDraw, (void *) &window);
        // end the current frame
        window.display();
    }
}
