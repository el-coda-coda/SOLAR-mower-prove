long bussola ()
{
    int degrees = sensorReading(COMPASS_READ);
    logInfo(String("DEGREES: ") + String(degrees));
    return degrees;
}
long qmc()
{
    int movement_to_do;
    bool turn_left;
    bool turn_right;
    if (bussola() < (compassOffSet - 3))   turn_left = true;
    else turn_left = false;
    if (bussola() > (compassOffSet + 3))   turn_right = true;
    else turn_right = false;
    if (turn_right == false && turn_left == false)  movement_to_do = MOVEMENT_OK;
    if (turn_right) movement_to_do = CURVE_RIGHT;
    if (turn_left) movement_to_do = CURVE_LEFT;
    logVerbose(String ("Movement compass: ") + String(movement_to_do));
    return movement_to_do;
}


void qmc_prova ()
{
    int cose = (int) (qmc());
    logInfo(String("RISULTATO: ") + String(cose));
}