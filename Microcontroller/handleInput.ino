boolean start_discharge_select = false;
boolean stop_discharge_select = false;

void printHelp()
{
  printHelp_1();
  printHelp_2();
  printHelp_3();
}

void printHelp_1() {
  Serial.println("\n/**************************");
  Serial.println(" *   USER INPUT OPTIONS   *");
  Serial.println("***************************");
  Serial.println("** DIRECT COMMANDS");
  Serial.println("******************");
  Serial.println(" * a    - Toggle start adc conversion");
  Serial.println(" * s    - Toggle start adc conversion - Allow discharge");
  Serial.println(" *");
}
void printHelp_2()
{
  Serial.println("*******************");
  Serial.println("** REGISTER CHANGES");
  Serial.println("*******************");

  Serial.println(" * d    - START discharging. Select which cells after entering d");
  Serial.println(" * z    - STOP discharging. Select which cells after entering z");
  Serial.println(" * 0-7  - Set comparator duty cycle");
  Serial.println(" * w    - Write config changes to monitor");
  Serial.println(" *");
}
void printHelp_3()
{
  Serial.println("*******************");
  Serial.println("** PRINT DEBUG DATA");
  Serial.println("*******************");
  Serial.println(" * C    - Print configuration data");
  Serial.println(" * D    - Print diagnostics data");
  Serial.println(" * H    - Print help message");
  Serial.println(" * S    - Print Battery status");
  Serial.println(" * V    - Print voltages data");
  Serial.println("*******************");
}


void handleInput(char user_input)
{
  if( start_discharge_select ) {
    startDischarge(user_input);
  }
  else if( stop_discharge_select ) {
    stopDischarge(user_input);
  }
  
  
  else if( (user_input >= '0') && (user_input <= '7') ) {
    MON_setComparatorDutyCycle((unsigned char) (user_input & 0x0F));
    if(__DEBUG__) {
      Serial.println("\nChanged comparatpr duty cycle in local buffer.");
    }
  }
  
  else if(user_input == 'a') {
    if(__DEBUG__) {
      Serial.println("\nToggle start adc conversion command to monitor.");
    }
    do_adc_conversion = !do_adc_conversion;
  }
  else if(user_input == 'd') {
    if(__DEBUG__) {
      Serial.println("\nDischarge on: Which cell? (0-b or 'x' for all):");
    }
    start_discharge_select = true;
  }
  else if(user_input == 's') {
    if(__DEBUG__) {
      Serial.println("\nToggle adc conversion, allow discharge command to monitor.");
    }
  do_adc_conversion_discharge = !do_adc_conversion_discharge;

  }
  else if(user_input == 'z') {
    if(__DEBUG__) {
      Serial.println("\nStop discharge: Which cell? (0-b or 'x' for all):");
    }
    stop_discharge_select = true;
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
  else if(user_input == 'S') {
    printBatteryStatus();
  }
  else if(user_input == 'V') {
    if(__DEBUG__) {
      Serial.println("\nPrint all voltages.");
    }
    MON_printAllVoltages();
  }
}


void startDischarge(char user_input)
{
  if( user_input == '0' ) {
    MON_dischargeCell0(true);
  }
  else if( user_input == '1' ) {
    MON_dischargeCell1(true);
  }
  else if( user_input == '2' ) {
    MON_dischargeCell2(true);
  }
  else if( user_input == '3' ) {
    MON_dischargeCell3(true);
  }
  else if( user_input == '4' ) {
    MON_dischargeCell4(true);
  }
  else if( user_input == '5' ) {
    MON_dischargeCell5(true);
  }
  else if( user_input == '6' ) {
    MON_dischargeCell6(true);
  }
  else if( user_input == '7' ) {
    MON_dischargeCell7(true);
  }
  else if( user_input == '8' ) {
    MON_dischargeCell8(true);
  }
  else if( user_input == '9' ) {
    MON_dischargeCell9(true);
  }
  else if( user_input == 'a' ) {
    MON_dischargeCell10(true);
  }
  else if( user_input == 'b' ) {
    MON_dischargeCell11(true);
  }
  else if( user_input == 'x' ) {
    MON_dischargeCell0(true);
    MON_dischargeCell1(true);
    MON_dischargeCell2(true);
    MON_dischargeCell3(true);
    MON_dischargeCell4(true);
    MON_dischargeCell5(true);
    MON_dischargeCell6(true);
    MON_dischargeCell7(true);
    MON_dischargeCell8(true);
    MON_dischargeCell9(true);
    MON_dischargeCell10(true);
    MON_dischargeCell11(true);
  }
  Serial.print("Input received (ascii): ");
  Serial.println(user_input , HEX);
  start_discharge_select = false;
}


void stopDischarge(char user_input)
{
  if( user_input == '0' ) {
    MON_dischargeCell0(false);
  }
  else if( user_input == '1' ) {
    MON_dischargeCell1(false);
  }
  else if( user_input == '2' ) {
    MON_dischargeCell2(false);
  }
  else if( user_input == '3' ) {
    MON_dischargeCell3(false);
  }
  else if( user_input == '4' ) {
    MON_dischargeCell4(false);
  }
  else if( user_input == '5' ) {
    MON_dischargeCell5(false);
  }
  else if( user_input == '6' ) {
    MON_dischargeCell6(false);
  }
  else if( user_input == '7' ) {
    MON_dischargeCell7(false);
  }
  else if( user_input == '8' ) {
    MON_dischargeCell8(false);
  }
  else if( user_input == '9' ) {
    MON_dischargeCell9(false);
  }
  else if( user_input == 'a' ) {
    MON_dischargeCell10(false);
  }
  else if( user_input == 'b' ) {
    MON_dischargeCell11(false);
  }
  else if( user_input == 'x' ) {
    MON_dischargeCell0(false);
    MON_dischargeCell1(false);
    MON_dischargeCell2(false);
    MON_dischargeCell3(false);
    MON_dischargeCell4(false);
    MON_dischargeCell5(false);
    MON_dischargeCell6(false);
    MON_dischargeCell7(false);
    MON_dischargeCell8(false);
    MON_dischargeCell9(false);
    MON_dischargeCell10(false);
    MON_dischargeCell11(false);
  }
  stop_discharge_select = false;
  Serial.print("Input received (ascii): ");
  Serial.println(user_input , HEX);
}
