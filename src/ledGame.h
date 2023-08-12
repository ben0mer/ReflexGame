#ifndef ledGame_h
#define ledGame_h

#include <Arduino.h>

class ledGame {
  private:
    int aktifLed;
    int puan;
    unsigned long baslangicZamani = 0;
    unsigned long gecenZaman = 2000;
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

  public:
    void ledYAK(int No);
    void ledSONDUR();
    void sensorFOCUS(int No);
    void sensorOKU(int *result);
    void oyunBaslat();


};

#endif