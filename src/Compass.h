void setCompassOffset()
{
    compassOffSet = 0;
    compassOffSet += sensorReading(COMPASS_READ);
    delay(2000);
    compassOffSet += sensorReading(COMPASS_READ);
    compassOffSet /= 2;
}

/*

long qmc_straight()
{
    int tolleranza = 4;
    int movement_to_do;
    bool turn_left;
    bool turn_right;
    //grado attuale
    int deg = sensorReading(COMPASS_READ);
    
    if (deg < (compassOffSet - tolleranza))   
        turn_right = true;
    else 
        turn_right = false;

    if (deg > (compassOffSet + tolleranza))   
        turn_left = true;
    else 
        turn_left = false;

    if (turn_right == false && turn_left == false)  movement_to_do = MOVEMENT_OK;

    if (turn_right) movement_to_do = CURVE_RIGHT;

    if (turn_left) movement_to_do = CURVE_LEFT;

    logVerbose(String ("Movement compass: ") + String(movement_to_do));

    return movement_to_do;
}
*/

//Utilizzata quando va dritto, determina la "costanza" della direzione con una tolleranza di +/- 3 (TOLLERANZA) gradi
//la direzione nominale viene indicata da "compassOffset" (quest'ultimo calcolato in setCompassOffset)
//Il 200 e 360 servono a gestire i casi limite di sterzate che superano i 360 gradi e si azzerano (o riducono il numero di gradi)
//Restituisce una combinazione della direzione (left, right) che deve fare e dei gradi deve fare in quella direzione
//questo viene fatto sommando i gradi alla direzione da seguire.
int qmc_straight1()
{
    int TOLLERANZA = 3;
    int  movement_to_do = MOVEMENT_OK;
    int deg = sensorReading(COMPASS_READ);
    int diff_deg;

    if (deg > compassOffSet)    
    {
        diff_deg = deg - compassOffSet;
        movement_to_do = CURVE_LEFT;
    }

    if (deg < compassOffSet)    
    {
        diff_deg = compassOffSet - deg;
        movement_to_do = CURVE_RIGHT;
    }

    if (deg > compassOffSet + 200)  
    {
        diff_deg = compassOffSet + 360 - deg;
        movement_to_do = CURVE_LEFT;
    }
    
    if (deg < compassOffSet - 200)  
    {
        diff_deg = compassOffSet - 360 + deg;
        movement_to_do = CURVE_RIGHT;
    }

    if (diff_deg >= TOLLERANZA)
    {
        if (movement_to_do == CURVE_RIGHT)   movement_to_do += diff_deg;
        if (movement_to_do == CURVE_LEFT)    movement_to_do -= diff_deg;
    }  
    else   
        movement_to_do = MOVEMENT_OK;

    return movement_to_do;
}



//Mi restituice i gradi di cui deve girare per darlo in pasto all'engine
//Se dovessi girare di 94 verso destra questo passa a engine di turnare a destra di 4 gradi
int qmc_straight_1r(int qmc_straight)
{
    int TOLLERANZA = 2;
    int movement_to_do;
    if (qmc_straight <= CURVE_LEFT) movement_to_do = ((qmc_straight + 90) * -1) - TOLLERANZA;
    if (qmc_straight >= CURVE_RIGHT)   movement_to_do = qmc_straight - 90 - TOLLERANZA;
    if (qmc_straight == MOVEMENT_OK)    movement_to_do = MOVEMENT_OK;     
    return movement_to_do;
}

/*
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

int qmc_curva_test (int direction, int deg)
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
*/
void qmc_prova()
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


//Riceve in input i gradi che devo fare e la direzione (left right) che deve fare
//in questo modo legge la bussola ed aggiunge o toglie in base alla direzione i gradi passati in input
//In questo modo calcola lo stop_deg ovvero il grado al quale si deve fermare

//Viene utilizzata nella gestione dei motori destra/sinistra come delay intelligente che smette di creare ritardo
//quando la busola segnala di aver raggiunto la direzione/grado finale
int qmc_prova_curva1(int deg, int dir)
{
    int compass1 = 0;
    int TOLLERANZA = 1;

    if (COMPASS_MEDIA)  
        compass1 = sensorReading(COMPASS_READ);
    else 
        compass1 = compassOffSet;

    logInfo(String("compass 1: ") + String(compass1));
    int stop_deg = 0;
    int diff_deg = 100;

    if (dir == CURVE_LEFT)    stop_deg = compass1 - deg;
    if (dir == CURVE_RIGHT)   stop_deg = compass1 + deg;

    //stop_deg modulo 360 : todo
    while (stop_deg > 360) stop_deg -= 360;
    while (stop_deg < 0) stop_deg += 360;
    
    logInfo(String("STOP_DEG: ") + String(stop_deg));

    while (diff_deg > TOLLERANZA)
    {
        if (dir == CURVE_RIGHT)
        {
            //logInfo(String("STOP_DEG: ") + String(stop_deg));
            //logInfo(String("COMPASS2: ") + String(compass2));
            diff_deg = stop_deg - sensorReading(COMPASS_READ);
            if (diff_deg < -5) diff_deg = 10;        
            //logInfo(String("DIFF_DEG: ") + String(diff_deg));
            //logInfo(String("ehi"));
        }
        if (dir == CURVE_LEFT)
        {
            //logInfo(String("STOP_DEG: ") + String(stop_deg));
            //logInfo(String("COMPASS2: ") + String(compass2));
            diff_deg = sensorReading(COMPASS_READ) - stop_deg;
            if (diff_deg < -5)  diff_deg = 10;
            //logInfo(String("DIFF_DEG: ") + String(diff_deg));
            //logInfo(String("ehi"));
        }
        delay(50);
    }   
}