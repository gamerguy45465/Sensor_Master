#include "sensor_master.h"
#include <vector>
#include <Arduino.h>
#include <thread>
#include <chrono>
#include <mutex>


bool stopTimer = false;

int time_track = 0;

std::mutex timer_mutex; 

bool debug = false;

void SensorMaster::init_list(int sensors_arr[])
{
    for(int i = 0; i <= (sizeof(sensors_arr)/sizeof(int)); i++)
        this->sensors.push_back(sensors_arr[i]); // Copy all elements from given array into the main Sensors Vector

    for(int sensor : this->sensors)
    {
        pinMode(sensor, INPUT); // Set the pinmodes for all pins in the given vector

    }
}

int SensorMaster::getOutput(int pin_number)
{
    for(int sensor : this->sensors)
    {
        if(sensor == pin_number)
            return digitalRead(sensor);
    }

    return -1; // Will return -1 if there is an error, or the pin was not found
    
}

void SensorMaster::display()
{
    for(int pin : this->sensors)
        Serial.println(pin); // Print all of the pins in the Sensors Vector
}


void stopwatch()
{
    while(stopTimer == false || debug == true)
    {
        timer_mutex.lock();
        time_track++;


        timer_mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


void getValues(int& pin1, int& pin2, int& time1, int& time2, std::vector<int> sensors)
{

    while((pin1 != 0 || pin2 != 0))
    {
        Serial.println(time_track);


       /* if(debug == true && (pin1 != 0 && pin2 != 0))
        {
            pin1 = 0;
            pin2 = 0;
        } */ 

    
        for(int i = 0; i < sensors.size(); i++)
        {
            int value = digitalRead(sensors[i]);
            if(pin1 == 0 && pin2 == 0)
                break;


            if(value == 0)
            {
                Serial.println("It entered this if statement");
                if(pin1 == 1)
                {
                    timer_mutex.lock();
                    pin1 = value;
                    stopTimer = true;
                    time1 = time_track;
                    time_track = 0;
                    stopTimer = false;
                    timer_mutex.unlock();
                    continue;
                    

                }

                else if(pin2 == 1)
                {
                    timer_mutex.lock();
                    pin2 = value;
                    stopTimer = true;
                    time2 = time_track;
                    time_track = 0;
                    stopTimer = false;
                    timer_mutex.unlock();
                    continue;

                }
            }
            /*if (debug == true && time_track >= 10)
            {
                if(pin1 == 0)
                {
                    Serial.println("It wen't into where it prints pin1");
                    pin1 = 1;
                    Serial.print("Pin 2: ");
                    Serial.println(pin1);
                    time1 = time_track;
                    

                }

                if(pin2 == 0)
                {
                    pin2 = 1;
                    Serial.print("Pin 1: ");
                    Serial.println(pin2);
                    time2 = time_track;

                }

                time_track = 0;

            } */
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    stopTimer = true;

}


int SensorMaster::poll()
{
    int pin1 = 1;
    int pin2 = 1;
    int time1 = 0;
    int time2 = 0;

    std::thread timer1(stopwatch);
    std::thread polling(getValues, std::ref(pin1), std::ref(pin2), std::ref(time1), std::ref(time2), this->sensors);
    timer1.join();
    polling.join();

    return time2;
}
