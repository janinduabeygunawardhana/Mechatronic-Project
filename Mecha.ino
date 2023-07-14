const byte interruptPin = 2;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
bool isSafe = true;

int stepPin = 3;
int directionPin = 4;

void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitPressed, HIGH);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitL, HIGH);
  // configure the sensors
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);

  digitalWrite(directionPin,HIGH);


}

void loop()
{
  Serial.begin
  if (isSafe == true){
    for (int stepCount = 1; stepCount < 200; stepCount++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }  
  }
 
}

void StepperLimitPressed()
{
  Serial.print("pressed , ");
  isSafe = false;
  Serial.println(isSafe);
}

//void StepperLimitL()
//{
//  Serial.print("pressed , ");
//  isSafe = true;
//  Serial.println(isSafe);
//}
