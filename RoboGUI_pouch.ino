
#include "RoboGUI_pouch.h"

enum State state;

void setup() {

  while (!Serial);
    delay(1000);

  Wire.begin();
  
  Serial.begin(9600);
/*
  for (uint8_t t=0; t<8; t++) {
    tcaselect(t);
    Serial.print("TCA Port #"); Serial.println(t);

    for (uint8_t addr = 0; addr<=127; addr++) {
      if (addr == TCAADDR) continue;
      
      uint8_t data;
      if (! twi_writeTo(addr, &data, 0, 1, 1)) {
         Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
      }
    }
  }
  Serial.println("\ndone");
*/
  tcaselect(0);
  matrix.begin(0x70);
  matrix.clear();
  matrix.writeDisplay();
  tcaselect(1);
  matrix.begin(0x70);
  matrix.clear();
  matrix.writeDisplay();
  tcaselect(2);
  matrix.begin(0x70);
  matrix.clear();
  matrix.writeDisplay();
  tcaselect(3);
  matrix.begin(0x70);
  matrix.clear();
  matrix.writeDisplay();
  tcaselect(4);
  matrix.begin(0x70);
  matrix.clear();
  matrix.writeDisplay();

  bootingFlag = true,
  idleFlag = true,
  turningLeftFlag = true,
  turningRightFlag = true,
  batteryFlag = true,
  emergencyFlag = true;
  
  state = BOOTING;

  pinMode(2, OUTPUT);
  //nh.getHardware()->setBaud(57600);
  //nh.initNode();
  //nh.subscribe(sub);
}

void loop() {

  //nh.spinOnce();
  //delay(1);
  
  switch(state){
    case BOOTING:
      booting();
    break;
    
    case IDLING:
    break;
    
    case TURNING_LEFT:
      turning_left();
    break;
    
    case TURNING_RIGHT:
      turning_right();
    break;
    
    case BATTERY:
      battery();
    break;
    
    case EMERGENCY:
      emergency();
    break;

    default:
      Serial.print("default error");
    break;
  }
  
}
