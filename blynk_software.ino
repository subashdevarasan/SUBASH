#include <Blynk.h>

#include<WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

#define DHPIN 23
#define DHTYPE DHT11

const int relay =22;
const int waterLevelSensor= 21;
const int SoilSensor = 19;

int waterLevel;
int moistureLevel;

DHT dht(DHPIN,DHTYPE);
BlynkTimer timer;

char auth[]= "YjD70tmlpQpd6v5J6jLGDdJEDFWchWXW";

char ssid[]="realme 2";
char pass[]="12345678";

void SendSensorDH()
{ 
 float humidity=dht.readHumidity ();
 float temperature= dht.readTemperature();
 Blynk.virtualWrite(V5,humidity);
 Blynk.virtualWrite(V4,temperature);
 
}

void SendSensorWaterSoil()
{
  waterLevel = analogRead(waterLevelSensor);
  waterLevel = map(waterLevel,0,2000,0,25);
  moistureLevel = analogRead(SoilSensor);
  moistureLevel = map(moistureLevel,0,4000,0,20);

  Blynk.virtualWrite(V7,waterLevel);
   Blynk.virtualWrite(V6,moistureLevel); 
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Blynk.begin(auth,ssid,pass);
dht.begin();
timer.setInterval(3000L,SendSensorDH );
timer.setInterval(6000L,SendSensorWaterSoil);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();

}
