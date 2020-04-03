#include <LoRa.h>
#include<String.h>
#include<SPI.h>
#include<ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ss 15
#define rst 16
#define dio0 2
WidgetLCD lcd(V1);

char auth[] = "AuthorizationCode";
char ssid[]="WiFi Username";
char password[]="WiFi Password";

void setup() 
{
  Serial.begin(9600); 
  Blynk.begin(auth,ssid,password);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
  Serial.println("LoRa Started");
  lcd.clear();
  lcd.print(1,0,"Waiting");
}

void loop() 
{
  Blynk.run();
  String str1="",str2="";
  int packetSize = LoRa.parsePacket(),i=0,len;
  if (packetSize) 
  {
    Serial.print("Received packet ");
    while (LoRa.available()) 
    {
      str1=str1+((char)LoRa.read()); 
    }
    Serial.println(str1);
    len=str1.length();
    //We can print only 15 characters in a single line. 
    //If there are more than 15 characters, we print them on next line.
    if(len-15 > 0)
    {
      str2=str1.substring(15,len);      
      str1=str1.substring(0,14);
    }
    lcd.clear();  
    lcd.print(0,0,str1);
    lcd.print(0,1,str2);
   }
}
