
void setup() {
  Serial.begin(9600);
}



void displayInitSequence()
{
  int i = 1;  
  while( i < 9 ) {
    MON_toggleGPIOLed1( ((i%2)==1) );
    MON_toggleGPIOLed2( ((i%2)==1) );
    SPI_writeConfigurationRegister();
    delay(300);
    i++;
  }
}



char user_input;
int loop_ctr = 0; 

void loop()
{
  user_input = Serial.read();
  if( user_input != -1 ) {
    handleInput(user_input);
  }
  
  if(loop_ctr == 0) {
    SPI_openBus();
    Serial.println("Opened SPI bus.");
    displayInitSequence();
  }
  if( 1000 <= loop_ctr ) {
    loop_ctr = 0;
  }
  
//  if(loop_ctr == 2) {
//    MON_toggleGPIOLed1(true);
//    MON_toggleGPIOLed2(true);
//    MON_setComparatorDutyCycle(3);
//    
//    SPI_writeConfigurationRegister();
//    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_ALL);
//  }
//  
//  if(loop_ctr == 4) {
//    MON_setComparatorDutyCycle(6);
//    SPI_writeConfigurationRegister();
//  }
//  
//  if(loop_ctr == 6) {
//    MON_toggleGPIOLed1(false);
//    MON_toggleGPIOLed2(false);
//    MON_setComparatorDutyCycle(10);
//    
//    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_SELF_TEST_1);
//    SPI_writeConfigurationRegister();
//  }
//
//  if(loop_ctr == 8) {
//    SPI_sendCommandToMonitor(MON_CMD_START_ADC_CONVERSION_SELF_TEST_2);
//  }
//
//
//  SPI_readDiagnostics();
//  SPI_readConfigurationRegister();
//  SPI_readAllVoltages();
//  
  delay(100);
  loop_ctr++;
}

