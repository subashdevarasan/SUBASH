#include<WiFi.h>
#include<WebServer.h>

const char* ssid="Subash ESP";
const char* password ="12345678";

IPAddress local_ip(192,168,0,165);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

WebServer server (80);

uint8_t ledone=2;
bool ledoneStatus=LOW;

uint8_t ledtwo=5;
bool ledoneStatus=LOW;

void setup() {
Serial.begin(115200);
pinMode(ledone,OUTPUT);
pinMode(ledtwo,OUTPUT);

WiFi.softAP(ssid,password);
WiFi.softAPConfig(local_ip,gateway,subnet);
delay(100);

server.on("/", handle_OnConnect); 
server.on("/led1on", handle_led1on); 
server.on("/led1off", handle_led1off);
server.on("/led2on", handle_led2on); 
server.on("/led2off", handle_led2off);
server.onNotFound(handle_NotFound);

server.begin();
Serial.println("HTTP Server has Started");
}

void loop() {
 server.handleClient();
 if(ledoneStatus)
 {digitalWrite(ledone,HIGH);}
 else
 {digitalWrite(ledone,LOW);}

 if(ledtwoStatus)
 {digitalWrite(ledtwo,HIGH);}
 else
 {digitalWrite(ledtwo,LOW);}
}

void handle_OnConnect()
{
  led1Status=LOW;
  led2Status=LOW;
  Serial.println("GPIO2 Status:OFF | GPIO5 Status: OFF");
  server.send(200,"text/html", SendHTML(ledoneStatus,ledoneStatus));
  }
  
void handle_led1on()
{
  led1Status=HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200,"text/html", SendHTML(true,led2Status));
  }
  
  void handle_led1off()
{
  led1Status=LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200,"text/html", SendHTML(false,led2Status));
  }

 void handle_led2on()
{
  led2Status=HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200,"text/html", SendHTML(led1Status,true));
  }
  
  void handle_led2off()
{
  led2Status=LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200,"text/html", SendHTML(led1Status,false));
  }

  void handle_NotFound()
  {
    server.send(404,"text/plain","Not found");
  }

    String SendHTML(uint8_t led1stat,uint8_t led2stat)
    {
      String ptr="<!DOCTYPE html>  <html>\n";
      ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0 user-scaleable=no\">\n";
      ptr +="<title> LED Contrl ESP32</title>\n";
      ptr+="<style> html {font-family:Arial; dispaly; inline-block; margin: Opx auto; text-align: centre;}\n";
      ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
      ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
      ptr +=".button-on {background-color: #3498db;}\n";
      ptr +=".button-on:active {background-color: #2980b9;}\n";
      ptr +=".button-off {background-color: #34495e;}\n";
      ptr +=".button-off:active {background-color: #2c3e50;}\n";
      ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
      ptr +="</style>\n";
      ptr +="</head>\n";
      ptr +="<body>\n";
      ptr +="<h1>ESP32 Web Server Text</h1>\n";
      ptr +="<h3>Using AP Mode</h3>\n";

      if(led1stat)
      {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
      else
      {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}
 
      if(led2stat)
      {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
      else
      {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
 
      ptr +="</body>\n";
      ptr +="</html>\n";
      return ptr;
      
      }
