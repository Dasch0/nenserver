//Simulation environment

#include <list>
#include "chipmunk/chipmunk.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


// Gravity constant for this environment
#define G 1000

static void
planetGravityVelocityFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    // Gravitational acceleration is proportional to the inverse square of
    // distance, and directed toward the origin. The central planet is assumed
    // to be massive enough that it affects the satellites but not vice versa.
    cpVect p = cpBodyGetPosition(body);
    cpFloat sqdist = cpvlengthsq(p);
    cpVect g = cpvmult(p, -G / (sqdist * cpfsqrt(sqdist)));

    cpBodyUpdateVelocity(body, g, damping, dt);
}

static void
motorPresolve(cpConstraint * motor, cpSpace *space)
{
}

class Satellite
{
    Satellite(cpSpace *s, cpFloat size, cpFloat mass, cpVect pos) :
        space(s),
        solverFunc(planetGravityVelocityFunc),
        motorControlFunc(motorPresolve)
    {
        cpVect verts[] = {
            cpv(-size,-size),
            cpv(-size, size),
            cpv( size, size),
            cpv( size,-size),
        };

        // Add rectangle, main body
        cpBody * rect = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero, cpFloat(0.0))));
        cpBodySetVelocityUpdateFunc(rect, solverFunc);
        cpBodySetPosition(rect, pos);
        bodies.push_front(rect);

        cpShape * rect_shape = cpSpaceAddShape(space, cpPolyShapeNew(rect, 4, verts, cpTransformIdentity, 0.0));
        cpShapeSetFilter(rect_shape, CP_SHAPE_FILTER_NONE);
        shapes.push_front(rect_shape);

        // Add wheel
        cpBody * wheel = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, size - 1, size - 2, cpvzero)));
        cpBodySetPosition(wheel, pos);
        bodies.push_front(wheel);

        cpShape * wheel_shape = cpSpaceAddShape(space, cpCircleShapeNew(wheel, size - 1, cpvzero));
        cpShapeSetFilter(wheel_shape, CP_SHAPE_FILTER_NONE);
        shapes.push_front(wheel_shape);

        // Connect wheel to rect and add motor
        cpSpaceAddConstraint(space, cpPivotJointNew(rect, wheel, pos));
        cpConstraint * motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(rect, wheel, 0.0));
        cpConstraintSetPreSolveFunc(motor, motorControlFunc);
    }

public:
    cpSpace *space;
    sf::RenderWindow *app;
    std::list<cpBody *> bodies;
    std::list<cpShape *> shapes;
    std::list<cpConstraint *> joints;
    cpBody *leftArm, *rightArm;
    cpBodyVelocityFunc solverFunc;
    cpConstraintPreSolveFunc motorControlFunc;
};
