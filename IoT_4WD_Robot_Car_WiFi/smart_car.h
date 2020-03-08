#ifndef smart_car_h
#define smart_car_h

#include "Arduino.h"


// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
// Motor B
int motor2Pin1 = 33; 
int motor2Pin2 = 32; 
int enable2Pin = 25;




void forward_car();
void backward_car();
void stop_car();
void left_car();
void right_car();

#endif
