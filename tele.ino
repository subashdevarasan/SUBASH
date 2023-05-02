#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid ="realme 2";
const char* password= "12345678";

#define BOTtokenValue""
#define OUR_CHAT_ID""

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtokenValue,client);

const int mSensor=21; // motion sensor
const int TempSensor=34; //temperature sensor
bool mDetected = false;  //to initiate motion is detected

void IRAM_ATTR movementdetection()
{
  Serial.println("Motion has been detected!");
  mDetected = true; 
  }
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

pinMode(mSensor, INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(mSensor),movementdetection,RISING);
Serial.print("Trying to Connect to WIFI:");
Serial.print(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);
client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

while(WiFi.status() !=WL_CONNECTED)
{
  Serial.println(".");
  delay(300);
  
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(OUR_CHAT_ID, "Motion and Temperature Bot Started UP","");
  

}
void loop() {
  // put your main code here, to run repeatedly:
if(mDetected)
{
  bot.sendMessage(OUR_CHAT_ID,"Motion has been Detected","");
  mDetected = false;
}
}
