#include <Arduino.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321); // Assign a unique ID to this sensor at the same time
Adafruit_BMP280 bmp(BMP_CS); // hardware SPI

//For Atmega328P's
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

float x = 0.0;
float y = 0.0;
float z = 0.0;
float alt = 0.0;
float gforce = 0.0;
float pressure = 0.0;
float temp = 0.0;

int camera_recording = 1;
int camera_pin = 13;

// Used to separate pieces of data when printed as serial data.
// Ground station will separate data based on the semicolon.
String s = ";";

void setup() {
    Serial.begin(9600);
    XBee.begin(9600);
    bmp.begin();
    
    pinMode(camera_pin, OUTPUT);

    accel.setRange(LSM303_RANGE_4G);
    lsm303_accel_range_t new_range = accel.getRange();

    accel.setMode(LSM303_MODE_NORMAL);
    lsm303_accel_mode_t new_mode = accel.getMode();

}

void loop() {
    /* Get a new sensor event */
    sensors_event_t event;
    accel.getEvent(&event);

    if (Serial.available() > 0) {
        camera_recording = Serial.read();
    } 

    if(camera_recording % 2 == 0) {
        digitalWrite(camera_pin, HIGH);
    } else {
        digitalWrite(camera_pin, LOW);
    }

    x = event.acceleration.x;
    y = event.acceleration.y;
    z = event.acceleration.z;
    alt = bmp.readAltitude(1013.25);
    gforce = event.acceleration.y;
    pressure = bmp.readPressure();
    temp = bmp.readTemperature();

    XBee.println(x + s + y + s + z + s + alt + s + gforce + s + pressure + s + temp);
    delay(50); 
}
