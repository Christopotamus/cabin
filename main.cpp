#include <SFML/Graphics.hpp>
#include "game.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/OpenGL.hpp>

using namespace std;

vector<object*> objList;

float mapCenterX;
float mapCenterY;

int gameSeed = 1254;
//rand();


void genBuilding(tilemap *m){
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
void drawWalls(){

    for(int i = 0; i < objList.size(); i++){
        //draw the object
        objList[i]->draw();

    }
}
int main()
{
    srand(gameSeed);

    mapCenterX = mapCenterY = 0;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rogue Zombies");


    human p(gameSeed);
    //p.printStats();
    tilemap m(gameSeed);
    object *objects[4];

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
    for(int i = 0; i < 4; i++){
        if(objects[i]->checkProperty(0) == true)
            cout << objects[i]->name << " is flammable" << endl;
        else
            cout << objects[i]->name << " is NOT flammable" << endl;

    }
/// END INITIALIZE OBJECTS
/// lets auto-gen a building on the tilemap

    genBuilding(&m);
    // Set color and depth clear value

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::W:
                        mapCenterY += 1;
                        break;
                    case sf::Keyboard::S:
                        mapCenterY -= 1;
                        break;
                    case sf::Keyboard::A:
                        mapCenterX -= 1;
                        break;
                    case sf::Keyboard::D:
                        mapCenterX += 1;
                        break;
                    case sf::Keyboard::Q:
                        mapCenterX -= 1;
                        mapCenterY += 1;
                        break;
                    case sf::Keyboard::E:
                        mapCenterX += 1;
                        mapCenterY += 1;
                        break;
                    case sf::Keyboard::Z:
                        mapCenterX -= 1;
                        mapCenterY -= 1;
                        break;
                    case sf::Keyboard::C:
                        mapCenterX += 1;
                        mapCenterY -= 1;
                        break;
                };
            }
        }


        glClearColor(0.f, 0.f, 0.f, 0.f);

        glDisable(GL_TEXTURE_2D | GL_DEPTH_TEST);
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glScalef(1.0f,-1.0f,1.0f);
        glOrtho(0, 1280, 0, 720, -1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();


        glClear(GL_COLOR_BUFFER_BIT);
        //window.clear();
        glPushMatrix();
        m.drawMap((mapCenterX),mapCenterY,mapCenterX + 41, mapCenterY + 23);
        glPopMatrix();
        //draw walls
        glPushMatrix();
        glTranslated(-(mapCenterX*31), -(mapCenterY*31),0);
        drawWalls();
        glPopMatrix();


        //window.draw(shape);
        glPopMatrix();

        window.display();
    }
    return 0;
}
