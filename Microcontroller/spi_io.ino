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
#define MON_READ_ALL_VOLTAGES 0x04
#define MON_START_DIAG_REG 0x52
#define MON_READ_DIAG_REG 0x54
#define MON_READ_CELL_1_4 0x06
#define MON_READ_CELL_5_8 0x08
#define MON_READ_CELL_9_12 0x0A


/* Global variables and structures */
unsigned char SPI_rec_buf[MON_BOARD_COUNT * 18]; /* Max data received from All Monitors */

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



unsigned char* SPI_readAllVoltages()
{
  int i = 0;
  unsigned char pec = calculatePECForByte( MON_READ_ALL_VOLTAGES , 0 , true);
  
  digitalWrite(SPI_SS_MON , LOW);
  SPI.transfer(MON_READ_ALL_VOLTAGES);
  SPI.transfer(pec);
  
  i = 0;
  while( i < 18 )
  {
    SPI_rec_buf[i] = SPI.transfer(0); /* Read response from monitor */
    i++;
    if( __DEBUG__ )
    {
      printByte(SPI_rec_buf[i]);
    }
  }
  
  digitalWrite(SPI_SS_MON , HIGH);
  return SPI_rec_buf;
}



void SPI_readDiagnostics()
{
  int i = 0;
  unsigned char pec = calculatePECForByte(MON_READ_DIAG_REG , 0 , true);
  
  digitalWrite(SPI_SS_MON , LOW);
  delayMicroseconds(250);
  SPI.transfer(MON_READ_DIAG_REG);
  SPI.transfer(pec);
  delayMicroseconds(20);
  i = 0;
  while( i < 3 )
  {
    SPI_rec_buf[i] = SPI.transfer(0); /* Read response from monitor */
    i++;
    if( __DEBUG__ )
    {
      printByte(SPI_rec_buf[i]);
    }
  }
  delayMicroseconds(250);
  digitalWrite(SPI_SS_MON , HIGH);
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

