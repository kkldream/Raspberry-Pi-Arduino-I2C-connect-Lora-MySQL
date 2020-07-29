#include <SPI.h>
#include <LoRa.h>
#define LED_PIN 2
#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
const char ssid[]     = "kk_2.4G";
const char password[] = "88888888";
IPAddress server_addr(192,168,0,11);
int MYSQLPort = 3308;
char user[] = "kk";
char pass[] = "12332162";
WiFiClient client;            
MySQL_Connection conn((Client *)&client);
void setup() {
  Serial.begin(250000);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (conn.connect(server_addr, MYSQLPort, user, pass)) delay(1000);
  else Serial.println("Connection failed.");
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("LoRa Receiver Callback");
  LoRa.setPins(5, 22, 17); //NSS, reset, DIO0
  if (!LoRa.begin(433E6)) {
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
    String str = "INSERT INTO robot.test (status,trash,gps) VALUES (";
    while (LoRa.available()) {
      str += (char)LoRa.read();
    }
    str += ",'24.745378,121.74488')";
    Serial.println(str);
    char INSERT_SQL[str.length()];
    str.toCharArray(INSERT_SQL,str.length());
'    // print RSSI of packet
    Serial.print(" with RSSI ")    Serial.println(LoRa.packetRssi());

    //char INSERT_SQL[] = "INSERT INTO robot.test (status,trash,gps) VALUES ('Move','1','24.745378,121.74488')";
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);  
    cur_mem->execute(INSERT_SQL);//execute SQL
    delete cur_mem;
  }
}
