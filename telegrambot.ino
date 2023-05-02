#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid ="realme 2";
const char* password= "12345678";

#define BOTtokenValue"6159234928:AAGDeIAlmnRnYvPSlu_951Rp_rOSKL0UAFw"
#define OUR_CHAT_ID"808155661"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtokenValue,client);

const int mSensor=21; // motion sensor
const int TempSensor=34; //temperature sensor

bool mDetected = false;  //to initiate motion is detected
int TempValue = 0;

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
 bool result = bot.sendMessage(OUR_CHAT_ID,"Motion has been detected!","") ;
 Serial.println("Motion has been detected!");
 
if(result)
{Serial.println("Message Sucessfully sent");
  }else
  {Serial.println("Error: Message Wasn't sent");}
 mDetected = false;
  
 }
 
 TempValue = analogRead(TempSensor);
 Serial.println(TempValue);
 float voltTemp    = (float)TempValue*(3300.0/4096.0);
 Serial.println(voltTemp);
float actualTempC = voltTemp / 10.0;
 Serial.println(actualTempC);
 
 String sensorMessage = String (actualTempC,DEC);
 bot.sendMessage(OUR_CHAT_ID,sensorMessage,"");
 delay(500);
 

}
