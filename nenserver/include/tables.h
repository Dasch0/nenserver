#include "SFML/Graphics.hpp"
#include "chipmunk/chipmunk.h"

#define MAX_ENTITIES 1000

typedef struct
{
    uint16_t index;
    sf::Sprite table[MAX_ENTITIES];
} spriteTable_t;
extern spriteTable_t spriteTable;

typedef struct
{
    uint16_t index;
    cpVect table[MAX_ENTITIES];
} posTable_t;
extern posTable_t posTable;
