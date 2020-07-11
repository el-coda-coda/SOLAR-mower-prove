long qmc ()
{
    int movement_to_do;
    int degrees = sensorReading(COMPASS_READ);
    int degrees_diff = degrees - compassOffSet;
    if (degrees_diff < 0)   bool turn_left = true;
    else turn_left = false;
    if (degrees_diff > 0)   bool turn_right = true;
    else turn_right = false;
    if (turn_right) movement_to_do = CURVE_RIGHT;
    if (turn_left) movement_to_do = CURVE_LEFT;
    if (turn_right == false && turn right == false) movement_to_do = MOVEMENT_OK;
    return moevement_to_do;
}