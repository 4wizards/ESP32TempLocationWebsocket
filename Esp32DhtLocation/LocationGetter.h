
#include <ArduinoJson.h>
//GPS Coordinates in globaly reachable variables
float latitude = 0.0;
float longitude = 0.0;
String locationName;


String getMyPublicIP()
{
  HTTPClient http;
  while (true) {
    http.begin("http://api.ipify.org/?format=json");
    int httpCode = http.GET();

    if (httpCode > 0)
    { //Check for the returning code
      DynamicJsonDocument doc(ESP.getMaxAllocHeap());
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);

      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        http.end();
        return "00.00.00.00";
      }
      else
      {
        String ip = doc["ip"];
        http.end();
        return ip;
      }
    }
  }
  return "00.00.00.00";
}


void newLocationApiGet(String myIp)
{
  HTTPClient http;
  while (true)
  {
    // Send request
    http.begin(IP_GEO_CONNECT + myIp);
    delay(100);
    int httpCode = http.GET();

    if (httpCode > 0)
    { //Check for the returning code
      //const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(3);
      DynamicJsonDocument doc(ESP.getMaxAllocHeap());
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      DeserializationError error = deserializeJson(doc, payload);

      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      else {
        longitude = doc["longitude"];
        latitude = doc["latitude"];
        locationName = doc["city"].as<String>();
        printf("from new api : Long  - %.3f, Lat - %.3f\n\n", longitude, latitude);
        http.end();
        return;
      }

    } else {

      Serial.println("Error on HTTP request");
      delay(200);

    }

  }
}
