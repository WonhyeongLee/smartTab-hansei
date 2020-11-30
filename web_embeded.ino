
#include <WiFi.h>
#include <ArduinoJson.h> //Json 사용을 위한 라이브러리 
//#include <HTTPClient.h>  //HTTP 전송을 위한 라이브러리
#include <PubSubClient.h> //MQTT 사용을 위한 라이브러리

//릴레이와 연결한 IO 설정
#define ESP32_GPIO1 5      
#define ESP32_GPIO2 17
#define ESP32_GPIO4 16

//WIFI 아이디, 비번 , MQTT 서버 , 포트 
const char* ssid = "KT_GiGA_2G_Wave2_1123";          // your network SSID (name)
const char* pass = "ke77ff4984";                     // your network password
const char* mqttServer = "172.30.1.53";
const int mqttPort = 1883;
//HTTPClient http;  
WiFiClient espClient;
PubSubClient client(espClient);

//개별멀티탭 초기상태설정 , 제어를 위한 변수 설정
int stateTab1 =1;
int stateTab2 =1;
int stateTab3 = 1;
String packet1,packet2,packet3;
char msg1[50];
char msg2[50];
char msg3[50];

// AdafruitIO_feed 테스트 
//AdafruitIO_Feed *counter = io.feed("first");
//AdafruitIO_Feed *counter2 = io.feed("second");
//AdafruitIO_Feed *counter4 = io.feed("third");

//WIFI 연결
void setup_wifi(){
    Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  Serial.print(F("WiFi connected! IP address: "));
  Serial.println(WiFi.localIP());
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/kkwon57/tab1", "FROM esp32 : tab1 connect");
      client.publish("/kkwon57/tab2", "FROM esp32 : tab2 connect");
      client.publish("/kkwon57/tab3", "FROM esp32 : tab3 connect");
      // ... and resubscribe
      client.subscribe("/kkwon57/tab_control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//  void handleMessage(AdafruitIO_Data *data){
//  Serial.print("received <- ");
//  Serial.println(data->value());
//  int state = data->toInt();
//  if(state==1){
//    digitalWrite(ESP32_GPIO4,LOW);
//  }else{
//    digitalWrite(ESP32_GPIO4,HIGH);
//  }
//  delay(2000);
//}

void setup() {
  // start the serial connection
  Serial.begin(115200);
  delay(1000);
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

   pinMode(ESP32_GPIO1, OUTPUT);
   pinMode(ESP32_GPIO2, OUTPUT);
   pinMode(ESP32_GPIO4, OUTPUT);
   
   digitalWrite(ESP32_GPIO1,LOW);
   digitalWrite(ESP32_GPIO2,LOW);
   digitalWrite(ESP32_GPIO4,LOW);



  // wait for serial monitor to open
//  while(! Serial);
//  Serial.print("Connecting to Adafruit IO");
//  // connect to io.adafruit.com
//  io.connect();
//   counter->onMessage(handleMessage);
//   counter2->onMessage(handleMessage);
//   counter4->onMessage(handleMessage);
//  // wait for a connection
//  while(io.status() < AIO_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }
//   counter->get();
//   counter2->get();
//   counter4->get();
//  // we are connected
//  Serial.println();
//  Serial.println(io.statusText());
//}
  // save count to the 'counter' feed on Adafruit IO
//  Serial.print("sending -> ");
//  Serial.println(count);
//  counter->save(count);
//
//  // increment the count by 1
//  count++;
//}
}
void loop() {

  //io.run();
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  packet1 = "tab1 state :   " + String(stateTab1); 
  packet2 = "tab2 state :   " + String(stateTab2); 
  packet3 = "tab3 state :   " + String(stateTab3); 
  packet1.toCharArray(msg1, 50); 
  packet2.toCharArray(msg2, 50); 
  packet3.toCharArray(msg3, 50); 
  client.publish("/kkwon57/tab1", msg1);
  client.publish("/kkwon57/tab2", msg2);
  client.publish("/kkwon57/tab3", msg3);
  delay(500);
}

void callback(char* topic, byte* payload, unsigned int length) {
  
String Msg="";
int i=0;
while(i<length) Msg += (char)payload[i++];

if(Msg == "TAB1 OFF"){
  stateTab1 = 0;
  digitalWrite(ESP32_GPIO1,HIGH);
}else if(Msg == "TAB1 ON"){
  stateTab1 = 1;
  digitalWrite(ESP32_GPIO1,LOW);
}else {
  Serial.println("error");
}
if(Msg == "TAB2 OFF"){
  stateTab2 = 0;
  digitalWrite(ESP32_GPIO2,HIGH);
}else if(Msg == "TAB2 ON"){
  stateTab2 = 1;
  digitalWrite(ESP32_GPIO2,LOW);
}else {
  Serial.println("error");
}
if(Msg == "TAB3 OFF"){
  stateTab3 = 0;
  digitalWrite(ESP32_GPIO4,HIGH);
}else if(Msg == "TAB3 ON"){
  stateTab3 = 1;
  digitalWrite(ESP32_GPIO4,LOW);
}else {
  Serial.println("error");
}
}
