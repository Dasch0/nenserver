//Simulation environment

#include <list>
#include "chipmunk/chipmunk.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


// Gravity constant for this environment
#define ARM_MASS 0.001
#define ARM_RADIUS 1
#define P -50

static void
planetGravityVelocityFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    cpVect f = cpvproject(cpv(P, 0), cpvrperp(cpBodyGetRotation(body)));

    cpBodyApplyForceAtWorldPoint(body, f, cpBodyGetPosition(body));


    cpBodyUpdateVelocity(body, gravity, damping, dt);
}

static void
motorPresolve(cpConstraint * motor, cpSpace *space)
{
    cpVect *in = (cpVect *) cpConstraintGetUserData(motor);
    cpSimpleMotorSetRate(motor, in->x);
    cpConstraintSetMaxForce(motor, in->y);
}

void addSat(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input)
{
    cpVect verts[] = {
        cpv(-size,-size),
        cpv(-size, size),
        cpv( size, size),
        cpv( size,-size),
    };

    // Add rectangle, main body
    cpBody * rect = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero, cpFloat(0.0))));
    cpBodySetVelocityUpdateFunc(rect, planetGravityVelocityFunc);
    cpBodySetPosition(rect, pos);

    cpShape * rect_shape = cpSpaceAddShape(space, cpPolyShapeNew(rect, 4, verts, cpTransformIdentity, 0.0));

    // Add wheel
    cpBody * wheel = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass/2, size - 1, size - 2, cpvzero)));
    cpBodySetPosition(wheel, pos);

    cpShape * wheel_shape = cpSpaceAddShape(space, cpCircleShapeNew(wheel, size - 1, cpvzero));
    cpShapeSetFilter(wheel_shape, CP_SHAPE_FILTER_NONE);

    // Connect wheel to rect and add motor
    cpSpaceAddConstraint(space, cpPivotJointNew(rect, wheel, pos));
    cpConstraint * motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(rect, wheel, 0.0f));

    // Connect I/O Channel to motor control
    cpConstraintSetUserData(motor, (cpDataPointer) input);

    // Set motor controller function
    cpConstraintSetPreSolveFunc(motor, motorPresolve);

    cpBody *left_arm = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(size/2, 0), cpv(-size/2, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(rect, planetGravityVelocityFunc);
    cpVect left_pos= pos + cpv(size * 2, 0);
    cpBodySetPosition(left_arm, left_pos);

    cpShape * left_arm_shape = cpSpaceAddShape(space, cpSegmentShapeNew(left_arm, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(left_arm_shape, CP_SHAPE_FILTER_NONE);

    cpBody *right_arm = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(-size, 0), cpv(size, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(rect, planetGravityVelocityFunc);
    cpVect right_pos = pos + cpv(-size * 2, 0);
    cpBodySetPosition(right_arm, right_pos);

    cpShape * right_arm_shape = cpSpaceAddShape(space, cpSegmentShapeNew(right_arm, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(right_arm_shape, CP_SHAPE_FILTER_NONE);
    cpSpaceAddConstraint(space, cpPivotJointNew2(rect, left_arm, cpv(-size, 0), cpv(size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(rect, left_arm, 0, 0));

    cpSpaceAddConstraint(space, cpPivotJointNew2(rect, right_arm, cpv(size, 0), cpv(-size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(rect, right_arm, 0, 0));

    cpBodySetAngle(rect, 1.57);
}
