// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <zmq.h>
#include "env.h"


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
    sprite.setPosition(cpBodyGetPosition(body).x, cpBodyGetPosition(body).y);
    cpFloat angle = cpvtoangle(cpBodyGetRotation(body)) * RAD_TO_DEG;
    sprite.setRotation(angle);

    sf::RenderWindow *window = (sf::RenderWindow *)data;
    window->draw(sprite);
}


int main(void)
{

    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1280.0f, 720.0f), "nenbody", sf::Style::Default, settings);
    sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
    // activate it
    window.setView(view);
    window.setFramerateLimit(60);
    texture.loadFromFile("assets/box.png");
    texture.setSmooth(true);
    // activate the window's context
    window.setActive(true);

    // Set up I/O channel
    cpVect input = cpvzero;
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");

    printf("%d", rc);

    // Set up physics environment
    cpSpace *space = cpSpaceNew();
    cpSpaceSetIterations(space, 20);
    cpSpaceSetGravity(space, cpv(1,0));
    cpSpaceSetDamping(space, 1.0);

    // Draw origin point
    sf::CircleShape origin;
    origin.setRadius(50);
    origin.setOrigin(25,25);
    origin.setOutlineColor(sf::Color::Red);
    origin.setOutlineThickness(10);
    origin.setPosition(0, 0);

    // the rendering loop
    while (window.isOpen())
    {
        // Event based I/O
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();

            // The escape key was pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // get the current mouse position in the window
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                // convert it to world coordinates
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                addSat(space, 16.f , 16.f, cpv(worldPos.x, worldPos.y), &input);
            }
        }

        // Polled IO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            view.zoom(1.05);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            view.zoom(0.95);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0, -10.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0, 10.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-10.0f, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(10.0f, 0);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            input.x = 100;
            input.y = 5000;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            input.x = -100;
            input.y = 5000;
        }
        else
        {
            input.x = 0;
            input.y = 0;
        }

        // Get Input
        char buffer [10];
        zmq_recv(responder, buffer, 10, ZMQ_NOBLOCK);

        // Update physics world
        update(space, 1.0/60.0);

        // Send Output
        zmq_send(responder, "World", 5, ZMQ_NOBLOCK);

        // Render
        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(origin);
        cpSpaceEachBody(space, basicDraw, (void *) &window);
        window.setView(view);
        window.display();
    }
}
