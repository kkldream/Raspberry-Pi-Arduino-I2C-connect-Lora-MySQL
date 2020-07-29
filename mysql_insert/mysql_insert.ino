#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

const char ssid[]     = "kk_2.4G";// change to your WIFI SSID
const char password[] = "88888888";// change to your WIFI Password
IPAddress server_addr(192,168,0,10);// change to you server ip, note its form split by "," not "."
int MYSQLPort = 3308;   //mysql port default is 3306
char user[] = "kk";// Your MySQL user login username(default is root),and note to change MYSQL user root can access from local to internet(%)
char pass[] = "12332162";// Your MYSQL password

WiFiClient client;            
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(250000);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);  
  //try to connect to WIFI 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //try to connect to mysql server
  if (conn.connect(server_addr, MYSQLPort, user, pass)) {
     delay(1000);
  }
  else{
    Serial.println("Connection failed.");
  }
  delay(2000);  
  //insert, change database name and values by string and char[]
  char INSERT_SQL[] = "INSERT INTO robot.test (status,trash,gps) VALUES ('Move','1','N25.020,E121.380')";
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);  
  cur_mem->execute(INSERT_SQL);//execute SQL
  delete cur_mem;
  conn.close();                  // close the connection
  Serial.println("Data Saved.");
}
void loop() {
//do nothing
}
