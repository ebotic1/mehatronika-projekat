#include <Arduino.h>
#include <ESP32Servo.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <vector>

const char *dajStranicu(std::vector<int> &vrijeme, std::vector<int> &napon);

const char* ssid = "PROMES-W4";
const char* password = "";

std::vector<int> napon, vrijeme;

AsyncWebServer server(80); // create AsyncWebServer object on port 80


const int naponPin = 39;
Servo motorSpin;
Servo motorRoll;

int lastPositioning = 0;
const int positionTimeout = 240;

void advance(Servo *s, int poz)
{
  if(poz > 180 || poz < 0){
    poz = (poz > 180) ? 180 : 0;
  }

  double trenuta = s->read();

  if (trenuta < poz)
  {
    for (int pos = trenuta; pos < poz; pos += 1)
    {
      s->write(pos); // Move to the current position
      delay(10);    // Delay for smoother movement

    }
  }
  else
    {
      for (int pos = trenuta; pos > poz; pos -= 1)
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
    
  delay(4000);
  int novi_napon = analogRead(naponPin);


  delay(500);

  advance(s, poz);


  return (novi_napon - napon)/step;
}

void nadiPoziciju(int preciznost){

  const int scale = 10;

  int sp = diferencijal(&motorSpin, preciznost) * scale;
  delay(2000);
  int rol = diferencijal(&motorRoll, preciznost) * scale;

  double duzina = sqrt(sp*sp + rol*rol);

  

  if(duzina == 0)
    return;

  advance(&motorSpin, motorSpin.read() + preciznost * (sp/duzina) );

  advance(&motorRoll, motorRoll.read() + preciznost * (rol/duzina) );


  Serial.println(preciznost * (rol/duzina));

}

void setup(){
    Serial.begin(115200);
     motorSpin.attach(18);
     motorRoll.attach(19);
     pinMode(naponPin, INPUT); 



    motorSpin.write(0);
    motorRoll.write(0);


    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", dajStranicu(vrijeme, napon));
    });

    server.begin();

    nadiPoziciju(180);
    nadiPoziciju(90);

}

int cnt_old = 0;

void loop(){

int cnt = (millis() / 1000) / positionTimeout;

if(cnt > cnt_old){
  cnt_old = cnt;
  for(int i = 40; i>0; i=i/2){
    nadiPoziciju(i);
    delay(2000);
  }

}


  vrijeme.push_back(millis() / 1000);
  napon.push_back(analogRead(naponPin));


  delay(10000);
}

