#pragma once
#include <vector>
#include <Arduino.h>

class SensorMaster
{
    std::vector<int> sensors;


    public:
    void init_list(int sensors_arr[]);
    int getOutput(int pin_number);
    int poll();
    void display();
};