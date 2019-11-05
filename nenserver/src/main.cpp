// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <zmq.h>
#include "env.h"


#define RAD_TO_DEG 57.2958

static sf::Texture texture;


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

static void
ioEventHandler(sf::RenderWindow *window)
{
    // Event based I/O
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            window->close();

        if (event.type == sf::Event::MouseButtonPressed)
        {

        }
    }
}

static void
ioPolledHandler(sf::View *view, cpBody* target)
{
    // Polled IO
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        view->zoom(1.001f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        view->zoom(0.999f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view->move(0, -10.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view->move(0, 10.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        view->move(-10.0f, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        view->move(10.0f, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        cpVect pos = cpBodyGetPosition(target);
        view->setCenter(pos.x, pos.y);
    }
}

static void envRender(sf::RenderWindow *window, cpSpace *space)
{
    cpSpaceEachBody(space, basicDraw, (void *) window);
}

int main(void)
{

    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1920.0f, 1080.0f), "nenbody", sf::Style::Default, settings);
    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    view.setCenter(0,0);
    // activate it
    window.setView(view);
    window.setFramerateLimit(240);
    texture.loadFromFile("assets/box.png");
    texture.setSmooth(true);
    // activate the window's context
    window.setActive(true);

    // Set up I/O channel
    cpVect input = cpvzero;
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *responder = zmq_socket (context, ZMQ_REP);
    zmq_bind (responder, "tcp://*:5555");

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

    // create satellite
    cpBody * target = addSat(space, 16.f , 16.f, cpv(10000,500), &input);

    // the rendering loop
    while (window.isOpen())
    {
        ioEventHandler(&window);
        ioPolledHandler(&view, target);

        envStep(space, responder, 1/60.0);

        window.clear(sf::Color(255, 255, 255, 255));
        envRender(&window, space);

        window.draw(origin);
        window.setView(view);
        window.display();
    }
}
