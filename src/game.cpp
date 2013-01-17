#include "game.h"

game::game()
{
    //ctor

    currentState = gs_loading;
    mapCenterX = mapCenterY = scrollVelX = scrollVelY = 0;

}

game::~game()
{
    //dtor
}

void game::loadGame(){


    //objects = new object[4];

    gameSeed = 125;

    srand(gameSeed);

    p = new human(gameSeed);
    //p.printStats();
    m = new tilemap (gameSeed);

    mapCenterX = mapCenterY = 0;

    loadTexture();
    loadObjects();

    genBuilding(m);

    currentState = gs_mainMenu;
}
void game::loadObjects(){
    /// INITIALIZE SOME OBJECTS, we'll throw this into a function later

    ifstream objlist;
    objlist.open("objects/itemlist.txt");
    int i = 0;

    if(objlist.is_open()){
        while(objlist.good()){
            //read in file list and load each object
            string line;
            getline(objlist, line);
            objects[i] = new object(line);
            i++;
        }
    }else{
        cout << "error opening file" << endl;
    }
    objlist.close();
    //p.printStats();
    for(int i = 0; i < NUM_OBJECTS; i++){
        if(objects[i]->checkProperty(0) == true)
            cout << objects[i]->name << " is flammable" << endl;
        else
            cout << objects[i]->name << " is NOT flammable" << endl;

    }
    /// END INITIALIZE OBJECTS
}
int game::loadTexture(){
    if(!spriteSheet.loadFromFile("texture.png")){

        return -1;
    }
}
void game::genBuilding(tilemap *m){
    //pick a random centerpoint for building

    int coordX, coordY, width, height;

    width = rand () % 10 + 4;
    height = rand() % 10 + 4;
    width = (width % 2 == 0) ? width : width+1;
    height = (height % 2 == 0) ? height : height+1;

    coordX = rand() % (128 - width) + width;
    coordY = rand() % (128 - height) + height;


    //coordX = width;
    //coordY = height+1;
    //coordX = (coordX %2 == 0) ? coordX : coordX +1;
    //coordY = (coordY %2 == 0) ? coordY : coordY +1;

    //go to centerpoint and add walls around it

/// TO-DO: LINK OBJECTS INSIDE THE MAP TILES THEY RESIDE IN
    for(int x = 0; x <= width; x++){
        //create a wall at point
        object * wall = new object("wall");
        wall->setCoords((coordX - width)+ x, (coordY-1));
        objList.push_back(wall);
        wall = NULL;

        wall = new object("wall");
        wall->setCoords((coordX - width) + x, coordY-height-1);
        objList.push_back(wall);
        wall= NULL;

    }
    for(int y = 0; y < height-1; y++){
        //create a wall at point
        object * wall = new object("wall");
        wall->setCoords((coordX), (coordY - height)+ y);
        objList.push_back(wall);
        wall = NULL;

        wall = new object("wall");
        wall->setCoords(coordX-width, (coordY - height) + y);
        objList.push_back(wall);
        wall=NULL;
    }

    //add wood flooring
    for(int x = 0; x < width-1; x++)
        for(int y = 1; y < height; y++){
            object *floor = new object("woodfloor");
            floor->setCoords(x+(coordX-width)+1, y+(coordY-height-1));
            objList.push_back(floor);
            floor = NULL;

        }
}
void game::draw(){
    switch(currentState){
        case gs_loading:
            break;
        case gs_mainMenu:
            break;
        case gs_options:
            break;
        case gs_playing:
            drawPlaying();
            break;
        case gs_gameOver:
            break;
        case gs_quit:
            break;
    };

}
void game::drawLoading(){

}
void game::drawPlaying(){
    drawMap();
    glPushMatrix();
    int offsetX =  (int)(31*mapCenterX) % 31;
    int offsetY = (int)(31*mapCenterY) % 31;
    glTranslated(mapCenterX/31 - offsetX, mapCenterY/31 - offsetY,0);
    glTranslated(-(mapCenterX*31)+offsetX, -(mapCenterY*31)+offsetY,0);
    drawWalls();
    glPopMatrix();
}
void game::drawMenu(){
}
void game::drawgameOver(){
}
void game::drawOptions(){
}
void game::drawWalls(){

    for(int i = 0; i < objList.size(); i++){
        //draw the object
        objList[i]->draw();
    }
}
void game::drawMap(){


    glPushMatrix();
    int offsetX =  (int)(31*mapCenterX) % 31;
    int offsetY = (int)(31*mapCenterY) % 31;
    glTranslated(mapCenterX/31 - offsetX, mapCenterY/31 - offsetY,0);
    m->drawMap((mapCenterX),mapCenterY,mapCenterX + 41, mapCenterY + 23);

    glPopMatrix();

}

/// LOGIC FUNCTIONS

void game::checkEvents(){
    scrollLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    scrollRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    scrollUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    scrollDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

}
void game::scrollMap(){
    if(scrollLeft)
        scrollVelX += -0.25;
    if(scrollRight)
        scrollVelX += 0.25;
    if(scrollUp)
        scrollVelY += 0.25;
    if(scrollDown)
        scrollVelY += -0.25;

    mapCenterX += scrollVelX;
    mapCenterY += scrollVelY;
    scrollVelX = scrollVelY = 0;
}
void game::updatePlaying(){
    scrollMap();

}
void game::update(){
    switch(currentState){
        case gs_loading:
            loadGame();
            break;
        case gs_mainMenu:
            currentState = gs_playing;
            break;
        case gs_options:
            break;
        case gs_playing:
            checkEvents();
            updatePlaying();

            break;
        case gs_gameOver:
            break;
        case gs_quit:
            break;
    };
}
