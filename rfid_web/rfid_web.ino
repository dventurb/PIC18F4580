#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5     // pino SDA
#define RST_PIN 21   // pino RST

MFRC522 rfid(SS_PIN, RST_PIN); // Criação do objeto MFRC522

const char *ssid = "ap-projeto";
const char *password = "a1234567";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Inicia o SPI
  rfid.PCD_Init(); // Inicia o leitor RFID
  WiFi.softAP(ssid, password);
  
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, World!");
  });

  server.begin();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) {
        Serial.print(":");
      }
    }
    Serial.println();
    delay(1000); // Delay para evitar múltiplas leituras
    rfid.PICC_HaltA(); // Para a leitura
  }
}
