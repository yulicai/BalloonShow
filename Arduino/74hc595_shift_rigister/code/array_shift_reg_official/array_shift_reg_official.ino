/*
 * This is command code for shift register 74HC595
 * controlling pin mode states through a pattern data pool
 * Based on Arduino shiftOut tutorial https://www.arduino.cc/en/Tutorial/ShftOut13
 * yuli cai
 * 2017 Spring for thesis at ITP NYU
 */

//Date Serial In Pin
int DS = 7;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP = 9;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP = 8;  //pin12 on 74hc595

byte data;
byte dataArray[10];


void setup() {
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);

  //Binary notation as comment
  dataArray[0] = 0xFF; //0b11111111;255 in decimal
  dataArray[1] = 0xFE; //0b11111110;254
  dataArray[2] = 0xFC; //0b11111100;252
  dataArray[3] = 0xF8; //0b11111000;248
  dataArray[4] = 0xF0; //0b11110000;240
  dataArray[5] = 0xE0; //0b11100000;224
  dataArray[6] = 0xC0; //0b11000000;192
  dataArray[7] = 0x80; //0b10000000;128
  dataArray[8] = 0x00; //0b00000000;0
  dataArray[9] = 0xE0; //0b11100000;224

  /*
   * The following array is the equivalent decimal version
   * For testing
   * It turns out it work the same ar the above
  dataArray[0] = 255; //0b11111111;255 in decimal
  dataArray[1] = 254; //0b11111110;254
  dataArray[2] = 252; //0b11111100;252
  dataArray[3] = 248; //0b11111000;248
  dataArray[4] = 240; //0b11110000;240
  dataArray[5] = 224; //0b11100000;224
  dataArray[6] = 192; //0b11000000;192
  dataArray[7] = 128; //0b10000000;128
  dataArray[8] = 0; //0b00000000;0
  dataArray[9] = 224; //0b11100000;224
   */

}


void loop() {

  for (int i = 0; i < sizeof(dataArray); i++) {
    data = dataArray[i];
    digitalWrite(ST_CP, LOW);
    shiftOut(DS, SH_CP, MSBFIRST, data);
    digitalWrite(ST_CP, HIGH);
    delay(100);
  }

}
