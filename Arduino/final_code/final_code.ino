/*
 * This is the final code for my thesis - Wave-washed Sands
 * Using 2 chains of shift registers, 6 shift registers in total
 * Controlling 27 solonoid valves, 9 pumps, 6 LED strips, 4 fans and 2 servos
 * yuli cai
 * 2017 Spring, thesis, at ITP NYU
 */

/*
 * TOP PART REF
 * 5 shift registers in a serie as daisy chained
 * one shift register for 2 balloons, 9 balloons in total
 * 4 digits for a ballon,[airpump, valve1, valve2,valve3,valve4]
 * MODE -- inflate 1101, deflate 1010, stay 0000
 * For one shift reg -- inflate one(208/13) two(221)
 * the farthest register gets programmed first, e.g. the command for balloon NO.9 goes the first line
 */

/*
 * BOTTOM PART REF
 * pin out matches series: led 1-6, fan group 1, fan group 2
 */

/*
 * Servo Ref
 * pin 5, angle from 10-110, Arduino servo library
 */



#include <math.h>
#include <Servo.h>

/* for shift register chain 1 st -TOP PART*/
//Date Serial In Pin
int DS = 7;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP = 9;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP = 8;  //pin12 on 74hc595

/* for shift register chain 2 nd - BOTTOM PART */
//Date Serial In Pin
int DS_2 = 2;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP_2 = 3;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP_2 = 4;  //pin12 on 74hc595

/* Servo Initiation */
Servo myservo;
Servo servo2;

int pos = 0;    // variable to store the servo position
int start_point = 120;
int end_point = 80;
int gap = 1;

/* Time Distribution */
int phase1_time = 18000;
int phase2_time = 30000;
int phase3_time = 15000;
int phase4_time = 12000;
int phase5_time = 15000;
int phase6_time = 18000;
int settle_time = 10000;

void setup() {
  /* shift reg */
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(DS_2, OUTPUT);
  pinMode(SH_CP_2, OUTPUT);
  pinMode(ST_CP_2, OUTPUT);

  /* servo */
  myservo.attach(5);
  servo2.attach(6);
  //  myservo.write(start_point);
}

void loop() {
  phase1(phase1_time);
  phase2(phase2_time);
  phase3(phase3_time);
  phase4(phase4_time);
  phase5(phase5_time);
  phase6(phase6_time);
  settle(settle_time);
}



// around 18 secs
void phase1(int t) {

  //MODE 1 -- ONLY CENTRAL BALLOON
  // led 1 on
  digitalWrite(ST_CP_2, LOW);
  //binary 10000000 - 128
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 128);
  digitalWrite(ST_CP_2, HIGH);

  //only central balloon is breathig, balloon no.2
  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 13);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  //deflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 13);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);



  //MODE 2 -- FANS ON
  // led 1 on, 2 fan groups both on
  digitalWrite(ST_CP_2, LOW);
  //binary 10000011 - 131
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 131);
  digitalWrite(ST_CP_2, HIGH);

  //deflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  //inflating
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 13);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  //deflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);


  //MODE 3 -- SHIFTING FANS
  digitalWrite(ST_CP_2, LOW);
  //binary 10000010 - 130; 10000001 -129
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 130);
  digitalWrite(ST_CP_2, HIGH);

  //inflating
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 13);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  //deflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);


  digitalWrite(ST_CP_2, LOW);
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 129);
  digitalWrite(ST_CP_2, HIGH);
  //inflating
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 13);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);

  //deflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 9);
}



// around 30 secs
void phase2(int t) {
  //MODE 1 -- all balloons are inflating, for a little bit
  // led 2 on
  digitalWrite(ST_CP_2, LOW);
  //binary 01000000 - 64
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 64);
  digitalWrite(ST_CP_2, HIGH);

  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  digitalWrite(ST_CP, HIGH);
  delay(t / 8);

  //MODE 2 -- all stop inflating, central one starts to deflate, fans on
  // led 2 on, all fans on
  digitalWrite(ST_CP_2, LOW);
  //binary 01000011 - 67
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 67);
  digitalWrite(ST_CP_2, HIGH);

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 5);

  // MODE 3 -- all starts to deflate badly,fans on
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  digitalWrite(ST_CP, HIGH);
  delay(t / 4);
}

void phase3(int t) {
  // led 3 on
  digitalWrite(ST_CP_2, LOW);
  //binary 00100000 - 32
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 32);
  digitalWrite(ST_CP_2, HIGH);

  //MODE 1 -- surrounding ones inflating, central one deflate, not long
  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 218);
  digitalWrite(ST_CP, HIGH);
  //  myservo.write(start_point);
  delay(t / 2);


  //MODE 2 -- all inflating
  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  digitalWrite(ST_CP, HIGH);
  //  myservo.write(start_point);
  delay(t / 2);


  //MODE 3 -- all balloons stay, fans on for a little bit, cage open
  digitalWrite(ST_CP_2, LOW);
  //binary 00100011 - 35
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 35);
  digitalWrite(ST_CP_2, HIGH);

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  digitalWrite(ST_CP, HIGH);
  for (pos = start_point; pos >= end_point; pos -= gap)
  {
    myservo.write(pos);
    delay(20);
  }
  myservo.write(end_point);
  delay(t / 5);



  //MODE 4 -- all balloons deflating, fans off, cage close
  digitalWrite(ST_CP_2, LOW);
  //binary 00100000 - 32
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 32);
  digitalWrite(ST_CP_2, HIGH);

  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  digitalWrite(ST_CP, HIGH);
  for (pos = end_point; pos <= start_point; pos += gap)
  {
    myservo.write(pos);
    delay(20);
  }
  //  myservo.write(start_point);
  delay(t);

}



//around 12 secs
void phase4(int t) {
  // led 4 on
  digitalWrite(ST_CP_2, LOW);
  //binary 00010000 - 16
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 16);
  digitalWrite(ST_CP_2, HIGH);

  // MODE 1 -- all balloons inflate, for a little bit
  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  digitalWrite(ST_CP, HIGH);
  delay(t / 3 );

  // MODE 2 -- surrounding ones stop inflating turn to deflate, central one keep inflating
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  //10101101 - 173
  shiftOut(DS, SH_CP, LSBFIRST, 173);
  digitalWrite(ST_CP, HIGH);
  delay(t / 3);


  // MODE 3 -- all stay, fans on
  digitalWrite(ST_CP_2, LOW);
  //binary 00010011 - 19
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 19);
  digitalWrite(ST_CP_2, HIGH);

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  digitalWrite(ST_CP, HIGH);
  delay(t / 3);


  // MODE 4 -- center one deflate

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  delay(t / 2);
}

void phase5(int t) {
  //MODE 1 -- surrounding ones inflating, central one stay, not long
  //MODE 2 -- central one start to inflate, till its half size, surrounding ones stay
  //MODE 3 -- central one keeps inflating, surrounding ones start to inflate too,till the central one gets to its round status
  //MODE 4 -- cage open, surrounding ones start to deflate,central one keep inflating
  //MODE 5 -- cage close, central one start to deflate as well, surrounding ones stay

  //MODE 1 -- surrounding ones inflating, central one stay, not long
  // led 5 on
  digitalWrite(ST_CP_2, LOW);
  //binary 00001000 - 8
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 8);
  digitalWrite(ST_CP_2, HIGH);

  //inflating
  //inflate one(208/13) two(221)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 208);
  digitalWrite(ST_CP, HIGH);
  delay(t / 2);

  //MODE 2 -- central one start to inflate, till its half size, surrounding ones stay
//  digitalWrite(ST_CP, LOW);
//  shiftOut(DS, SH_CP, LSBFIRST, 0);
//  shiftOut(DS, SH_CP, LSBFIRST, 0);
//  shiftOut(DS, SH_CP, LSBFIRST, 0);
//  shiftOut(DS, SH_CP, LSBFIRST, 0);
//  shiftOut(DS, SH_CP, LSBFIRST, 13);
//  digitalWrite(ST_CP, HIGH);
//  delay(t / 4);


  //MODE 3 -- central one keeps inflating, surrounding ones start to inflate too,till the central one gets to its round status
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  digitalWrite(ST_CP, HIGH);
  delay(t / 3);


  //MODE 4 -- surrounding ones start to deflate,central one keep inflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  //10101101 - 173
  shiftOut(DS, SH_CP, LSBFIRST, 173);
  digitalWrite(ST_CP, HIGH);
  //cage open
  for (pos = start_point; pos >= end_point; pos -= gap)
  {
    myservo.write(pos);
    delay(20);
  }
  delay(t / 2);


  //MODE 5 -- entral one start to deflate as well, surrounding ones stay
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 0);
  shiftOut(DS, SH_CP, LSBFIRST, 10);
  digitalWrite(ST_CP, HIGH);
  //cage close
  for (pos = end_point; pos <= start_point; pos += gap)
  {
    myservo.write(pos);
    delay(20);
  }
  delay(t / 2);

}

void phase6(int t) {
  digitalWrite(ST_CP_2, LOW);
  //binary 00000111 - 7
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 7);
  digitalWrite(ST_CP_2, HIGH);

  //MODE 1 -- fans on, all inflate for a little
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  shiftOut(DS, SH_CP, LSBFIRST, 221);
  digitalWrite(ST_CP, HIGH);
  delay(t / 3);


  //MODE 2 -- surrounding ones deflate, center one keep inflating
  //defalte one(160/10) two(170)
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  //10101101 - 173
  shiftOut(DS, SH_CP, LSBFIRST, 173);
  digitalWrite(ST_CP, HIGH);
  delay(t);
}

void settle(int t) {
  digitalWrite(ST_CP_2, LOW);
  //binary 00000000 - 0
  shiftOut(DS_2, SH_CP_2, LSBFIRST, 0);
  digitalWrite(ST_CP_2, HIGH);
  //All deflate
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  shiftOut(DS, SH_CP, LSBFIRST, 170);
  digitalWrite(ST_CP, HIGH);
  delay(t);
}

