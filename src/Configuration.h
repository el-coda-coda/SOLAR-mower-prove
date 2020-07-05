/* SolarMower Arduino */
/* configuration file */

#define ESC_MAX_SIGNAL 2000
#define ESC_MIN_SIGNAL 1000
#define VBat_Level_Min  9.0
#define VBat_Level_Max 13.8
#define ICut_Min 0.4      // not used on version 1.0
#define ICut_Max 2.0      // defines the maximum permissible current to the cut motor
#define accelerateTime 2  //total time accelerate = accelerationtime*255 [msec]
#define USdistance 30     //obstacle distance for ultrasonic sensor
#define timeReverse 3000  // duration reverse motor when obstacle detect
#define timeRotate  2000  // duration rotate motor when obstacle detect
#define PWMSpeed    255   // PWM value for thrust motor
#define timeClock   500   // time reading sensor
int PUP=1;
int PDW=2;
int PEN=3;

//Analog Pin
#define Button_PIN     0  // Push button pin
#define ICUT_PIN       1  // Motor cut current
#define IPANEL_PIN     2  // Panel current
#define IBAT_PIN       3  // Battery voltage
#define SDA_PIN        4  // SDA for I2C
#define SCL_PIN        5  // SCL for I2C

//Digital pin
#define RXD_PIN        0  // Arduino serial hardware RX
#define TXD_PIN        1  // Arduino serial hardware TX
// #define Encoder_Pin    2  // Wheels encoder
#define PWMA_PIN       3  // PWM for motor A
#define DIRA_PIN      4  // motor DIRA
//#define BWFR_pin       5  // BWFR signal
//#define BWFL_pin       6  // BWFL signal
#define Panel_PIN      7  // Panel on/off
#define ESC_PIN       8  // ESC for motor cut
#define SWOL_PIN       9  // switch for right obstacle
#define SWOR_PIN      10  // switch for lift obstacle
#define PWMB_PIN      11  // PWM for motor B
#define DIRB_PIN      12  // motor DIRB
//#define LCD_pin       13  // LCD data signal
#define US1_TRIG_PIN    5
#define US1_ECHO_PIN    2
#define US2_TRIG_PIN    6
#define US2_ECHO_PIN    13

//Parameters for US
#define ULTRASONIC_OUTOFRANGE 38000
#define VERY_LONG_DINSTANCE 1000
#define ULTRASONIC_PARAMETER 0.034
#define MOVEMENT_OBSTACLE_DISTANCE 50

// Parameters for ESC
#define ESC_OFF 1000
#define ESC_ON 1300 //ESC ON PUO' ANDARE DA 1000 A 2000

//Parameters for engines
#define ENGINE_MAX 255 //30 rpm a vuoto
#define ENIGNE_LEFT_OFFSET  0 // differenza di potenza per mandare il robot dritto
#define ENGINE_RIGHT_OFFSET 6   // differenza di potenza per mandare il robot dritto
#define ENGINE_DELAY 1000
#define ENGINE_STEP_DELAY 200 //Delay per ogni step di motore
#define MOVEMENT_OBSTACLE_FOUND -10
#define MOVEMENT_GENERIC_ERROR -1
#define US_DELAY 200
#define CURVE_RIGHT 90
#define CURVE_LEFT -90
#define TURN_180 180
#define RANGE_US_ERROR 5
#define GO_BACK -255
#define MOVEMENT_OK  0
//wheel diameter in centimeters
#define WHEEL_DIAMETER 12
#define RPM 25
#define CURVE_LENGHT 65.94

#define distanza_curva  20
#define ROBOT_LARGE 50
#define BLADE_LARGE 23
#define CURVE_PROBLEM 2 // il robot quando gira su una sola ruota impiega il doppio del tempo a fare la stessa strada
//LCD
#define DEBUG_LEVEL   5
#define INFO_LEVEL   1
#define VERBOSE_LEVEL   7

//CONSTANS FOR COMUNICATION
#define BATTERY_READ    1
#define PANEL_READ_VOLTS  2
#define ESC_READ    3
#define US_READ 4
#define PANEL_READ_AMP  5
#define RECTANGLE_ENABLED true
#define MOVEMENT_ENABLED true
#define ULTRASONIC_ENABLED false
#define ESC_ENABLED true
#define LOG_TO_SERIAL true
#define LOG_TO_LCD true
#define LOG_LEVEL  1    //1 INFO, 5 DEBUG , 7 VERBOSE DEBUG
#define RECTANGLE_MODE_1    1
#define RECTANGLE_MODE_0    0

//variables
float VBat;               // Battery voltage [V]
int VBatPC;               // Battery voltage percentage
float VBatScale=0.054;    // Battery scale for Volt converter
float IPanel;             // Panel current [A]
float IPanelOffset;       // Panel current offset
float IPanelScale=0.185;  // Panel current scale V/A
float ICut;               // Motor cut current [A]
float ICutOffset;         // Motor cut current offset
float ICutScale=0.185;    // Motor cut current scale V/A
int i;
int cutPower=0;           // Cut Power from 0%=ESC_MIN_SIGNAL to 100%=ESC_MAX_SIGNAL
int cutPower_uSec=ESC_MIN_SIGNAL;      // Cut Power from ESC_MIN_SIGNAL to ESC_MAX_SIGNAL
int oldSpeed=0;           // Speed of mower (0-255)
float IPanelMax=0;           // IPanel max current
unsigned long BWFL_count;
unsigned long BWFR_count;
unsigned long previousMillis = 0;
unsigned long currentMillis; 
volatile int mowerStatus=0; // 0=oncharge (press pen for run)
                            // 1=run
                            // 2=stuck
                            // 3=search
                            // 4=batlow
                            // 5=charge and restart when full
                            // 6=cuterror
volatile unsigned long wheelTime=0;
int movement_return = 0;


// abbiamo un problema: i loro ultrasuoni funzionano con i2c, quindi i loro pin erano collegati ai pin analogici 3 e 4, mentre i nostri devono usare  i pin digitali
// quindi non possiamo usare i pin dello shield, per ora uso i pin di altre cose che non usiamo

int vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // inserire valore esatto resistenza R1 (100K) 
float R2 = 51000.0; // inserire valore esatto resistenza R2 (10K) 
int value = 0;
int us_query = 0;
int distanza1 = 0;
int distanza2 = 0;
int ON_OFF = 1;
int  ON_OFF_ESC_PIN = 4;
int rectangle_mode = 0;
//int x_array = 0;
//int y_array = 0;