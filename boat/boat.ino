#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

#define SERVO 5

RF24 radio(7, 8);
Servo myServo;

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
  radio.openReadingPipe(0, addr);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  myServo.attach(SERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    myServo.write(map(data.x, 0, 1024, 0, 180));
  }
  delay(15);
}
