#include <Arduino.h>
#include <ESP32Servo.h>

const int naponPin = 4;
Servo motorSpin;
Servo motorRoll;


bool startup = true;

void advance(Servo *s, int poz)
{
  poz = poz - (poz / 360) * 360;
  if(poz < 0) poz+=360;
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
  int poz = s->read();
  advance(s, poz + step);
    
  delay(5000);
  int novi_napon = analogRead(naponPin);

  if(novi_napon == napon)
  Serial.println("mater ti jebem");

  
  if(s == &motorRoll){
    Serial.print("info: ");
    Serial.print(napon);
    Serial.print(" ");
    Serial.print(novi_napon);
    Serial.println(" info end");
    novi_napon = 40;
  }

  delay(500);

  advance(s, poz-step);


  return (novi_napon - napon);
}

void nadiPoziciju(int preciznost){

  int sp = diferencijal(&motorSpin, preciznost);
  delay(3000);
  int rol = diferencijal(&motorRoll, preciznost);

  double duzina = sqrt(sp*sp + rol*rol);

  

  if(duzina == 0)
    return;
  if(sp > 5)
  advance(&motorSpin, motorSpin.read() + preciznost * (sp/duzina) );

  if(rol > 5)
  advance(&motorRoll, motorRoll.read() + preciznost * (rol/duzina) );


  Serial.println(preciznost * (rol/duzina));

}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(18);
     motorRoll.attach(19);
     pinMode(naponPin, INPUT); 



    motorSpin.write(180);
    motorRoll.write(180);

}


void loop(){

//Serial.println(analogRead(naponPin));
//advance(&motorRoll, -10);
//delay(900);
  //return;

  Serial.println("pocetak");

  for(int i = 170; i>0; i=i/2){
    nadiPoziciju(i);
    delay(2000);
}


  Serial.println("kraj");

  delay(100000);

}

