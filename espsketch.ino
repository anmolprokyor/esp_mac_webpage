#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
const char* ssid = "Airtel_harm_7181";
const char* password = "air29929";
WebSocketsServer webSocket = WebSocketsServer(81);
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();  
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); 
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
void loop() {
  webSocket.loop();
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.println("WebSocket connected");
    String macAddress = WiFi.macAddress();
    webSocket.sendTXT(num, macAddress);
  }
}
