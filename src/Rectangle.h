void rectangle_path (int lato_piano, int lato_inclinato)
{
    // if (lato_piano < lato_inclinato)     rectangle_mode = RECTANGLE_MODE_1;
    // if (lato_piano >= lato_inclinato)    rectangle_mode = RECTANGLE_MODE_0;
    int a = 0;
    int b = 0;
    int query = 0;
    bool passaggio = true;
    int movement_result =0;
    int passate =  (int)(lato_inclinato / BLADE_LARGE);
    int avanzo = lato_inclinato % BLADE_LARGE;
    int ultimo_passaggio = ROBOT_LARGE - avanzo;
    int x_array = lato_piano;
    int y_array = lato_inclinato;
    while (passate >= a)
    {   x_array = lato_piano;
        y_array -= ROBOT_LARGE;
        logDebug(String("y_array: ") + String(y_array)); 
        if (a > 0)
        {
            if (query == 0 )
            {
                logDebug(String("GO Y"));
                turn_left90();
                delay(500);
                if (passaggio)  
                {
                    go_back((ROBOT_LARGE - BLADE_LARGE)/2);
                    logDebug(String("TORNO INDIETRO POCO"));
                    y_array += (ROBOT_LARGE - BLADE_LARGE)/2;
                }
                else    
                {
                    go_back(ultimo_passaggio);
                    logDebug(String("TORNO INDIETRO UN BOTTO"));
                    y_array += ultimo_passaggio;
                }
                turn_left90();
                query = 1;
            }
            else
            {
                logDebug(String("GO Y"));
                turn_right90();
                delay(500);
                if (passaggio)  
                {
                    go_back((ROBOT_LARGE - BLADE_LARGE)/2);
                    logDebug(String("TORNO INDIETRO POCO"));
                    y_array += (ROBOT_LARGE - BLADE_LARGE)/2;
                }
                else    
                {
                    go_back(ultimo_passaggio);
                    logDebug(String("TORNO IN DIETRO UN BOTTO"));
                    y_array += ultimo_passaggio;
                }
                turn_right90();
                query = 0;
            }
        }
        logDebug(String("GO X"));
        movement_result = go_forward1(lato_piano);
        engines_stop();
        delay(500);
        if (movement_result!= MOVEMENT_OK)
        {
            if (movement_result == GO_BACK)
            {
                int lenght_go_back = curve_back();
                x_array += lenght_go_back;
                logDebug(String("GO BACK: ") + String(lenght_go_back) + String("cm"));
                go_back(lenght_go_back);
            }
            else
            {
                aggira(movement_result, x_array, y_array);
            }        
        }
        if (y_array < ROBOT_LARGE)
        {
            passaggio = false;
        }
        else
        {
            passaggio = true;
        }    
        b++;
        a++;
    }
}