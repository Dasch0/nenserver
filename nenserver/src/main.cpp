// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include "env.h"
#include "server.h"


void renderingThread(sf::RenderWindow* window)
{
    // activate the window's context
    window->setActive(true);

    // the rendering loop
    while (window->isOpen())
    {
        // draw...

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
