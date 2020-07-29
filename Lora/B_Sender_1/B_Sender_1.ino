#include <SPI.h>
#include <LoRa.h>
#define LED_PIN D1
int counter = 0;

void setup() {
  Serial.begin(115200);
//  while (!Serial);

  Serial.println("LoRa Sender");
  pinMode(LED_PIN, OUTPUT);
  LoRa.setPins(D8, D4, D0);// set NSS, reset, DIO0 pin
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();
  
  counter++;
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(900);
  
}
