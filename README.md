Here is the Sensor Master Documentation:

Class: 
SensorMaster

Methods:
void init_list(int sensors_arr[]);
int getOutput(int pin_number);
int poll();
void display();





void init_list(int sensors_arr[]):
  -Initializes all of the hall effect sensors on the board. Takes an array object of ints, and also stores them in a C++ Vector for reference.



int getOutput(int pin_number):
  -returns the digitalRead output of the pin_number that was passed in. Returns a -1 if an error occured or if no pin was found. Useful for debugging reasons.

int poll():
  -Starts the timer, and goes through each sensor stored in the class vector until it finds two sensors that are activated. Also, keeps track of how much time it took for
  each sensor to activate, and returns the time it took inbetween.
