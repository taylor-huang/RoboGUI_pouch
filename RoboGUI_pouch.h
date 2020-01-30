#ifndef ROBOGUI_POUCH_H
#define ROBOGUI_POUCH_H

#include <Wire.h>
#include <Adafruit_GPS.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
extern "C" {
  #include "utility/twi.h"
}

#define TCAADDR 0x71
#define D2 2

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

enum State{
  BOOTING,
  IDLING,
  TURNING_LEFT,
  TURNING_RIGHT,
  BATTERY,
  EMERGENCY
};

static const uint8_t PROGMEM
  boot0[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  boot1[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111 },
  boot2[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111 },
  boot3[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111 },
  boot4[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
  boot5[] =
  { B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
  boot6[] =
  { B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
  boot7[] =
  { B00000000,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
  boot8[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
  turn_right[] =
  { B00000000,
    B11110000,
    B11100000,
    B11110000,
    B10111111,
    B00011111,
    B00000000,
    B00000000 },
  turn_left[] =
  { B00000000,
    B00001111,
    B00000111,
    B00001111,
    B11111101,
    B11111000,
    B00000000,
    B00000000 },
  battery_6[] =
 {  B00111100,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
    battery_5[] =
 {  B00111100,
    B11100111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
    battery_4[] =
 {  B00111100,
    B11100111,
    B10000001,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
    battery_3[] =
 {  B00111100,
    B11100111,
    B10000001,
    B10000001,
    B11111111,
    B11111111,
    B11111111,
    B11111111 },
    battery_2[] =
 {  B00111100,
    B11100111,
    B10000001,
    B10000001,
    B10000001,
    B11111111,
    B11111111,
    B11111111 },
    battery_1[] =
 {  B00111100,
    B11100111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111,
    B11111111 },
    battery_0[] =
 {  B00111100,
    B11100111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111 },
    emergency_alert[] =
  { B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00011000,
    B00011000 };

boolean bootingFlag,
  idleFlag,
  turningLeftFlag,
  turningRightFlag,
  batteryFlag,
  emergencyFlag;

void flashlightOn(){
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
}

void flashlightOff(){
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void booting(){
  bootingFlag = true;
  while(bootingFlag){
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot0, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot1, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot2, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot3, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot4, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot5, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot6, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot7, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, boot8, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(200);
    bootingFlag = false;
  }
}

void idling(){
  
}

void turning_right(){
  turningRightFlag = true;
  while(turningRightFlag){
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, turn_right, 8, 8, LED_YELLOW);
      matrix.writeDisplay();
    }
    delay(300);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.writeDisplay();
    }
    delay(300);
    turningRightFlag = false;
  }
}

void turning_left(){
  turningLeftFlag = true;
  while(turningLeftFlag){
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, turn_left, 8, 8, LED_YELLOW);
      matrix.writeDisplay();
    }
    delay(300);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.writeDisplay();
    }
    delay(300);
    turningLeftFlag = false;
  }
}

void battery(){
  batteryFlag = true;
  while(batteryFlag){
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_6, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);

    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_5, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);
    
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_4, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);
    
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_3, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);
    
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_2, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);
    
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.drawBitmap(0, 0, battery_1, 8, 8, LED_GREEN);
      matrix.writeDisplay();
    }
    delay(1000);
    
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        tcaselect(j);
        matrix.clear();
        matrix.writeDisplay();
      }
      delay(200);
      for(int j = 0; j < 5; j++){
        tcaselect(j);
        matrix.drawBitmap(0, 0, battery_0, 8, 8, LED_RED);
        matrix.writeDisplay();
      }
      delay(200);
    }
    batteryFlag = false;
  }
}

void emergency(){
  emergencyFlag = true;
  while(emergencyFlag){
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.clear();
      matrix.writeDisplay();
    }
    delay(200);
    for(int i = 0; i < 5; i++){
      tcaselect(i);
      matrix.drawBitmap(0, 0, emergency_alert, 8, 8, LED_RED);
      matrix.writeDisplay();
    }
    delay(200);
    emergencyFlag = false;
  }
}


#endif
