#ifndef HUMAN_H
#define HUMAN_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct bone{
    bool isBroken;
    bool isSevered;
};

typedef enum illness_type{
    illness_diabeetus,
    illness_flu,
    illness_asthma,
    illness_arthritis,
    illness_dysentary,
    illness_pneumonia,
    illness_infection, // zombie infection
    illness_none,
    illness_COUNT,
}illness_type;

class human
{
    public:
        human(int seed);
        virtual ~human();

        void printStats(); //debug function
        void printIllnessName();

        void setCoords(int x, int y);
    protected:
    private:

        float blood; // amount of blood in liters
        int stamina; // amount of energy, sleep to replenish
        int hunger; //eat to replenish
        int thirst; //how thirsty are you
        bool badVision; // does the character have bad vision? (if yes, start with glasses)
        float bodyTemp; //36.8 Celsius
        bool asleep; // is the character sleeping or not?
        illness_type illness; // you generally start out with none

        int coordX, coordY;

        bone leftForearm, rightForearm, leftWrisst, rightWrist, leftShoulder,
        rightShoulder, leftHip, rightHip,leftKnee,rightKnee,leftAnkle,rightAnkle,neck,head;

        void draw();
};

#endif // HUMAN_H
