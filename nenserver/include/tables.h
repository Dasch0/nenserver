#include "SFML/Graphics.hpp"
#include "chipmunk/chipmunk.h"

#define MAX_ENTITIES 100

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

typedef struct
{
    uint16_t index;
    sf::Texture table[MAX_ENTITIES];
} textureTable_t;
extern textureTable_t textureTable;
