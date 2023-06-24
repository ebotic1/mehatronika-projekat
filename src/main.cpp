#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 39;
Servo motorSpin;
Servo motorRoll;

double spin = 55;
double roll = 40;

void advance(Servo *s, double poz)
{
  /*
  int znak = (s->read() < poz) ? 1 : -1;
  if (znak == 1)
  {
    for (int pos = s->read(); pos <= poz; pos += 1)
    {
      s->write(pos); // Move to the current position
      delay(500);    // Delay for smoother movement
    }
  }
  else
    {
      for (int pos = s->read(); pos >= poz; pos -= 1)
      {
        s->write(pos); // Move to the current position
        delay(500);    // Delay for smoother movement
      }
    }
*/
    s->write(poz);
  
}

double diferencijal(Servo * s, double step) {
  int napon = analogRead(naponPin);

  advance(s, spin + step);
    

  delay(1000);
  double rezultat = (analogRead(naponPin) - napon)/step;
  delay(1000);

  advance(s, spin-step);

  return rezultat;
}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(4);
     motorRoll.attach(2);

    advance(&motorSpin, spin);
    advance(&motorRoll, roll);

}

void loop(){
  
  
  Serial.println(diferencijal(&motorSpin, 10));



  delay(8000);

}

