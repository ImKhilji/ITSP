
#include<SoftwareSerial.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>

#define RELAY1 7
#define RELAY2 8
Servo myservo;  
int pos = 0; 
byte val;

byte mac[] = { 0x08, 0x00, 0x27, 0x01, 0xA8, 0x3F };
IPAddress ip(192,168,1,100); 
//byte gateway[] = { 10, 16, 35, 250};                  
//byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server(80); 

String readString;

SoftwareSerial serial(10,11); 

void setup(){
  myservo.attach(4);
  
  myservo.write(0);
  serial.begin(9600);
  Ethernet.begin(mac, ip /*gateway, subnet*/);
  server.begin();

  
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(2,OUTPUT);
}

void loop(){
              ///////////////////BLUETOOTH\\\\\\\\\\\\\\\\\\\
  digitalWrite(12,LOW);
  int a=0;
  if(serial.available()){
    val=serial.read();
    serial.println(int(val));
  }
  if(int(val)==49){
    digitalWrite(12,HIGH);
  }
  if(int(val)==50){
    digitalWrite(12,LOW);
  }
  if(int(val)==52){
    analogWrite(6,50);              
  }
  if(int(val)==53){
    analogWrite(6,100);
  }
  if(int(val)==54){
    analogWrite(6,150);
    //digitalWrite(2,HIGH);
  }
  if(int(val)==55){
    analogWrite(6,200);
    //digitalWrite(2,LOW);
  }
 if(int(val)==56){
    analogWrite(6,255);
}
if(int(val)==51){
    analogWrite(6,0);
}
if(int(val)==57){
  //for (pos = 0; pos <= 180; pos += 2) {  
    myservo.write(180);              
    //delay(100);                       
  //}
}
if(int(val)==48){
 // for (pos = 180; pos >= 0; pos -= 2) { 
    myservo.write(0);              
 //   delay(100);                       
 // }
}
                  ///////////////ETHERNET\\\\\\\\\\\\\\\\

EthernetClient client = server.available();
  if (client) {  
    while (client.connected()) {
      if (client.available()) {   
        char c = client.read();
        if (readString.length() < 100) {
            readString += c;
           }
        
        Serial.println(readString);
        if (c == '\n') {

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<meta http-equiv='refresh' content='5'>");
          //client.println("<meta http-equiv=\"/refresh\"\" content=\"/5; URL='http://192.168.100.19'\"\">");
          client.println("<link rel='stylesheet' type='text/css' href='http://homepages.iitb.ac.in/~14d070044/Third.css' />");
          client.println("<TITLE>Arduino Control Online</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>TechnoHome</H1>");
          client.println("<hr />");
          client.println("<div id='buttons'>");
          client.println("<a href=\?button1on class='btn blue'>Button 1 ON</a>");
          client.println("<a href=\?button1off class='btn blue'>Button 1 OFF</a>");
          client.println("<H3>");
          if (readString.indexOf("?1") > 0) {
            digitalWrite(8, HIGH);
            
          }
          if (readString.indexOf("?2") > 0) {
            digitalWrite(8, LOW);
            
          }
          if (readString.indexOf("?3") > 0) {
            analogWrite(6, 0);
            
          }
          if (readString.indexOf("?4") > 0) {
            analogWrite(6, 50);
            
          }
          if (readString.indexOf("?5") > 0) {
            analogWrite(6, 100);
            
          }
          if (readString.indexOf("?6") > 0) {
            analogWrite(6, 150);
            
          }
          if (readString.indexOf("?7") > 0) {
            analogWrite(6, 200);
            
          }
          if (readString.indexOf("?8") > 0) {
            analogWrite(6, 255);
            
          }
         /* if (readString.indexOf("?9") > 0) {
            myservo.write(180);
            
          }
          if (readString.indexOf("?0") > 0) {
            myservo.write(0);
            
          }*/
          if (readString.indexOf("?10") > 0) {
            digitalWrite(RELAY1,HIGH);
            delay(8000);
            digitalWrite(RELAY1,LOW);
          }
          if(readString.indexOf("?11") > 0) {
            digitalWrite(RELAY2,HIGH);
            delay(8000);
            digitalWrite(RELAY2,LOW);
          }

          readString = "";

          client.println("</body>");
          client.println("</html>");
          
          
          
          
          delay(100);
          client.stop();
          
         

          // close the connection
          
        }
      }
    }
  }
}

