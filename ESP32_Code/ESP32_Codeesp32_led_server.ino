#include <WiFi.h>
#include <WebServer.h>

/* -------- WiFi Details -------- */
const char* ssid = "mohini_4G";
const char* password = "salonikawifi";

/* -------- Web Server -------- */
WebServer server(80);

/* -------- LED Pins -------- */
const int LED1 = 27;
const int LED2 = 26;
const int LED3 = 25;
const int LED4 = 33;
const int LED5 = 32;

/* -------- Function -------- */
void allOff() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  allOff();

  /* -------- WiFi Connect -------- */
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  /* -------- ROUTES (CUMULATIVE) -------- */

  server.on("/F1", []() {
    allOff();
    digitalWrite(LED1, HIGH);
    server.send(200, "text/plain", "1 LED ON");
  });

  server.on("/F2", []() {
    allOff();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    server.send(200, "text/plain", "2 LED ON");
  });

  server.on("/F3", []() {
    allOff();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    server.send(200, "text/plain", "3 LED ON");
  });

  server.on("/F4", []() {
    allOff();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    server.send(200, "text/plain", "4 LED ON");
  });

  server.on("/F5", []() {
    allOff();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    server.send(200, "text/plain", "5 LED ON");
  });

  server.on("/OFF", []() {
    allOff();
    server.send(200, "text/plain", "ALL LED OFF");
  });

  server.begin();
  Serial.println("Server Started");
}

void loop() {
  server.handleClient();
}