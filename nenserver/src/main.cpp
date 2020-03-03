// nenserver main file

// Force chipmunk2d to use single precision ieee754 floating point
// Force chipmunk2d to use single precision ieee754 floating point
#undef CP_USE_DOUBLES
#define CP_USE_DOUBLES 0

#include <cstdlib>
#include <ctime>
#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include "zmq.h"
#include "env.h"
#include "util.h"
#include "asset.h"

static void
ioEventHandler(sf::RenderWindow *window, sf::Sprite *sprite, cpVect *goalPos)
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
            // get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);

            // convert it to world coordinates
            sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
            goalPos->x = worldPos.x;
            goalPos->y = worldPos.y;
            sprite->setPosition(worldPos);
        }
    }
}

static void
ioPolledHandler(sf::View *view, cpBody *target)
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
        view->setCenter((float) pos.x,(float) pos.y);
    }
}

static void drawEnvSprites(cpBody *body, void * window)
{
    cpVect pos = cpBodyGetPosition(body);
    cpFloat angle = cpvtoangle(cpBodyGetRotation(body)) * RAD_TO_DEG;
    uint index = (uint) ((uint64_t) cpBodyGetUserData(body));

    Asset::Sprite::draw(index, pos, angle, (sf::RenderWindow *) window);
}

int main(void)
{

    Asset::Texture::init();

    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1920.0f, 1080.0f), "nenbody", sf::Style::Default, settings);
    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    view.setCenter(0,0);
    // activate it
    window.setView(view);
    window.setFramerateLimit(240);
    // activate the window's context
    window.setActive(true);

    // Set up I/O channel
    cpVect input = cpvzero;
    //  Socket to talk to clients
    void *context = zmq_ctx_new();

    // Set up physics environment
    cpSpace *space = cpSpaceNew();
    cpSpaceSetIterations(space, 20);
    cpSpaceSetGravity(space, cpv(0,0));
    cpSpaceSetDamping(space, 1.0);

    // Draw origin point
    sf::CircleShape origin;
    origin.setRadius(50);
    origin.setOrigin(25,25);
    origin.setOutlineColor(sf::Color::Red);
    origin.setOutlineThickness(10);
    origin.setPosition(0, 0);

    // create satellite
    cpBody * target = addUfo(space, 16.0 , 16.0, cpv(10000,500), &input);

    sf::Sprite test;
    cpVect goalPos = cpvzero;
    cpVect goalVel = cpvzero;

    test.setTexture(Asset::Texture::list[Asset::Texture::wheel]);

    sf::VertexArray stars = sf::VertexArray(sf::Points, 1000);
    std::srand((uint) time(0));
    for(int i = 0; i < 10000; i++)
    {
        stars.append(sf::Vertex(sf::Vector2f(rand() % 30000 - 15000,rand() % 30000 - 15000), sf::Color::White));
    }

    while (window.isOpen())
    {
        ioEventHandler(&window, &test, &goalPos);
        ioPolledHandler(&view, target);

        envStep(space, responder, 0.002, &goalPos, &goalVel);
        envStep(space, responder, 0.002, &goalPos, &goalVel);
        envStep(space, responder, 0.002, &goalPos, &goalVel);
        envStep(space, responder, 0.002, &goalPos, &goalVel);
        envStep(space, responder, 0.002, &goalPos, &goalVel);


        window.clear(sf::Color(0,0,0,255));
        window.draw(test);
        window.draw(stars);

        // update entity coordinates
        cpSpaceEachBody(space, drawEnvSprites, (void *) &window);

        window.setView(view);
        window.display();
    }
}
