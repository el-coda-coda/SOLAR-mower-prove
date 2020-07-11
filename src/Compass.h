long qmc ()
{
    long millOffset = millis();
    long time;
    int degrees = sensorReading(COMPASS_READ);
    int degrees_diff = degrees - compassOffSet;
    if (degrees_diff < 0)   bool turn_left = true;
    if (degrees_diff > 0)   bool turn_right = true;
    while (turn_right)
    {
        turn_rightxx((unsigned) degrees_diff);
        time = millis() - millOffset;
        if (degrees_diff !< 0)   bool turn_left = false;
    }
    while (turn_left)
    {
        turn_leftxx((unsigned) degrees_diff);
        time = millis() - millOffset;
        if (degrees_diff !> 0)   bool turn_right = false;
    }
    return time;
}