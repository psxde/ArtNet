// Please include ArtnetEther.h to use Artnet on the platform
// which can use both WiFi and Ethernet
#include <ArtnetEther.h>
// #include <ArtnetNativeEther.h>  // only for Teensy 4.1
// this is also valid for other platforms which can use only Ethernet
// #include <Artnet.h>

// Ethernet stuff
const IPAddress ip(192, 168, 0, 201);
uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

ArtnetSender artnet;
const String target_ip = "192.168.0.200";
uint16_t universe = 1;

const uint16_t size = 512;
uint8_t data[size];
uint8_t value = 0;

void setup() {
    Serial.begin(115200);
    delay(2000);

    Ethernet.begin(mac, ip);
    artnet.begin();

    Serial.println("start");
#ifdef UDP_TX_PACKET_MAX_SIZE
    Serial.println(UDP_TX_PACKET_MAX_SIZE);
#endif
}

void loop() {
    value = (millis() / 4) % 256;
    memset(data, value, size);

    artnet.setArtDmxData(data, size);
    artnet.streamArtDmxTo(target_ip, universe);  // automatically send set data in 40fps
    // artnet.streamArtDmxTo(target_ip, net, subnet, univ);  // or you can set net, subnet, and universe
}
