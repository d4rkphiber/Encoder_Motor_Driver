#include <Arduino.h>
#include <motor.h>

#define AIN1 26
#define BIN1 13
#define AIN2 27
#define BIN2 12
#define PWMA 25
#define PWMB 14
#define STBY 23

//need more Interrupts? Add them in encoder.h and encoder.cpp
#define Enc1A 16
#define Enc1B 17
#define Enc2A 18
#define Enc2B 19
const int channel1 = 0;
const int channel2 = 1;
const int offsetA = 1;
const int offsetB = 1;

//   avoid using pins with LEDs attached
Motor motor1(AIN1, AIN2, offsetA, PWMA ,STBY, channel1, Enc1A, Enc1B);
Motor motor2(BIN1, BIN2, offsetB, PWMB ,STBY, channel2, Enc2A, Enc2B);
long newPosition1  = 1000;

long newPosition2  = 1000;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test Motor!!!!:");
  Serial.println((*motor1.encoder.encoder.pin1_register, HEX));
  Serial.println((uint32_t)motor1.encoder.encoder.pin2_register, HEX);
  uint32_t bitmask =  digitalPinToBitMask(26);
  Serial.println(bitmask, BIN);
  uint32_t  base = digitalPinToPort(AIN1);
  Serial.println(base, HEX);
  volatile uint32_t * reg2 = portInputRegister(base);
  Serial.println((uint32_t)reg2, HEX);
  Serial.println((uint32_t)&reg2, HEX);


  
}


void loop() {
   motor1.drive(-100);
   while (motor1.encoder.read() < newPosition1)
      {}
   motor1.brake();
   delay(200);
   Serial.println(motor1.encoder.read());
   motor1.drive(100);
   while (motor1.encoder.read() > 0)
      {}
   motor1.brake();
   delay(200); 
   Serial.println(motor1.encoder.read());

   motor2.drive(-100);
   while (motor2.encoder.read() < newPosition2)
      {
         
      }
   motor2.brake();
   delay(200);
   Serial.println(motor2.encoder.read());
   motor2.drive(100);
   while (motor2.encoder.read() > 0)
      {}
   motor2.brake();
   delay(200); 
   Serial.println(motor2.encoder.read());

}