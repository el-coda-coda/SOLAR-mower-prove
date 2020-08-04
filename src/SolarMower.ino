#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include "Configuration.h"
#include "Display.h"
#include "Logging.h"
#include "Ultrasuoni_SRF04.h"
#include "Sensors.h"
#include "Esc_control.h"
#include "Compass.h"
#include "Engines.h"
#include "Segments.h"
#include "Rectangle.h"



void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(DIRA_PIN, OUTPUT);    
  pinMode(Panel_PIN, OUTPUT);  
  pinMode(ESC_PIN, OUTPUT);  
  pinMode(SWOR_PIN, INPUT_PULLUP);
  pinMode(SWOL_PIN, INPUT_PULLUP);       
  pinMode(PWMB_PIN, OUTPUT);
  pinMode(DIRB_PIN, OUTPUT);   
  pinMode(US1_ECHO_PIN, INPUT);
  pinMode(US1_TRIG_PIN, OUTPUT);
  pinMode(US2_ECHO_PIN, INPUT);
  pinMode(US2_TRIG_PIN, OUTPUT);  
  pinMode(IPANEL_PIN, INPUT);
  digitalWrite(Panel_PIN, LOW);
  
  engines_stop();
  sensorInit();  
  esc_setup();
  delay(1000);
  sensorReading(PANEL_READ_AMP);  
  digitalWrite(Panel_PIN, HIGH);
  delay(300);
  compassOffSet = sensorReading(COMPASS_READ);
  // turn_left90();
  // turn_left90();
  // turn_left90();
  // turn_left90();
}
void loop ()
{
  delay(2000);
  //int qmc_result = qmc_straight1();
  // if (qmc_result <= CURVE_LEFT) 
  // {
  //   logInfo(String("MTD: curve left: ") + String(qmc_straight_1r(qmc_result)));
  //   engines(-ENGINE_MAX, ENGINE_MAX);
  //   while (qmc_straight_1r(qmc_result) != MOVEMENT_OK)  qmc_result = qmc_straight1();
  //   engines_stop();
  // }
  // if (qmc_result >= CURVE_RIGHT)  
  // {
  //   logInfo(String("MTD: curve right: ") + String(qmc_straight_1r(qmc_result)));
  //   engines(ENGINE_MAX , -ENGINE_MAX);
  //   while (qmc_straight_1r(qmc_result) != MOVEMENT_OK)  qmc_result = qmc_straight1();;
  //   engines_stop();
  // }

  //if (qmc_result == MOVEMENT_OK)  logInfo(String("MTD: MOVEMENT OK"));
  rectangle_path(100, 70);
  //go_forward1(50);
  //turn_left90();
  //logInfo(String("giro finito"));
}