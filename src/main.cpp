#include <Arduino.h>
#include "ledGame.h"

ledGame oyun;

ledGame::Menu_States menu_State = ledGame::BASLA;

void setup(){
  oyun.ledGameSetup();
}



void loop(){
  
  switch (menu_State)
  {
  case ledGame::SKOR2:
    menu_State = oyun.genelSkor();
    break;
  case ledGame::SKOR:
    menu_State = oyun.skorTablosu();
    break;
  case ledGame::OYUN:
    if(oyun.oyuncuSayisi == 1){
      menu_State = oyun.oyunBaslat();
      break;
    }
    else if(oyun.oyuncuSayisi == 2){
      menu_State = oyun.oyunBaslat2();
      break;
    }
  case ledGame::BASLA:
    menu_State = oyun.menu();
    break;
  case ledGame::AYARLAR:
    menu_State = oyun.ayarlar();
    break;
  case ledGame::GERI:
    menu_State = oyun.geri();
    break;
  case ledGame::ZORLUK:
    menu_State = oyun.zorluk();
    break;
  case ledGame::OYUNCU:
    menu_State = oyun.oyuncu();
    break;
  case ledGame::TUS:
    menu_State = oyun.tus();
    break;
  case ledGame::SURE:
    menu_State = oyun.sure();
    break;
  }

  Serial.println("deneme");
  delay(300);
}



  // int sensorValue = digitalRead(sensor_STATE);
  // Serial.println(sensorValue);

  // int sensorVerisi[16];
  // sensorOKU(sensorVerisi);
  // for (int i = 0; i < 16; i++) {
  //   Serial.print(sensorVerisi[i]);
  // }

  // ledGame oyun;
  // oyun.oyunBaslat();
  // Serial.println("deneme");
