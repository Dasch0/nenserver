// nenserver main file

#include <chipmunk/chipmunk.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <zmq.h>
#include "env.h"
#include "tables.h"

#define RAD_TO_DEG 57.2958

namespace Asset
{
    namespace Texture
    {
        const uint count = 3;
        const AssetID box = 0;
        const AssetID wheel = 1;
        const AssetID wing = 2;

        sf::Texture list[count];
        const char* files[count] =
        {
            "assets/box.png",
            "assets/wheel.png",
            "assets/wing.png",
        };

        void init(void)
        {
            for (int i = 0; i < count; i++)
            {
            list[i].loadFromFile(files[i]);
            list[i].setSmooth(true);
            }
        }
    }

    namespace Sprite
    {
        uint count = 0;
        sf::Sprite list[MAX_ENTITIES];

        // returns index in list
        uint add(AssetID texture)
        {
           sf::Vector2u size;
           sf::Texture *t = &Asset::Texture::list[texture];
           size = t->getSize();
           list[count].setTexture(*t);
           list[count].setOrigin(size.x * 0.5f, size.y * 0.5f);
           return count++;
        }

        void draw(uint index, cpVect position, double angle, sf::RenderWindow *window)
        {
            list[index].setPosition((float) position.x, (float) position.y);
            list[index].setRotation((float) angle);
            window->draw(list[index]);
        }

        sf::Sprite * get(uint index)
        {
            return &list[index];
        }

    }
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
    cpBody * target = addSat(space, 16.0 , 16.0, cpv(10000,500), &input);

    sf::Sprite test;

    test.setTexture(Asset::Texture::list[Asset::Texture::wheel]);

    while (window.isOpen())
    {
        ioEventHandler(&window);
        ioPolledHandler(&view, target);

        envStep(space, responder, 0.001);
        envStep(space, responder, 0.001);
        envStep(space, responder, 0.001);

        window.clear(sf::Color(0,0,0,255));
        window.draw(test);

        // update entity coordinates
        cpSpaceEachBody(space, drawEnvSprites, (void *) &window);

        window.setView(view);
        window.display();
    }
}
