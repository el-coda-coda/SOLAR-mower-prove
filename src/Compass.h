long qmc_straight()
{
    int movement_to_do;
    bool turn_left;
    bool turn_right;
    int deg = sensorReading(COMPASS_READ);
    if (deg < (compassOffSet - 2))   turn_right = true;
    else turn_right = false;
    if (deg > (compassOffSet + 2))   turn_left = true;
    else turn_left = false;
    if (turn_right == false && turn_left == false)  movement_to_do = MOVEMENT_OK;
    if (turn_right) movement_to_do = CURVE_RIGHT;
    if (turn_left) movement_to_do = CURVE_LEFT;
    logVerbose(String ("Movement compass: ") + String(movement_to_do));
    return movement_to_do;
}

long qmc_curva_testW (int curve, int xx)
{
    int deg = sensorReading(COMPASS_READ);
    if (curve == CURVE_RIGHT)   
    {
        variabile = compassOffSet + xx;
        if (variabile > 360)    variabile -= 360;
    }
    if (curve == CURVE_LEFT)
    {
        variabile = compassOffSet - xx;
        if (variabile < 0)    variabile += 360;
    }
    logVerbose(String("Var: ") + String(variabile));
   
    long diff = variabile - deg;
    if (diff < 0)  diff *= -1;
    logInfo(String("DIFF: ") + String(diff));
    return diff;
}
int qmc_curva (int degrees)
{
    int compass1 = sensorReading(COMPASS_READ);
    int compass2;
    int xx = degrees;

    while (xx >= 0)
    {
        compass2 = sensorReading(COMPASS_READ);
        logInfo(String("CURVE CD: ") + String(xx));
        if (compass1 != compass2)
        {
            xx --;
            compass1 = compass2;
        }
        delay(10);

    }
}

qmc_curva_test (int direction, int deg)
{
    int compass1 = sensorReading(COMPASS_READ);
    int compass2;
    int xx = deg;
    if (direction == CURVE_RIGHT)
    {
        while (xx >= 0)
        {
            compass2 = sensorReading(COMPASS_READ);
            logInfo(String("CURVE CD: ") + String(xx));
            if ((compass1 + 1 < compass2) || (compass1 > compass2 + 50))
            {
                xx -= 2;
                compass1 = compass2;
            }
            delay(10);
            
        }
    }
    if (direction == CURVE_LEFT)
    {
            while (xx >= 0)
        {
            compass2 = 0; //sensorReading(COMPASS_READ);
            logInfo(String("CURVE CD: ") + String(xx));
            for (int i = 0; i <= 10; i++)   compass2 += sensorReading(COMPASS_READ);
            compass2 /= 10;
            if ((compass1 + 1 > compass2) || (compass1 < compass2 + 50))
            {
                xx -= 2;
                compass1 = compass2;
            }
            delay(10);
            
        }
    }
}
void qmc_prova ()
{
    int deg = sensorReading(COMPASS_READ); 
    int compass1 = compassOffSet + 90;
    int diff = 0;
    while ((diff < compass1 -1) || (diff < compass1 -1))
    {
        diff = compass1 - sensorReading(COMPASS_READ);
        logInfo(String("diff") + String(diff));
    }
    
}

qmc_prova_curva1 (int deg, int direction)
{
    int compass1 = sensorReading(COMPASS_READ);
    int compass2 = 0;
    int stop_deg = 0;
    int diff_deg = 0;
    if (direction == CURVE_LEFT)    stop_deg = compass1 - deg;
    if (direction == CURVE_RIGHT)   stop_deg = compass1 + deg;
    logInfo(String("offset_qmc ") + String(stop_deg));
    if (stop_deg > 360) stop_deg -= 360;
    if (stop_deg < 360) stop_deg += 360;
    while (true)
    {
        if (direction == CURVE_RIGHT)
        {
            logInfo(String("offset_qmc ") + String(stop_deg));
            compass2 = sensorReading(COMPASS_READ);
            logInfo(String("compass 2 ") + String(compass2));
            logInfo(String("diff m ") + String(stop_deg - compass2));
            diff_deg = stop_deg - compass2;
            //if (diff_deg <= (stop_deg - 360))   diff_deg = stop_deg * 2;
            logInfo(String("DIFF DEG: ") + String(diff_deg)); 
            delay(100);
        }
    }   
}