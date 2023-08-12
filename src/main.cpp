#include <Arduino.h>
#include "ledGame.h"



const int led_S0 = 10;
const int led_S1 = 11;
const int led_S2 = 12;
const int led_S3 = 13;
const int led_STATE = 4;

const int sensor_S0 = 9;
const int sensor_S1 = 8;
const int sensor_S2 = 7;
const int sensor_S3 = 6;
const int sensor_STATE = 3;

void setup() {
  pinMode(led_S0, OUTPUT);
  pinMode(led_S1, OUTPUT);
  pinMode(led_S2, OUTPUT);
  pinMode(led_S3, OUTPUT);
  pinMode(led_STATE, OUTPUT);

  pinMode(sensor_S0, OUTPUT);
  pinMode(sensor_S1, OUTPUT);
  pinMode(sensor_S2, OUTPUT);
  pinMode(sensor_S3, OUTPUT);
  pinMode(sensor_STATE, INPUT);

  Serial.begin(9600);
}

void loop() {
  // int sensorValue = digitalRead(sensor_STATE);
  // Serial.println(sensorValue);

  // int sensorVerisi[16];
  // sensorOKU(sensorVerisi);
  // for (int i = 0; i < 16; i++) {
  //   Serial.print(sensorVerisi[i]);
  // }

  ledGame oyun;
  oyun.oyunBaslat();
  Serial.println("deneme");
  
  delay(1000);
}
