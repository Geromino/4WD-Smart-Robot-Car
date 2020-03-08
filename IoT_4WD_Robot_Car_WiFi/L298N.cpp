/*
  L298N.cpp - Library to manage the movements of a Car with 4 motors with the L298N driver	
  Autore:   zachar papkov
  git :https://github.com/Geromino/4WD-Smart-Robot-Car.git 
*/
#include <LiquidCrystal.h>
#include "L298N.h"

typedef void (*CallBackFunction) ();

L298N::L298N(int pinEnable, int pinIN1, int pinIN2){
  _pinEnable = pinEnable;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _freq = 30000;
  _pwmChannel = 0;
  _resolution = 8;
  _dutyCycle = 200;

  pinMode(_pinEnable, OUTPUT);
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);

      // configure LED PWM functionalitites
  ledcSetup(_pwmChannel, _freq, _resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(_pinEnable, _pwmChannel);
}


void L298N::setSpeed(int dutyCycle){
  _dutyCycle = dutyCycle;  
}

int L298N::getSpeed(){
  return _dutyCycle;
}

void L298N::forward(){
  
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, LOW);
  ledcWrite(_pwmChannel,_dutyCycle);   

  _isMoving = true;
}


void L298N::forwardFor(unsigned long delay, CallBackFunction callback){
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    this->forward();
  }

  if (((millis() - _lastMs) > delay) && _canMove) {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();

  }
}

void L298N::forwardFor(unsigned long delay){
  this->forwardFor(delay, fakeCallback);
}


void L298N::backward(){
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, HIGH);

  ledcWrite(_pwmChannel, _dutyCycle);   

  _isMoving = true;
}

void L298N::backwardFor(unsigned long delay, CallBackFunction callback){

  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    this->backward();
  }

  if (((millis() - _lastMs) > delay) && _canMove) {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();

  }
}

void L298N::backwardFor(unsigned long delay){
  this->backwardFor(delay, fakeCallback);
}

void L298N::run(uint8_t direction){
  switch(direction){
    case BACKWARD:
      this->backward();
    break;
    case FORWARD:
      this->forward();
    break;
  }
}

void L298N::stop(){
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, LOW);

  _isMoving = false;
}

void L298N::reset(){
  _canMove = true;
}

boolean L298N::isMoving(){
  return _isMoving;
}

void L298N::fakeCallback(){

}
