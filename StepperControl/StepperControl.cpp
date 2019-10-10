#include "StepperControl.h"

StepperControl :: StepperControl(int coil1P, int coil1N, int coil2P, int coil2N) : precision{
    {1,0,0,0}, {1,1,0,0,}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}} {
    this->coil1P = coil1P;
    this->coil1P = coil1N;
    this->coil1P = coil2P;
    this->coil1P = coil2N;
    pinMode(coil1P, OUTPUT);
    pinMode(coil1N, OUTPUT);
    pinMode(coil2P, OUTPUT);
    pinMode(coil2N, OUTPUT);
    
}

int StepperControl :: getSerial()  {
    while(!Serial)  Serial.println("Serial not initialized");

}

int StepperControl :: getAngle(int angle)  {
    
}

void StepperControl :: rotateClockwise(int delay, int serialData)  {
    int j = 0;
    int final_angle = serialData/0.6;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil1P, precision[j][0]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2N, precision[j][3]);
        delayMicroseconds(delay);
        j = j<7?j++:0;
    }
}

void StepperControl :: rotateAnticlockwise(int delay, int serialData)  {
    int j = 0;
    int final_angle = serialData/0.6;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil2N, precision[j][3]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1P, precision[j][0]);
        delayMicroseconds(delay);
        j = j!=7?j++:0;
    }
}

void StepperControl :: rotate(char dir, int serialPort) {
    this->coil2P = coil2P;
    if(dir == 'c')   rotateClockwise(serialData);
    else if(dir == 'a')  rotateAnticlockwise(serialData);
    else Serial.println("Enter 'a' or 'c'");
}

void StepperControl :: rotateToAngle(int serialData)    {

}