//variable for lifting
const byte interruptPin = 2; //green pin - limit switch
bool isSafe = true; 
bool calibrated = false;
int stepPin = 3; 
int directionPin = 4;

// varialble for pushing
int Run = 1; // use Run = 1 to actuate one time
int inputPin1 = 4;
int inputPin2 = 5;
int outputPin1 = 6;
int outputPin2 = 7;

void StepperLimitChanged(){
  if (digitalRead(2)){
    Serial.print("Released , ");
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

    if(calibrated){
      error();
    }
  }
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepperLimitChanged, CHANGE);
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);

  //pins for pushing
  pinMode (outputPin1,OUTPUT);
  pinMode (outputPin2,OUTPUT);
  pinMode (inputPin1,INPUT);
  pinMode (inputPin2,INPUT);

  CalibrateLifter();

}

void loop() {
  StoreL2Rack();
  delay(1000);
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
 liftUp(100);
 calibrated = true;
 Serial.println("Calibration Successfull");
 delay(1000);
}

void StoreL2Rack(){
  int stp = 2400;
  liftUp(stp);
  delay(2000);
  liftDown(stp);
  delay(500);
}
void error(){
  while(true){
    Serial.println("error occured: Press Reset");
    delay(250);    
  }

}

// define a function for push the object
void push(int x){
  if(x==1){
  while(digitalRead(inputPin2)==0){
    digitalWrite(outputPin1,LOW);
    digitalWrite(outputPin2,HIGH);
  }
  while(digitalRead(inputPin1)==0){
    digitalWrite(outputPin1,HIGH);
    digitalWrite(outputPin2,LOW);
  }
  digitalWrite(outputPin1,LOW);
  digitalWrite(outputPin2,LOW);
  Run = 0;
  }
}
