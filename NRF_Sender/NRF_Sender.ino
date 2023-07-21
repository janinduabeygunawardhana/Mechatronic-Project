/*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <HCSR04.h>

RF24 radio(7, 8); // CE, CSN
HCSR04 hc2(5, 6); //initialisation class HCSR04 rack 1 (trig pin , echo pin)
HCSR04 hc(3, 4); //initialisation class HCSR04 rack 1 (trig pin , echo pin)

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  bool is_Cell1_empty = false;
  bool is_Cell2_empty = false;
};

Data_Package data; // Create a variable with the above structure

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(2,INPUT_PULLUP);
}

void loop() {
  Serial.println(hc.dist());
  Serial.println(hc2.dist());
  if(hc.dist()>10 or hc.dist() == 0.00){
    data.is_Cell1_empty = true;
  }
  else{
    data.is_Cell1_empty = false;
  }
  
  if(hc2.dist()>10 or hc2.dist() == 0.00){
    data.is_Cell2_empty = true;
  }
  else{
    data.is_Cell2_empty = false;
  }
  radio.write(&data, sizeof(Data_Package));
  delay(1000);
}
