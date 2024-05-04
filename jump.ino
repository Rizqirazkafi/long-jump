#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Arduino.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <SafeString.h>
String sensor1 = "iotapp/sensor1";
String sensor2 = "iotapp/sensor2";
String sensor3 = "iotapp/sensor3";
void connectWifi();
void connect_mqtt();
String mqttBroker = "test.mosquitto.org";
WiFiClient client;
PubSubClient mqtt(client);

void setup() {
  pinMode(14, OUTPUT);
  Serial.begin(9600);
  connectWifi();
  mqtt.setServer(mqttBroker.c_str(), 1883);
}

// testing
void loop() {
  digitalWrite(14, LOW);
  if(!mqtt.connected()){
    connect_mqtt();
    Serial.println("MQTT Connected");
    mqtt.publish("ioatapp/on", "ONLINE");
  }
  mqtt.loop();
  String input_sensor1 = String(digitalRead(D1));
  if (input_sensor1 == "1"){
    input_sensor1 = "tripped";
    for (int i = 0; i < 3 ; i++){
      mqtt.publish(sensor1.c_str(), input_sensor1.c_str());
      Serial.println(input_sensor1);
      digitalWrite(14, HIGH);
      delay(500);
      digitalWrite(14, LOW);
      delay(1000);
    }
    return;
  }else {
    input_sensor1 = "clear";
    mqtt.publish(sensor1.c_str(), input_sensor1.c_str());
    Serial.println(input_sensor1);
  }
  String input_sensor2 = String(digitalRead(D2));
  if (input_sensor2 == "1"){
    input_sensor2 = "tripped";
    for (int i = 0; i < 3; i++){
      mqtt.publish(sensor2.c_str(), input_sensor2.c_str());
      Serial.println(input_sensor2);
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(200);
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(1000);
    }
    return;
  }else {
    input_sensor2 = "clear";
    mqtt.publish(sensor2.c_str(), input_sensor2.c_str());
    Serial.println(input_sensor2);
  }
  String input_sensor3 = String(digitalRead(D3));
  if (input_sensor3 == "1"){
    input_sensor3 = "tripped";
    for (int i = 0; i < 3; i++){
      mqtt.publish(sensor3.c_str(), input_sensor3.c_str());
      Serial.println(input_sensor3);
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(200);
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(200);
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(1000);
    }
    return;
  }else {
    input_sensor3 = "clear";
    mqtt.publish(sensor3.c_str(), input_sensor3.c_str());
    Serial.println(input_sensor3);
  }
  delay(100);
}
void connectWifi() {
  WiFi.hostname("JUMP1");
  WiFiManager wm;
  wm.resetSettings();
  bool res;
  res = wm.autoConnect("jump1", "Segosambel!@3");
  if (!res) {
    Serial.println("Failed to connect");
  } else {
    Serial.println("Connected");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
  }
}
void connect_mqtt(){
  while(!mqtt.connected()){
    Serial.println("Connecting MQTT ...");
    if(mqtt.connect("iotapp")){
      mqtt.subscribe("iotapp/sensor1");
    }
  }
}
