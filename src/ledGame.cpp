#include "ledGame.h"

void ledGame::ledYAK(int No) {
  No = No-1;
  bool S0 = bitRead(No, 0);
  bool S1 = bitRead(No, 1);
  bool S2 = bitRead(No, 2);
  bool S3 = bitRead(No, 3);
  digitalWrite(led_STATE, HIGH);
  digitalWrite(led_S0, S0);
  digitalWrite(led_S1, S1);
  digitalWrite(led_S2, S2);
  digitalWrite(led_S3, S3);
}

void ledGame::ledSONDUR(){
  digitalWrite(led_STATE, LOW);
}

void ledGame::sensorFOCUS(int No) {
  No = No-1;
  bool S0 = bitRead(No, 0);
  bool S1 = bitRead(No, 1);
  bool S2 = bitRead(No, 2);
  bool S3 = bitRead(No, 3);
  digitalWrite(sensor_S0, S0);
  digitalWrite(sensor_S1, S1);
  digitalWrite(sensor_S2, S2);
  digitalWrite(sensor_S3, S3);
}

void ledGame::sensorOKU(int *result) {
  for (int i = 0; i < 16; i++) {
    bool S0 = bitRead(i, 0);
    bool S1 = bitRead(i, 1);
    bool S2 = bitRead(i, 2);
    bool S3 = bitRead(i, 3);
    digitalWrite(sensor_S0, S0);
    digitalWrite(sensor_S1, S1);
    digitalWrite(sensor_S2, S2);
    digitalWrite(sensor_S3, S3);
    int sensorValue = digitalRead(sensor_STATE);
    if (sensorValue == 1) {
      result[i] = 1;
    }
    else {
      result[i] = 0;
    } 
  }
}

void ledGame::oyunSetup(){
    int aktifLed = 0;
    int puan = 0;
}

void ledGame::oyunBaslat() {
    oyunDurumu = true;
    for (int i = 0; i < 10 ; i++){
        aktifLed = random(1, 17); // Üye değişkeni olarak güncellenmeli
        ledYAK(aktifLed);
        sensorFOCUS(aktifLed);
        baslangicZamani = millis(); // Başlangıç zamanını güncellemeli
        while (oyunDurumu == true){
            unsigned long suankiZaman = millis();
            if (suankiZaman - baslangicZamani >= gecenZaman) {
                ledSONDUR();
                break;
            }
            if (digitalRead(sensor_STATE) == 1) {
                ledSONDUR();
                puan += 1;
                break;
            }
        }
    }
    oyunDurumu = false;
    Serial.println(puan);
    oyunSetup();
}
