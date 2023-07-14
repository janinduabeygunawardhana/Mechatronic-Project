const byte interruptPin = 2;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
bool isSafe = true;

int stepPin = 3;
int directionPin = 4;

void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitChanged, CHANGE);
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);


}

void loop()
{
  if(isSafe){
    Serial.println("Running");
    liftDown(1000);  
  }
  else{
    liftUp(400);
  }
  
  //liftDown(10);
  delay(100);
  
}


void liftUp(int steps){
  digitalWrite(directionPin,HIGH);
  for (int stepCount = 1; stepCount < steps; stepCount++){
    if(isSafe){
      break;  
    }
    Serial.println("Lifting Up");
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }   
}


int liftDown(int steps){
  digitalWrite(directionPin,LOW);
  for (int stepCount = 1; stepCount < steps; stepCount++){
    if(!isSafe){
      break;  
    }
    Serial.println("Lifting Down");
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }   
}



void StepperLimitChanged()
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
