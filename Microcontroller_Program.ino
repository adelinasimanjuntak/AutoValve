#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ESP8266_BAUD 115200
#define ONE_WIRE_BUS D6
#define solenoidPin D3
#define pumpPin D2
#define BLYNK_PRINT Serial

//BLYNK AUTH TOKEN
const char *auth = "d9OA477Nix5U-n6A1oW5Vzz8qhLCgCfG";
const char *ssid = "ALDINERS";
const char *password = "12345678";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorSuhu(&oneWire); 
float suhuSekarang;
float perintahPipa;
float maksimal = 95.00;
String Celcius;
String Fahrenheit;

float ambilSuhu()
{
      sensorSuhu.requestTemperatures();
      float Celcius = sensorSuhu.getTempCByIndex(0);
      float Fahrenheit = sensorSuhu.toFahrenheit(Celcius);
      return Fahrenheit;   
}

void setup() {
  Serial.begin(115200);
  sensorSuhu.begin();
  pinMode(solenoidPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  //EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, ssid, password);
}

void loop() {
  suhuSekarang = ambilSuhu();
  digitalWrite(solenoidPin, LOW);
  digitalWrite(pumpPin, LOW);
  Blynk.run();
  float perintahPipa = kondisiPipa();
 
}

  float kondisiPipa(){
     if(suhuSekarang>maksimal){
      Serial.println(suhuSekarang);
      digitalWrite(solenoidPin, HIGH);
      digitalWrite(pumpPin, HIGH);
      
      //BLYNK
      Blynk.email("adelinasimanjuntak@gmail.com", "The System has been stoped", "Temperature is over 95F!");
      Blynk.notify("The System has been stoped - Temperature is over 95F!");
      delay(3000);
     }
      
    }
