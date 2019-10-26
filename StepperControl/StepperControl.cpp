#include "StepperControl.h"

StepperControl :: StepperControl(int coil1P, int coil1N, int coil2P, int coil2N) : precision{
    {1,0,0,0}, {1,1,0,0,}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}} {
    this->coil1P = coil1P;
    this->coil1P = coil1N;
    this->coil1P = coil2P;
    this->coil1P = coil2N;
    this->index = 0;
    this->angle = 0;
    this->cur_angle = 0;
    pinMode(coil1P, OUTPUT);
    pinMode(coil1N, OUTPUT);
    pinMode(coil2P, OUTPUT);
    pinMode(coil2N, OUTPUT);
    
}

int StepperControl :: getSerial()  {
    while(!Serial)  Serial.println("Serial not initialized");

}

int StepperControl :: getAngle(int X, int Y)  {
    XVal = analogRead(X) - 346;
    YVal = analogRead(Y) - 340;
    float angle = atan2(YVal, XVal);
    angle = angle*180/3.1415926;
    if(angle<0)
        angle = 360 - abs(angle);
    return int(angle);
}

void StepperControl :: rotateAnticlockwise(int delay, int serialData)  {
    int j = index;
    int final_angle = serialData/0.6;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil1P, precision[j][0]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2N, precision[j][3]);
        delayMicroseconds(delay);
        index = j;

        j = j<7?j++:0;
    }
    int cur_angle = final_angle;
    digitalWrite(coil1P, 0);
    digitalWrite(coil2P, 0);
    digitalWrite(coil1N, 0);
    digitalWrite(coil2N, 0);
}

void StepperControl :: rotateClockwise(int delay, int serialData)  {
    int j = index;
    int final_angle = serialData/0.6;
    for(int i=final_angle; i>0; i++) {
        digitalWrite(coil1P, precision[j][0]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2N, precision[j][3]);
        delayMicroseconds(delay);
        index = j;
        j = j!=0?j--:7;
    }
    digitalWrite(coil1P, 0);
    digitalWrite(coil2P, 0);
    digitalWrite(coil1N, 0);
    digitalWrite(coil2N, 0);
}

void StepperControl :: rotate(char dir, int serialPort) {
    this->coil2P = coil2P;
    if(dir == 'c')   rotateClockwise(serialData);
    else if(dir == 'a')  rotateAnticlockwise(serialData);
    else Serial.println("Enter 'a' or 'c'");
}

void StepperControl :: rotateToAngle(int delay, int serialData, int X, int Y)    {
    if(serialData>getAngle(X, Y))   
        rotateClockwise(int delay, abs(serialData-getAngle(X, Y)));
    else if(erialData<getAngle(X, Y))
        rotateAnticlockwise(int delay, abs(serialData-getAngle(X, Y));
}