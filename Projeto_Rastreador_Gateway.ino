/*
  This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
  Base on TinyGPSPlus //https://github.com/mikalhart/TinyGPSPlus
*/

#include <TinyGPS++.h>
#include "boards.h"
#include <LoRa.h>

String serial_numer = "2023-11-01RX";


TinyGPSPlus gps;

unsigned long tempo_teste_leitura_gps = millis();

void displayInfo();

void setup() {
  initBoard();
  // When the power is turned on, a delay is required.
  delay(1500);

  Serial.println(TinyGPSPlus::libraryVersion());

  Serial.print("LoRa Gateway ");
  Serial.println(serial_numer);

  LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
  if (!LoRa.begin(LoRa_frequency)) {
    Serial.println("Falha ao Inicialiar o Lora!");
    while (1)
      ;
  }
}

void loop() {

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet

    String recv = "";
    // read packet
    while (LoRa.available()) {
      recv += (char)LoRa.read();
    }

    Serial.print("Dados recebidos: ");
    Serial.println(recv);
  }
}

void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
