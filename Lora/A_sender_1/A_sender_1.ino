#include <SPI.h>
#include <LoRa.h>

int counter = 0; //傳送次數計數器
void setup() {
  Serial.begin(115200);
  while (!Serial);  //等待序列埠起始完畢
  Serial.println("LoRa Sender");
  LoRa.setPins(5, 22, 4); //NSS, reset, DIO0
  
//  LoRa.setFrequency(433E6);
//  LoRa.setSpreadingFactor(6);
//  LoRa.setSignalBandwidth(125E3);
//  LoRa.setCodingRate4(5);
//  LoRa.setPreambleLength(8);
  LoRa.setTxPower(1000);
  
  if (!LoRa.begin(915E6)) {  //起始 433MHz LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  LoRa.beginPacket();  //封包傳送開始
  LoRa.print("hello ");  //封包內容
  LoRa.print(counter);  //封包內容
  LoRa.endPacket();  //封包傳送結束
  counter++;  //計數器增量 1
  delay(1000);
}
