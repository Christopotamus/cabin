#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>

/*
+all items/objects have properties (flammable, strong/weak, liquid/solid, passable/impassable,
        light/heavy, alive/dead, soluble/non-soluble, edible/inedible, drinkable,
        poisonous, explosive, sharp/dull/blunt, barricade-material, locked/unlocked, broken, meltable)
*/

using namespace std;

typedef enum object_property{
    obj_flammable,
    obj_strong,
    obj_weak,
    obj_big,    //doesn't fit in pocket
    obj_small, //fits in pocket
    obj_liquid,
    obj_passable,
    obj_impassable,
    obj_light,
    obj_heavy,
    obj_soluble,
    obj_edible,
    obj_drinkable,
    obj_poisonous,
    obj_explosive,
    obj_sharp,
    obj_dull,
    obj_blunt,
    obj_barricade,
    obj_broken,
    obj_meltable,
    obj_obtainable,
    obj_openable,
    property_count,
}object_property;


//an example of a knife: strong, small, passable, light, sharp/dull
//a candle: flammable, weak, small, passable, light, blunt, meltable
//an Axe: strong, big, passable, heavy, sharp/dull, obtainaable
//a wall: strong, big, impassable, heavy, flammable

class object
{
    public:
        string name;
        object(string objectName);
        virtual ~object();

        void setCoords(int x, int y);
        bool checkProperty(int i);
        void draw();

    protected:
    private:

        int prop_itr;
        int coordX, coordY;
        int properties[24]; //boolean array of the properties

        void switchTextureCoords();
        void addProperty(object_property p);
        void removeProperty(object_property p);

};

#endif // OBJECT_H
