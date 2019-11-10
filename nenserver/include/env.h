//

#include "chipmunk/chipmunk.h"
#include "SFML/Graphics.hpp"

#define ARM_MASS 0.001
#define ARM_RADIUS 1
#define P -50

typedef struct
{
    cpVect *in;
    cpBody *plant;
} Control_t;

void envStep(cpSpace *, void *, double);

cpBody * addSat(cpSpace *space, cpFloat size, cpFloat mass, cpVect pos, cpVect *input, spriteTable_t *sprites);
