#ifndef TILEMAP_H
#define TILEMAP_H

#include "object.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <SFML/OpenGL.hpp>

#define ITEMS_PER_TILE 5

using namespace std;

typedef enum tile_types{
    tile_mud,
    tile_dirt,
    tile_grass,
    tile_stone,
}tile_types;

struct map_cell{
    tile_types tile_type;
    object *items[ITEMS_PER_TILE];
};

class tilemap{
    public:
        tilemap(int seed); // load a specific map
        tilemap(); //generate a random map

        virtual ~tilemap();

        void drawMap(int x, int y, int x2, int y2); //draw map starting at x,y and ending at x2,y2
        void console_drawMap(int x, int y, int x2, int y2); //draw map starting at x,y and ending at x2,y2

    protected:
    private:
        map_cell tile[128][128];
        int xSeed, ySeed;

        bool outOfRange(int coord);
        void setTextCoords(tile_types type);

        ///perlin noise
        inline float integerNoise2(int x, int y);
};

#endif // TILEMAP_H
