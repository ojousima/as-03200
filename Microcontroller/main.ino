/* #define __DEBUG__ true */


unsigned char initInput() {
  unsigned char in = 0;
  bitSet(in , 5);
  bitSet(in , 3);
  bitSet(in , 1);
  return in; // Returning 0000 0001
}


void setup() {
  Serial.begin(9600);
}


int loop_ctr = 0; 



void loop()
{
  SPI_openBus();
  Serial.println("Opened SPI bus.");
  delay(1000);
//  SPI_writeConfigurationRegister();
//  delay(1000);
  SPI_readConfigurationRegister();
//  SPI_startDiagnostics();
  delay(1000);

  delay(1000);
  SPI_readDiagnostics();
  delay(1000);
  SPI_closeBus();
  Serial.println("Closed SPI bus");

  delay(1000);
  loop_ctr++;
}


/*
void loop() {
  unsigned char pec = 0;
  unsigned char data_input = initInput();

  delay(1000);  
  if( loop_ctr == 0 ) {
    pec = calculatePECForByte(data_input , 0 , true);
    if( __DEBUG__ )
    {
      printByte(pec);
    }
  }
  
  delay(2000);
  loop_ctr++;
}
*/
