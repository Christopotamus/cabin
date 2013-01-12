#include "human.h"

human::human(int seed)
{
    srand(seed);
    //ctor
    blood = 5.0; // amount of blood in quarts
    stamina = 1000; // amount of energy.isBroken = true;sleep to replenish
    hunger = 100; //eat to replenish
    thirst = 100; //how thirsty are you
    if(rand() %100 < 30)
        badVision = 1; // does the character have bad vision? (if yes.isBroken = true;start with glasses)
    else
        badVision = 0;
    bodyTemp = 36.8; //36.8 Celsius
    asleep = false; // is the character sleeping or not

    if(rand() % 10 <= 3)
        illness = (illness_type)(rand() % ((int)illness_COUNT - 3)); // you generally start out with none
    else
        illness = (illness_type)7;

    leftForearm.isBroken = false;
    rightForearm.isBroken = false;
    leftWrisst.isBroken = false;
    rightWrist.isBroken = false;
    leftShoulder.isBroken = false;
    rightShoulder.isBroken = false;
    leftHip.isBroken = false;
    rightHip.isBroken = false;
    leftKnee.isBroken = false;
    rightKnee.isBroken = false;
    leftAnkle.isBroken = false;
    rightAnkle.isBroken = false;
    neck.isBroken = false;
    head.isBroken = false;;
    coordX = coordY = 0;
}

human::~human()
{
    //dtor
}

void human::setCoords(int x, int y){
    coordX = x;
    coordY = y;
}
void human::printStats(){
    printf("Blood %f\nStamina %i\nHunger %i\nThirst %i\nVision%i\nTemperature %f\nSleeping %i\n", blood, stamina, hunger, thirst, (int)badVision, bodyTemp,(int)asleep);
    printIllnessName();
}
void human::printIllnessName(){
    switch(illness){
        case 0:
            printf("Diabeetus\n");
            break;
        case 1:
            printf("The Flu\n");
            break;
        case 2:
            printf("Asthma\n");
            break;
        case 3:
            printf("Arthritis\n");
            break;
        case 4:
            printf("Dystentary\n");
            break;
        case 5:
            printf("Pneumonia\n");
            break;
        case 6:
            printf("Zombie Infection!\n");
            break;
        case 7:
            printf("You're as healthy as a butterfly!\n");
            break;
        default:
            break;
    };
}
void human::draw(){

}
