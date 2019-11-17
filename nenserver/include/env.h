//

#include "chipmunk/chipmunk.h"
#include "SFML/Graphics.hpp"
#include "tables.h"

#define ARM_MASS 0.001
#define ARM_RADIUS 1
#define P -25

typedef struct
{
    cpVect *in;
    cpBody *plant;
} Control_t;

void envStep(cpSpace *, void *, double, cpVect*, cpVect*);

cpBody * addSat(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input);

cpBody * addUfo(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input);
