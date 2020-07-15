#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <QMC5883L.h>
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
  for(int vc=0; vc <100; vc ++)
  {
    sensorReading(COMPASS_READ);
    turn_left_xx(3.6);
  }
}
void loop() 
{
  //compassOffSet = sensorReading(COMPASS_READ);
  
  //engines_forward(5);
  compassOffSet = sensorReading(COMPASS_READ);
  logInfo(String("Inizio a girare"));
  turn_right90();
  //qmc_prova();
  // logInfo(String("BUSSOLA: ") + String(sensorReading(COMPASS_READ)));
  delay(1000);
}