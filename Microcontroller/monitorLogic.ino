#ifdef __DEMO__
#define MON_CONF_OVERVOLTAGE    4000    /* DEMO mV */
#define MON_CONF_UNDERVOLTAGE   3650    /* DEMO mV */
#endif
#ifndef __DEMO__
#define MON_CONF_OVERVOLTAGE    4200    /* mV */
#define MON_CONF_UNDERVOLTAGE   3700    /* mV */
#endif


#define MON_CONF_START_BALANCING_THRESH    30  /* mV */
#define MON_CONF_STOP_BALANCING_THRESH     60  /* mV */


char voltIndicator[ 12 ];




/****************************/
/* MODIFY MONITOR BEHAVIOUR */
/****************************/

/* Toggle GPIO Led 1 in monitor configuration register */
void MON_toggleGPIOLed1(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] & 0xBF);
  }
  else {
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] | 0x40);
  }
}

/* Toggle GPIO Led 2 in monitor configuration register */
void MON_toggleGPIOLed2(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] & 0xDF);
  }
  else {
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] | 0x20);
  }
}

void MON_dischargeCell0(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x01);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xFE);
  }
}
void MON_dischargeCell1(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x02);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xFC);
  }
}
void MON_dischargeCell2(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x04);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xFB);
  }
}
void MON_dischargeCell3(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x08);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xF7);
  }
}
void MON_dischargeCell4(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x10);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xEF);
  }
}
void MON_dischargeCell5(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x20);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xDF);
  }
}
void MON_dischargeCell6(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x40);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0xBF);
  }
}
void MON_dischargeCell7(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] | 0x80);
  }
  else {
    MON_configuration_register_local[1] = (MON_configuration_register_local[1] & 0x7F);
  }
}
void MON_dischargeCell8(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] | 0x01);
  }
  else {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] & 0xFE);
  }
}
void MON_dischargeCell9(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] | 0x02);
  }
  else {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] & 0xFD);
  }
}
void MON_dischargeCell10(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] | 0x04);
  }
  else {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] & 0xFB);
  }
}
void MON_dischargeCell11(boolean toggle)
{
  if(toggle) {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] | 0x08);
  }
  else {
    MON_configuration_register_local[2] = (MON_configuration_register_local[2] & 0xF7);
  }
}





/* Set comparator duty cycle. Value is a number between 0-7. See LTC6803 datasheet. */
void MON_setComparatorDutyCycle(unsigned char level)
{
  if( 8 > level ) {
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] & 0xF8);
    MON_configuration_register_local[0] = (MON_configuration_register_local[0] | level);
  }
  else if(__DEBUG__) {
    Serial.println("ERR: Trying to set invalid ADC conversion level!");
  }
}







void checkVoltages()
{
  int i = 0;
  while( i < 12 ) {
    if( MON_voltages[i] > ((MON_CONF_OVERVOLTAGE - MON_CONF_START_BALANCING_THRESH) / 1.5) + 512 ) {
      voltIndicator[i] = 1;
    }
    else if( MON_voltages[i] < ((MON_CONF_UNDERVOLTAGE + MON_CONF_START_BALANCING_THRESH)/ 1.5) + 512 ) {
      voltIndicator[i] = -1;
    }
    else {
      voltIndicator[i] = 0;
    }
    i++;
  }
}

