
// WiFi Lib

#include "WiFi.h"
void WiFiConnectionInit()
{
  WiFi.begin(SSID, PWD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(666);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("------------YOU ARE NOW CONNECTED TO THE INTERNET-------------");
  Serial.println(" Connected to the Wireless network of spells with IP Address: ");
  Serial.println(WiFi.localIP());
}
