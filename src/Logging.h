int riga = 0;

void logDebug(String message, float value) {
   
    if (LOG_LEVEL >= DEBUG_LEVEL) {
        if(LOG_TO_SERIAL == true){
            Serial.print(message);
            Serial.println(value);
        }
        if(LOG_TO_LCD == true){
            display_print(0,message);
            display_print(1,String(value));
        }
    }
}

void logDebug(String message) {
    
    if (LOG_LEVEL >= DEBUG_LEVEL) {
        if(LOG_TO_SERIAL == true){
            Serial.println(message);
        }
        if(LOG_TO_LCD == true)
        {
            if(riga == 5)  riga = 0;
            display_print(riga, message);
            riga++;
        }
    }
}

void logVerbose(String message) {
    
    if (LOG_LEVEL >= VERBOSE_LEVEL) {
        if(LOG_TO_SERIAL == true){
            Serial.println(message);
        }
        if(LOG_TO_LCD == true)
        {
            if(riga == 5)  riga = 0;
            display_print(riga, message);
            riga++;
        }
    }
}


void logInfo(String message) {
    if (LOG_LEVEL >= INFO_LEVEL) {
        if(LOG_TO_SERIAL == true){
            Serial.println(message);
        }
        if(LOG_TO_LCD == true)
        {
            if(riga == 5)  riga = 0;
            display_print(riga, message);
            riga++;
        }
    }
}
void logInfo(String message, float value){
    if (LOG_LEVEL >= INFO_LEVEL) {
        if(LOG_TO_SERIAL == true){
            Serial.print(message);
            Serial.println(value);
        }
        if(LOG_TO_LCD == true){
            display_print(0,message);
            display_print(1,String(value));
        }
    }
}
