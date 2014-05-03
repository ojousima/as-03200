
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
  
  if(loop_ctr == 3) {
    MON_setGPIOLed1(true);
    MON_setGPIOLed2(true);
    SPI_writeConfigurationRegister();
  }
  
  if(loop_ctr == 5) {
    SPI_readAllVoltages();
  }
  
  if(loop_ctr == 7) {
    MON_setGPIOLed1(false);
    MON_setGPIOLed2(false);
    SPI_writeConfigurationRegister();
  }

  if( (loop_ctr % 2) == 0 ) {
    SPI_readDiagnostics();
    SPI_readConfigurationRegister();
    delay(1000);
  }
  
  delay(4000);
  loop_ctr++;
}

