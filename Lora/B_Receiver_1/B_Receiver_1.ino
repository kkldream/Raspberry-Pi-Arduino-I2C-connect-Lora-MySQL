#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");

  LoRa.setPins(D8, D4);// set NSS, reset, DIO0 pin
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
