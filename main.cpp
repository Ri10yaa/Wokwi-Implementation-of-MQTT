#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker
const char* mqttServer = "192.168.162.64";   // change to your MQTT server IP
const int mqttPort = 1883;

// Topics
const char* pubTopic = "pubC";
const char* subTopic = "subC";


LiquidCrystal_I2C lcdPub(0x27, 16, 2);  
LiquidCrystal_I2C lcdSub(0x3F, 16, 2);  

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;


void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
}

void messageHandler(char* topic, byte* payload, unsigned int length) {

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received: ");
  Serial.println(message);

  lcdSub.setCursor(0, 1);
  lcdSub.print(message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");

    if (client.connect("ESP32_Client")) {
      Serial.println("connected");
      client.subscribe(subTopic);
    } else {
      Serial.print("Failed, rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  lcdPub.init();
  lcdPub.backlight();
  lcdPub.setCursor(0,0);
  lcdPub.print("Publisher:");

  lcdSub.init();
  lcdSub.backlight();
  lcdSub.setCursor(0,0);
  lcdSub.print("Subscriber");

  setup_wifi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(messageHandler);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if (millis() - lastMsg > 5000) {
    lastMsg = millis();

    String msg = "Hi from ESP32!";
    client.publish(pubTopic, msg.c_str());

    Serial.println("Published: " + msg);
 
    lcdPub.setCursor(0, 1);
    lcdPub.print(msg);
  }
}