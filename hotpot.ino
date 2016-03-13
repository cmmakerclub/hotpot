#include <WiFiConnector.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);

MqttConnector *mqtt;
WiFiConnector *wifi;

#define RELAY_01_DISPENSE_PIN 3 // dispense
#define RELAY_02_REBOIL_PIN 4 // reboil

#define RELAY_03_WARM_STATUS_PIN 14 // warm status
#define RELAY_04_BOIL_STATUS_PIN 12 // boil status

#define RELAY_01_MASK 0b0000001
#define RELAY_02_MASK 0b0000010

#define MQTT_PORT        1883
#define PUBLISH_EVERY    1*1000 // every 15 seconds

/* comment ทิ้งถ้าไม่ส่ username/password */
#define MQTT_HOST "cmmc.xyz"
//#define MQTT_USERNAME "GaBH7sxFDUEX0hl"
//#define MQTT_PASSWORD "g6CtSEWUKwflkAyOEBE1IHF95ng="
#define MQTT_CLIENT_ID "hotpot001"
#define MQTT_PREFIX "/NatWeerawan/gearname"

/* SENSOR INFO */
#define DEVICE_NAME "ESP HOT POT"
#define AUTHOR      "Nat Weerawan"
#define BOARD       "ESPressoLite"
#define SENSOR      "RELAY"

/* WIFI INFO */
#define WIFI_SSID        ""
#define WIFI_PASSPHARSE  ""

#include "init_wifi.h"
#include "_receive.h"
#include "_publish.h"

void init_hardware()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("BEGIN");
  pinMode(RELAY_01_DISPENSE_PIN, OUTPUT);
  pinMode(RELAY_02_REBOIL_PIN, OUTPUT);

  digitalWrite(RELAY_01_DISPENSE_PIN, HIGH);
  digitalWrite(RELAY_02_REBOIL_PIN, HIGH);

  pinMode(RELAY_03_WARM_STATUS_PIN, INPUT);
  pinMode(RELAY_04_BOIL_STATUS_PIN, INPUT);

}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
  wifi->connect();
  mqtt->connect();
}

void loop()
{
  wifi->loop();
  mqtt->loop();
}
