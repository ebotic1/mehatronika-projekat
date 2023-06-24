#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 39;
Servo motorSpin;
Servo motorRoll;

void setup(){
    Serial.begin(115200);
     motorSpin.attach(4);
     motorRoll.attach(2);

    motorSpin.write(65);
    motorRoll.write(40);

}

void loop(){
  
  int napon = analogRead(naponPin);
  
  Serial.println(napon);


  delay(1001);

}


