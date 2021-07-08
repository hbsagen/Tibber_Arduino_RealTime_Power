#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <TM1637TinyDisplay.h>

char ssid[] = "K40";                                     // your network SSID (name)
char pass[] = "2eaee065047f63383b869ca7379bab26";        // your network password
int status = WL_IDLE_STATUS;                             // the Wifi radio's status
unsigned long nc;
unsigned int localPort = 52522;                          // local port to listen on
char packetBuffer[64];

WiFiEspUDP Udp;
TM1637TinyDisplay display(6, 7);                         //CLK, DIO

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  
  display.setBrightness(BRIGHT_1);
  display.clear();
  display.showString("boot",4,0);
  
  WiFi.init(&Serial3);

  if (WiFi.status() == WL_NO_SHIELD) {
        while (true);
  }

  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
  }

  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }

    if (atoi(packetBuffer) > 9999){
      display.showNumber(9999, false, 4, 0);
    }
    else {
      display.showNumber(atoi(packetBuffer), false, 4, 0);
      nc = millis();
    }
  }
  else if (millis() - nc > 10000) {                      //time before timout, "nc" displayed
      display.showString(" nc ",4,0);
  }
}
