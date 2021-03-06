

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


int engines_movement(double duration, int power_left, int power_right) 
{
  if (MOVEMENT_ENABLED)
  {
    if (power_right < 0 && power_left < 0)  engines(power_left+ENIGNE_LEFT_OFFSET, power_right+ENGINE_RIGHT_OFFSET);
    else engines(power_left-ENIGNE_LEFT_OFFSET, power_right-ENGINE_RIGHT_OFFSET);
    
    long duration_millseconds = (float)(duration * 1000);
    long curr_time = 0;
    long time_offset = millis();
    int movement_result = 0;

    while ((curr_time < duration_millseconds) && movement_result == 0)
    {
        delay(ENGINE_STEP_DELAY);
        curr_time = millis() - time_offset;
        
    }
    
    return movement_result;
  }
}




//Moves left at max power for <duration> seconds
int engines_left(int degrees) {
  engines(0, ENGINE_MAX);
  qmc_prova_curva1(degrees, CURVE_LEFT);
  engines_stop();
}

//Moves right at max power
int engines_right(int degrees) {
  engines(ENGINE_MAX, 0);
  qmc_prova_curva1(degrees, CURVE_RIGHT);
  engines_stop();
}


//Moves back at max power
int engines_back(double duration) {
  return engines_movement(duration,-ENGINE_MAX, -ENGINE_MAX);
}

// //Moves left at max power for <duration> seconds
int engines_movement_controlled(double duration, int power_left, int power_right) 
{
  
  if (MOVEMENT_ENABLED)
  {
    logDebug(String("engines_movement_controlled: ENGINES GO"));
    
    
    long duration_millseconds = (float)(duration * 1000);
    logVerbose(String("DURATION: ") + String(duration_millseconds));
    long curr_time = 0;
    long time_offset = millis();
    int movement_result = 0;
    long time_qmc = 0;
    long timeOffset_qmc = 0;
    int qmc_result = 0;
    while ((curr_time < duration_millseconds) && movement_result == MOVEMENT_OK)
    {
        
        time_qmc = 0;
        if (us_query == 2) 
        {
          movement_result = sensorReading(US_READ);
          if (movement_result != MOVEMENT_OK) movement_result = MOVEMENT_OBSTACLE_FOUND;
          us_query = 0;
          
          timeOffset_qmc = millis();
          qmc_result = qmc_straight1();
          if (qmc_result <= CURVE_LEFT) 
          {
            logInfo(String("MTD: curve left: ") + String(qmc_straight_1r(qmc_result)));
            engines(-ENGINE_MAX, ENGINE_MAX);
            while (qmc_straight_1r(qmc_result) != MOVEMENT_OK)  qmc_result = qmc_straight1();
            engines_stop();
          }
          if (qmc_result >= CURVE_RIGHT)  
          {
            logInfo(String("MTD: curve right: ") + String(qmc_straight_1r(qmc_result)));
            engines(ENGINE_MAX , -ENGINE_MAX);
            while (qmc_straight_1r(qmc_result) != MOVEMENT_OK)  qmc_result = qmc_straight1();;
            engines_stop();
          }
          time_qmc = millis() - timeOffset_qmc;
        }
        if (qmc_result == MOVEMENT_OK)  
        {
          if (power_right < 0 && power_left < 0)  engines(power_left+ENIGNE_LEFT_OFFSET, power_right+ENGINE_RIGHT_OFFSET);
          else engines(power_left-ENIGNE_LEFT_OFFSET, power_right-ENGINE_RIGHT_OFFSET);
        }
        curr_time = millis() - time_offset;
        curr_time -= time_qmc; 
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

//Moves forward at max power
int engines_forward(double duration) {
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