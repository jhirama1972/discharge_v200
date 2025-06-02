/****************************************************************************************/
/* �ėp */
/****************************************************************************************/
unsigned char sw_stat[2] = {1, 1}; // SW

unsigned char sw_stat2[2] = {2, 2}; // SW

int count_1sec = 0;
int count_batt = 0;
int count_30msec = 0;
int count_100msec = 0;
int count_sw_func = 0;
int count = 0;
int vin_flg = 0; //
long vcnt = 0;   //
float CalcV ;    // (4.12/1023.0);
float calc_v ;    // (4.12/1023.0);
char dsp_mode;   // 0=Soft 1=Midiam 2=Powerful
int read_gauss;

/****************************************************************************************/
/* MENU�A�����p */
/****************************************************************************************/
int display_stat = FUNC_DISCHARGE;

float f_gauss ;
int gcnt = 0 ;
int i_gauss = 0;
int i_gauss_max[2] = {0, 0};
int sign_gauss = 0;

/****************************************************************************************/

/* ���d�p */
/****************************************************************************************/
#define DCG_END   0
#define DCG_START 1
float duty = 0.0 ;
int discharge_interval = 0;
unsigned int discharge_time = 0;
unsigned int discharge_all_time = 0;
unsigned char discharge_sts = 0;
float f_volt[3] = {2.80, 2.75, 0};      // [0]=Now [1]=target
float f_current[2] = {0, 0};           // [0]=Now [1]=target

float target_current=3.0;            // 放電制御中に使用する変数
float target_race_current = 2.0;     // 絞り放電の電流値（開始の値
float target_normal_current = 2.0;   // 通常放電の電流値（最初から最後までこの値
float f_normal_target = 2.00;        // 


boolean hold_mode;
boolean hold_mode_disp=false;
