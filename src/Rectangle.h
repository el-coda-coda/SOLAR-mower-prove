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

    //Passate: numero di volte che devo passare per coprire tutto il lato inclinato (direzione Y)
    //a: contatore di passate 
    while (passate >= a)
    {   
        x_array = lato_piano;
        y_array -= ROBOT_LARGE;
        logDebug(String("y_array: ") + String(y_array)); 

        //effettuo una curva solo se ho già fatto un passaggio
        if (a > 0)
        {
            //query: determina se ruotare verso destra o sinistra per "spazzolare" il lato Y
            //sono tutte curve da 180 gradi costituite da turn90 + arretra + turn90 verso la direzione
            //decisa da query
            if (query == 0 )
            {
                logDebug(String("GO Y"));
                turn_left90();
                delay(500);

                //passaggio: booleano che dice se ci sta ancora un passaggio "intero" (true) o se il robot è troppo largo (false)
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


        //Parte dritta del segmento da segare
        logDebug(String("GO X"));
        movement_result = go_forward1(lato_piano);
        engines_stop();
        delay(500);


        //Utile nel caso di ultrasuoni
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

        //Verifico se il robot "si può permettere" ancora un passaggio intero
        if (y_array < ROBOT_LARGE)
        {
            passaggio = false;
        }
        else
        {
            passaggio = true;
        }    

        a++;
    }
}