
// Json Lib
#include "ArduinoJson.h"

String parseDataToJson()
{
  
  DynamicJsonDocument package(256);

    // Prepare JSON document with correct array structure
  JsonObject deviceData = package.createNestedObject("device");
   
  deviceData["deviceName"]      = deviceName;
  deviceData["mcuType"]         = mcuType;
  deviceData["sensor"]          = sensorType;


  JsonObject locationData = package.createNestedObject("location");
  locationData["locationName"]  = locationName;
  locationData["latitude"]      = String(latitude);
  locationData["longitude"]     = String(longitude);
  //char result[8]; // 
  //dtostrf(resistance, 6, 2, result); //6an e hela siffron och 2an antal decimal

  JsonObject measurementData = package.createNestedObject("measurement");

  measurementData["measurementTime"]  = String(epochTime);
  measurementData["temperature"]      = tempCelcius;
  measurementData["humidity"]         = humi;
  //measurementData["heatIndex"]        = heatIndexCelcius;
  


  // Serialize JSON document
  String jsonPackage;
  serializeJson(package, jsonPackage);
  Serial.println(jsonPackage);
  Serial.println("Package :");
  //Serial.println(package);

  return jsonPackage;
}


bool sendFunction(String jsonPackage)
{
  HTTPClient http;

  // Send request
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponse = http.POST(jsonPackage);
  
  if(!http.POST(jsonPackage))
  {
    Serial.println("Failed to send package");
    return false;
  }

    // Read response and print to console
  Serial.println(http.getString() + " Has been sent");

  // Disconnect
  http.end();
  return true;
}
