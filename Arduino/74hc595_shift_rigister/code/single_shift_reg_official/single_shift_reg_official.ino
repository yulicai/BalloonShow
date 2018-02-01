/*
 * This is a simple command code for shift register 74HC595
 * 5 shift registers in a serie as daisy chained
 * Using the original Arduino shiftOut tutorial https://www.arduino.cc/en/Tutorial/ShftOut11
 * one shift register for 2 balloons
 * 4 digits for a ballon,[airpump, valve1, valve2,valve3,valve4]
 * inflate 1101, deflate 1010, stay 0000
 * yuli cai
 * 2017 Spring for thesis at ITP NYU
 */

//Date Serial In Pin
int DS = 7;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP = 9;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP = 8;  //pin12 on 74hc595

void setup() {
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
}


void loop() {
  digitalWrite(ST_CP, LOW);
  //221 in binary is 11011101
  //first input is for the farthest register
  shiftOut(DS, SH_CP, LSBFIRST,10); //last 4 digit 1101
  shiftOut(DS, SH_CP, LSBFIRST, 1);
  shiftOut(DS, SH_CP, LSBFIRST,10);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  shiftOut(DS, SH_CP, LSBFIRST, 1);
  digitalWrite(ST_CP, HIGH);
  delay(3000);
  
  digitalWrite(ST_CP, LOW);
  //221 in binary is 11011101
  shiftOut(DS, SH_CP, LSBFIRST,0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST,0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  digitalWrite(ST_CP, HIGH);
  delay(1000);
}
