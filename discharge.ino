#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>
void discharge_init() {
  discharge_sts = 0;
  duty = 0;
  discharge_time = 0;
  discharge_all_time = 0;
  discharge_start(DCG_END, 0);
  hold_mode_disp=false;

}

/*
   放電ー
*/
#define DSG_AREA_CHECK 0.048
void discharge() {
  discharge_interval++;
  //手動で放電キャンセル

  if ((sw_stat[0] & SW_CANCEL_BIT) != 0 && discharge_sts > 0 ) {
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
    //    comp_dsp = 0;
    BatVolt_num = 0;
    sw_wait();
    digitalWrite(LED_DISCHARGE, LOW);
  }

  if ( discharge_interval > 600 ) {
    discharge_interval = 0;
    switch (discharge_sts) {
      case 0: // 開始前（ターゲット電圧設定モード）
        discharge_time = 0;
        break;

      case 1: // 開始
        duty = 0;
        if ( target_current < 1.0 ) {
          discharge_interval = -6000;
        }
        else if ( target_current >= 1.0 && target_current <= 1.5 ) {
          discharge_interval = -3000;
        }
        discharge_start(DCG_START, duty);
        discharge_sts++;
        break;

      case 2: // 目標放電電流まであがってるか確認
        if ( f_current[0] >= target_current - 0.20  && f_current[0] <= target_current - 0.15  ) {
          discharge_sts++;
          discharge_interval = -6000;
        }
        if ( f_current[0] < target_current - 0.20 ) {
          if ( f_current[0] <= 0.3 ) {
            duty += 5;
          }
          else {
            duty++;
          }
          discharge_start(DCG_START, duty);
        }
        else if ( f_current[0] > target_current - 0.15 ) {
          duty--;
          discharge_sts++;
          discharge_interval = -3000;
          discharge_start(DCG_START, duty);
        }
        if ( discharge_time_check() != 0 ) {
          // 絞りの時だけ一時放電停止
          discharge_start(DCG_END, 0);
          discharge_time = 0;
          discharge_sts = 5;
        }
        break;
      case 3: // 目標放電電流安定化待ち
        if ( f_current[0] >= target_current - DSG_AREA_CHECK && f_current[0] <= target_current + DSG_AREA_CHECK  ) {
          if ( dsg_first == true && shibori == 1 ) {
            // 絞りの時だけ一時放電停止
            discharge_start(DCG_END, 0);
            discharge_time = 0;
            discharge_sts = 5;
            dsg_first = false;
          }
          else {
            discharge_sts++;
          }
        }
        else if ( f_current[0] <= target_current - DSG_AREA_CHECK ) {
          duty++;
          discharge_start(DCG_START, duty);
          discharge_interval = -3000;
        }
        else if ( f_current[0] >= target_current + DSG_AREA_CHECK ) {
          duty--;
          discharge_start(DCG_START, duty);
          discharge_interval = -3000;
        }
        if ( shibori == 1 ) {
          if ( discharge_time_check() != 0 ) {
            // 絞りの時だけ一時放電停止
            discharge_start(DCG_END, 0);
            discharge_time = 0;
            discharge_sts = 5;
          }
        }
        else {
          if ( discharge_check(0) != 0) {
            discharge_start(DCG_END, duty);
            discharge_sts = 0;   // 放電終了
            display_stat &= ~FUNC_MOVE;
            display_stat |= FUNC_COMP ;
            hold_mode_disp=false;
            duty = 0;
            eep_data_get();
            digitalWrite(LED_DISCHARGE, LOW);

            if ( BatVolt_num <= 0 ) {
              BatVolt = 0;
            }
            else {
              BatVolt = BatVolt / BatVolt_num  ;
            }
            //            comp_dsp = 0;
            BatVolt_num = 0;
          }
        }
        break;
      case 4: // 放電中で終了確認
        if ( f_current[0] <= target_current - DSG_AREA_CHECK ) {
          duty++;
          discharge_start(DCG_START, duty);
          discharge_interval = -3000;
        }
        else if ( f_current[0] >= target_current + DSG_AREA_CHECK ) {
          duty--;
          discharge_start(DCG_START, duty);
          discharge_interval = -3000;
        }
        //放電時間経過したか？
        if ( shibori == 1 ) {
          if ( discharge_time_check() != 0 ) {
            // 絞りの時だけ一時放電停止
            discharge_start(DCG_END, 0);
            discharge_time = 0;
   
            discharge_sts++;
          }
        }
        else {
          if ( discharge_check(0) != 0) {
            discharge_start(DCG_END, duty);
            discharge_sts = 0;   // 放電終了
            hold_mode_disp=false;

            display_stat &= ~FUNC_MOVE;
            display_stat |= FUNC_COMP ;
            duty = 0;
            eep_data_get();
            digitalWrite(LED_DISCHARGE, LOW);

            // ver 1.3.1 改修
            if ( BatVolt_num <= 0 ) {
              BatVolt = 0;
            }
            else {
              BatVolt = BatVolt / BatVolt_num  ;
            }
            //            comp_dsp = 0;
            BatVolt_num = 0;
            // ver 1.3.1 改修
          }
        }
        break;
      case 5: //放電後に少し待って再測定する。その待ち時間。
        if ( (discharge_time >= DISCHARGE_AFTER_TIME) || shibori == 0) {
          discharge_sts++;
        }
        break;
      case 6:  //本当の終了判断
        discharge_time = 0;
        if ( discharge_check(0) != 0) {
          if ( hold_mode == true && shibori == 1 ) {
            discharge_sts++;   // HOLD_MODE
          }
          else {
            discharge_sts = 0;   // 放電終了
            hold_mode_disp=false;
            display_stat |= FUNC_COMP ;
            eep_data_get();
            display_stat &= ~FUNC_MOVE;
            if ( discharge_all_time <= 0 ) {
              BatVolt = 0;
            }
            else {
              BatVolt = BatVolt / BatVolt_num  ;
            }
            BatVolt_num = 0;
          }
          discharge_start(DCG_END, duty);
          digitalWrite(LED_DISCHARGE, LOW);
          duty = 0;
        }
        else {
          discharge_sts = 1;    // 放電再開
        }
        break;
      case 7:  // HOLD_MODE
        hold_mode_disp=true;
        if ( discharge_check(0.01) == 0) {
          discharge_sts = 1;    // 放電再開
          display_stat |= FUNC_MOVE;
          dsg_first = true;
          digitalWrite(LED_DISCHARGE, HIGH);
        }
        break;
    }
  }
}

/*
   放電開始/停止
*/
void discharge_start(char start, float fduty) {
  if ( start == DCG_START) {
//    Serial.print("dsg start  duty=");
//    Serial.println(fduty);
    analogWrite(DSG_PWM, fduty); // PWM　duty
    dsg_flg = true;
  }
  else {
    dsg_flg = false;
    analogWrite(DSG_PWM, 0.0);  // PWM　終了
  }
}

/*
   時間による放電完了確認
   ret=0 放電継続
   ret=1 放電終了
*/
unsigned char discharge_time_check() {
  if (discharge_time >= DISCHARGE_TIME) {
    return (1);
  }
  return (0);
}

/*
   電圧測定判定
   ret=0 放電継続
   ret=1 放電終了
*/
unsigned char discharge_check(float offset) {
  if ( shibori == 1 ) {
    if ( f_volt[0] <= f_volt[1] + offset ) {
      // 目標電圧以下に到達
      return (1);
    }
    else {
      float diff = f_volt[0] - f_volt[1];
      // 放電条件設定
      discharge_modeset(diff);
      // 目標電圧以下に未達
      return (0);
    }
  }
  else {
    if ( f_volt[0] <= f_normal_target ) {
      // 目標電圧以下に到達
      return (1);
    }
    else {
      return (0);
    }
  }
}
/*
  　放電条件設定
*/
void discharge_modeset(float diff) {
  if ( shibori == 1) {
    target_current = diff * 100;
    if ( target_current <= 0.5 ) {
      target_current = 0.5;
    }
    //　最大値チェック
    if ( target_current >= target_race_current) {
      target_current = target_race_current;
    }
  }
}
