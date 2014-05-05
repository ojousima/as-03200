/**************************
 *   USER INPUT OPTIONS   *
***************************
** LOWER CASE
*************
 * a    - adc conversion - start
 * 0-7  - Set comparator duty cycle
 * w    - Write configuration changes to monitor
 *
*************
** UPPER CASE
*************
 * C    - Print configuration data
 * D    - Print diagnostics data
 * V    - Print voltages data
 *
************************************/


void handleInput(char user_input)
{
  if( (user_input >= '0') && (user_input <= '7') ) {
    MON_setComparatorDutyCycle((unsigned char) (user_input & 0x0F));
    if(__DEBUG__) {
      Serial.println("Changed comparatpr duty cycle in local buffer.");
    }
  }
  
  else if(user_input == 'a') {
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_ALL);
    if(__DEBUG__) {
      Serial.println("Start adc conversion command sent to monitor.");
    }
  }
  else if(user_input == 'w') {
    SPI_writeConfigurationRegister();
    if(__DEBUG__) {
      Serial.println("Wrote local configuration register buffer to monitor.");
    }
  }
  
  
  
  else if(user_input == 'C') {
    if(__DEBUG__) {
      Serial.println("Print monitor configuration register.");
    }
    MON_printConfigurationRegister();
  }
  else if(user_input == 'D') {
    if(__DEBUG__) {
      Serial.println("Print monitor diagnostics register.");
    }
    MON_printDiagnosticsRegister();
  }
  else if(user_input == 'L') {
    if(__DEBUG__) {
      Serial.println("Print local configuration register buffer.");
    }
    MON_printConfigurationRegisterLocal();
  }
  else if(user_input == 'V') {
    if(__DEBUG__) {
      Serial.println("Print all voltages.");
    }
    MON_printAllVoltages();
  }
}

