#include "smart_car.h"

void forward_car(){
  
    motor1.forward();
    motor2.forward();
}

void backward_car(){
    motor1.backward();
    motor2.backward();
}

void stop_car(){
  
   motor1.stop();
   motor2.stop();

}

void left_car(){

}

void right_car(){

}