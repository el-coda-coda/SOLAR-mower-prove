QMC5883L compass;

void sensorInit()
{
  IPanelOffset=0;
  ICutOffset=0;
  for (i=0; i<50; i++)
  {                                    
    IPanelOffset += analogRead(IPANEL_PIN);
    delay(20);
    ICutOffset += analogRead(ICUT_PIN);      
    delay(20);
  }
  IPanelOffset /= i; 
  ICutOffset /= i;
  logDebug(String("PANEL SETUP: ") + String(IPanelOffset));
  compass.init();
	compass.setSamplingRate(50);
  compass.resetCalibration();
  logDebug(String("COMPASS SETUP: RUOTA IL ROBOT"));
}

float sensorReading(int type)
{
  long curr_time_start = millis();
  long curr_time_end=0;
  logVerbose(String("Sensor reading start-time: ") + String(curr_time_start));
  if (type == BATTERY_READ)
  {
    digitalWrite(Panel_PIN, LOW);
    delay(20);
    VBat=VBatScale*float(analogRead(IBAT_PIN));
    VBatPC = 100.0*(VBat-VBat_Level_Min)/(VBat_Level_Max-VBat_Level_Min);
    VBatPC = constrain(VBatPC, 0, 100);
    logInfo(String("Battery charge: ") + String(VBatPC) + String(" %"));
    digitalWrite(Panel_PIN, HIGH);

    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::BATTERY_READ: ") + String(curr_time_end-curr_time_start));
    return VBatPC;
  }
  
  
  if (type == PANEL_READ_VOLTS)
  { 
    value = analogRead(IPANEL_PIN);
    vin = map(value, 0, 1023, 0, 18000);
    if (vin <400) vin = 0;
    IPanel = vin;
    logDebug(String("PAN curr: ") + String(IPanel) + String(" mV"));

    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::PANEL_READ_VOLTS: ") + String(curr_time_end-curr_time_start));
    return IPanel;
  }
  
  if (type == PANEL_READ_AMP)
  { 
    digitalWrite(Panel_PIN, HIGH);
    delay(20);
    IPanel=IPanelOffset-float(analogRead(IPANEL_PIN));
    IPanel=(IPanel*5.0/1024.0)/IPanelScale;
    IPanel=constrain(IPanel, 0, 1.8);
    logInfo(String("IPANEL: ") + String(IPanel));

    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::PANEL_READ_AMP: ") + String(curr_time_end-curr_time_start));
    return IPanel;
  }
  if (type == ESC_READ)
  {
    ICut=float(analogRead(ICUT_PIN))-ICutOffset;
    ICut=(ICut*5.0/1023.0)/ICutScale;   
    ICut=constrain(ICut, 0, 5.0);
    logInfo(String("ESC current (A): ") + String(ICut));

    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::ESC_READ: ") + String(curr_time_end-curr_time_start));
    return ICut;
  }
  if (type == US_READ)
  { 
    delay(50);
    int distance_R = get_obstacle_distance(US1_TRIG_PIN, US1_ECHO_PIN);
    delay(50);
    int distance_L = get_obstacle_distance(US2_TRIG_PIN, US2_ECHO_PIN);
    
    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::US_READ: ") + String(curr_time_end-curr_time_start));
    if (distance_R < MOVEMENT_OBSTACLE_DISTANCE || distance_L < MOVEMENT_OBSTACLE_DISTANCE)
    {
        if (distance_R < (MOVEMENT_OBSTACLE_DISTANCE - 3) || distance_L < (MOVEMENT_OBSTACLE_DISTANCE - 3))
        {
            logDebug(String("GO BACK, distance right: ") + String(distance_R) + String(" cm, distance left: ") + String(distance_L) + String(" cm"));

            return GO_BACK;
        }
        if ((distance_L - RANGE_US_ERROR) < distance_R  && distance_R < (distance_L + RANGE_US_ERROR))
        {
            logDebug(String("TURN 180°, distance right: ") + String(distance_R) + String(" cm, distance left: ") + String(distance_L) + String(" cm"));
            return(TURN_180);
        }
        else
        {
            if(distance_R > distance_L)
            {
                logDebug(String("TURN RIGHT 90°, distance right: ") + String(distance_R) + String(" cm, distance left: ") + String(distance_L) + String(" cm"));
                return (CURVE_RIGHT);
            }
            if (distance_R < distance_L)
            {
                logDebug(String("TURN LEFT 90°, distance right: ") + String(distance_R) + String(" cm, distance left: ") + String(distance_L) + String(" cm"));
                return(CURVE_LEFT);
            }
        }
    }
    else
    {
        logDebug(String("No obstacle founds"));
        return MOVEMENT_OK;
    }
  }
  if (type == COMPASS_READ)
  {
    heading = compass.readHeading();
    logInfo(String("Compass: ") + String(heading));
  }
}  
int sensorReading_all ()
{
  sensorReading(BATTERY_READ);
  sensorReading(PANEL_READ_VOLTS);
  sensorReading(PANEL_READ_AMP);
  sensorReading(ESC_READ);
  sensorReading(US_READ);
}

int Button(int buttonPin)
{
  int pushValue = analogRead(buttonPin);
  if ( pushValue < 164 ) 
    return 1;
  else if ( pushValue < 502 )
   return 2;
  else if ( pushValue < 850 )
     return 3;
  else
     return 0;  //nessun pulsante premuto
}

unsigned long FreqCounter(int pin, unsigned long gateTime)
{ 
  unsigned long time, timeInitial;
  unsigned long count=0;
  boolean level, lastLevel;
  
  timeInitial = millis();
  time=timeInitial;
    
  while((time-timeInitial)<gateTime) 
  {    
    level = digitalRead(pin);
    if((level != lastLevel) ) // if transient
    { 
       lastLevel = level;
       if(level == HIGH) count++; //rising front
    }
  time=millis();
  }
  return count;
}
