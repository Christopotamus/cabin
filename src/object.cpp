#include "object.h"

object::object(string objectName){
    //ctor
    coordX = 0;
    coordY = 0;
    prop_itr = 0;
    //load object properties for object type
    //find filename that has EXACTLY objectName in it
    ifstream objFile;
    char *bit = new char[200];


    objFile.open((string("./objects/")+objectName + string(".orz")).c_str(), ios::in);

    if(objFile.is_open()){
        //cout << "Building " << (string("objects/")+objectName).c_str() << endl;
        //read first bit
        if(objFile.good()){
            objFile.get(bit, 2);
            //cout << "Name is: " << bit << " characters long" << endl;
            objFile.get(bit,atoi(bit)+1);
            name = bit;
            //cout << "The name is:" << name << endl;
            while(objFile.good()){
                objFile.get(*bit);
                properties[prop_itr++] = atoi(bit);
            }
        }else
            objFile.close();

    }

    delete bit;

}

object::~object(){
    //dtor
}
bool object::checkProperty(int i){
    return properties[i];
}
void object::setCoords(int x, int y){
    coordX = x;
    coordY = y;
}
void object::draw(){
    glPushMatrix();

    glTranslated(coordX*31,coordY*31,0);
    switchTextureCoords();
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
    //glTranslated(0,31,0);

    glPopMatrix();
}
void object::addProperty(object_property p){
}
void object::removeProperty(object_property p){
}
void object::switchTextureCoords(){
    if(name == "wall"){
        glColor3ub(209,178,111);

    }else if(name == "woodfloor")
        glColor3ub(173,129,80);

}
