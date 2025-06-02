#include <EEPROM.h>
/*
   起動時のEEPデータ読み込み
*/
#define EEP_PASS "daiki123"
void eep_data_get() {
  EEPData eep;
  // passworkcheck
  EEPROM.get( 0, eep );
  if ( memcmp(eep.password, EEP_PASS, 8) != 0) {
    // パスワードNGなら初期値書き込み
    memcpy(eep.password, EEP_PASS, 8);
    eep.calc_v = (-0.0000012 * 100);
//    eep.calc_v = 0.0048191593352884 +(0.0000012 * 100);
    eep.dischg_v = 2.7;
    eep.f_normal_target = 1.8;
    eep.target_race_current = 2.0;
    eep.target_normal_current = 3.0;
    eep.hold_mode=true;
    EEPROM.put( 0, eep );
  }
  calc_v = eep.calc_v;
  f_volt[1] = eep.dischg_v;
  f_normal_target = eep.f_normal_target;
  target_race_current = eep.target_race_current;
  target_normal_current = eep.target_normal_current;
  hold_mode = eep.hold_mode;
}
/*
   データ設定時ののEEPデータ書き込み
*/
void eep_data_put() {
  EEPData eep;
  memcpy(eep.password, EEP_PASS, 8);
  eep.calc_v = calc_v;
  eep.dischg_v = f_volt[1];
  eep.f_normal_target = f_normal_target;
  eep.target_race_current = target_race_current;
  eep.target_normal_current = target_normal_current;
  eep.hold_mode =hold_mode;
  EEPROM.put( 0, eep );
}
