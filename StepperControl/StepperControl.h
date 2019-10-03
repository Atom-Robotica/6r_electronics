#ifndef StepperControl
#define StepperControl

#include "Arduino.h"

class StepperControl    {
    int angle;
    char dir;
    int serialData;         //Data recieved from serial input.
    int serialPort;         //Serial port used.(0 by default in case of Arduino Uno, more than 1 in case of Mega)
    int precision[8][4];    //Precision is set as 0.6 degree/step. Default of motor is 1.8 degree/step
    int coil1P;             //Digital pin on board to energize coil 1 positive
    int coil1N;             //Digital pin on board to energize coil 1 negative
    int coil2P;             //Digital pin on board to energize coil 2 positive
    int coil2N;             //Digital pin on board to energize coil 2 negative
    int getSerial();        //Private function to decode serial data recieved
    public:

    StepperControl();
    //StepperControl(int angle);
    void getAngle();
    void rotateClockwise(int serialData = 360; int coil1P, int coil1N, int coil2P, int coil2N);
    void rotateAnticlockwise(int serialData = 360, int coil1P, int coil1N, int coil2P, int coil2N);
    void rotate(char dir, int serialPort = 0, int coil1P = 4, int coil1N = 5, int coil2P = 6, int coil2N = 7);
    void rotateToAngle(int serialData, int coil1P = 4, int coil1N = 5, int coil2P = 6, int coil2N = 7)
};
#endif