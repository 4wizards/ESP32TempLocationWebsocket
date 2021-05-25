// Sensor Lib
#include "Adafruit_Sensor.h"
#include "DHT.h"
#include "DHT_U.h"

#define DHTPIN 22      // Wont interfere with WiFi connectivity
#define DHTTYPE DHT11  // Just the booring old DHT11
#define CELCIUS 0
#define FARENHEIT 1
#define tempDiff 1

DHT dht(DHTPIN, DHTTYPE);

RTC_DATA_ATTR float previousTemp = NAN; //keeps value during deep sleep

//Globaly accessable Sensordata
float tempCelcius = NAN;
float heatIndexCelcius = NAN;
float currentTemp = NAN;
float humi = NAN;

float tempFarenheit = NAN;
float heatIndexFarenheit = NAN;

void checkSensorDataCelcius() 
{
  humi = dht.readHumidity();
  tempCelcius = dht.readTemperature();
  heatIndexCelcius = dht.computeHeatIndex(tempCelcius,humi,CELCIUS);
  Serial.println("Sensor Data Updated");
  currentTemp = tempCelcius;
}

void checkSensorDataFarenheit()
{
  tempFarenheit = dht.convertCtoF(tempCelcius);
  heatIndexFarenheit = dht.computeHeatIndex(FARENHEIT);
  Serial.println("Sensor Data Updated");
  currentTemp = tempFarenheit;  
  
} 
