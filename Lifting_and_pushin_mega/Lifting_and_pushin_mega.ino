#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//variable for lifting
//Motor pin Red Out b
//Motor pin Black Out a
//Input vialot GND
//Input yellow tied Input pin 1
//Input yellow Input pin 2
//Input a outputPin 1
//Input b outputPin 2

RF24 radio(7, 8); // CE, CSN

int LED_pin1 = 2;
int LED_pin2 = 3;

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  bool is_Cell1_empty = false;
  bool is_Cell2_empty = false;
};

Data_Package data; //Create a variable with the above structure

const byte interruptPin = 2;
bool isSafe = true;
bool calibrated = false;

int stepPin = 14;
int directionPin = 15;

//variables for pushin mechamism

int Run = 0; // use Run = 1 to actuate one time
int inputPin1 = 24;
int inputPin2 = 25;
int outputPin1 = 26;
int outputPin2 = 27;

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

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(2,INPUT);

  //define pins for pushing
  pinMode (outputPin1,OUTPUT);
  pinMode (outputPin2,OUTPUT);
  pinMode (inputPin1,INPUT_PULLUP);
  pinMode (inputPin2,INPUT_PULLUP);
  
  while(digitalRead(inputPin1)==1){
    digitalWrite(outputPin1,HIGH);
    digitalWrite(outputPin2,LOW);
  }
  digitalWrite(outputPin1,LOW);
  digitalWrite(outputPin2,LOW);
  CalibrateLifter();

}

void loop() {
//  liftUp(200);
//  delay(500);
  StoreL2Rack();
  delay(1000);
  StoreL1Rack();
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
  Run = 1;
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
 liftUp(200);
 calibrated = true;
 Serial.println("Calibration Successfull");
 delay(1000);
}

void StoreL2Rack(){
  int stp = 2000;
  liftUp(stp);
  push(Run);
  liftDown(stp);
  delay(500);
}

void StoreL1Rack(){
  push(Run);
  delay(500);
}

void error(){
  while(true){
    Serial.println("error occured: Press Reset");
    delay(250);    
  }

}

void push(int x){
  if(x==1){
  while(digitalRead(inputPin2)==1){
    digitalWrite(outputPin1,LOW);
    digitalWrite(outputPin2,HIGH);
  }
  while(digitalRead(inputPin1)==1){
    digitalWrite(outputPin1,HIGH);
    digitalWrite(outputPin2,LOW);
  }
  digitalWrite(outputPin1,LOW);
  digitalWrite(outputPin2,LOW);
  Run = 0;
  }
}

void Read_Data(){
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    
    Serial.print("is_Cell1_empty : ");
    Serial.println(data.is_Cell1_empty);
    Serial.print("is_Cell2_empty : ");
    Serial.println(data.is_Cell2_empty);
    
    if(data.is_Cell1_empty){
      //digitalWrite(LED_pin1,HIGH);
      Serial.println("LED_1 high");
    }
    else{
      //digitalWrite(LED_pin1,LOW);
      Serial.println("LED_1 low");
    }

    if(data.is_Cell2_empty){
      //digitalWrite(LED_pin2,HIGH);
      Serial.println("LED_2 high");
    }
    else{
      //digitalWrite(LED_pin2,LOW);
      Serial.println("LED_2 low");
    }
    Serial.println();
    
  }
}
