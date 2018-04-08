/* 
 *  LINKS
 *  https://circuits4you.com/2018/02/05/esp8266-arduino-wifi-web-server-led-on-off-control/
 *  http://forum.arduino.cc/index.php?topic=41954.0
 *  https://eatelier.nl/?e_tutorial=esp8266-web-server
 *  https://iot-playground.com/blog/2-uncategorised/40-esp8266-wifi-relay-switch-arduino-ide
 *  
 */ 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define Red D1
#define Yellow D2

String RedStatus,YellowStatus;

const char* ssid = "WIFI-SSID";
const char* password = "WIFI-PASSWORD";

ESP8266WebServer server(80); //Port 80

void togglePin(int pinNum) {
  digitalWrite(pinNum, !digitalRead(pinNum));
}

void handleRoot() {
  String html = "<HTML>";
  html += "<TITLE>Relay Controller</TITLE>";
  html += "<BODY>";
  html += "<FORM method='post' action='/form'>";
  html += "<TABLE>";
  
  html += "<TR>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='RedOn' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='RedOff' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD>" + RedStatus + "</TD>";
  html += "</TR>";
   
  html += "<TR>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='YellowOn' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='YellowOff' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD>" + YellowStatus + "</TD>";
  html += "</TR>";
   
  html += "<TR>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='AllOn' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD><INPUT TYPE=SUBMIT VALUE='AllOff' name=submit style='height:300px; width:300px'></TD>";
  html += "<TD></TD>";
  html += "</TR>";
  
  html += "</TABLE>";
  html += "</FORM>";
  html += "</BODY>";
  html += "</HTML>";

  server.send(200, "text/html", html);
}

void handleForm() {
  String t_state = server.arg("submit");
  
  //Change Red
  if(t_state=="RedOn")
  {
    RedStatus="ON";    
    digitalWrite(Red, HIGH);
  }
  
  if(t_state=="RedOff")
  {
    RedStatus="OFF";    
    digitalWrite(Red, LOW);
  }
  //Change Yellow
  if(t_state=="YellowOn")
  {
    YellowStatus="ON";    
    digitalWrite(Yellow, HIGH);
  }
  
  if(t_state=="YellowOff")
  {
    YellowStatus="OFF";    
    digitalWrite(Yellow, LOW);
  }
  //Change All
  if(t_state=="AllOn")
  {
    RedStatus="ON";
    YellowStatus="ON";
    digitalWrite(Red, HIGH);
    digitalWrite(Yellow, HIGH);
  }
  
  if(t_state=="AllOff")
  {
    RedStatus="OFF";
    YellowStatus="OFF";
    digitalWrite(Red, LOW);
    digitalWrite(Yellow, LOW); 
  }
 
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //The HTTP 302 redirects back to the main page
   
  delay(500);
}

void setup(void){
  Serial.begin(115200);

  WiFi.hostname("LivingRoom");
  WiFi.begin(ssid, password);
  Serial.println("");

  //Setup Digital Pins for Relay Control
  pinMode(Red,OUTPUT); 
  pinMode(Yellow,OUTPUT); 
  //Set Pin Power Low by default
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);
  server.on("/form", handleForm);
  server.begin();
}

void loop(void){
  server.handleClient();
}
