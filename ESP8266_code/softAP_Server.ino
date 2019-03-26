#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h"

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {

  //String html_page = String("<!DOCTYPE HTML>\r\n") + "<html><head><meta name='viewport' charset='utf-8' content='width=device-width, initial-scale=1'><title>Sunvox Manager</title><style>#main_header{ color: blue; font-family: 'Lucida Console', Monaco, monospace;}</style><script> function gen_up(){ console.log('Generator Up'); } function gen_down(){ console.log('Generator Down'); }</script></head><body><h1 id='main_header'>Sunvox Controls</h1><div> <form action='/gen_up'> <input type='submit' value='Generator Up'></input> </form></div><div> <form action='/gen_down'> <input type='submit' value='Generator Down'></input> </form></div></html>";
  //server.send(200, "text/html", html_page);
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
  Serial.println("Message sent to client");
}

void handleCommand(){
  String command = server.arg("command");
  Serial.println(command);
  server.send(200, "text/plane", command); //Send web page
}

void setup() {
  //delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/send_command", handleCommand);
  server.begin();
}

void loop() {
  server.handleClient();
}
