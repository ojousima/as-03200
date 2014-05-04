/**************************
 *   USER INPUT OPTIONS   *
***************************
** LOWER CASE
*************
 * a    - adc conversion - start
 * 0-7  - Set comparator duty cycle
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
  if(__DEBUG__) {
    Serial.println("\n--- GOT USER INPUT ---\n");
  }
  
  if( (user_input >= '0') && (user_input <= 7) ) {
    MON_setComparatorDutyCycle((unsigned char) user_input);
  }
  else if(user_input == 'a') {
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_ALL);
  }
  else if(user_input == 'C') {
    SPI_readConfigurationRegister();
  }
  else if(user_input == 'D') {
    SPI_readDiagnostics();
  }
  else if(user_input == 'V') {
    SPI_readAllVoltages();
  }
}

