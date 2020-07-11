

//Delay on engine movement
void engines_delay() {
  delay(ENGINE_DELAY);
}


//Set the engines power, integer value from 0 to 255
void engines(int left_power, int right_power)
{

  if(right_power >= 0)
  {

    analogWrite(PWMA_PIN, right_power);
    digitalWrite(DIRA_PIN, LOW);

  }
  if(right_power < 0)
  {

    analogWrite(PWMA_PIN, (-right_power));
    digitalWrite(DIRA_PIN, HIGH);

  }
  if(left_power >= 0)
  {

    analogWrite(PWMB_PIN, left_power);
    digitalWrite(DIRB_PIN, LOW);

  }
  if(left_power < 0)
  {

    analogWrite(PWMB_PIN, (-left_power));
    digitalWrite(DIRB_PIN, HIGH);


  }
  
}

//Stop each engine
int engines_stop() 
{
  engines(0,0);
  return 0;
}


// //Moves left at max power for <duration> seconds
int engines_movement_controlled(float duration, int power_left, int power_right) 
{
  compassOffSet = sensorReading(COMPASS_READ);
  if (MOVEMENT_ENABLED)
  {
    logDebug(String("engines_movement_controlled: ENGINES GO"));
    if (power_right < 0 && power_left < 0)  engines(power_left+ENIGNE_LEFT_OFFSET, power_right+ENGINE_RIGHT_OFFSET);
    else engines(power_left-ENIGNE_LEFT_OFFSET, power_right-ENGINE_RIGHT_OFFSET);
    
    int duration_millseconds = (int)(duration * 1000);
    long curr_time = 0;
    long time_offset = millis();
    int movement_result = 0;
    while ((curr_time < duration_millseconds) && movement_result == MOVEMENT_OK)
    {
        if (us_query == 2) 
        {
          movement_result = sensorReading(US_READ);
          if (movement_result != MOVEMENT_OK) movement_result = MOVEMENT_OBSTACLE_FOUND;
          us_query = 0;
        }
        curr_time = millis() - time_offset; 
        us_query ++;
        logVerbose(String("CURR TIME: ") + String(curr_time));
    }
    engines_stop();
    if (!RECTANGLE_ENABLED && movement_result == MOVEMENT_OK)
    {
      movement_result = CURVE_LEFT;
    }
    return movement_result;
  }
}

int engines_movement(float duration, int power_left, int power_right) 
{
  if (MOVEMENT_ENABLED)
  {
    if (power_right < 0 && power_left < 0)  engines(power_left+ENIGNE_LEFT_OFFSET, power_right+ENGINE_RIGHT_OFFSET);
    else engines(power_left-ENIGNE_LEFT_OFFSET, power_right-ENGINE_RIGHT_OFFSET);
    
    int duration_millseconds = (int)(duration * 1000);
    long curr_time = 0;
    long time_offset = millis();
    int movement_result = 0;

    while ((curr_time < duration_millseconds) && movement_result == 0)
    {
        delay(ENGINE_STEP_DELAY);
        curr_time = millis() - time_offset;
        
    }
    engines(0,0);
    
    return movement_result;
  }
}




//Moves left at max power for <duration> seconds
int engines_left(float duration) {
   return engines_movement(duration, 0, ENGINE_MAX); 
}

//Moves right at max power
int engines_right(float duration) {
   return engines_movement(duration, ENGINE_MAX, 0);
}


//Moves back at max power
int engines_back(float duration) {
  return engines_movement(duration,-ENGINE_MAX, -ENGINE_MAX);
}

//Moves forward at max power
int engines_forward(float duration) {
  return engines_movement_controlled(duration,ENGINE_MAX, ENGINE_MAX);
}

long curve_back ()
{    
    delay(50);
    int right_US = get_obstacle_distance(US1_TRIG_PIN, US1_ECHO_PIN);
    delay(50);
    int left_US = get_obstacle_distance(US2_TRIG_PIN, US2_ECHO_PIN);
    if (right_US <= (MOVEMENT_OBSTACLE_DISTANCE - 3) || left_US <= (MOVEMENT_OBSTACLE_DISTANCE - 3))
    {
        if (right_US < left_US)
        {
            logDebug(String("bebug curve back ") + String(right_US));
            logDebug(String("go back of: ") + String(MOVEMENT_OBSTACLE_DISTANCE - right_US));
            return (MOVEMENT_OBSTACLE_DISTANCE - right_US);
        }
        if (right_US > left_US)
        {
            logDebug(String("bebug curve back ") + String(right_US));
            logDebug(String("go back of: ") + String(MOVEMENT_OBSTACLE_DISTANCE - left_US));            
            return (MOVEMENT_OBSTACLE_DISTANCE - left_US);
        }
    }
}