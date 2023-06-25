#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 2;
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
      delay(10);    // Delay for smoother movement
    }
  }
  else
    {
      for (int pos = trenuta; pos >= poz; pos -= 1)
      {
        s->write(pos); // Move to the current position
        delay(10);    // Delay for smoother movement
      }
    }

  
}

double diferencijal(Servo * s, double step) {
  int napon = analogRead(naponPin);
  spin = s->read();
  advance(s, spin + step);
    

  delay(2000);
  double rezultat = (analogRead(naponPin) - napon)/step;
  delay(500);

  advance(s, spin-step);

  return rezultat*step;
}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(18);
     motorRoll.attach(19);
     pinMode(naponPin, INPUT); 



    motorSpin.write(spin);
    motorRoll.write(roll);

}

void loop(){

  Serial.println("pocetak");
  Serial.println(diferencijal(&motorSpin, 10));
  delay(2000);
  Serial.println(diferencijal(&motorSpin, 30));
  delay(2000);
  Serial.println(diferencijal(&motorSpin, 50));
  delay(2000);
  Serial.println(diferencijal(&motorSpin, 60));
  
  Serial.println("kraj");

  delay(8000);

}

