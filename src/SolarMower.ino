#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Configuration.h"
#include "Display.h"
#include "Logging.h"
#include "Ultrasuoni_SRF04.h"
#include "Sensors.h"
#include "Esc_control.h"
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
void loop() 
{
  rectangle_path(300, 100);
  logDebug(String("RETTANGOLO FINITO"));
  delay(10000);
  go_back(310);
  turn_right90();
  go_forward1(100);
  turn_left90;
  delay(5000);
}