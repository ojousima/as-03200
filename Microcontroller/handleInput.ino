
void printHelp()
{
  Serial.println("\n/**************************");
  Serial.println(" *   USER INPUT OPTIONS   *");
  Serial.println("***************************");
  Serial.println("** LOWER CASE");
  Serial.println("*************");
  Serial.println(" * a    - adc conversion - start");
  Serial.println(" * 0-7  - Set comparator duty cycle");
  Serial.println(" * w    - Write configuration changes to monitor");
  Serial.println(" *");
  Serial.println("*************");
  Serial.println("** UPPER CASE");
  Serial.println("*************");
  Serial.println(" * H    - Print help message");
  Serial.println(" * C    - Print configuration data");
  Serial.println(" * D    - Print diagnostics data");
  Serial.println(" * V    - Print voltages data");
  Serial.println(" *");
  Serial.println("************************************/");
}


void handleInput(char user_input)
{
  if( (user_input >= '0') && (user_input <= '7') ) {
    MON_setComparatorDutyCycle((unsigned char) (user_input & 0x0F));
    if(__DEBUG__) {
      Serial.println("\nChanged comparatpr duty cycle in local buffer.");
    }
  }
  
  else if(user_input == 'a') {
    if(__DEBUG__) {
      Serial.println("\nSending start adc conversion command to monitor.");
    }
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_ALL);
  }
  else if(user_input == 'w') {
    if(__DEBUG__) {
      Serial.println("\nWriting local configuration register buffer to monitor.");
    }
    SPI_writeConfigurationRegister();
  }
  
  
  else if(user_input == 'H') {
    printHelp();
  }
  else if(user_input == 'C') {
    if(__DEBUG__) {
      Serial.println("\nPrint monitor configuration register.");
    }
    MON_printConfigurationRegister();
  }
  else if(user_input == 'D') {
    if(__DEBUG__) {
      Serial.println("\nPrint monitor diagnostics register.");
    }
    MON_printDiagnosticsRegister();
  }
  else if(user_input == 'L') {
    if(__DEBUG__) {
      Serial.println("\nPrint local configuration register buffer.");
    }
    MON_printConfigurationRegisterLocal();
  }
  else if(user_input == 'V') {
    if(__DEBUG__) {
      Serial.println("\nPrint all voltages.");
    }
    MON_printAllVoltages();
  }
}

