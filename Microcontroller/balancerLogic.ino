#ifdef __DEMO__
#define MON_CONF_OVERVOLTAGE    900    /* DEMO mV */
#define MON_CONF_UNDERVOLTAGE   130    /* DEMO mV */
#endif
#ifndef __DEMO__
#define MON_CONF_OVERVOLTAGE    4200    /* mV */
#define MON_CONF_UNDERVOLTAGE   3700    /* mV */
#endif


#define MON_CONF_START_BALANCING_THRESH    30  /* mV */
#define MON_CONF_STOP_BALANCING_THRESH     60  /* mV */


char voltIndicator[ 12 ];


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



void printBatteryStatus()
{
  int i = 0;
  Serial.println("\nBATTERY STATUS:");
  while( i < 12 ) {
    Serial.print("Batt ");
    Serial.print(i , DEC);
    Serial.print(": ");
    Serial.println(voltIndicator[i] , DEC);
    i++;
  }
}
