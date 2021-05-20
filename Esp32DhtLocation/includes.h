

//--------------------------------------
//           Include Project .h Files
//--------------------------------------

#include "SECRET.h"                // <-- Sensitive data, passwords and DB Connection strings
#include "deviceConfig.h"          // <-- Configuration properties on the device

#include "WiFiConnectionConfig.h"
#include "HTTPPostConfig.h"
#include "DHTConfig.h"
#include "GoogleMapsApi.h"
#include "EpochTimeConfig.h"
#include "sendConfig.h"
#include <ArduinoWebsockets.h>


void serialPrintDataSets()
{
      Serial.println("-----------------------------\n");
      Serial.println("Device Stuff");
      Serial.print("Device Id : ");         Serial.println(deviceName);
      Serial.print("Location Name : ");     Serial.println(locationName);

      Serial.println("------------Measurements-------------\n");
      
      Serial.println("New Data ::");
      Serial.print("Temperature : ");       Serial.println(currentTemp);
      Serial.print("Humidity : ");          Serial.println(humi);
      Serial.print("Feels like : ");        Serial.println(heatIndexCelcius);
      Serial.print("EpochTime : ");         Serial.println(epochTime);
      Serial.print("Location Lat: ");       Serial.println(latitude);
      Serial.print("Location Lon: ");       Serial.println(longitude);

      Serial.println("-----------------------------\n");
}
