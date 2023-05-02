

#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>


const char* ssid="realme 2";
const char* password ="12345678";
const int ledPin1 =  2;
const int ledPin2 =  5;

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT);
Serial.begin(115200);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);
Serial.println("WiFi Connection Attempt");
while(WiFi.status() !=WL_CONNECTED)
{
   delay(350);
 Serial.print(".");
  }
Serial.println("");
Serial.println("CONNECTED TO WiFi Network with Name: ");
Serial.print(ssid);
Serial.print("IP Address for ESP32:");
Serial.println(WiFi.localIP());


server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){request->send(200,"text/plain","OTA ");});


AsyncElegantOTA.begin(&server);
server.begin();
Serial.println("Elegant OTA Initiated");
Serial.println("HTTP Server Has stated Sucessfully");
Serial.println("To access OTA Update,type");
Serial.println(WiFi.localIP());
Serial.println("/ledon");
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
