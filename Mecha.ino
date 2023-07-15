const byte interruptPin = 2;
bool isSafe = true;

int stepPin = 3;
int directionPin = 4;

void StepperLimitChanged(){
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

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitChanged, CHANGE);
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);

  CalibrateLifter();

}

void loop() {

}

void liftUp(int stp){
  digitalWrite(directionPin, HIGH);
  Serial.println("UP");
  for (int stepCount = 1; stepCount < stp; stepCount++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

void liftDown(int stp){
  digitalWrite(directionPin, LOW);
  Serial.println("Down");
  for (int stepCount = 1; stepCount < stp; stepCount++){
    if(!isSafe){
      break;  
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

void CalibrateLifter(){
  liftUp(200);
  while(isSafe){
    liftDown(200);
  }
 Serial.println("Calibration Successfull");
}
