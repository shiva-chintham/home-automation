
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server;
uint8_t pin_led = 2;
  
char* ssid = "samsung";
char* password = "shiva@123";


void setup()
{
  
  pinMode(16,OUTPUT);                                         // Digital Pin 10 as Input Pin for Motor A
  pinMode(5,OUTPUT);                                          // Digital Pin 9 as Input Pin for Motor A
  pinMode(4,OUTPUT);                                          // Digital Pin 7 as Input Pin for Motor B
  pinMode(0,OUTPUT);                                          // Digital Pin 6 as Input Pin for Motor B

 
  SPIFFS.begin();
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",serveIndexFile);
  server.on("/ledstate",getLEDState);
  server.on("/bulb_one",bulb_one);
  server.on("/bulb_two",bulb_two);
  server.on("/bulb_three",bulb_three);
  server.on("/bulb_four",bulb_four);
  
  server.begin();
}
void serveIndexFile()
{

  File file=SPIFFS.open("/index.html","r");
  server.streamFile(file,"text/html");
  file.close();
}


void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
}

void getLEDState()
{
  toggleLED();
  String led_state = digitalRead(pin_led) ? "ON" : "OFF";
  server.send(200,"text/plain", led_state);
}
void bulb_one()
{

digitalWrite(pin_led,!digitalRead(pin_led));
  digitalWrite(16,!digitalRead(16));
  Serial.println(digitalRead(16));
  Serial.println("bulb one");
   
}

void bulb_two(){
   digitalWrite(5,!digitalRead(5));
   Serial.println("bulb two");
   
   Serial.println(digitalRead(5));
  
}


void bulb_three(){
   digitalWrite(4,!digitalRead(4));
   Serial.println("bulb three");
  
     Serial.println(digitalRead(4));
}


void bulb_four(){
   digitalWrite(0,!digitalRead(0));
   Serial.println("bulb four");
 
   Serial.println(digitalRead(0));
   
}
