#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "L04D_57EB8F81";
const char* password = "261DE409";

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.on("/aircon", []() {

    if(server.args() > 0)
    {
      if(server.argName(0) == "ope")
      {
        if(server.arg(0) == "run")
        {
          Serial.println("run");
          server.send(200, "text/plain", "Required 'run'");
        }
        else if(server.arg(0) == "power")
        {
          Serial.println("power");
          server.send(200, "text/plain", "Required 'power'");
        }
        else if(server.arg(0) == "stop")
        {
          Serial.println("stop");
          server.send(200, "text/plain", "Required 'stop'");
        }
        else
        {
          server.send(200, "text/plain", "Invalid parameter value.");
        }
      }
      else
      {
        server.send(200, "text/plain", "Invalid parameter name.");
      }
    }
    else
    {
      server.send(200, "text/plain", "Missing parameter.");
    }
    //server.argName(i) + ": " + server.arg(i)
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
