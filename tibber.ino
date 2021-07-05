#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <TM1637TinyDisplay.h>

char ssid[] = "insert_your_ssid";            // your network SSID (name)
char pass[] = "insert_your_password";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned int localPort = 52522;  // local port to listen on
int disptemp;

char packetBuffer[64];          // buffer to hold incoming packet

WiFiEspUDP Udp;
TM1637TinyDisplay display(6, 7); //CLK, DIO

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  WiFi.init(&Serial3);

  display.setBrightness(BRIGHT_1);
  display.clear();

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
    IPAddress remoteIp = Udp.remoteIP();
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    
    Serial.println(packetBuffer);
    disptemp = atoi(packetBuffer);
    display.showNumber(disptemp, false, 4, 0);    // Number, length=4, position=0 (left)
  }
}
