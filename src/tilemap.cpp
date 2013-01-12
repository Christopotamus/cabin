#include "tilemap.h"

tilemap::tilemap()
{
    //ctor
    for(int x = 0; x < 128; x++)
    for(int y = 0; y < 128; y++){
            tile[x][y].tile_type = (tile_types)0;
    }

    srand(time(NULL));
    xSeed = rand();
    ySeed = rand();
}
tilemap::tilemap(int seed)
{
    //ctor
    srand(seed);
    //ctor
    for(int x = 0; x < 128; x++)
    for(int y = 0; y < 128; y++){
        tile[x][y].tile_type = tile_grass;
    }
    xSeed = rand();
    ySeed = rand();

    //pick a few random dirt spots
    int numSpots = rand() % 35;

    for(int i = 0; i < numSpots; i++){
        int h = rand() % 128;
        int k = rand() % 128;
        int radius = rand() % 5+2;
        for(int x = h - radius+1; x < h+radius; x++){
            for(int y = k - radius+1; y < k + radius; y++){
                if((pow(abs(x-h),2) + (pow(abs(y-k),2))) <= radius*radius)
                    tile[x][y].tile_type = tile_dirt;
            }
        }
    }
}

tilemap::~tilemap()
{
    //dtor
}


void tilemap::drawMap(int x, int y, int x2, int y2){ //draw map starting at x,y and ending at x2,y2
    glPushMatrix();
    for(int coordX = x; coordX <= x2; coordX++){
        glPushMatrix();
        for(int coordY = y; coordY <= y2; coordY++){

            //if out of range draw blank tile
            if(outOfRange(coordX) || outOfRange(coordY)){
                ///draw blank tile
                glColor3d(0,0,0);

                glBegin(GL_QUADS);
                    glVertex2d(0,0);
                    glVertex2d(0,32);
                    glVertex2d(32,32);
                    glVertex2d(32,0);
                glEnd();

                glColor3d(1,1,1);
                glBegin(GL_LINE_LOOP);
                    glVertex2d(0,0);
                    glVertex2d(0,32);
                    glVertex2d(32,32);
                    glVertex2d(32,0);
                glEnd();
                glTranslated(0,31,0);

            }else{
                ///draw real tile

                setTextCoords(tile[coordX][coordY].tile_type);

                glBegin(GL_QUADS);
                    glVertex2d(0,0);
                    glVertex2d(0,32);
                    glVertex2d(32,32);
                    glVertex2d(32,0);
                glEnd();

                glColor3d(0,0,0);
                glBegin(GL_LINE_LOOP);
                    glVertex2d(0,0);
                    glVertex2d(0,32);
                    glVertex2d(32,32);
                    glVertex2d(32,0);
                glEnd();
                glTranslated(0,31,0);

            }
        }
        glPopMatrix();
        glTranslated(31,0,0);
    }
    glPopMatrix();

}
bool tilemap::outOfRange(int coord){
    if(coord < 0 || coord >= 128)
        return true;
    else
        return false;
}
void tilemap::setTextCoords(tile_types type){
    //for now we'll just switch type and set a color
    switch(type){
        case tile_mud:
            glColor3ub(115, 92, 18);
            break;
        case tile_dirt:
            glColor3ub(138, 110, 69);
            break;
        case tile_grass:
            glColor3ub(63, 155, 11);
            break;
        case tile_stone:
            glColor3ub(173, 165, 135);
            break;
    };

}

void tilemap::console_drawMap(int x, int y, int x2, int y2){ //draw map starting at x,y and ending at x2,y2

}
inline float tilemap::integerNoise2(int x, int y){
    x += xSeed;
    y += ySeed;
    int n = x + y * 57;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 2147483648) / 1073741824.0);
}
