# Tibber Arduino RealTime Power
A Arduino and python project that displays real time power consumption

Buildt with:
- Arduino Mega
- ESP8266
- 4-Digit LED Display

Run on server or other 24/7 computer:
1. Requires ‘Python GraphQL Client’ package: pip install python-graphql-client  
2. Open server.py and change UDP_IP and UDP_PORT to the IP of your Arduino  
3. Insert your Tibber "home ID" and "access token". You can get these at https://developer.tibber.com/  
4. run with "pyhon3 server.py  

In tibber.ino
1. Make sure the unsigned int localPort = 52522; matches UDP_PORT from server.py
2. Insert your SSID and PASSWORRD for your wifi network  
3. Upload to Arduino
