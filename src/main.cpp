#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 39;
Servo motorSpin;
Servo motorRoll;

double spin = 65;
double roll = 40;

void setup(){
    Serial.begin(115200);
     motorSpin.attach(4);
     motorRoll.attach(2);

    motorSpin.write(spin);
    motorRoll.write(roll);

}

void loop(){
  
  
  Serial.println(diferencijal(&motorSpin, 5));

  delay(1500);

}


double diferencijal(motorSpin *s, double step){

  int napon = analogRead(naponPin);

  s->write(spin + step);
  delay(300);
  double rezultat = (analogRead(naponPin) - napon)/step;

  s->write(spin - step);

  return rezultat;

}