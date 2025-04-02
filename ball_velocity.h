#pragma once


class BallVelocity
{
    int sensor1 = 0;
    int sensor2 = 0;
    int Time1 = 0;
    int Time2 = 0;


    public:

    BallVelocity(int pin1, int pin2, int t1, int t2);
    void calculateVelocity();

};