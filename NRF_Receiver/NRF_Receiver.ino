/*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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

void setup() {
  Serial.begin(9600);
  Serial.println("started");  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(LED_pin1,OUTPUT);
  pinMode(LED_pin2,OUTPUT);

  digitalWrite(LED_pin1,LOW);
  digitalWrite(LED_pin2,LOW);
}

void loop() {
  Read_Data();
}

void Read_Data(){
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    
    Serial.print("is_Cell1_empty : ");
    Serial.println(data.is_Cell1_empty);
    Serial.print("is_Cell2_empty : ");
    Serial.println(data.is_Cell2_empty);
    
    if(data.is_Cell1_empty){
      digitalWrite(LED_pin1,HIGH);
      Serial.println("LED_1 high");
    }
    else{
      digitalWrite(LED_pin1,LOW);
      Serial.println("LED_1 low");
    }

    if(data.is_Cell2_empty){
      digitalWrite(LED_pin2,HIGH);
      Serial.println("LED_2 high");
    }
    else{
      digitalWrite(LED_pin2,LOW);
      Serial.println("LED_2 low");
    }
    Serial.println();
    
  }
}
