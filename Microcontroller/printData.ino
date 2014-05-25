void MON_printAllVoltages()
{
  int i = 0;
  Serial.println("VOLTAGES:");
  while( i < 12 ) {
    Serial.print("Batt ");
    Serial.print(i , DEC);
    Serial.print(": ");
    printVoltage(MON_voltages[i]);
    i++;
  }
}



void MON_printConfigurationRegisterLocal()
{
  int i = 0;
  Serial.println("LOCAL CONFIGURATION REGISTER:");
  while( i < MON_SIZE_OF_CONF_REG ) {
    printByte(MON_configuration_register_local[i]);
    i++;
  }
  Serial.println("");
}

void MON_printConfigurationRegister()
{
  int i = 0;
  Serial.println("MONITOR CURRENT CONFIGURATION REGISTER:");
  while( i < MON_SIZE_OF_CONF_REG ) {
    printByte(MON_configuration_register[i]);
    i++;
  }
  Serial.println("");
}




void MON_printDiagnosticsRegister()
{
  MON_printDiagnosticsRegister_1();
  MON_printDiagnosticsRegister_2();
}

void MON_printDiagnosticsRegister_1()
{
  Serial.println(F("DIAGNOSTICS REGISTER:"));
  Serial.print(F("Ref volt: "));
  printVoltage(MON_DIAG_reference_voltage);
  Serial.print(F("Rev numb: "));
  Serial.println(MON_DIAG_revision_number , DEC);
  Serial.print(F("Mux fail: "));
  Serial.println(MON_DIAG_muxfail , DEC);
}
void MON_printDiagnosticsRegister_2()
{
  Serial.print(F("ADC conversion on: "));
  Serial.println(do_adc_conversion , DEC);
  Serial.print(F("ADC conv with discharge: "));
  Serial.println(do_adc_conversion_discharge , DEC);
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
