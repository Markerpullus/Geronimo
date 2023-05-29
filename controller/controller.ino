#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define DIR_X 0
#define DIR_Y 1

RF24 radio(7, 8);

const byte addr[6] = "00001";

struct Data {
  int x;
  int y;
};

Data data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addr);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  data.x = analogRead(DIR_X);
  data.y = analogRead(DIR_Y);
  radio.write(&data, sizeof(Data));
  delay(15);
}
