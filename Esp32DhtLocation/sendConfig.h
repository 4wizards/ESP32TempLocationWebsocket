


#include "ArduinoJson.h"
bool _ERROR = false;
unsigned long previousMillis;
int LedState = 0;

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

  if (!http.POST(jsonPackage))
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


void sendingError()
{
  if (_ERROR)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1000)
    {

      if (LedState == 0)
      {
        digitalWrite(ONBOARD_LED, HIGH);
        LedState = 1;
      }

      else
      {
        digitalWrite(ONBOARD_LED, LOW);
        LedState = 0;
      }
      previousMillis = currentMillis;
    }
  }
}



void routineDataCheckNSend()
{
  while (WiFi.status() == WL_CONNECTED )
  {
    refreshEpochTime();
    checkSensorDataCelcius();
    while (isnan(currentTemp))
    {
      _ERROR = true;
      sendingError();
      checkSensorDataCelcius();
      if (!isnan(currentTemp)) {
        _ERROR = false;
      }
    }

   
    if ((epochTime > 1600000000) && (!isnan(currentTemp)) && (_ERROR == false) )
    {

      String package = parseDataToJson();
      sendFunctionWebsocket(package);
      sendFunction(package);
      serialPrintDataSets(); // Uncomment if serial check is necessary
      WiFi.disconnect();
    }

  }
}
