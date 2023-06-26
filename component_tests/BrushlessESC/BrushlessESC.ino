#include <Servo.h>

Servo ESC;

int potValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESC.attach(9);
  ESC.writeMicroseconds(1500);

  delay(7000);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(A0);
  potValue = map(potValue, 0, 1024, 1000, 2000);
  Serial.println(potValue);
  ESC.writeMicroseconds(potValue);
}
