#include <MsTimer2.h>
#include <pt.h>
#include <U8glib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include "m4_defines.h"
#include "eepdata.h"
#include "function.h"
#define DISCHARGE_TIME  10 + 3

const unsigned char bootimg[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x9F, 0xFF, 0x07, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xFE, 0x9F, 0xFF, 0x07, 0x06, 0xFF, 0x3F, 0x00, 0x82, 0x20, 0xC0, 0xF0, 0x00, 0x00, 0x00, 0x10, 0xFE, 0x9F, 0xFF, 0x07, 0x0F, 0xFF, 0x3F, 0x50, 0x00, 0x30, 0xC0, 0x90, 0x44, 0x04, 0x02, 0x10, 0x06, 0x98, 0x03, 0x86, 0x1F, 0x07, 0x38, 0xFC, 0xBA, 0x28, 0xA7, 0xF0, 0x68, 0x6B, 0x01, 0x18, 0x06, 0x98, 0x03, 0xC6, 0x39, 0x07, 0x38, 0xA4, 0xAA, 0x78, 0xF6, 0x51, 0x2E, 0x2F, 0x03, 0x1C, 0xFE, 0x9F, 0xFF, 0xE7, 0x70, 0x07, 0x38, 0xA4, 0xAA, 0x20, 0x8D, 0xD0, 0xEE, 0x2E, 0x87, 0x1E, 0xFE, 0x9F, 0xFF, 0x7F, 0xE0, 0x07, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x0E, 0x9C, 0x03, 0x3E, 0xC0, 0xC7, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x2F, 0x06, 0x98, 0x03, 0x1E, 0x80, 0xC7, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0x0E, 0x9C, 0x03, 0x0E, 0x80, 0xC7, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0xFE, 0x9F, 0xFF, 0xFF, 0xFF, 0xC7, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xC0, 0x07, 0xFE, 0x9F, 0xFF, 0xFF, 0xFF, 0xC7, 0x38, 0xFC, 0xFF, 0xF9, 0xFF, 0x03, 0x02, 0x0E, 0xC0, 0x03, 0x06, 0x60, 0x00, 0x06, 0x06, 0xC7, 0x38, 0xFC, 0xFF, 0xF9, 0xFF, 0x03, 0x07, 0x1E, 0xE0, 0x01, 0x06, 0x60, 0x00, 0x06, 0x06, 0xC7, 0x38, 0xFC, 0xFF, 0xF9, 0xFF, 0x03, 0x07, 0x3E, 0xF0, 0x01, 0xC6, 0xFF, 0x3F, 0xFE, 0xFF, 0xFF, 0x3F, 0x00, 0x07, 0x38, 0x00, 0x80, 0x0F, 0x7E, 0xF0, 0x01, 0xC6, 0xFF, 0x3F, 0xFE, 0xFF, 0xFF, 0x3F, 0x00, 0x07, 0x38, 0x00, 0xC0, 0x1F, 0x7E, 0xF8, 0x01, 0x06, 0x07, 0x0C, 0x0E, 0x06, 0x07, 0x38, 0x00, 0x07, 0x38, 0x00, 0xC0, 0x1D, 0xEE, 0xFC, 0x01, 0xC6, 0xFF, 0x3F, 0x06, 0x06, 0xF7, 0x3B, 0x00, 0x07, 0xF8, 0x3F, 0xE0, 0x3D, 0xEE, 0xDF, 0x01, 0xC6, 0xFF, 0x3F, 0x06, 0x06, 0xF7, 0x3B, 0x00, 0x07, 0xF8, 0x3F, 0xE0, 0x38, 0xCE, 0xCF, 0x01, 0x06, 0x00, 0x00, 0x26, 0x66, 0xF7, 0x3B, 0x00, 0x07, 0xF8, 0x3F, 0xF0, 0x7F, 0x8E, 0xC7, 0x01, 0xC6, 0xFF, 0x3F, 0x76, 0x76, 0x37, 0x3B, 0x00, 0x07, 0x38, 0x00, 0xF0, 0x7F, 0x0E, 0xC7, 0x01, 0xC6, 0xFF, 0x3F, 0xE6, 0x7F, 0x37, 0x3B, 0x00, 0x07, 0x38, 0x00, 0xF8, 0xFF, 0x0E, 0xC3, 0x01, 0xC6, 0x01, 0x30, 0xC6, 0x3F, 0x37, 0x3B, 0x00, 0x07, 0x38, 0x00, 0x38, 0xE0, 0x0E, 0xC0, 0x01, 0xC6, 0x00, 0x30, 0x86, 0x1F, 0x37, 0x3B, 0x00, 0x07, 0xF8, 0xFF, 0x3F, 0xC0, 0x0F, 0xC0, 0x01, 0xC6, 0xFF, 0x3F, 0xFE, 0xFF, 0xF7, 0x3B, 0x00, 0x07, 0xF8, 0xFF, 0x1F, 0xC0, 0x0F, 0xC0, 0x01, 0xC6, 0xFF, 0x3F, 0xFE, 0xFF, 0xF7, 0x3B, 0x00, 0x07, 0xF0, 0xFF, 0x0F, 0x80, 0x0F, 0xC0, 0x01, 0xC6, 0xFF, 0x3F, 0xFE, 0xFF, 0xF7, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const unsigned char bmpdata[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x0F, 0x80, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xE0, 0x1F, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x90, 0xFF, 0xFF, 0xFF, 0xFF, 0x63, 0xC7, 0xFC, 0xF1, 0xDE, 0xE7, 0x2D, 0x76, 0xDF, 0x13, 0x00, 0x90, 0xFF, 0xFF, 0xFF, 0xFF, 0x21, 0xF7, 0xFD, 0xD8, 0xFA, 0xF1, 0x9E, 0xFF, 0xFF, 0x19, 0x00, 0x08, 0x00, 0xF8, 0x03, 0x00, 0xB1, 0xFF, 0xFF, 0x78, 0x6F, 0xFE, 0xFE, 0xBF, 0xFF, 0x0D, 0x00, 0x8C, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0xCC, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xC7, 0xFF, 0xFF, 0xFF, 0x3F, 0x7F, 0x9E, 0x73, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0x9E, 0x01, 0x00, 0x01, 0x00, 0xFF, 0x01, 0x20, 0x7F, 0x9F, 0x73, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0x9F, 0x00, 0x80, 0xF9, 0xFF, 0xFF, 0xFF, 0x5F, 0x80, 0x8F, 0x73, 0x00, 0x00, 0x00, 0x70, 0x9E, 0xCF, 0x00, 0x80, 0xFC, 0xFF, 0xFF, 0xFF, 0x7F, 0x80, 0x0F, 0x00, 0xF8, 0xFF, 0xFF, 0x3B, 0x9F, 0x47, 0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x7F, 0xF8, 0xFF, 0xFF, 0xB9, 0xCF, 0x67, 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0xA0, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0x9D, 0xC7, 0x23, 0x00, 0x60, 0xF8, 0xFF, 0xFF, 0xFF, 0x83, 0xFF, 0xFF, 0x3F, 0x00, 0x7C, 0x00, 0xCC, 0xE3, 0xF3, 0x1F, 0xE0, 0xFD, 0xFF, 0xFF, 0xFF, 0x03, 0xF0, 0x00, 0x3E, 0xFF, 0x3C, 0xFE, 0xEF, 0xE3, 0x03, 0x18, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0x03, 0xF9, 0x7E, 0x9E, 0xC1, 0x3E, 0x03, 0xF6, 0xF1, 0x01, 0x08, 0x70, 0x7E, 0xE0, 0x0F, 0xFC, 0xC1, 0x7C, 0x22, 0x9F, 0x40, 0x9E, 0x01, 0xF2, 0xF0, 0xF0, 0x0D, 0x18, 0x7E, 0xE0, 0x07, 0xFC, 0xC1, 0x3E, 0x01, 0xCF, 0x60, 0x9F, 0x00, 0xF9, 0xFA, 0xF0, 0x04, 0xC8, 0xFF, 0xFF, 0xFF, 0xFF, 0x77, 0x9E, 0x90, 0x4F, 0x20, 0xCF, 0x80, 0x7D, 0x79, 0xF8, 0x06, 0xEC, 0xFF, 0xFF, 0xFF, 0xFF, 0x33, 0xDF, 0x90, 0x27, 0xB0, 0x4F, 0xC0, 0x3C, 0x7D, 0x78, 0x02, 0xE4, 0xFF, 0xFF, 0xFF, 0xFF, 0x9B, 0xEF, 0xCF, 0xF7, 0x9F, 0xE7, 0x7F, 0x9E, 0x3C, 0x7C, 0x03, 0xE6, 0x1F, 0xF0, 0x83, 0xFF, 0xC0, 0x27, 0xE0, 0x03, 0xC0, 0x07, 0x00, 0xDF, 0x3E, 0x3E, 0x01, 0xC2, 0x1F, 0xF0, 0x81, 0x3F, 0xFC, 0x93, 0xFF, 0xE1, 0xFF, 0xFF, 0xCF, 0x4F, 0xFE, 0xBF, 0x01, 0xCF, 0xFF, 0xFF, 0xFF, 0x1F, 0xFE, 0xD9, 0xFF, 0xF0, 0xFF, 0xFF, 0xEF, 0x67, 0xFF, 0x8F, 0x00, 0xEC, 0xFF, 0xFF, 0xFF, 0x0F, 0xFE, 0xEC, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0x33, 0xFF, 0x47, 0x00, 0xE4, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x38, 0x00, 0x30, 0x00, 0x06, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
float Vcc=5.0;
float bat_in_total[2] = {0,0};;

char shibori = 1 ;
boolean startup = true;
boolean dsg_first = false;
float dsg_current_base;
float dsg_current_volt;
/****************************************************************************************/
//thread
#define PT_WAIT(pt, timestamp, usec) PT_WAIT_UNTIL(pt, millis() - *timestamp > usec);*timestamp = millis();
static struct pt pt1;
float BatmAh = 0;    //容量
float BatmAh_num = 0; //1秒の容量変化値
float BatVolt = 0;   //放電中の電圧加算(1秒ごとの加算値
float BatVolt_num = 0;   //放電中の電圧加算(1秒ごとの加算値
boolean dsg_flg = false;   //放電中の電圧加算(1秒ごとの加算値
int base = 0; // (0G) = 2.5V(2500mV)
int BattLow = 0;
float BattLowLevel = 0.0;
void vcc_test_display(float data) {
  char buf[32] = {0};
  char buf2[32] = {0};

  sprintf(buf, "Vcc In = %s", dtostrf(data, 1, 5, buf2));
  u8g.firstPage();
  do {
    u8g.drawStr(0, C_LINE2, buf);
  } while ( u8g.nextPage() );
}
/*********************************************************************
   pinModeInit
 *********************************************************************/
void pinModeInit() {
  for ( int i = 0; i < 20; i++ ) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(DCV_in, INPUT); //
  pinMode(DSG_in, INPUT); //
  pinMode(BAT_in, INPUT); //
  digitalWrite(DCV_in, LOW);
  pinMode(SW_PLUS_PORT, INPUT_PULLUP);
  pinMode(SW_MINUS_PORT, INPUT_PULLUP);
  pinMode(SW_ENTER_PORT, INPUT_PULLUP);
  pinMode(SW_CANCEL_PORT, INPUT_PULLUP);
  pinMode(DSG_PWM, OUTPUT);
  pinMode(LED_DISCHARGE, OUTPUT);
  digitalWrite(LED_DISCHARGE, LOW);
}

int   REF_VAL = 0;    // 基準値取得
float REF_DEF = 0;    // 基準電圧
/*********************************************************************
   startup処理
 *********************************************************************/
void setup() {
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;  //PWM周期変更
  // ptを初期化
  PT_INIT(&pt1);
  pinModeInit();

  Serial.begin(115200);
  Serial.println("start");

  eep_data_get();
  count = 150;

  //1sec timer set
  MsTimer2::set(10, timer_10msec);
  MsTimer2::start();
  u8g.setFont(u8g_font_7x14r);
#if BMP_LOGO==true
  u8g.firstPage();
  do {
    u8g.drawXBMP( 0, 0, 128, 64, bootimg);
  } while ( u8g.nextPage() );
  delay(100);
#endif
  //放電停止
  discharge_init();
  startup = true;
}
/* ******************************************************************/
// 単4電池電圧測定処理
float cpuVcc() {                     // 電源電圧(AVCC)測定関数
  long sum = 0;
  adcSetup(0x4E);                    // Vref=AVcc, input=internal1.1V
  for (int n = 0; n < 10; n++) {
    sum = sum + adc();               // adcの値を読んで積分
  }
  return (1.10 * 10240.0) / sum;    // ここは絶対1.10を掛け算する（過去8台は演算良くないかも）
                                    // 電圧を計算して戻り値にする
}

/* ******************************************************************/
void adcSetup(byte data) {           // ADコンバーターの設定
  ADMUX = data;                      // ADC Multiplexer Select Reg.
  ADCSRA |= ( 1 << ADEN);            // ADC イネーブル
  ADCSRA |= 0x07;                    // AD変換クロック　CK/128
  delay(10);                         // 安定するまで待つ
}

/* ******************************************************************/
unsigned int adc() {                 // ADCの値を読む
  unsigned int dL, dH;
  ADCSRA |= ( 1 << ADSC);            // AD変換開始
  while (ADCSRA & ( 1 << ADSC) ) {   // 変換完了待ち
  }
  dL = ADCL;                         // LSB側読み出し
  dH = ADCH;                         // MSB側
  return dL | (dH << 8);             // 10ビットに合成した値を返す
}

/*********************************************************************
   10msecタイマー割り込み
 **********************************************************************/
void timer_10msec() {
  count_1sec++;
  count_30msec ++;
  count_100msec ++;
  count_sw_func ++;
  int chk_num;
  char buf[32]  = {0};

  if ( count > 0) {
    if ( --count <= 0 ) {
      startup = false;
      BattLowLevel=Vcc-0.03;
    }
  }

  if ( count_1sec > 99) {
    timer_1sec();
    count_1sec = 0 ;
  }

  // P-006電池電圧判断
  if ( startup ) {
    chk_num=2;
  }
  else{
    chk_num=50;
  }
    
#if 1
  if ( ++count_batt > chk_num) {
    Vcc  = (Vcc * 0.9) + (cpuVcc() * 0.1);                   // 電源電圧測定
    CalcV = (Vcc /1023 ) + calc_v ;
//    vcc_test_display(Vcc);
    if( startup == false ){
      if ( Vcc < BattLowLevel ) {
        BattLow++;
      }
      else {
        BattLow = 0;
      }
    }    
    count_batt = 0;
  }
#endif
}

/*********************************************************************
   swatch
 **********************************************************************/
static int swatch(struct pt *pt) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while (true) {
    key_in();      // key 入力
    PT_WAIT(pt, &timestamp, 30);
  }
  PT_END(pt);
}

/*********************************************************************
   1secタイマー割り込み
 **********************************************************************/
void timer_1sec() {
  switch (display_stat) {
    case FUNC_DISCHARGE +FUNC_MOVE:
    case FUNC_DISCHARGE2+FUNC_MOVE:
      discharge_time++;  //放電時間用　秒数カウント
      discharge_all_time++;
      if ( dsg_flg ) {
        BatmAh_num = (f_current[0] * 1000) / 3600; //1秒の容量変化値
        BatmAh += BatmAh_num ;      //容量加算
        BatVolt += f_volt[0] ;
        BatVolt_num++;
      }
      {
        Serial.print(discharge_all_time);
        Serial.print(",");
        Serial.print(f_volt[0]);
        Serial.print(",");
        Serial.print(f_current[0]);
        Serial.print(",");
        Serial.print(BatmAh);
        Serial.print(",");
        Serial.println(duty);
      }

      break;
    default : break;
  }
}
/*********************************************************************
   main処理
 **********************************************************************/
#define CUR_CALC_CALIB      5.000 //
#define VOL_BASE_NUM        0.001181640625

void loop() {
  swatch(&pt1);

  if ( count_sw_func > 1 ) {
    count_sw_func = 0;
    sw_func();
  }

  volt_in();
  if ( count_30msec > 3) {
    if ( vcnt >= 30 ) {
//      bat_in_total[0] = bat_in_total[1]* (0.0048191593352884 +(0.0000012 * 200)) ;

      f_volt[0] = (f_volt[2] / vcnt)  ;
      f_volt[0] *= CalcV ;

      if( f_volt[0] < 0.3){
        f_volt[0]=0;
      }
      f_volt[2] = 0;

      f_current[1] = (f_current[1] / vcnt) ;
      f_current[1] *= CalcV ;
      f_current[0] = (dsg_current_base - f_current[1]) * CUR_CALC_CALIB;
      if ( f_current[0] <= 0.1) {
        f_current[0] = 0.0;
      }
      dsg_current_volt = f_current[1] ;
      if (display_stat == (FUNC_DISCHARGE | FUNC_MOVE) || display_stat == (FUNC_DISCHARGE2 | FUNC_MOVE) ) {
      }
      else {
        dsg_current_base = f_current[1];
      }
      f_current[1] = 0;
      vcnt = 0;
    }
    count_30msec = 0 ;
  }

#if BMP_LOGO==true
  if ( count_100msec > 10 && startup == false) {  // logo
#else
  if ( count_100msec > 10) {
#endif
    //　表示切替
    count_100msec = 0 ;
    u8g.firstPage();
    do {
      lcd_display();
    } while ( u8g.nextPage() );
  }
  discharge();

#if MULTI_CHECK==true
  if ( rpm_cnt > 0) {
    calc_rpm();
    for (int i = 0; i < 100 ; i++) {
      delay(10);
    }
  }
#endif
}

/*
   電圧測定サブルーチン
*/
float vin = 0;
float cin = 0;
int g_in = 0;;

void volt_in() {
  if ( vin_flg > 5 ) {
    vin = (analogRead(DCV_in) * 2) ;
    f_volt[2] = f_volt[2] + vin;
    {
      cin = analogRead(DSG_in) ;
      f_current[1] = f_current[1] + cin;
    }
//    // アナログ入力の値を電圧に変換(mV)
//    bat_in_total[1] = (bat_in_total[1] * 0.9) + ((float)(analogRead(BAT_in)*0.1)) ;
 
    vin_flg = 0;
    vcnt++;
  }
  else {
    vin_flg++;;
  }
}

/*********************************************************************
   lcd_display 表示処理
 **********************************************************************/
void lcd_display() {
  char buffer0[32] = {0};
  char buffer1[32] = {0};
  char buffer2[32] = {0};
  char buf[32]  = {0};
  char buf2[32] = {0};
  char buf3[32] = {0};
  int t_sec, t_min;

  if ( startup ) {
#if BMP_LOGO==true
    discharge_init();
    display_stat = FUNC_DISCHARGE;
#else
    strcpy(buffer0, APP_NAME);
    strcpy(buffer2, APP_VER);
    discharge_init();
    display_stat = FUNC_DISCHARGE;
    u8g.drawStr(0, C_LINE1, buffer0);
    u8g.drawStr(0, C_LINE2, buffer1);
    u8g.drawStr(0, C_LINE3, buffer2);
#endif
    return;
  }
  
//  if ( BattLow >= 3 ) {
//    sprintf(buffer0, "Battery %s %s",dtostrf(Vcc,2,2,buf3),dtostrf(BattLowLevel,2,2,buf));
////    strcpy(buffer0, "Battery Empty  ");
//    strcpy(buffer2, "         Change");
//    discharge_init();
//    display_stat = FUNC_DISCHARGE;
//    u8g.drawStr(0, C_LINE1, buffer0);
//    u8g.drawStr(0, C_LINE2, buffer1);
//    u8g.drawStr(0, C_LINE3, buffer2);
//    return;
//  }


  switch (display_stat) {
    case FUNC_DISCHARGE:
      strcpy(buffer0, "Discharge Race  ");
//      sprintf(buffer0, "Discharge Race%s",dtostrf(Vcc,2,2,buf3));
      sprintf(buffer2, "%sV  %sV  %sA", dtostrf(f_volt[0], 2, 2, buf2), dtostrf(f_volt[1], 2, 2, buf3), dtostrf(target_race_current, 2, 1, buf));
      break;
    case FUNC_DISCHARGE2:
      strcpy(buffer0, "Discharge Normal");
      sprintf(buffer2, "%sV  %sV  %sA", dtostrf(f_volt[0], 2, 2, buf2), dtostrf(f_normal_target, 2, 2, buf3), dtostrf(target_normal_current, 2, 1, buf));
      break;
    case (FUNC_DISCHARGE+FUNC_EDIT):
      strcpy(buffer0, "Target Set  Race");
      sprintf(buffer2, "       %sV", dtostrf(f_volt[1], 2, 2, buf3));
      break;
    case (FUNC_DISCHARGE2+FUNC_EDIT):
      strcpy(buffer0, "Target Set  Normal");
      sprintf(buffer2, "       %sV", dtostrf(f_normal_target, 2, 2, buf3));
      break;
    case (FUNC_DISCHARGE+FUNC_EDIT2):
      strcpy(buffer0, "Current Set Race ");
      sprintf(buffer2, "              %sA", dtostrf(target_race_current, 2, 1, buf3));
      break;
    case (FUNC_DISCHARGE2+FUNC_EDIT2):
      strcpy(buffer0, "Current Set Normal");
      sprintf(buffer2, "              %sA", dtostrf(target_normal_current, 2, 1, buf3));
      break;

    case (FUNC_DISCHARGE+FUNC_MOVE):
    case (FUNC_DISCHARGE2+FUNC_MOVE):
      t_min = discharge_all_time / 60;
      t_sec = discharge_all_time % 60;

      if ( display_stat == FUNC_DISCHARGE + FUNC_MOVE) {
        if( hold_mode_disp == true){
          if ( t_min >= 100) {
            sprintf(buffer0, "Set:%sV H %03d:%02d", dtostrf(f_volt[1], 2, 2, buf3), t_min, t_sec);
          }
          else {
            sprintf(buffer0, "Set:%sV H  %02d:%02d", dtostrf(f_volt[1], 2, 2, buf3), t_min, t_sec);
          }
        }
        else{
          if ( t_min >= 100) {
            sprintf(buffer0, "Set:%sV R %03d:%02d", dtostrf(f_volt[1], 2, 2, buf3), t_min, t_sec);
          }
          else {
            sprintf(buffer0, "Set:%sV R  %02d:%02d", dtostrf(f_volt[1], 2, 2, buf3), t_min, t_sec);
          }
        }
      }
      else {
        if ( t_min >= 100) {
          sprintf(buffer0, "Set:%sV N %03d:%02d", dtostrf(f_normal_target, 2, 2, buf3), t_min, t_sec);
        }
        else {
          sprintf(buffer0, "Set:%sV N  %02d:%02d", dtostrf(f_normal_target, 2, 2, buf3), t_min, t_sec);
        }
      }
      sprintf(buffer2, "Now:%sV     %sA ", dtostrf(f_volt[0], 2, 2, buf2), dtostrf(f_current[0], 2, 1, buf));
      // 2セルで1.75Vを下回ったら終わる
      if ( f_volt[0] <= 1.75 ) {
        discharge_start(DCG_END, 0);
        discharge_time = 0;
        discharge_sts = 0;   // 放電終了
        hold_mode_disp=false;
        display_stat &= ~FUNC_MOVE;
        display_stat |= FUNC_COMP ;
        if ( BatVolt_num <= 0 ) {
          BatVolt = 0;
        }
        else {
          BatVolt = BatVolt / BatVolt_num  ;
        }
//        comp_dsp = 0;
        BatVolt_num = 0;
        digitalWrite(LED_DISCHARGE, LOW);
      }
      break;
    case FUNC_DISCHARGE + FUNC_COMP:
      t_min = discharge_all_time / 60;
      t_sec = discharge_all_time % 60;
      if ( t_min >= 100) {
        sprintf(buffer0, "%sV %sV %03d:%02d", dtostrf(f_volt[0], 2, 2, buf), dtostrf(f_volt[1] , 2, 2, buf3), t_min, t_sec);
      }
      else {
        sprintf(buffer0, "%sV %sV  %02d:%02d", dtostrf(f_volt[0], 2, 2, buf), dtostrf(f_volt[1] , 2, 2, buf3), t_min, t_sec);
      }
      sprintf(buffer2, "%sA %sV %s", dtostrf(target_race_current, 2, 2, buf), dtostrf(BatVolt, 2, 2, buf2), dtostrf(BatmAh , 4, 0, buf3));

      break;
    case FUNC_DISCHARGE2 + FUNC_COMP:
      t_min = discharge_all_time / 60;
      t_sec = discharge_all_time % 60;
      if ( t_min >= 100) {
        sprintf(buffer0, "%sV %sV %03d:%02d", dtostrf(f_volt[0], 2, 2, buf), dtostrf(f_normal_target , 2, 2, buf3), t_min, t_sec);
      }
      else {
        sprintf(buffer0, "%sV %sV  %02d:%02d", dtostrf(f_volt[0], 2, 2, buf), dtostrf(f_normal_target , 2, 2, buf3), t_min, t_sec);
      }
      sprintf(buffer2, "%sA %sV %s", dtostrf(target_normal_current, 2, 2, buf), dtostrf(BatVolt, 2, 2, buf2), dtostrf(BatmAh , 4, 0, buf3));

      break;
    case FUNC_CALIB:
      strcpy(buffer0, "Calibration     ");
      sprintf(buffer2, "%sV ", dtostrf(f_volt[0], 2, 4, buf));
//      sprintf(buffer2, "%sV %s", dtostrf(f_volt[0], 2, 4, buf),dtostrf(vin, 4, 0, buf2));
      break;
    case (FUNC_CALIB + FUNC_EDIT) :
      strcpy(buffer0, "Calibration  Set");
      sprintf(buffer2, "%sV  DOWN/UP", dtostrf(f_volt[0], 2, 4, buf));
      break;
    case FUNC_HOLDMODE:
      strcpy(buffer0,   "HOLD MODE       ");
      if( hold_mode){
        strcpy(buffer2, " ->ON           ");
      }
      else{
        strcpy(buffer2, " ->OFF          ");
      }
      break;
    case (FUNC_HOLDMODE + FUNC_EDIT) :
      strcpy(buffer0, "HOLD MODE Select");
      if( hold_mode){
        strcpy(buffer2, " ->ON    DOWN/UP");
      }
      else{
        strcpy(buffer2, " ->OFF   DOWN/UP");
      }
      break;
#if MULTI_CHECK == true
    case FUNC_SPEED:
      if ( speed_num >= 10.0) {
        sprintf(buffer2, "%s Km/h", dtostrf(speed_num, 2, 2, buf));
      }
      else {
        sprintf(buffer2, " %s Km/h", dtostrf(speed_num, 2, 2, buf));
      }
      break;
    case FUNC_GAUSS:
      calc_gauss();
      if ( sign_gauss == 1 ) {
        sprintf(buffer0, "Gauss N=%3d", i_gauss);
      }
      else {
        sprintf(buffer0, "Gauss S=%3d", i_gauss);
      }
      sprintf(buffer2, "MAX N=%3d  S=%3d", i_gauss_max[0], i_gauss_max[1]);
      break;
#endif
    default : break;
  }
  u8g.drawStr(0, C_LINE1, buffer0);
  u8g.drawStr(0, C_LINE3, buffer2);

  if ( display_stat == (FUNC_DISCHARGE + FUNC_COMP ) ||
       display_stat == (FUNC_DISCHARGE2 + FUNC_COMP) ) {
    u8g.setFont(u8g_font_5x8r);
    u8g.drawStr(112, C_LINE3, "mAh");
    u8g.setFont(u8g_font_7x14r);
  }
}

/*********************************************************************
   sw_func :　スイッチ
 **********************************************************************/
int sw_phase = 0 ;
boolean sw_wait_flg = true ; // true = 解除まで待つ  false=長押しモード
int long_push_count = 0;
void sw_func() {

  switch (sw_phase) {
    case 0:       // 押下待ち

      sw_wait_flg = false;
      if ( sw_stat[0] & SW_MINUS_BIT) {
        if (display_stat == FUNC_DISCHARGE + FUNC_EDIT) {
          f_volt[1] = f_volt[1] - 0.01 ;
          if ( f_volt[1] <= 1.8) {
            f_volt[1] = 1.8;
          }
        }
        else if (display_stat == FUNC_DISCHARGE + FUNC_EDIT2) {
          target_race_current = target_race_current - 0.1 ;
          if ( target_race_current <= 0.5) {
            target_race_current = 0.5;
          }
        }
        else if (display_stat == FUNC_DISCHARGE2 + FUNC_EDIT) {
          f_normal_target = f_normal_target - 0.01 ;
          if ( f_normal_target <= 1.8) {
            f_normal_target = 1.8;
          }
        }
        else if (display_stat == FUNC_DISCHARGE2 + FUNC_EDIT2) {
          // 放電電流設定
          target_normal_current = target_normal_current - 0.1 ;
          if ( target_normal_current <= 0.3) {
            target_normal_current = 0.3;
          }
        }
        else if ( display_stat == (FUNC_CALIB + FUNC_EDIT)) {
          //キャリブレーション
          calc_v = calc_v - 0.0000012 ;
          sw_wait_flg = true;
        }
        else if ( display_stat == (FUNC_HOLDMODE + FUNC_EDIT)) {
          if( hold_mode ){
            hold_mode=false;
          }
          else{
            hold_mode=true;
          }
        }
        else if ( display_stat == (FUNC_DISCHARGE2 + FUNC_COMP) || display_stat == (FUNC_DISCHARGE + FUNC_COMP)) {
        }
        sw_phase = 1;
      }
      else if ( sw_stat[0] & SW_PLUS_BIT) {
        if (display_stat == FUNC_DISCHARGE + FUNC_EDIT) {
          // 電圧設定
          f_volt[1] = f_volt[1] + 0.01 ;
          if ( f_volt[1] >= 3.2) {
            f_volt[1] = 3.2 ;
          }
        }
        if (display_stat == FUNC_DISCHARGE2 + FUNC_EDIT) {
          // 電圧設定
          f_normal_target = f_normal_target + 0.01 ;
          if ( f_normal_target >= 3.2) {
            f_normal_target = 3.2;
          }
        }
        else if (display_stat == FUNC_DISCHARGE + FUNC_EDIT2) {
          // 電流設定
          target_race_current = target_race_current + 0.1 ;
// 3.0
          if ( target_race_current >= 3.0) {
            target_race_current = 3.0 ;
          }
        }
        else if (display_stat == FUNC_DISCHARGE2 + FUNC_EDIT2) {
          target_normal_current = target_normal_current + 0.1 ;
// 3.0
          if ( target_normal_current >= 3.0) {
            target_normal_current = 3.0;
          }
        }
        else if ( display_stat == (FUNC_CALIB + FUNC_EDIT)) {
          calc_v = calc_v + 0.0000012 ;
          sw_wait_flg = true;
        }
        else if ( display_stat == (FUNC_HOLDMODE + FUNC_EDIT)) {
          if( hold_mode ){
            hold_mode=false;
          }
          else{
            hold_mode=true;
          }
        }
        else if ( display_stat == (FUNC_DISCHARGE2 + FUNC_COMP) || display_stat == (FUNC_DISCHARGE + FUNC_COMP)) {
//          if ( comp_dsp == 0) {
//            comp_dsp = 1;
//          }
//          else {
//            comp_dsp = 0;
//          }
        }
        sw_phase = 1;
      }

#if MULTI_CHECK == false
      if ( sw_stat[0] & SW_CANCEL_BIT )
#else
      if ( sw_stat[0] & SW_CANCEL_BIT || sw_stat2[0] & SW_SPEED_BIT )
#endif
      {
        sw_phase = 1;
        sw_wait_flg = true;
        if (display_stat == (FUNC_DISCHARGE | FUNC_EDIT) || display_stat == (FUNC_DISCHARGE2 | FUNC_EDIT)) {
          display_stat &= ~FUNC_EDIT;
          lcd_display();
        }
        else if (display_stat == (FUNC_DISCHARGE | FUNC_EDIT2) || display_stat == (FUNC_DISCHARGE2 | FUNC_EDIT2)) {
          display_stat &= ~FUNC_EDIT2;
          display_stat |= FUNC_EDIT;
          lcd_display();
        }
        else if (display_stat == (FUNC_DISCHARGE | FUNC_MOVE)) {
        }
        else if (display_stat == (FUNC_DISCHARGE2 | FUNC_MOVE)) {
        }
        else if (display_stat == (FUNC_DISCHARGE | FUNC_COMP)) {
          display_stat = FUNC_DISCHARGE;
          lcd_display();
        }
        else if (display_stat == (FUNC_DISCHARGE2 | FUNC_COMP)) {
          display_stat = FUNC_DISCHARGE2;
          lcd_display();
        }
        else if ((display_stat == (FUNC_CALIB |  FUNC_EDIT)) ) {
          display_stat = FUNC_DISCHARGE;
          eep_data_get();   // 元に戻す
        }
        else if ((display_stat == (FUNC_HOLDMODE |  FUNC_EDIT)) ) {
          display_stat = FUNC_CALIB;
          eep_data_get();   // 元に戻す
        }
        else if ((display_stat == (FUNC_CALIB |  FUNC_EDIT2)) ) {
          display_stat = FUNC_DISCHARGE;
          eep_data_get();   // 元に戻す
        }
        else {
          display_stat++;
          if (display_stat > FUNC_MAX ) {
            display_stat = 0;
          }
#if MULTI_CHECK==true
          if ( display_stat == FUNC_GAUSS ) {
            gsuss_init();
          }
#endif
        }
      }

      if ( sw_stat[0] & SW_ENTER_BIT) {
        sw_phase = 1;
        sw_wait_flg = true;
        if ( display_stat == (FUNC_DISCHARGE | FUNC_EDIT) || display_stat == (FUNC_DISCHARGE2 | FUNC_EDIT)) {
          display_stat &= ~FUNC_EDIT;
          display_stat |= FUNC_EDIT2;
        }
        else if (display_stat == (FUNC_DISCHARGE | FUNC_EDIT2) || display_stat == (FUNC_DISCHARGE2 | FUNC_EDIT2)) {
          if (display_stat == (FUNC_DISCHARGE | FUNC_EDIT2 )) {
            shibori = 1;
          }
          else {
            shibori = 0;
          }
          display_stat &= ~FUNC_EDIT2;
          display_stat |= FUNC_MOVE;
          discharge_check(0);     // このなかで放電のduty決まっている。
          if ( shibori == 1 ) {
            target_current = target_race_current;
          }
          else {
            target_current = target_normal_current;
          }
          discharge_sts = 1;
          discharge_time = 0 ;
          discharge_all_time = 0;
          dsg_first = true;
          eep_data_put();
          BatmAh = 0;
          BatVolt = 0;
          digitalWrite(LED_DISCHARGE, HIGH);
        }

        if (display_stat == FUNC_DISCHARGE || display_stat == FUNC_DISCHARGE2 ) {
          display_stat |= FUNC_EDIT;
        }

        if ( (display_stat == (FUNC_CALIB | FUNC_EDIT)) ||
             (display_stat == (FUNC_CALIB | FUNC_EDIT2))) {
          display_stat = FUNC_CALIB;
          eep_data_put();  //保存
        }
        else if (display_stat == FUNC_CALIB ) {
          display_stat |= FUNC_EDIT;
        }
        else if ( display_stat == (FUNC_HOLDMODE | FUNC_EDIT)) {
          display_stat = FUNC_HOLDMODE;
          eep_data_put();  //保存
        }
        else if (display_stat == FUNC_HOLDMODE ) {
          display_stat |= FUNC_EDIT;
        }
        else if (display_stat == (FUNC_DISCHARGE | FUNC_COMP)) {
          display_stat = FUNC_DISCHARGE;
          lcd_display();
        }
        else if (display_stat == (FUNC_DISCHARGE2 | FUNC_COMP)) {
          display_stat = FUNC_DISCHARGE2;
          lcd_display();
        }
#if MULTI_CHECK == true
        if ( display_stat == FUNC_GAUSS ) {
          gsuss_init();
        }
#endif
      }
      if ( sw_stat[0] == 0x00 ) {
        long_push_count = 0;
      }
      break;
    case 1:       // 解除待ち
      if ( sw_wait_flg == true ) {
        if ( sw_stat[0] == 0x00 ) {
          long_push_count = 0;
          sw_phase = 0;
        }
      }
      else {
        if ( sw_stat[0] == 0x00 ) {
          sw_phase = 0;
          long_push_count = 0;
        }
        if ( ++long_push_count  >= 20 ) {
          // 長押しあり
          long_push_count = 19 ;
          sw_phase = 0;
        }
      }
      break;
  }
}
#if MULTI_CHECK == true
void gsuss_init() {

  if ( display_stat == FUNC_GAUSS) {


    f_gauss = f_gauss / gcnt;
    f_gauss = (f_gauss / 1024.0) * 5.0 * 1000;
    base = f_gauss;
    i_gauss_max[0] = 0;
    i_gauss_max[1] = 0;
    gcnt = 0;
    f_gauss = 0;
    u8g.firstPage();
    do {
      lcd_display();
    } while ( u8g.nextPage() );
    //    eep_data_put();
  }
  sw_wait();
}

#endif
