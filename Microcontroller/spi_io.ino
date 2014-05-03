#include <SPI.h>

/* Definitions about SPI bus */
/* Chip select DIO output definitions */
#define SPI_SS_MON 10 /* SPI Chip/Slave Select (SS) for lowest monitor in stack */
#define SPI_MOSI 11  /* SPI MOSI DIO output */
#define SPI_MISO 12  /* SPI MISO DIO output */
#define SPI_CLK  13  /* SPI CLOCK DIO output */
/* Definitions about SPI Slave - Monitor */
#define MON_BOARD_COUNT 6  /* Amount of monitor boards connected to system */
/* Values of registers in the LTC6803 circuit */
#define MON_WRITE_CONF_REG 0x01
#define MON_READ_CONF_REG 0x02
#define MON_READ_ALL_VOLTAGES 0x04
#define MON_START_DIAG_REG 0x52
#define MON_READ_DIAG_REG 0x54
#define MON_READ_CELL_1_4 0x06
#define MON_READ_CELL_5_8 0x08
#define MON_READ_CELL_9_12 0x0A

#define MON_SIZE_OF_CONF_REG 6
#define MON_SIZE_OF_DIAG_REG 2


/* Global variables and structures */
unsigned char SPI_rec_buf[MON_BOARD_COUNT * 18]; /* Max data received from All Monitors */
unsigned char MON_configuration_register[MON_SIZE_OF_CONF_REG];

/*********************/
/* SPI API functions */
/*********************/

/* Open SPI bus for communication */
void SPI_openBus()
{
  SPI.begin();
  pinMode(SPI_SS_MON , OUTPUT);    /* Set slave select 1 to output */
  digitalWrite(SPI_SS_MON , HIGH); /* Slave select high when no traffic */
  SPI.setBitOrder(MSBFIRST);             /* LTC-6803 has Most Significant Bit first */
  SPI.setDataMode(SPI_MODE3);            /* CPHA = 1 , CPOL = 1. (LTC-6803 datasheet page 17) */
  SPI.setClockDivider(SPI_CLOCK_DIV32);  /* Bus speed */
}

/* End SPI bus communication */
void SPI_closeBus()
{
  SPI.end();
}

void SPI_setSlaveSelect(boolean level)
{
  if(level) {
    digitalWrite(SPI_SS_MON , HIGH);
  }
  else {
    digitalWrite(SPI_SS_MON , LOW);
  }
  delayMicroseconds(100);
}







/****************************/
/* MODIFY MONITOR BEHAVIOUR */
/****************************/

/* Toggle GPIO Led 1 in monitor configuration register */
void MON_setGPIOLed1(boolean toggle)
{
  if(toggle) {
    MON_configuration_register[0] = (MON_configuration_register[0] & 0xBF);
  }
  else {
    MON_configuration_register[0] = (MON_configuration_register[0] | 0x40);
  }
}

/* Toggle GPIO Led 2 in monitor configuration register */
void MON_setGPIOLed2(boolean toggle)
{
  if(toggle) {
    MON_configuration_register[0] = (MON_configuration_register[0] & 0xDF);
  }
  else {
    MON_configuration_register[0] = (MON_configuration_register[0] | 0x20);
  }
}



/* Write configuration register to monitor */
void SPI_writeConfigurationRegister()
{
  int i = 0;
  unsigned char pec = calculatePECForByte(MON_WRITE_CONF_REG , 0 , true);

  if(__DEBUG__) {
    Serial.println("\nWriting configuration register:");
  }
  
  SPI_setSlaveSelect(false);
  SPI.transfer(MON_WRITE_CONF_REG);
  SPI.transfer(pec);
  
  while( i < MON_SIZE_OF_CONF_REG ) {
    SPI.transfer(MON_configuration_register[i]);
    if(__DEBUG__) {
      printByte(MON_configuration_register[i]);
    }
    i++;
  }
  pec = calculatePECForByteArray(MON_configuration_register , 6);
  SPI.transfer(pec);

  if(__DEBUG__) {
    Serial.print("PEC: ");
    printByte(pec);
    Serial.println("END OF write configuration register\n");
  }

  SPI_setSlaveSelect(true);
}



/* Read configuration register from monitor */
unsigned char* SPI_readConfigurationRegister()
{
  int i = 0;
  unsigned char in_pec = 0;
  unsigned char in_pec_own = 0;
  unsigned char out_pec = calculatePECForByte(MON_READ_CONF_REG , 0 , true);

  if(__DEBUG__) {
    Serial.println("\nReading configuration register:");
  }

  SPI_setSlaveSelect(false);
  SPI.transfer(MON_READ_CONF_REG);
  SPI.transfer(out_pec);
    
  i = 0;
  while( i < MON_SIZE_OF_CONF_REG )
  {
    MON_configuration_register[i] = SPI.transfer(0);
    if(__DEBUG__)
    {
      printByte(MON_configuration_register[i]);
    }
    i++;
  }
  in_pec = SPI.transfer(0);
  in_pec_own = calculatePECForByteArray(MON_configuration_register , 6);
  SPI_setSlaveSelect(true);
  
  if(__DEBUG__) {
    if( in_pec == in_pec_own ) {
      Serial.println("PECs match!");
      printByte(in_pec);
    }
    else {
      Serial.println("PECs MISMATCH!");
      Serial.print("Pec received: ");
      printByte(in_pec);
      Serial.print("Pec calculated: ");
      printByte(in_pec_own);
    }
    Serial.println("END OF read configuration register\n");
  }
  
  return SPI_rec_buf;
}



unsigned char* SPI_readAllVoltages()
{
  int i = 0;
  unsigned char pec_out = calculatePECForByte( MON_READ_ALL_VOLTAGES , 0 , true);
  unsigned char pec_in = 0;
  unsigned char pec_in_own = 0;

  if(__DEBUG__) {
    Serial.println("\nReading all voltages:");
  }

  SPI_setSlaveSelect(false);
  SPI.transfer(MON_READ_ALL_VOLTAGES);
  SPI.transfer(pec_out);
  
  i = 0;
  while( i < 18 )
  {
    SPI_rec_buf[i] = SPI.transfer(0); /* Read response from monitor */
    if(__DEBUG__)
    {
      printByte(SPI_rec_buf[i]);
    }
    i++;
  }
  pec_in = SPI.transfer(0);
  pec_in_own = calculatePECForByteArray(SPI_rec_buf , 18);
  SPI_setSlaveSelect(true);
  
  if(__DEBUG__) {
    if( pec_in == pec_in_own ) {
      Serial.println("PECs match!");
      printByte(pec_in);
    }
    else {
      Serial.println("PECs MISMATCH!");
      Serial.print("Pec received: ");
      printByte(pec_in);
      Serial.print("Pec calculated: ");
      printByte(pec_in_own);
    }
    Serial.println("END OF read all voltages register\n");
  }
  
  return SPI_rec_buf;
}



void SPI_readDiagnostics()
{
  int i = 0;
  unsigned char out_pec = calculatePECForByte(MON_READ_DIAG_REG , 0 , true);
  unsigned char in_pec = 0;
  unsigned char in_pec_own = 0;

  if(__DEBUG__) {
    Serial.println("\nReading diagnostics register:");
  }  

  SPI_setSlaveSelect(false);
  SPI.transfer(MON_READ_DIAG_REG);
  SPI.transfer(out_pec);

  i = 0;
  while( i < MON_SIZE_OF_DIAG_REG )
  {
    SPI_rec_buf[i] = SPI.transfer(0); /* Read response from monitor */
    
    if(__DEBUG__) {
      printByte(SPI_rec_buf[i]);
    }
    i++;
  }
  in_pec = SPI.transfer(0);
  in_pec_own = calculatePECForByteArray(SPI_rec_buf , 2);
  SPI_setSlaveSelect(true);
  
  if(__DEBUG__) {
    if( in_pec == in_pec_own ) {
      Serial.println("PECs match!");
      printByte(in_pec);
    }
    else {
      Serial.println("PECs MISMATCH!");
      Serial.print("Pec received: ");
      printByte(in_pec);
      Serial.print("Pec calculated: ");
      printByte(in_pec_own);
    }
    Serial.println("END OF read diagnostics register\n");
  }

  return;
}



void SPI_startDiagnostics()
{
  unsigned char pec = calculatePECForByte(MON_START_DIAG_REG , 0 , true);

  digitalWrite(SPI_SS_MON , LOW);
  delayMicroseconds(100);

  SPI.transfer(MON_START_DIAG_REG);
  SPI.transfer(pec);

  delayMicroseconds(100);
  digitalWrite(SPI_SS_MON , HIGH);
  return;
}

