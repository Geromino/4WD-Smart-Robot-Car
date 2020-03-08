#ifndef L298N_h
#define L298N_h

#include "Arduino.h"



typedef void (*CallBackFunction) ();

class L298N{
   public:
      typedef enum
      {
            FORWARD  = 0,
            BACKWARD = 1
      } Direction;
      L298N(int pinEnable, int pinIN1, int pinIN2);
      void setSpeed(int dutyCycle);
      int  getSpeed();
      void forward();
      void forwardFor(unsigned long delay, CallBackFunction callback);
      void forwardFor(unsigned long delay);
      void backward();
      void backwardFor(unsigned long delay, CallBackFunction callback);
      void backwardFor(unsigned long delay);
      void run(uint8_t direction);
      void stop();
      void reset();
      boolean isMoving();
   private:
      int _pinEnable;
      int _pinIN1;
      int _pinIN2;
      unsigned long _lastMs;
      boolean _canMove;
      boolean _isMoving;
	    int _freq;
      int _pwmChannel;
      int _resolution;
	    int _dutyCycle;
      static void fakeCallback();
};

#endif
