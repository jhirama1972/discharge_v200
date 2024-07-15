//TEST
typedef struct EEP_Data {
  float calc_v;
  float dischg_v;
  float f_normal_target;
  float target_race_current;
  float target_normal_current;
  boolean hold_mode;
  char  password[8]; /* daiki1111*/
} EEPData, *pEEPData;
