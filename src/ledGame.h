#ifndef ledGame_h
#define ledGame_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class ledGame {
  private:
    int aktifLed;
    bool oyunDurumu;
    unsigned long baslangicZamani = 0;
    unsigned long gecenZaman = 3000;
    
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

    const int analog_Buton = A1;
    int analog_Buton_Degeri = 0;
    int zorlukSeviyesi = 1;
    int oyuncuSayisi = 1;
    int oyunSuresi = 30;
    int tusSayisi = 10;

  public:
    enum Menu_States {BASLA, AYARLAR, GERI, ZORLUK, OYUNCU, TUS, SURE, OYUN, SKOR};
    int puan;
    void ledGameSetup();
    void ledYAK(int No);
    void ledSONDUR();
    void sensorFOCUS(int No);
    void sensorOKU(int *result);
    Menu_States oyunBaslat();
    Menu_States skorTablosu();
    void oyunBasliyor();
    void ekranaYazdir(int puan, int i);
    void ekranSetup();
    int zorlukDelay(int zorlukSeviyesi);
    Menu_States menu();
    Menu_States ayarlar();
    Menu_States geri();
    Menu_States zorluk();
    Menu_States oyuncu();
    Menu_States tus();
    Menu_States sure();
    int butonOKU();

};

#endif