#include "ESP32_MailClient.h"

const char* ssid = "realme 2";
const char* password = "12345678";

#define emailSenderAccount"subashdevaraj@gmail.com"
#define emailSenderPassword"bdrgloyexyknkzju"
#define emailRecipient "subashdevaraj@gmail.com"
#define smtpServer"smtp.gmail.com"
#define smtpServerPort 465
#define emailSubject "ESP32 Testing Email"

SMTPData smtpData;

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
  //smtpData.setMessage("Hello World This is ESP Email Testing", true);
  smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP board</p></div>");
 
  smtpData.addRecipient(emailRecipient);

if(!MailClient.sendMail(smtpData))
{
  Serial.println("Error in Sending the Email"+MailClient.smtpErrorReason());
  }

  smtpData.empty();
  }

void loop() {
  // put your main code here, to run repeatedly:

}


void sendCallback(SendStatus message)
{
  Serial.println(message.info());

  if(message.success()){Serial.print("++++++++");}
}
