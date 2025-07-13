#include <SoftwareSerial.h>
#include <DHT.h>

// Bluetooth module HC-05 connections
#define BT_TX 10  // Arduino TX (connect to HC-05 RX)
#define BT_RX 11  // Arduino RX (connect to HC-05 TX)
SoftwareSerial BT(BT_TX, BT_RX);

// Sensor and Actuator pins
#define DHT_PIN A1
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define LDR_PIN A0
#define IR_SENSOR_PIN 3
#define BUZZER_PIN 4
#define LED_AC 5
#define LED_LIGHT 6
#define FAN_PIN 7

// Global variables
bool lockMode = false;
bool isNight = false;

void setup() {
    Serial.begin(9600);
    BT.begin(9600);
    dht.begin();
    pinMode(IR_SENSOR_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_AC, OUTPUT);
    pinMode(LED_LIGHT, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_AC, LOW);
    digitalWrite(LED_LIGHT, LOW);
    digitalWrite(FAN_PIN, LOW);
}

void loop() {
    float temp = dht.readTemperature();
    int ldrValue = analogRead(LDR_PIN);
    int irValue = digitalRead(IR_SENSOR_PIN);
    
    // Check temperature condition
    if (temp > 27.8) { // X value assumed as 25
        digitalWrite(LED_AC, HIGH);
        Serial.println(temp);
        delay(2000);
        BT.println("AC turned ON");
    } else {
        digitalWrite(LED_AC, LOW);
    }
    
    // Check light condition
    if ((ldrValue > 700 || isNight) && irValue ==0) {
        digitalWrite(LED_LIGHT, HIGH);

        BT.println("Light turned ON");
        delay(5000);
    } else {
        digitalWrite(LED_LIGHT, LOW);
    }
    
    // Lock mode security check
    if (lockMode && irValue == 0) {
        digitalWrite(BUZZER_PIN, HIGH);
        tone(BUZZER_PIN,1000);
        BT.println("Intruder detected! Buzzer ON");
        delay(7000);
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, LOW);
    }
    
    // Check Bluetooth command
    if (BT.available()) {
        String command = BT.readString();
        command.trim();
        
        if (command == "LOCK") {
            lockMode = true;
            BT.println("Lock mode enabled");
        } else if (command == "UNLOCK") {
            lockMode = false;
            BT.println("Lock mode disabled");
        } else if (command == "FAN") {
            digitalWrite(FAN_PIN, HIGH);
            BT.println("Fan turned ON");
        } else if (command == "NOFAN") {
            digitalWrite(FAN_PIN, LOW);
            BT.println("Fan turned OFF");
        } else if (command == "NIGHT") {
            isNight = true;
            BT.println("Night mode enabled");
        } else if (command == "DAY") {
            isNight = false;
            BT.println("Day mode enabled");
        }
    }
}