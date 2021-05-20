
#include "includes.h"

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;

void sendFunctionWebsocket(String jsonPackage){
  if(client.connect(websockets_server) == false){
    client.connect(websockets_server);
    }else{
      client.send(jsonPackage);
    }
}

void setup() {
 
  Serial.begin(115200);
  delay(100);
  WiFiConnectionInit();// This Section should be started before other functions, Without WiFi nothing will work....
  dht.begin();
  newLocationApiGet(getMyPublicIP());
  initializeCurrentlLocationTime();
  refreshEpochTime();
  delay(100);
  
  // Setup Callbacks
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
    
  // Send a ping
  client.ping();
}

void loop() 
{
  while(WiFi.status() == WL_CONNECTED)
  {
    refreshEpochTime();
    checkSensorDataCelcius();
    
    //if (currentTemp > (previousTemp + tempDiff) || currentTemp < (previousTemp - tempDiff))
    //{
        if(epochTime> 1600000000){
          String package = parseDataToJson();
          sendFunctionWebsocket(package);
          sendFunction(package);
          serialPrintDataSets(); // Uncomment if serial check is necessary
        }
    //}
    delay(SLEEPTIME);
  }
  
}
