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
    int compass1;
    if (direction == CURVE_LEFT)    compass1 = compassOffSet - deg;
    if (direction == CURVE_RIGHT)   compass1 = compassOffSet + deg;
    if (compass1 > 360)  compass1 -= 360;
    if (compass1 < 360) compass1 += 360;
    if (compass1 > compassOffSet)
    while (compass1 < sensorReading(COMPASS_READ))
    {
        delay(50);
    }
    

}
void qmc_prova ()
{
    int cose = (int) (qmc_straight());
    logInfo(String("RISULTATO: ") + String(cose));
}
