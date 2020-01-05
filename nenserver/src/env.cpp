//Simulation environment

#include <cstring>
#include <string>
// Force chipmunk2d to use single precision ieee754 floating point
#undef CP_USE_DOUBLES
#define CP_USE_DOUBLES 0
#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_structs.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "zmq.h"
#include "env.h"
#include "tables.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)



// Gravity constant for this environment

static char buffer [500];
static cpVect nengoForce;

static Control_t ctrl;

static void
planetGravityVelocityFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    cpVect f = cpvproject(cpv(GRAV, 0), cpvrperp(cpBodyGetRotation(body)));

    cpBodyApplyForceAtWorldPoint(body, f, cpBodyGetPosition(body));

    cpBodyUpdateVelocity(body, gravity, damping, dt);
}

static void
nengoPresolve(cpConstraint * motor, cpSpace * space)
{
    Control_t *c = (Control_t *) cpConstraintGetUserData(motor);

    // Calculate desired theta from force
    cpFloat theta = cpvtoangle(nengoForce) / 2.0;

    // Calculate theta error
    cpFloat theta_err = theta - (cpvtoangle(cpvperp(cpBodyGetRotation(c->plant))));

    // Calculate rate & force to achieve theta (simple P controller for now)
    cpFloat rate = theta_err * 3;

    cpSimpleMotorSetRate(motor, ((int) c->in->x) ? c->in->x : rate);
    cpConstraintSetMaxForce(motor, 1000);
}

static void
ufoPresolve(cpConstraint * motor, cpSpace * space)
{
    Control_t *c = (Control_t *) cpConstraintGetUserData(motor);

    cpBodyApplyForceAtWorldPoint(c->plant, nengoForce * -10, cpBodyGetPosition(c->plant));
}


static void
motorPresolve(cpConstraint * motor, cpSpace *space)
{
    Control_t *c = (Control_t *) cpConstraintGetUserData(motor);

    // Compute positional term
    cpVect pos = cpBodyGetPosition(c->plant);
    cpVect pos_err = pos - cpv(500, 500);

    cpVect vel = cpBodyGetVelocity(c->plant);
    cpVect vel_err = cpv(vel.x, vel.y) * cpvlength(vel);

    // Calculate desired forces (simple PID controller for now)
    cpVect F = pos_err + vel_err * 1;

    // Calculate desired theta from force
    cpFloat theta = cpvtoangle(F) / 2;

    // Calculate theta error
    cpFloat theta_err = theta - (cpvtoangle(cpvperp(cpBodyGetRotation(c->plant))));

    // Calculate rate & force to achieve theta (simple P controller for now)
    cpFloat rate = theta_err * 3;

    cpSimpleMotorSetRate(motor, ((int) c->in->x) ? c->in->x : rate);
    cpConstraintSetMaxForce(motor, 1000);
}

namespace env
{
    typedef int handle;
    typedef int status;
    struct Swimmer
    {
     // commands are sent from neurons to body
     typedef struct
     {
         cpFloat torque;
         cpFloat force;
     } Commands_t;

     // signals are sent from body to neurons
     typedef struct
     {
         cpFloat stateAngle;
         cpFloat goalAngle;
         cpFloat goalDist;
         uint32_t goalState;
     } Signals_t;

     typedef struct
     {
         cpBody *core;
         cpBody *wheel;
         cpConstraint *pivot;
         cpConstraint *motor;
     } Skeleton_t;

     static env::status createSkeleton(cpSpace * space, cpVect pos, Skeleton_t *s)
     {
         // Hardcoded parameters and locals
         // TODO: clean up hardcoded parameters
         cpVect coreVerts[] = {
             cpv(-5,0),
             cpv(5, 0),
             cpv(0, 5),
         };
         cpFloat radius = 2.5;
         cpFloat mass = 5;
         uint64_t index;

         s->core = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, coreVerts, cpvzero, 0.0)));
         index = Asset::Sprite::add(Asset::Texture::box);
         cpBodySetUserData(s->core, (void *) index);
         cpBodySetVelocityUpdateFunc(s->core, planetGravityVelocityFunc);
         cpBodySetPosition(s->core, pos);
         cpShape * coreShape = cpSpaceAddShape(space, cpPolyShapeNew(s->core, 3, coreVerts, cpTransformIdentity, 0.0));
         cpShapeSetFilter(coreShape, CP_SHAPE_FILTER_NONE);

         s->wheel = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, coreVerts, cpvzero, 0.0)));
         index = Asset::Sprite::add(Asset::Texture::wheel);
         cpBodySetUserData(s->core, (void *) index);
         cpBodySetVelocityUpdateFunc(s->core, planetGravityVelocityFunc);
         cpBodySetPosition(s->core, pos);
         cpShape * wheelShape = cpSpaceAddShape(space, cpCircleShapeNew(s->core, 2.5, cpvzero));
         cpShapeSetFilter(wheelShape, CP_SHAPE_FILTER_NONE);

         s->pivot = cpSpaceAddConstraint(space, cpPivotJointNew(s->core, s->wheel, pos));
         s->motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(s->core, s->wheel, 0.0));

         // TODO: improve status codes
         return 0;
     }

     static env::status bindSignals()
     {

         return 0;
     }

     static env::status bindCommands()
     {
         return 0;
     }

    private:
     Swimmer();
     ~Swimmer();
    };
}

namespace env
{

    template <class species, int max_size>
    struct orgTable
    {
        uint16_t count;
        int16_t status;
        uint32_t flags;

        // Networking parameters
        struct species::Commands_t inputTable[max_size];
        struct species::Signals_t outputTable[max_size];
        void * sockets[max_size];
        zmq_msg_t inMsgs[max_size];
        zmq_msg_t outMsgs[max_size];
        void * context;

        // Physics parameters
        struct species::Skeleton_t bodies[max_size];
        cpSpace * space;

        orgTable(void * zmqContext, cpSpace * space) :
            count(0), status(0), flags(0), context(zmqContext), space(space) {}

        env::handle add(void)
        {
            if(count <= max_size)
                return -1;

            // Set up networking
            sockets[count] = zmq_socket(context, ZMQ_REP);
            int status = 0;
            status |= zmq_bind(sockets[count], "tcp://*:5555");
            status |= zmq_msg_init_data(inMsgs[count], inputTable[count], sizeof(inputTable[count]), NULL, NULL);
            status |= zmq_msg_init_data(outMsgs[count], outputTable[count], sizeof(inputTable[count]), NULL, NULL);

            // Create physics components of org
            // TODO: Add initial positions other than 0
            status |= species::createSkeleton(space, cpvzero, bodies[count]);
            status |= species::bindCommands();
            status |= species::bindSignals();

            // Check for failures
            if (unlikely(status < 0)) return status;

            // increment count and return
            count++;
            return count;
        }

        env::status recv(void)
        {
            env::status status = 0;
            for(int i = 0; i < count; i++)
            {
                status |= zmq_msg_recv(inMsgs[i], sockets[i], 0);
            }
            return status;
        }

        env::status send(void)
        {
            env::status status = 0;
            for(int i = 0; i < count; i++)
            {
                status |= zmq_msg_send(outMsgs[i], sockets[i], 0);
            }
            return status;
        }

        env::status remove(handle h)
        {
            h = 0;
            count--;
            return -1;
        }

        ~orgTable(void) {}
    };
}

void envStep(cpSpace *space, void *responder, double dt, cpVect *goalPos, cpVect *goalVel)
{
    // Get input

    zmq_recv(responder, buffer, 100, 0);

    std::string vals = std::string(buffer);
    std::string::size_type sz;
    double x = std::stod(vals, &sz);
    double y = std::stod(vals.substr(sz));

    nengoForce = cpv(x,y);

    // simulate physics
    cpSpaceStep(space, dt);

    // Send Output
    cpVect pos = cpBodyGetPosition(ctrl.plant);
    cpVect vel = cpBodyGetVelocity(ctrl.plant);

    sprintf(buffer, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", pos.x, pos.y, vel.x, vel.y, goalPos->x, goalPos->y, goalVel->x, goalVel->y);
    zmq_send(responder, buffer, strlen(buffer), 0);
}

cpBody * addSat(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input)
{
    cpVect verts[] = {
        cpv(-size,-size),
        cpv(-size, size),
        cpv( size, size),
        cpv( size,-size),
    };

    uint index;

    // Add rectangle, main body
    cpBody * rect = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero, cpFloat(0.0))));
    index = Asset::Sprite::add(Asset::Texture::box);
    cpBodySetUserData(rect, (void *) ((uint64_t) index));
    cpBodySetVelocityUpdateFunc(rect, planetGravityVelocityFunc);
    cpBodySetPosition(rect, pos);

    cpShape * rect_shape = cpSpaceAddShape(space, cpPolyShapeNew(rect, 4, verts, cpTransformIdentity, 0.0));

    // Add wheel
    cpBody * wheel = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass/2, size - 1, size - 2, cpvzero)));
    index = Asset::Sprite::add(Asset::Texture::wheel);
    cpBodySetUserData(wheel, (void *) ((uint64_t) index));

    cpBodySetPosition(wheel, pos);

    cpShape * wheel_shape = cpSpaceAddShape(space, cpCircleShapeNew(wheel, size - 1, cpvzero));
    cpShapeSetFilter(wheel_shape, CP_SHAPE_FILTER_NONE);

    // Connect wheel to rect and add motor
    cpSpaceAddConstraint(space, cpPivotJointNew(rect, wheel, pos));
    cpConstraint * motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(rect, wheel, 0.0));

    // Connect I/O Channel to motor control
    ctrl.in = input;
    ctrl.plant = rect;
    cpConstraintSetUserData(motor, (cpDataPointer) &ctrl);

    // Set motor controller function
    cpConstraintSetPreSolveFunc(motor, nengoPresolve);

    cpBody *left_arm = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(size/2, 0), cpv(-size/2, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(left_arm, planetGravityVelocityFunc);
    index = Asset::Sprite::add(Asset::Texture::wing);
    cpBodySetUserData(left_arm, (void *) ((uint64_t) index));
    cpVect left_pos= pos + cpv(size * 2, 0);
    cpBodySetPosition(left_arm, left_pos);
    cpShape * left_arm_shape = cpSpaceAddShape(space, cpSegmentShapeNew(left_arm, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(left_arm_shape, CP_SHAPE_FILTER_NONE);

    cpBody *left_arm2 = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(size/2, 0), cpv(-size/2, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(left_arm2, planetGravityVelocityFunc);
    index = Asset::Sprite::add(Asset::Texture::wing);
    cpBodySetUserData(left_arm2, (void *) ((uint64_t) index));
    cpVect left_pos2 = left_pos + cpv(size * 2, 0);
    cpBodySetPosition(left_arm2, left_pos2);
    cpShape * left_arm_shape2 = cpSpaceAddShape(space, cpSegmentShapeNew(left_arm2, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(left_arm_shape2, CP_SHAPE_FILTER_NONE);

    cpBody *right_arm = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(-size, 0), cpv(size, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(right_arm, planetGravityVelocityFunc);
    index = Asset::Sprite::add(Asset::Texture::wing);
    cpBodySetUserData(right_arm, (void *) ((uint64_t) index));
    cpVect right_pos = pos + cpv(-size * 2, 0);
    cpBodySetPosition(right_arm, right_pos);
    cpShape * right_arm_shape = cpSpaceAddShape(space, cpSegmentShapeNew(right_arm, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(right_arm_shape, CP_SHAPE_FILTER_NONE);

    cpBody *right_arm2 = cpSpaceAddBody(space, cpBodyNew(ARM_MASS, cpMomentForSegment(ARM_MASS, cpv(-size, 0), cpv(size, 0), ARM_RADIUS)));
    cpBodySetVelocityUpdateFunc(right_arm2, planetGravityVelocityFunc);
    index = Asset::Sprite::add(Asset::Texture::wing);
    cpBodySetUserData(right_arm2, (void *) ((uint64_t) index));
    cpVect right_pos2 = right_pos + cpv(-size * 2, 0);
    cpBodySetPosition(right_arm2, right_pos2);
    cpShape * right_arm_shape2 = cpSpaceAddShape(space, cpSegmentShapeNew(right_arm2, cpv(-size, 0),  cpv(size, 0), ARM_RADIUS));
    cpShapeSetFilter(right_arm_shape2, CP_SHAPE_FILTER_NONE);

    cpSpaceAddConstraint(space, cpPivotJointNew2(rect, left_arm, cpv(-size, 0), cpv(size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(rect, left_arm, 0, 0));

    cpSpaceAddConstraint(space, cpPivotJointNew2(left_arm, left_arm2, cpv(-size, 0), cpv(size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(left_arm, left_arm2, 0, 0));

    cpSpaceAddConstraint(space, cpPivotJointNew2(rect, right_arm, cpv(size, 0), cpv(-size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(rect, right_arm, 0, 0));

    cpSpaceAddConstraint(space, cpPivotJointNew2(right_arm, right_arm2, cpv(size, 0), cpv(-size, 0)));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(right_arm, right_arm2, 0, 0));

    return rect;
}

cpBody * addUfo(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input)
{
    cpVect verts[] = {
        cpv(-size,-size),
        cpv(-size, size),
        cpv( size, size),
        cpv( size,-size),
    };

    uint index;

    // Add rectangle, main body
    cpBody * rect = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero, cpFloat(0.0))));
    index = Asset::Sprite::add(Asset::Texture::box);
    cpBodySetUserData(rect, (void *) ((uint64_t) index));
    cpBodySetVelocityUpdateFunc(rect, planetGravityVelocityFunc);
    cpBodySetPosition(rect, pos);

    cpShape * rect_shape = cpSpaceAddShape(space, cpPolyShapeNew(rect, 4, verts, cpTransformIdentity, 0.0));

    // Add wheel
    cpBody * wheel = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass/2, size - 1, size - 2, cpvzero)));
    index = Asset::Sprite::add(Asset::Texture::wheel);
    cpBodySetUserData(wheel, (void *) ((uint64_t) index));

    cpBodySetPosition(wheel, pos);

    cpShape * wheel_shape = cpSpaceAddShape(space, cpCircleShapeNew(wheel, size - 1, cpvzero));
    cpShapeSetFilter(wheel_shape, CP_SHAPE_FILTER_NONE);

    // Connect wheel to rect and add motor
    cpSpaceAddConstraint(space, cpPivotJointNew(rect, wheel, pos));
    cpConstraint * motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(rect, wheel, 0.0));

    // Connect I/O Channel to motor control
    ctrl.in = input;
    ctrl.plant = rect;
    cpConstraintSetUserData(motor, (cpDataPointer) &ctrl);

    // Set motor controller function
    cpConstraintSetPreSolveFunc(motor, ufoPresolve);

    return rect;
}
