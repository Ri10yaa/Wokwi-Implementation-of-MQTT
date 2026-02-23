# ESP32 MQTT Publisher & Subscriber with Dual I2C LCDs

## Project Overview

This project demonstrates how an ESP32 acts as both an MQTT publisher
and subscriber using two 16x2 I2C LCD displays.

-   LCD 1 displays published messages.
-   LCD 2 displays subscribed (received) messages.

Both LCDs share the same I2C bus but use different I2C addresses.

------------------------------------------------------------------------

## Hardware Used

-   ESP32 DevKit V1
-   2 × 16x2 I2C LCD Displays
-   WiFi Network
-   MQTT Broker (Mosquitto recommended)

------------------------------------------------------------------------

## I2C LCD Addresses

  LCD     I2C Address   Purpose
  ------- ------------- ------------------------------
  LCD 1   0x27          Displays Published Messages
  LCD 2   0x3F          Displays Subscribed Messages

------------------------------------------------------------------------

## ESP32 to LCD Connections

  ESP32 Pin   LCD1   LCD2
  ----------- ------ ------
  3V3         VCC    VCC
  GND         GND    GND
  GPIO21      SDA    SDA
  GPIO22      SCL    SCL

Both LCDs share SDA and SCL lines but must have different I2C addresses.

------------------------------------------------------------------------

## MQTT Configuration

    const char* mqttServer = "192.168.162.64";  // Change to your MQTT Broker IP
    const int mqttPort = 1883;

    const char* pubTopic = "pubC";
    const char* subTopic = "subC";

------------------------------------------------------------------------

## How It Works

1.  ESP32 connects to WiFi.
2.  Connects to the MQTT broker.
3.  Every 5 seconds:
    -   Publishes "Hi from ESP32!" to topic pubC.
    -   Displays the message on the Publisher LCD.
4.  When a message is received on topic subC:
    -   Displays the message on the Subscriber LCD.

------------------------------------------------------------------------

## Testing Using Mosquitto

### To Subscribe to ESP32:

    mosquitto_sub -h <MQTT-server-IP> -p 1883 -t <topic-name>

Example:

    mosquitto_sub -h 192.168.162.64 -p 1883 -t pubC

------------------------------------------------------------------------

### To Publish to ESP32:

    mosquitto_pub -h <MQTT-server-IP> -p 1883 -t <topic-name> -m "Your Message"

Example:

    mosquitto_pub -h 192.168.162.64 -p 1883 -t subC -m "Hello ESP32"

The message will appear on the Subscriber LCD.

------------------------------------------------------------------------

## Project Files

-   esp32_mqtt_dual_lcd.ino → Main ESP32 Code
-   diagram.json → Wokwi Circuit Configuration

------------------------------------------------------------------------

## Required Libraries

Install from Arduino Library Manager:

-   WiFi (built-in for ESP32)
-   PubSubClient
-   LiquidCrystal_I2C
-   Wire (built-in)

------------------------------------------------------------------------

## Important Notes

-   Ensure both LCDs have different I2C addresses.
-   Make sure the MQTT broker IP matches your local network.
-   If both LCDs show the same output, verify:
    -   Correct I2C addresses
    -   Correct topic names
    -   Proper wiring of SDA and SCL

------------------------------------------------------------------------

## Author

Rithanyaa
