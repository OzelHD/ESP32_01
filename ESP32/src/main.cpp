#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

#define SDA_PIN 0
#define SCL_PIN 1

TwoWire I2CBus = TwoWire(0);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &I2CBus);

void setup() {
  Serial.begin(115200);
  I2CBus.begin(SDA_PIN, SCL_PIN);
  if (!bno.begin()) {
    Serial.println("❌ BNO055 not found");
    while (1);
  }
  delay(100);
}

// helper to print an euler/vector event
void printVector(const char* label, sensors_event_t &e) {
  Serial.print(label);               // e.g. "🧭 Orientation"
  Serial.print(" -> X: "); Serial.print(e.orientation.x, 2);
  Serial.print(" | Y: "); Serial.print(e.orientation.y, 2);
  Serial.print(" | Z: "); Serial.println(e.orientation.z, 2);
}

// helper to print quaternion
void printQuat(const char* label, imu::Quaternion &q) {
  Serial.print(label);
  Serial.print(" -> W: "); Serial.print(q.w(), 4);
  Serial.print(" | X: "); Serial.print(q.x(), 4);
  Serial.print(" | Y: "); Serial.print(q.y(), 4);
  Serial.print(" | Z: "); Serial.println(q.z(), 4);
}

void loop() {
  sensors_event_t euler;
  bno.getEvent(&euler, Adafruit_BNO055::VECTOR_EULER);
  Serial.printf("EULER,%.2f,%.2f,%.2f\n", 
  euler.orientation.x,  // roll
  euler.orientation.y,  // pitch
  euler.orientation.z); // yaw


}
