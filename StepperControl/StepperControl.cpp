#include "StepperControl.h"
#include "Serial.h"

StepperControl :: StepperControl() : precision{
    {1,0,0,0}, {1,1,0,0,}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}} {
    //this->get_angle(90);
    
}

void StepperControl :: getSerial()  {
    while(!Serial)  System.println("Serial not initialized");

}

int StepperControl :: getAngle(int angle)  {
    
}

void StepperControl :: rotateClockwise(int coil1P, int coil1N, int coil2P, int coil2N, int serialData)  {
    int j = 0;
    final_angle = angle/0.6;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil1P, arr[j][0]);
        digitalWrite(coil2P, arr[j][1]);
        digitalWrite(coil1N, arr[j][2]);
        digitalWrite(coil2N, arr[j][3]);
        j = j<7?j++:0;
    }
}

void StepperControl :: rotateAnticlockwise(int coil1P, int coil1N, int coil2P, int coil2N, int serialData)  {
    int j = 0;
    final_angle = serialData/0.6;
    for(int i=0; i<final_angle; i++) {
        digitalWrite(coil2N, arr[j][3]);
        digitalWrite(coil1N, arr[j][2]);
        digitalWrite(coil2P, arr[j][1]);
        digitalWrite(coil1P, arr[j][0]);
        j = j!=8?j++:0;
    }
}

void StepperControl :: rotate(char dir, int serialPort, int coil1P, int coil1N, int coil2P , int coil2N ) {
    if(dir == 'c')   rotateClockwise(int coil1P, int coil1N, int coil2P, int coil2N, int serialData);
    else if(dir == 'a')  rotateAnticlockwise(int coil1P, int coil1N, int coil2P, int coil2N, int serialData);
    else System.println("Enter 'a' or 'c'");
}

void StepperControl :: rotateToAngle(int serialData, int coil1P = 4, int coil1N = 5, int coil2P = 6, int coil2N = 7)    {

}