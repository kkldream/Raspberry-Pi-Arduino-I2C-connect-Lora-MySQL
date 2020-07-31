#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x04    // 設定Arduino開發板I2C的位址
#define LED_PIN 7
int status = 0;

void setup() {
  Serial.begin(250000);   // Serial通訊埠通訊設為9600速率
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);  // 初始化Arduino的I2C位址
  Wire.onReceive(receiveData); //I2C訊號接收時，啟用函式
  Wire.onRequest(sendData);  //主機要求讀取時，啟用函式
  
  Serial.println("LoRa Sender");
  LoRa.setPins(10, 9, 8);// set NSS, reset, DIO0 pin
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("\n\nReady!");
}

void loop() {
  
}

void receiveData(int byteCount){
  digitalWrite(LED_PIN, HIGH);
  while(Wire.available()){
    int msg = Wire.read();
    String str = "'";
    Serial.print("msg = ");
    Serial.println(msg);
    Serial.print("stutas = ");
    switch ((msg & 0b110000) >> 4) {
      case 0:
        Serial.println("Sleep");
        str += "Sleep";
        break;
      case 1:
        Serial.println("Move");
        str += "Move";
        break;
      case 2:
        Serial.println("Grip");
        str += "Grip";
        break;
      default:
        Serial.println("other");
        str += "other";
        break;
    }
    str += "','";
    Serial.print("trush = ");
    Serial.println(msg & 0b1111);
    str += msg & 0b1111;
    str += "'";
    
    LoRa.beginPacket();
    LoRa.print(str);
    Serial.println(str);
    LoRa.endPacket();
  }
  digitalWrite(LED_PIN, LOW);
}

void sendData(){
  Wire.write(status);
}
