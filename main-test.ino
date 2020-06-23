#include <Arduino.h>

float alt = 0.0;
float spd = 0.0;
float gforce = 0.0;
float pressure = 0.0;
float bat_temp = 0.0;
float cube_temp = 0.0;
float motor_temp = 0.0;
float gps_lat = 0.0;
float gps_long = 0.0;

int camera_recording = 1;
int camera_pin = 13;

// Used to separate pieces of data when printed as serial data.
// Ground station will separate data based on the semicolon.
String s = ";";

void setup() {
    Serial.begin(9600);
    pinMode(camera_pin, OUTPUT);
}

void loop() {

    if (Serial.available() > 0) {
        camera_recording = Serial.read();
    } 

    if(camera_recording % 2 == 0) {
        digitalWrite(camera_pin, HIGH);
    } else {
        digitalWrite(camera_pin, LOW);
    }
  
    alt += 10.23;
    spd += 9.1;
    gforce += .1;
    pressure += .2;
    bat_temp += .1;
    cube_temp += .3;
    motor_temp += .4;

    Serial.println(alt + s + spd + s + gforce + s + pressure + s + bat_temp + s + cube_temp + s + motor_temp + s + gps_lat + s + gps_long);
    delay(200);
}
