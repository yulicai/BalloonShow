/*
 * This is a simple command code for shift register 74HC595
 * Using the original Arduino shiftOut tutorial https://www.arduino.cc/en/Tutorial/ShftOut11
 * yuli cai
 * 2017 Spring for thesis at ITP NYU
 */

/* for shift register chain 1 st */
//Date Serial In Pin
int DS_1 = 7;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP_1 = 9;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP_1 = 8;  //pin12 on 74hc595

/* for shift register chain 2 nd */
//Date Serial In Pin
int DS_2 = 2;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP_2 = 3;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP_2 = 4;  //pin12 on 74hc595

void setup() {
  pinMode(DS_1, OUTPUT);
  pinMode(SH_CP_1, OUTPUT);
  pinMode(ST_CP_1, OUTPUT);
  pinMode(DS_2, OUTPUT);
  pinMode(SH_CP_2, OUTPUT);
  pinMode(ST_CP_2, OUTPUT);
}


void loop() {
  digitalWrite(ST_CP_1, LOW);
  //221 in binary is 11011101
  shiftOut(DS_1, SH_CP_1, LSBFIRST, 1);
  shiftOut(DS_1, SH_CP_1, LSBFIRST, 221);
  digitalWrite(ST_CP_1, HIGH);
  
  digitalWrite(ST_CP_2, LOW);
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 200);
  digitalWrite(ST_CP_2, HIGH);
  delay(500);
  
  digitalWrite(ST_CP_1, LOW);
  shiftOut(DS_1, SH_CP_1, LSBFIRST, 0);
  shiftOut(DS_1, SH_CP_1, LSBFIRST, 0);
  digitalWrite(ST_CP_1, HIGH);

  digitalWrite(ST_CP_2, LOW);
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 200);
  digitalWrite(ST_CP_2, HIGH);
  delay(500);

}
