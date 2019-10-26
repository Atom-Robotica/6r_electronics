#ifndef STEPPERCONTROL_H
#define STEPPERCONTROL_H

#include "Arduino.h"

class StepperControl    {
    int angle;
    char dir;
    int delay;
    int serialData;         //Data recieved from serial input.
    int serialPort;         //Serial port used.(0 by default in case of Arduino Uno, more than 1 in case of Mega)
    int precision[8][4];    //Precision is set as 0.6 degree/step. Default of motor is 1.8 degree/step
    int coil1P;             //Digital pin on board to energize coil 1 positive
    int coil1N;             //Digital pin on board to energize coil 1 negative
    int coil2P;             //Digital pin on board to energize coil 2 positive
    int coil2N;             //Digital pin on board to energize coil 2 negative
    int getSerial();        //Private function to decode serial data recieved
    int index;
    public:

    StepperControl(int coil1P, int coil1N, int coil2P, int coil2N);
    //StepperControl(int angle);
    int getAngle(int X, int Y);
    void rotateClockwise(int delay = 2000, int serialData = 360);
    void rotateAnticlockwise(int delay = 2000,int serialData = 360);
    void rotate(char dir, int serialPort = 0);
    void rotateToAngle(int serialData = 0);
};

#endif