/****************************************************************************************/
// define's
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
#define BMP_LOGO false
#define MULTI_CHECK false

#if MULTI_CHECK == false
#define APP_NAME "Discharge Unit    "   //
#define APP_VER  "         ver 2.0.0"   // テスト開始
#else
#define APP_NAME "Multi func Unit2  "   //
#define APP_VER  "         ver 1.0.0"   // テスト開始
#endif

#define FUNC_DISCHARGE     0x00  // 絞り
#define FUNC_DISCHARGE2    0x01  // Normal
#if MULTI_CHECK == true
#define FUNC_SPEED         0x02// 
#define FUNC_GAUSS         0x03  // 
#define FUNC_CALIB         0x04  // キャリブレーション
#else
#define FUNC_HOLDMODE      0x02  // HOLD MODE
#define FUNC_CALIB         0x03  // キャリブレーション
#endif
#define FUNC_MAX       FUNC_CALIB

#define FUNC_EDIT      0x10
#define FUNC_EDIT2     0x20
#define FUNC_MOVE      0x40
#define FUNC_COMP      0x80

#if MULTI_CHECK == true
#define SWNUM 5
#else
#define SWNUM 4
#endif

#define SW_CANCEL_PORT 2
#if MULTI_CHECK == true
#define SW_MINUS_PORT  9
#else
#define SW_MINUS_PORT  3
#endif
#define SW_PLUS_PORT   4
#define SW_ENTER_PORT  5
#if MULTI_CHECK == true
#define SW_SPEED_PORT  8
#endif
#define C_LINE1 12
#define C_LINE2 22
#define C_LINE3 27

#define DSG_in   A3     // 
#define DCV_in   A0     // 

#define RPM_in   3     // 割り込み
//#define BAT_in A1     // アナログ入力 分圧で半分になっている
#define BAT_in A0     // todo アナログ入力
//#define GAUSS_in A1     // アナログ入力

#define DSG_PWM  10      //  6(tim0)  →　10(tim1)変更 2022/03/16
#define LED_DISCHARGE 13

#define SW_CANCEL_BIT      0x01
#define SW_MINUS_BIT       0x02
#define SW_PLUS_BIT        0x04
#define SW_ENTER_BIT       0x08
#if MULTI_CHECK == true
#define SW_SPEED_BIT       0x01
#endif

#define SW_LONG_CANCEL_BIT 0x10
#define SW_LONG_MINUS_BIT  0x20
#define SW_LONG_PLUS_BIT   0x40
#define SW_LONG_ENTER_BIT  0x80
#if MULTI_CHECK == true
#define SW_LONG_SPEED_BIT  0x10
#endif

/****************************************************************************************/
int sw_port[SWNUM] = {
  SW_CANCEL_PORT,
  SW_MINUS_PORT,
  SW_PLUS_PORT,
#if MULTI_CHECK == false
  SW_ENTER_PORT
#else
  SW_ENTER_PORT,
  SW_SPEED_PORT
#endif
};

/****************************************************************************************/
#define DISCHARGE_AFTER_TIME  5  //

typedef  enum D_mode {
  DSG_HARD = 1,
  DSG_MID,
  DSG_SOFT
} Discharge_mode ;
