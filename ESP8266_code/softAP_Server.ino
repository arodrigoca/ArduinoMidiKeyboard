#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

#include "index.h"

#ifndef APSSID
#define APSSID "314Synth"
#define APPSK  "itspi"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
const byte DNS_PORT = 53;
DNSServer dnsServer;
ESP8266WebServer server(80);
IPAddress apIP(192, 168, 1, 1);

void handleRoot() {

  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
  Serial.println("Message sent to client");
}

void handleCommand(){
  String command = server.arg("command");
  Serial.println(command);
  server.send(200, "text/plane", command); //Send web page
  if(command = "gen_up"){
    digitalWrite(0, HIGH);
    delay(500);
    digitalWrite(0, LOW);
  }else if(command == "gen_down"){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
  }
}

void test_handler(){
  server.send(200, "text/plane", "This is a test");
}

void setup() {
  //delay(1000);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "www.example.com", apIP);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/send_command", handleCommand);
  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
