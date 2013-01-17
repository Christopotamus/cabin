#ifndef GAME_H
#define GAME_H
#include "human.h"
#include "tilemap.h"
#include "object.h"
#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>

#define NUM_OBJECTS 4

typedef enum gamestate{
    gs_mainMenu,
    gs_loading,
    gs_options,
    gs_playing,
    gs_gameOver,
    gs_quit,

} gamestate;

class game
{
    public:
        game();
        virtual ~game();

        void draw();
        void update();
    protected:
    private:

        gamestate currentState;
        vector<object*> objList;

        float mapCenterX;
        float mapCenterY;
        float scrollVelX, scrollVelY;

        bool scrollUp, scrollDown, scrollLeft, scrollRight;

        int gameSeed;

        sf::Texture spriteSheet;
        human *p;
        tilemap *m;
        object * objects[4];

        void loadGame();
        void loadObjects();
        int loadTexture();
        void genBuilding(tilemap *m);

        void drawLoading();
        void drawPlaying();
        void drawMenu();
        void drawgameOver();
        void drawOptions();
        void drawWalls();
        void drawMap();

        ///logic functions

        void checkEvents();
        void scrollMap();
        void updatePlaying();
};


#endif // GAME_H
