#include "StepperControl.h"

StepperControl :: StepperControl(int coil1P, int coil1N, int coil2P, int coil2N) : precision{
    {1,0,0,0}, {1,1,0,0,}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}} {
    this->coil1P = coil1P;
    this->coil1N = coil1N;
    this->coil2P = coil2P;
    this->coil2N = coil2N;
    this->index = 0;
    this->angle = 0;
    //this->cur_angle = 0;
    pinMode(coil1P, OUTPUT);
    pinMode(coil1N, OUTPUT);
    pinMode(coil2P, OUTPUT);
    pinMode(coil2N, OUTPUT);
    
}

int StepperControl :: getSerial()  {
    while(!Serial)  Serial.println("Serial not initialized");

}

int StepperControl :: getAngle(int X, int Y)  {
    int XVal = analogRead(X) - 346;
    int YVal = analogRead(Y) - 340;
    float angle = atan2(YVal, XVal);
    angle = angle*180/3.1415926;
    if(angle<0)
        angle = 360 - abs(angle);
    return int(angle);
}

void StepperControl :: rotateAnticlockwise(int del, int serialData)  {
    int j = index;
    int final_angle = serialData/0.9;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil1P, precision[j][0]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2N, precision[j][3]);
        delayMicroseconds(del);
        index = j;
        if(j==7)   
            j = 0;
        else
            j=j+1;
        //j = j<7?j++:0;
    }
    int cur_angle = final_angle;
    digitalWrite(coil1P, 0);
    digitalWrite(coil2P, 0);
    digitalWrite(coil1N, 0);
    digitalWrite(coil2N, 0);
}

void StepperControl :: rotateClockwise(int del, int serialData)  {
    int j = index;
    int final_angle = serialData/0.9;
    for(int i=final_angle; i>0; i--) {
        digitalWrite(coil1P, precision[j][0]);
        digitalWrite(coil2P, precision[j][1]);
        digitalWrite(coil1N, precision[j][2]);
        digitalWrite(coil2N, precision[j][3]);
        delayMicroseconds(del);
        index = j;
        if(j==0)   
            j = 7;
        else
            j=j-1;
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

void StepperControl :: rotateToAngle(int del, int X, int Y, int serialData)    {
    int a = getAngle(X, Y);
    int diff = serialData - a;
    if((diff<=180) && (diff>=0))    
        rotateClockwise(del, abs(diff));
    
    else if(diff>180)   
        rotateAnticlockwise(del, abs(diff));
    
    else if(diff<=-180)
        rotateAnticlockwise(del, abs(diff));
    
    else if((diff>-180) && (diff<=0))
        rotateClockwise(del, abs(diff));
    
    /*
    if(serialData>getAngle(X, Y))   {

        rotateClockwise(int del, abs(serialData-getAngle(X, Y)));
    }
    else if(erialData<getAngle(X, Y))
        rotateAnticlockwise(int del, abs(serialData-getAngle(X, Y));
    */
}