#include <QTRSensors.h>

// This example is designed for use with six analog QTR sensors. These
// reflectance sensors should be connected to analog pins A0 to A5. The
// sensors' emitter control pin (CTRL or LEDON) can optionally be connected to
// digital pin 2, or you can leave it disconnected and remove the call to
// setEmitterPin().
//
// The setup phase of this example calibrates the sensors for ten seconds and
// turns on the Arduino's LED (usually on pin 13) while calibration is going
// on. During this phase, you should expose each reflectance sensor to the
// lightest and darkest readings they will encounter. For example, if you are
// making a line follower, you should slide the sensors across the line during
// the calibration phase so that each sensor can get a reading of how dark the
// line is and how light the ground is. Improper calibration will result in
// poor readings.
//
// The main loop of the example reads the calibrated sensor values and uses
// them to estimate the position of a line. You can test this by taping a piece
// of 3/4" black electrical tape to a piece of white paper and sliding the
// sensor across it. It prints the sensor values to the serial monitor as
// numbers from 0 (maximum reflectance) to 1000 (minimum reflectance) followed
// by the estimated location of the line as a number from 0 to 5000. 1000 means
// the line is directly under sensor 1, 2000 means directly under sensor 2,
// etc. 0 means the line is directly under sensor 0 or was last seen by sensor
// 0 before being lost. 5000 means the line is directly under sensor 5 or was
// last seen by sensor 5 before being lost.

QTRSensors qtr;

const byte interruptPin = 2;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
bool isSafe = true;

int stepPin = 3;
int directionPin = 4;

void setup()
{ 
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimit, HIGH);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitL, HIGH);
  // configure the sensors
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);

  pinMode(2, INPUT);


}

void loop()
{
  for (int stepCount = 1; stepCount < 200; stepCount++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(4000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(4000);
  }   
}

//void StepperLimit()
//{
//  Serial.print("pressed , ");
//  isSafe = false;
//  Serial.println(isSafe);
//}
//
//void StepperLimitL()
//{
//  Serial.print("pressed , ");
//  isSafe = true;
//  Serial.println(isSafe);
//}
