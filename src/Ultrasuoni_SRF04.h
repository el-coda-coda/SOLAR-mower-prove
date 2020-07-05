//Computes distance from obstacle in centimeters
//Argumnents trigger_pin and echo_pin on arduino for ultrasonic sensor



long get_obstacle_distance(int trigger_pin, int echo_pin)
{   
    long curr_time_start = millis();
    long curr_time_end=0;
    logVerbose(String("Ultrasonic: get_obstacle_distance: START"));
    digitalWrite(trigger_pin, LOW);
    digitalWrite(trigger_pin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    
    

    long duration = pulseIn(echo_pin, HIGH, ULTRASONIC_OUTOFRANGE);  
    long distance = ULTRASONIC_PARAMETER * duration / 2;  
    curr_time_end = millis();
    logVerbose(String("Ultrasonic: get_obstacle_distance: DURATION: ") +  String(curr_time_end-curr_time_start));
   
    if ((duration > ULTRASONIC_OUTOFRANGE) || !ULTRASONIC_ENABLED)
    {
        return VERY_LONG_DINSTANCE;
    }
    else
    {
        return distance; 
    }
}
