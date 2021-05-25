#include "includes.h"


void setup() 
{
  // Initialize
  Serial.begin(115200);
  delay(100);
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_SECONDS * uS_TO_S_FACTOR);
  WiFiConnectionInit();// This Section should be started before other functions, Without WiFi nothing will work....
  dht.begin();
  newLocationApiGet(getMyPublicIP());
  initializeCurrentlLocationTime();
  pinMode(ONBOARD_LED, OUTPUT);
  delay(100);
  
  // Setup Callbacks
  //client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
    
  // Send a ping
  client.ping();

  // Data update and send
  routineDataCheckNSend();

  Serial.println(F("Going to sleep"));
   delay(1000);
  Serial.flush(); 
  
  esp_deep_sleep_start();
}

void loop() 
{
  //not used
}
