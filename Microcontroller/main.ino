
void setup() {
  Serial.begin(9600);
}



int loop_ctr = 0; 

void loop()
{
  if(loop_ctr == 0) {
    delay(2000);
    SPI_openBus();
    Serial.println("Opened SPI bus.");
  }
  
  if(loop_ctr == 2) {
    MON_toggleGPIOLed1(true);
    MON_toggleGPIOLed2(true);
    MON_setComparatorDutyCycle(3);
    
    SPI_writeConfigurationRegister();
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_ALL);
  }
  
  if(loop_ctr == 4) {
    MON_setComparatorDutyCycle(6);
    SPI_writeConfigurationRegister();
  }
  
  if(loop_ctr == 6) {
    MON_toggleGPIOLed1(false);
    MON_toggleGPIOLed2(false);
    MON_setComparatorDutyCycle(10);
    
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_SELF_TEST_1);
    SPI_writeConfigurationRegister();
  }

  if(loop_ctr == 8) {
    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_SELF_TEST_2);
  }


  SPI_readDiagnostics();
  SPI_readConfigurationRegister();
  SPI_readAllVoltages();
  
  delay(500);
  loop_ctr++;
}

