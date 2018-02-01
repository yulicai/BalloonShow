/*
 * This is a simple command code for shift register 74HC595
 * without using the original Arduino shiftOut tutorial
 * instead, using http://v.youku.com/v_show/id_XNzQwMTE0MDIw.html?f=22385121
 * yuli cai
 * 2017 Spring for thesis at ITP NYU
 */

//Date Serial In Pin
int DS = 7;     //pin14 on 74hc595
//SHift register Clock Pin
int SH_CP = 9;  //pin11 on 74hc595
//STorage register Clock Pin
int ST_CP = 8;  //pin12 on 74hc595

//least/most significant bit, msb is starting from the left-most bit
const int LSB = 0;
const int MSB = 1;


void setup() {
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
}


/*
 * function for using shifter register clock pin to shift one bit
 * serial bits in
 */
void shift(int data_pin, int sh_cp, int bit_to_write) {
  digitalWrite(sh_cp, LOW);
  digitalWrite(data_pin, bit_to_write);
  digitalWrite(sh_cp, HIGH);
}



/*
 * function to triger the parallel out of the storage resister 
 * after all the bits are shifted in to shifter register
 * arduino has orginal built-in function called shiftOut()
 */
void shiftout(int data_pin, int sh_cp, int order, byte num) {
  int s;
  order == LSB ? s = 1 : s = 128;
  for (int i = 0; i < 8; i++) {
    shift(data_pin, sh_cp, num & s);
    //shift one bit
    //if it is least significant bit first, shift from right to left
    //else, shift from left to right
    order == LSB ? s <<= 1 : s >>= 1;
  }
}



void loop() {
  digitalWrite(ST_CP, LOW);
  //221 in binary is 11011101
  shiftout(DS, SH_CP, LSB, 221);
  digitalWrite(ST_CP, HIGH);

}

