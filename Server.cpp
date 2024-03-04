#include "Server.h"
#include "Sensor.h"

char *ssid = "Mfm241@bin#_2.4GHz@unifi";
const char *password = "makanasi23";


unsigned int localPort = 8090;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet

ESP8266WiFiMulti WiFiMulti;
WiFiUDP Udp;

void connectWifi()
{
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid, password);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while (WiFiMulti.run() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void startServer(){
    Udp.begin(localPort);
}

void runServer()
{
    int packetSize = Udp.parsePacket();

    if (packetSize)
    {

        Serial.print("Received packet of size ");

        Serial.println(packetSize);

        Serial.print("From ");

        IPAddress remoteIp = Udp.remoteIP();

        Serial.print(remoteIp);

        Serial.print(", port ");

        Serial.println(Udp.remotePort());

        // read the packet into packetBufffer

        int len = Udp.read(packetBuffer, 255);

        if (len > 0)
        {

            packetBuffer[len] = 0;
        }

        Serial.println("Contents:");

        Serial.println(packetBuffer);

        // send a reply, to the IP address and port that sent us the packet we received

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

        char ReplyBuffer[100]; 
        sprintf(ReplyBuffer, "%2.2f, %2.2f%%", currentTempValue, currentHumidityValue);
        Serial.print("Reply: ");
        Serial.println(ReplyBuffer);
        Udp.write(ReplyBuffer);

        Udp.endPacket();
    }
}
