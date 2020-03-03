#ifndef __SPECIES_HEADER
#define __SPECIES_HEADER

#include <cstdint>
#include <assert.h>
#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_structs.h"
#include "zmq.h"
#include "env.h"

namespace nenv
{
    template <class Command, class Signal, int maxCount>
    class SpeciesTable
    {
    public:
        // TODO: Improve access control of members
        uint64_t _count;

        // Networking members
        void *_zmqContext;
        void *_sockets[maxCount];
        zmq_msg_t _inMsgs[maxCount];
        zmq_msg_t _outMsgs[maxCount]

        // Environment members
        cpSpace *_space;
        Command _commands[maxCount];
        Signal _signals[maxCount];
        cpBody _cores[_count]s[maxCount];
        cpBody _wheels[_count]s[maxCount];
        cpSimpleMotor motors[maxCount];
        cpPivotJoint pivots[maxCount];
        


        SpeciesTable(void * zmqContext, cpSpace * space) :
            _count(0), _zmqContext(zmqContext), _space(space) {}

        handle add(void)
        {
            // TODO: Improve error handling
            assert(unlikely(_count>=maxCount));

            initNetworking();

            initPhysical();

            _count++;
            return _count;
        }

        status recv(void)
        {
            status ret = 0;
            for(int i = 0; i < _count; i++)
            {
                ret |= zmq_msg_recv(_inMsgs[i], _sockets[i], 0);
            }
            return ret;
        }

        status 

        status send(void)
        {
            status ret = 0;
            for(int i = 0; i < _count; i++)
            {
                ret |= zmq_msg_send(_outMsgs[i], _sockets[i], 0);
            }
            return ret;
        }

        ~SpeciesTable(void) {}

    private:
        void initNetworking(void)
        {
            _sockets[_count] = zmq_socket(_zmqContext, ZMQ_REP);
            int ret = 0;
            ret |= zmq_bind(_sockets[_count], "tcp://*:5555");
            ret |= zmq_msg_init_data(_inMsgs[_count], _commands[_count], sizeof(_commands[_count]), NULL, NULL);
            ret |= zmq_msg_init_data(_outMsgs[_count], _signals[_count], sizeof(_signals[_count]), NULL, NULL);

            assert(unlikely(ret < 0));
        }

        void initPhysical(void)
        {
            // TODO: clean up hardcoded parameters
            cpVect coreVerts[] = {
                cpv(-5,0),
                cpv(5, 0),
                cpv(0, 5),
            };
            cpFloat radius = 2.5;
            cpFloat mass = 5;
            uint64_t index;

            _cores[_count] = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, coreVerts, cpvzero, 0.0)));
            index = Asset::Sprite::add(Asset::Texture::box);
            cpBodySetUserData(_cores[_count], (void *) index);
            cpBodySetVelocityUpdateFunc(_cores[_count], envVelocityFunc);
            cpBodySetPosition(_cores[_count], pos);
            cpShape * coreShape = cpSpaceAddShape(space, cpPolyShapeNew(_cores[_count], 3, coreVerts, cpTransformIdentity, 0.0));
            cpShapeSetFilter(coreShape, CP_SHAPE_FILTER_NONE);

            _wheels[_count] = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, coreVerts, cpvzero, 0.0)));
            index = Asset::Sprite::add(Asset::Texture::wheel);
            cpBodySetUserData(_wheels[_count], (void *) index);
            cpBodySetVelocityUpdateFunc(_wheels[_count], envVelocityFunc);
            cpBodySetPosition(_wheels[_count], pos);
            cpShape * wheelShape = cpSpaceAddShape(space, cpCircleShapeNew(_wheels[_count], 2.5, cpvzero));
            cpShapeSetFilter(wheelShape, CP_SHAPE_FILTER_NONE);

            _pivots[_count] = cpSpaceAddConstraint(space, cpPivotJointNew(_cores[_count], _wheels[_count], pos));
            _motor[_count] = cpSpaceAddConstraint(space, cpSimpleMotorNew(_cores[_count], _wheels[_count], 0.0));

            // TODO: improve status codes
            return 0;
        }
    };

    namespace Swimmer
    {

    }
}

#endif //__SPECIES_HEADER
