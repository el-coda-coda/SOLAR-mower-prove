//Solo questa classe lo può utilizzare
float segment_time(int wheel_diamater,float segment_length)
{
  float rps = ((float) RPM) / 60;
  
  float circumference = wheel_diamater * 3.14;
  logDebug("Circumference: ",circumference);

  float rotation_number = segment_length / circumference;
  logDebug("rotation number: ",rotation_number);
  
  float segment_time_result = rotation_number / rps;
  logDebug("segment time result: ",segment_time_result);
  return segment_time_result;

}

int turn_right_xx (int grade)
{
  int movement_result=0;

  int lenght_curve = (grade*(ROBOT_LARGE*6.28))/360; //grade / 360° = lenght_curve / (ROBOT_LARGE*6.28)
  float seg_time = segment_time((int)WHEEL_DIAMETER, lenght_curve * CURVE_PROBLEM);
  
  movement_result=engines_right(seg_time);
  return movement_result;
}

int turn_left_xx (int grade)
{
  int movement_result=0;

  int lenght_curve = (grade*(ROBOT_LARGE*6.28))/360; //grade / 360° = lenght_curve / (ROBOT_LARGE*6.28)
  float seg_time = segment_time((int)WHEEL_DIAMETER, lenght_curve * CURVE_PROBLEM);
  
  movement_result=engines_left(seg_time);
  return movement_result;
}

int turn_right180() {
  int movement_result=0;

  movement_result=turn_right_xx(180);
  return movement_result;
}


int turn_left180() {
  int movement_result=0;
  
  movement_result=turn_left_xx(180);
  return movement_result;
}
int turn_right90() {
  int movement_result=0;

  movement_result=turn_right_xx(90);
  return movement_result;
}


int turn_left90() {
  int movement_result=0;
  
  movement_result=turn_left_xx(90);
  return movement_result;
}

int go_back(float segment_length) {
  int movement_result=0;

  float seg_time = segment_time(WHEEL_DIAMETER, segment_length);
  movement_result = engines_back(seg_time);
  return movement_result;
}

 
int go_forward1(float segment_length) 
{
    int movement_result=0;
    int count = 0;
    float seg_time = segment_time(WHEEL_DIAMETER, segment_length);
    //logDebug(String("Go forwardo for time (sec) ") + String(seg_time));
    //logDebug(String("Segment length (cm): ") + String(segment_length));
    movement_result = engines_forward(seg_time);
    if (movement_result != MOVEMENT_OK) 
    {
        if (movement_result == MOVEMENT_GENERIC_ERROR) 
        {
          //logDebug(String("generic movement error"));
          movement_result = MOVEMENT_GENERIC_ERROR;
          engines_stop();        
        }
        if (movement_result == MOVEMENT_OBSTACLE_FOUND)
        {
          //logDebug(String("Obstacle found"));
          engines_stop();
          movement_result = sensorReading(US_READ);   
        }
    }
  return movement_result;
}

int go_forward(float segment_length, int &x_array) 
{
    int movement_result=0;
    float seg_time = 0.0;
    seg_time = segment_time(WHEEL_DIAMETER, 5);
    logDebug(String("Segment length (cm): ") + String(segment_length));
    long start_time = millis();

    while (x_array > 0 && movement_result == MOVEMENT_OK)
    {
      movement_result = engines_forward(seg_time);
      x_array -= 5;
      logDebug(String("x_array: ") + String(x_array));
    }
    
    if (movement_result != MOVEMENT_OK) 
    {
        if (movement_result == MOVEMENT_GENERIC_ERROR) 
        {
          logDebug(String("generic movement error"));
          movement_result = MOVEMENT_GENERIC_ERROR;
          engines_stop();        
        }
        if (movement_result == MOVEMENT_OBSTACLE_FOUND)
        {
          logDebug(String("Obstacle found"));
          engines_stop();
          movement_result = sensorReading(US_READ);   
        }
    }
  logInfo(String("GO FORWARD END: DURATION: ") + String(millis()-start_time));
  return movement_result;
}

// Prove per vedere come aggirare un ostacolo
int aggira (int movement_result, int &x_array, int &y_array)
{
  int curve_result = MOVEMENT_OBSTACLE_FOUND;
  int come_back = 0;
  if (movement_result == CURVE_RIGHT)
  {
    turn_right90();
    while (curve_result == MOVEMENT_OBSTACLE_FOUND)
    {
      if (go_forward1(5) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
      turn_left90();
      curve_result = sensorReading(US_READ);
      turn_right90();
      y_array += 5;
      come_back += 5;
      logDebug(String("y_array: ") + String(y_array));
    }
    curve_result = MOVEMENT_OBSTACLE_FOUND;
    turn_left90();
    while (curve_result == MOVEMENT_OBSTACLE_FOUND)
    {
      if (go_forward1(5) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
      turn_left90();
      curve_result = sensorReading(US_READ);
      turn_right90();
      x_array -= 5;
      logDebug(String("x_array: ") + String(x_array));
    }
    turn_left90();
    if (go_forward1(come_back) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
    y_array -= come_back;
    logDebug(String("y_array: ") + String(y_array));
    turn_right90();
  }
  if (movement_result == CURVE_LEFT)
  {
    turn_left90();
    while (curve_result == MOVEMENT_OBSTACLE_FOUND)
    {
      if (go_forward1(5) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
      turn_right90();
      curve_result = sensorReading(US_READ);
      turn_left90();
      y_array += 5;
      come_back += 5;
      logDebug(String("y_array: ") + String(y_array));
    }
    curve_result = MOVEMENT_OBSTACLE_FOUND;
    turn_right90();
    while (curve_result == MOVEMENT_OBSTACLE_FOUND)
    {
      if (go_forward1(5) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
      turn_right90();
      curve_result = sensorReading(US_READ);
      turn_left90();
      x_array -= 5;
      logDebug(String("x_array: ") + String(x_array));
    }
    turn_right90();
    if (go_forward1(come_back) != MOVEMENT_OK) return MOVEMENT_OBSTACLE_FOUND;
    y_array -= come_back;
    logDebug(String("y_array: ") + String(y_array));
    turn_left90();
  }
}

