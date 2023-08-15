#include "ledGame.h"

LiquidCrystal_I2C lcd(0x20, 16, 2);
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

void ledGame::ekranSetup() {
  lcd.init();
  lcd.backlight();
}

void ledGame::ekranaYazdir(int puan, int i) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Puan        Tus");
  lcd.setCursor(0, 1);
  lcd.print("  "+String(puan)+"          "+String(tusSayisi-i));
}

int ledGame::zorlukDelay(int zorlukSeviyesi) {
  switch (zorlukSeviyesi)
  {
  case 1:
    return 3000;
    break;
  case 2:
    return 2000;
    break;
  case 3:
    return 1500;
    break;
  case 4:
    return 1000;
    break;
  case 5:
    return 500;
    break;
  default:
    return 3000;
    break;
  }
}

ledGame::Menu_States ledGame::skorTablosu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SKOR      BASARI");
  lcd.setCursor(0, 1);
  lcd.print(" "+String(puan1)+"        "+String(puan1*100/tusSayisi)+"%");
  delay(3000);
  return BASLA;
}

void ledGame::skorTablosu2(bool stage, int puan1, int puan2){
  if (stage == true){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SKOR      BASARI");
    lcd.setCursor(0, 1);
    lcd.print(" "+String(puan1)+"        "+String(puan1*100/tusSayisi)+"%");
    delay(3000);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SKOR      BASARI");
    lcd.setCursor(0, 1);
    lcd.print(" "+String(puan2)+"        "+String(puan2*100/tusSayisi)+"%");
    delay(3000);
  }
}

ledGame::Menu_States ledGame::genelSkor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OYUNCU 1 --> "+String(ledGame::puan1));
  lcd.setCursor(0, 1);
  lcd.print("OYUNCU 2 --> "+String(ledGame::puan2));
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  if (puan1 > puan2){
    lcd.print("KAZANAN OYUNCU 1");
    lcd.setCursor(0, 1);
    lcd.print("   TEBRIKLER!");
  }
  else if (puan1 < puan2) {
    lcd.print("KAZANAN OYUNCU 2");
    lcd.setCursor(0, 1);
    lcd.print("   TEBRIKLER!");
  }
  else {
    lcd.print("  KAZANAN YOK");
    lcd.setCursor(0, 1);
    lcd.print("   BERABERE!");
  }
  
  delay(2000);
  return BASLA;
}

ledGame::Menu_States ledGame::oyunBaslat2() {
  oyunDurumu = true;
  puan1 = 0;
  puan2 = 0;
  ekranSetup();
  oyunBasliyor2(1);
  gecenZaman = zorlukDelay(zorlukSeviyesi);
  for (int i = 0; i < tusSayisi ; i++){
      aktifLed = random(1, 17); // Üye değişkeni olarak güncellenmeli
      ledYAK(aktifLed);
      sensorFOCUS(aktifLed);
      ekranaYazdir(puan1, i);
      baslangicZamani = millis(); // Başlangıç zamanını güncellemeli
      while (oyunDurumu == true){
          unsigned long suankiZaman = millis();
          if (suankiZaman - baslangicZamani >= gecenZaman) {
              ledSONDUR();
              break;
          }
          if (digitalRead(sensor_STATE) == 1) {
              ledSONDUR();
              puan1 += 1;
              break;
          }
      }
  }
  ekranaYazdir(puan1, tusSayisi);
  skorTablosu2(true, puan1, puan2);
  oyunBasliyor2(2);
  for (int i = 0; i < tusSayisi ; i++){
    aktifLed = random(1, 17); // Üye değişkeni olarak güncellenmeli
    ledYAK(aktifLed);
    sensorFOCUS(aktifLed);
    ekranaYazdir(puan2, i);
    baslangicZamani = millis(); // Başlangıç zamanını güncellemeli
    while (oyunDurumu == true){
        unsigned long suankiZaman = millis();
        if (suankiZaman - baslangicZamani >= gecenZaman) {
            ledSONDUR();
            break;
        }
        if (digitalRead(sensor_STATE) == 1) {
            ledSONDUR();
            puan2 += 1;
            break;
        }
    }
  }
  ekranaYazdir(puan2, tusSayisi);
  skorTablosu2(false, puan1, puan2);
  oyunDurumu = false;
  return SKOR2;
}

void ledGame::oyunBasliyor2(int stage) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" OYUN BASLIYOR!");
  lcd.setCursor(0, 1);
  lcd.print("    OYUNCU "+String(stage));
  delay(1000);
  lcd.clear();
  lcd.print("        3");
  delay(1000);
  lcd.clear();
  lcd.print("        2");
  delay(1000);
  lcd.clear();
  lcd.print("        1");
  delay(1000);
}

void ledGame::oyunBasliyor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" OYUN BASLIYOR!");
  lcd.setCursor(0, 1);
  lcd.print("   Hazirlanin");
  delay(1000);
  lcd.clear();
  lcd.print("        3");
  delay(1000);
  lcd.clear();
  lcd.print("        2");
  delay(1000);
  lcd.clear();
  lcd.print("        1");
  delay(1000);
}

ledGame::Menu_States ledGame::oyunBaslat() {
    oyunDurumu = true;
    puan1 = 0;
    ekranSetup();
    oyunBasliyor();
    gecenZaman = zorlukDelay(zorlukSeviyesi);
    for (int i = 0; i < tusSayisi ; i++){
        aktifLed = random(1, 17); // Üye değişkeni olarak güncellenmeli
        ledYAK(aktifLed);
        sensorFOCUS(aktifLed);
        ekranaYazdir(puan1, i);
        baslangicZamani = millis(); // Başlangıç zamanını güncellemeli
        while (oyunDurumu == true){
            unsigned long suankiZaman = millis();
            if (suankiZaman - baslangicZamani >= gecenZaman) {
                ledSONDUR();
                break;
            }
            if (digitalRead(sensor_STATE) == 1) {
                ledSONDUR();
                puan1 += 1;
                break;
            }
        }
    }
    oyunDurumu = false;
    ekranaYazdir(puan1, tusSayisi);
    Serial.println(puan1);
    delay(3000);
    return SKOR;
}





ledGame::Menu_States ledGame::menu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oyuna Basla    >");
  lcd.setCursor(0, 1);
  lcd.print("Ayarlar");
  int butonPressed = butonOKU();
  if (butonPressed == 3){
    Serial.println("Oyun Basladi");
    return OYUN;
  }
  else if (butonPressed == 4){
    return AYARLAR;
  }
  else {
    return BASLA;
  }
}

ledGame::Menu_States ledGame::ayarlar() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oyuna Basla");
  lcd.setCursor(0, 1);
  lcd.print("Ayarlar        >");
  int butonPressed = butonOKU();
  if (butonPressed == 1){
    return BASLA;
  }
  else if (butonPressed == 3){
    return GERI;
  }
  else {
    return AYARLAR;
  }
}

ledGame::Menu_States ledGame::geri() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Geri           >");
  lcd.setCursor(0, 1);
  lcd.print("Zorluk   - "+String(zorlukSeviyesi)+" +");
  int butonPressed = butonOKU();
  if (butonPressed == 3){
    return AYARLAR;
  }
  else if (butonPressed == 4){
    return ZORLUK;
  }
  else {
    return GERI;
  }
}

ledGame::Menu_States ledGame::zorluk() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Geri           ");
  lcd.setCursor(0, 1);
  lcd.print("Zorluk   - "+String(zorlukSeviyesi)+" + >");
  int butonPressed = butonOKU();
  if (butonPressed == 1){
    return GERI;
  }
  else if (butonPressed == 2){
    if (zorlukSeviyesi != 1)
    {
      zorlukSeviyesi -= 1;
    }
    return ZORLUK;
  }
  else if (butonPressed == 3){
    if (zorlukSeviyesi != 5)
    {
      zorlukSeviyesi += 1;
    }
    return ZORLUK;
  }
  else if (butonPressed == 4){
    return OYUNCU;
  }
  else {
    return ZORLUK;
  }
}

ledGame::Menu_States ledGame::oyuncu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oyuncu    - "+String(oyuncuSayisi)+" +>");
  lcd.setCursor(0, 1);
  lcd.print("Tus Adet - "+String(tusSayisi)+" +");
  int butonPressed = butonOKU();
  if (butonPressed == 1){
    return ZORLUK;
  }
  else if (butonPressed == 2){
    if (oyuncuSayisi != 1)
    {
      oyuncuSayisi -= 1;
    }
    return OYUNCU;
  }
  else if (butonPressed == 3){
    if (oyuncuSayisi != 2)
    {
      oyuncuSayisi += 1;
    }
    return OYUNCU;
  }
  else if (butonPressed == 4){
    return TUS;
  }
  else {
    return OYUNCU;
  }
}

ledGame::Menu_States ledGame::tus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oyuncu    - "+String(oyuncuSayisi)+" + ");
  lcd.setCursor(0, 1);
  lcd.print("Tus Adet - "+String(tusSayisi)+" +>");
  int butonPressed = butonOKU();
  if (butonPressed == 1){
    return OYUNCU;
  }
  else if (butonPressed == 2){
    if (tusSayisi != 10)
    {
      tusSayisi -= 1;
    }
    return TUS;
  }
  else if (butonPressed == 3){
    if (tusSayisi != 40)
    {
      tusSayisi += 1;
    }
    return TUS;
  }
  else if (butonPressed == 4){
    return SURE;
  }
  else {
    return TUS;
  }
}

ledGame::Menu_States ledGame::sure() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sure  - "+String(oyunSuresi)+"sn + >");
  int butonPressed = butonOKU();
  if (butonPressed == 1){
    return TUS;
  }
  else if (butonPressed == 2){
    if (oyunSuresi != 30)
    {
      oyunSuresi -= 1;
    }
    return SURE;
  }
  else if (butonPressed == 3){
    if (oyunSuresi != 90)
    {
      oyunSuresi += 1;
    }
    return SURE;
  }
  else {
    return SURE;
  }
}

int ledGame::butonOKU(){
  while(true){
    analog_Buton_Degeri = analogRead(analog_Buton);
    Serial.println(analog_Buton_Degeri);
    if (analog_Buton_Degeri < 800 && analog_Buton_Degeri >750){
      Serial.println("4");
      return 4;
    }
    else if (analog_Buton_Degeri < 749 && analog_Buton_Degeri >650){
      Serial.println("3");
      return 3;
    }
    else if (analog_Buton_Degeri < 649 && analog_Buton_Degeri >425){
      Serial.println("2");
      return 2;
    }
    else if (analog_Buton_Degeri < 425 && analog_Buton_Degeri >=0){
      Serial.println("1");
      return 1;
    }
    else {
      //Serial.println("0");
      delay(100);
    }
  }
}

void ledGame::ledGameSetup() {
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

  pinMode(analog_Buton, INPUT);
  ekranSetup();
  Serial.begin(9600);
}