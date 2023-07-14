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
