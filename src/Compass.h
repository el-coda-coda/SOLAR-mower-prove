long bussola ()
{
    int degrees = sensorReading(COMPASS_READ);
    logVerbose(String("DEGREES: ") + String(degrees));
    return degrees;
}
long qmc_straight()
{
    int movement_to_do;
    bool turn_left;
    bool turn_right;
    if (bussola() < (compassOffSet - 2))   turn_left = true;
    else turn_left = false;
    if (bussola() > (compassOffSet + 2))   turn_right = true;
    else turn_right = false;
    if (turn_right == false && turn_left == false)  movement_to_do = MOVEMENT_OK;
    if (turn_right) movement_to_do = CURVE_RIGHT;
    if (turn_left) movement_to_do = CURVE_LEFT;
    logVerbose(String ("Movement compass: ") + String(movement_to_do));
    return movement_to_do;
}

long qmc_curva (int curve, int xx)
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
int qmc_curva_test (int zz)
{
    int compass1 = sensorReading(COMPASS_READ);
    int degrees = zz;
    while (sensorReading(COMPASS_READ) == compass1) delay(10);
    degrees --;
    return zz;
}

void qmc_prova ()
{
    int cose = (int) (qmc_straight());
    logInfo(String("RISULTATO: ") + String(cose));
}