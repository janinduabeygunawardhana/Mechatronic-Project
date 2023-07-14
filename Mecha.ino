const byte interruptPin = 2;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
bool isSafe = true;

int stepPin = 3;
int directionPin = 4;

void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitPressed, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitReleased, FALLING);
  // configure the sensors
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);

  digitalWrite(directionPin,HIGH);


}

void loop()
{
  Serial.println(isSafe);
  if (isSafe == true){
    for (int stepCount = 1; stepCount < 200; stepCount++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }  
  }
 delay(250);
}

void StepperLimitPressed()
{
  if (digitalRead(2)){
    Serial.print("pressed , ");
    Serial.print(digitalRead(2));
    isSafe = true;
    Serial.print(" Is Safe : ");
    Serial.println(isSafe);  
  }
  else{
    Serial.print("pressed , ");
    Serial.print(digitalRead(2)); 
    isSafe = false;
    Serial.print(" Is Safe : ");
    Serial.println(isSafe);  
  }

}

void StepperLimitReleased()
{
  Serial.print("Released , ");
  isSafe = true;
  Serial.println(isSafe);
}
