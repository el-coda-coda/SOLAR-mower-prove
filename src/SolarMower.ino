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
}
void loop ()
{
  logInfo(String(sensorReading(COMPASS_READ)));
  compassOffSet = sensorReading(COMPASS_READ);
  engines_forward(5);
  delay(2000);
}