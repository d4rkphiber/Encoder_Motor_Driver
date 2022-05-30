#include <Arduino.h>
#include <encoder.h>

class Motor
{
public:
       
    Motor(int PinA, int PinB, int offset, int PWMpin, int STDBY, int channel, int EncA, int EncB);
    Encoder encoder;
    void drive(int speed);
    void brake(); 
    int In1, In2, PWM, Offset, Standby;
    void fwd(int speed);
	void rev(int speed);
};

