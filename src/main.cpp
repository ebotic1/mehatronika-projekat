#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 39;
Servo motorSpin;
Servo motorRoll;

double spin = 90;
double roll = 60;

bool startup = true;

void advance(Servo *s, double poz)
{
  double trenuta = s->read();
  
  if (trenuta < poz)
  {
    for (int pos = trenuta; pos <= poz; pos += 1)
    {
      s->write(pos); // Move to the current position
      delay(40);    // Delay for smoother movement
    }
  }
  else
    {
      for (int pos = trenuta; pos >= poz; pos -= 1)
      {
        s->write(pos); // Move to the current position
        delay(40);    // Delay for smoother movement
      }
    }

  
}

double diferencijal(Servo * s, double step) {
  int napon = analogRead(naponPin);

  advance(s, spin + step);
    

  delay(500);
  double rezultat = (analogRead(naponPin) - napon)/step;
  delay(500);

  advance(s, spin-step);

  return rezultat;
}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(4);
     motorRoll.attach(2);



    motorSpin.write(spin);
    motorRoll.write(roll);

}

void loop(){

  
  Serial.println(diferencijal(&motorSpin, 100));



  delay(8000);

}

