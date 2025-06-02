
unsigned int sw_long[SWNUM] = {0}; // TEST


/*
   SW長押し待ち
*/
void sw_long_wait()
{
  for (;;) {
    swatch(&pt1);
    if ((sw_stat[0] & 0xF0) != 0 ) {
      return;
    }
    if (sw_stat[0] == 0 ) {
      return;
    }
    delay(30);
  }
}

/*
   SW押下解除wait
*/
void sw_wait()
{
  for (;;) {
    swatch(&pt1);
    if (sw_stat[0] == 0) {
      return;
    }
    delay(30);
  }
}

/*
   SW 入力
*/
void key_in() {
  unsigned char sw_bit = 0x01 ;
  unsigned char sw = 0;

  for ( int i = 0 ; i < 4 ; i++) {
    if ( digitalRead(sw_port[i]) == LOW ) {
      sw |= sw_bit ;
      sw_long[i]++;
    }
    else {
      sw &= ~sw_bit;
      sw_long[i] = 0;
    }
    sw_bit = sw_bit << 1 ;
  }
  sw_stat[0] = sw ;
  sw_bit = 0x10 ;
  for ( int i = 0 ; i < SWNUM ; i++) {
    if ( sw_long[i] > 30) {
      sw_stat[0] |= sw_bit ;
    }
    sw_bit = sw_bit << 1 ;
  }

  if( SWNUM >= 5 ){
    sw_bit = 0x01 ;
    sw = 0;
    for ( int i = 0 ; i < SWNUM - 4 ; i++) {
      if ( digitalRead(sw_port[i + 4]) == LOW ) {
        sw |= sw_bit ;
        sw_long[i + 4]++;
      }
      else {
        sw &= ~sw_bit;
        sw_long[i * 4] = 0;
      }
      sw_bit = sw_bit << 1 ;
    }
    sw_stat2[0] = sw ;
    sw_bit = 0x10 ;
    for ( int i = 0 ; i < SWNUM - 4; i++) {
      if ( sw_long[i] > 30) {
        sw_stat2[0] |= sw_bit ;
      }
      sw_bit = sw_bit << 1 ;
    }
  }
 
}
