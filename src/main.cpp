#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 2;
Servo motorSpin;
Servo motorRoll;


bool startup = true;

void advance(Servo *s, int poz)
{
  poz = poz - (360 / poz) * 360;
  double trenuta = s->read();
  Serial.print("trenutna: ");
  Serial.println(trenuta);
  Serial.print("zadana: ");
  Serial.println(poz);
  
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

  Serial.print("nakon pomjeranja");
  Serial.println(s->read());
  
}

double diferencijal(Servo * s, double step) {
  int napon = analogRead(naponPin);
  int poz = s->read();
  advance(s, poz + step);
    

  delay(3000);
  double rezultat = (analogRead(naponPin) - napon)/step;
  delay(500);

  advance(s, poz-step);

  return rezultat;
}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(18);
     motorRoll.attach(19);
     pinMode(naponPin, INPUT); 



    motorSpin.write(180);
    motorRoll.write(180);

}

void nadiPoziciju(int preciznost){

  int sp = diferencijal(&motorSpin, preciznost);
  delay(3000);
  int rol = diferencijal(&motorRoll, preciznost);

  double duzina = sqrt(sp*sp + rol*rol);

  advance(&motorSpin, motorSpin.read() + preciznost * (sp/duzina) );
  Serial.println(preciznost * (sp/duzina));
  advance(&motorRoll, motorRoll.read() + preciznost * (rol/duzina) );
  Serial.println(preciznost * (rol/duzina));

}

void loop(){
  Serial.println("pocetak");

  
  nadiPoziciju(40);
  delay(1000);
  nadiPoziciju(10);


  Serial.println("kraj");

  delay(10000);

}

