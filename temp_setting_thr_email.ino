#include "ESP32_MailClient.h"
#include "WiFi.h"

const char* ssid = "realme 2";
const char* password = "12345678";

#define emailSenderAccount"subashdevaraj@gmail.com"
#define emailSenderPassword"bdrgloyexyknkzju"
#define emailRecipient "subashdevaraj@gmail.com"
#define smtpServer"smtp.gmail.com"
#define smtpServerPort 465
#define emailSubject "ESP32 Testing Email"

SMTPData smtpData;

int touchValue;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while (WiFi.status() !=WL_CONNECTED)
  {
    Serial.print("*");
    delay(200);
  }

  Serial.println("WiFi is Connected");

  smtpData.setLogin(smtpServer,smtpServerPort, emailSenderAccount, emailSenderPassword);
  smtpData.setSender("ESP32 Sender", emailSenderAccount);
  smtpData.setPriority("High");
  smtpData.setSubject(emailSubject);
 // smtpData.setMessage("Hello World This is ESP Email Testing", true);
 
 
  //smtpData.addRecipient(emailRecipient);

/*if(!MailClient.sendMail(smtpData))
{
  Serial.println("Error in Sending the Email"+MailClient.smtpErrorReason());
  }*/

  smtpData.empty();
  }

void loop()
{
  smtpData.setLogin(smtpServer,smtpServerPort, emailSenderAccount, emailSenderPassword);
  smtpData.setSender("ESP32 Sender", emailSenderAccount);
  smtpData.setPriority("High");
  smtpData.setSubject(emailSubject);

 touchValue=touchRead(4);
 Serial.print("The touch sensor value:");
 Serial.println(touchValue);
 if(touchValue>=100)
{
  smtpData.setMessage("The Touch Sensor value is above 100"+touchValue+0x30,true);
    //smtpData.setMessage(Serial.println(touchValue),true);
  delay(1000);
  smtpData.addRecipient(emailRecipient);

  if(!MailClient.sendMail(smtpData))
{
  Serial.println("Error in Sending the Email"+MailClient.smtpErrorReason());
  }
  
  }
}


void sendCallback(SendStatus message)
{
  Serial.println(message.info());

  if(message.success()){Serial.print("++++++++");}
}
