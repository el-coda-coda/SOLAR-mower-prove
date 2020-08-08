Servo esc;

void esc_on()
{
  if(ESC_ENABLED)
  {
    esc.writeMicroseconds(ESC_ON);
  }
  else esc.writeMicroseconds(ESC_OFF);
  logDebug(String("ESC ON"));
}

void esc_off()
{
  if(ESC_ENABLED)
  {
    esc.writeMicroseconds(ESC_OFF);
  }
  else esc.writeMicroseconds(ESC_OFF);
  logDebug(String("ESC OFF"));
}

void esc_botton_toggle()
{
    if(digitalRead(ON_OFF_ESC_PIN) == HIGH)
    {
        ON_OFF = ON_OFF * -1;
    }
    if(ON_OFF < 0)
    {
        esc_on();
    }
    else
    {
        esc_off();
    }  
}
void esc_xx ( int value)
{
  value = map(value, 0, 100, 1000, 2000);
  esc.writeMicroseconds(value);
}


void esc_setup ()
{
  logInfo(String("SETUP ESC"));
  esc.attach(ESC_PIN);
  //ESC setup for starting up.
  if (ESC_ENABLED)
  {
    delay(1000);
    esc_off();
    delay(3000);
    esc_on();
    delay(3000);
    esc_off();
  } 
}