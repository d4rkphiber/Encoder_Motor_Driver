#include <motor.h>

int freq = 5000;
int resolution = 8;


Motor::Motor(int PinA, int PinB, int offset, int PWMpin, int STDBY, int PWMChannel, int EncA, int EncB)
: encoder(EncA, EncB)
    {
        In1 = PinA;
        In2 = PinB;
        PWM = PWMChannel;
        Standby = STDBY;
        Offset = offset;
  
        pinMode(In1, OUTPUT);
        pinMode(In2, OUTPUT);
        pinMode(PWM, OUTPUT);
        pinMode(Standby, OUTPUT);
        ledcSetup(PWM, freq, resolution);
        ledcAttachPin(PWMpin, PWM);
     } 

void Motor::drive(int speed)
{
  digitalWrite(Standby, HIGH);
  speed = speed * Offset;
  if (speed>=0) fwd(speed);
  else rev(-speed);
}

void Motor::fwd(int speed)
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
   //analogWrite(PWM, speed);
   ledcWrite(PWM, speed);

}

void Motor::rev(int speed)
{
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);
   //analogWrite(PWM, speed);
   ledcWrite(PWM, speed);
}

void Motor::brake()
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, HIGH);
   //analogWrite(PWM,0);
   ledcWrite(PWM, 0);
}