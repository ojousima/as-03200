#define __DEBUG__ true
#define __PEC_DEBUG__ false

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

#define MON_CMD_START_ADC_CONVERSION_ALL 0x10
#define MON_CMD_START_ADC_CONVERSION_SELF_TEST_1 0x1E
#define MON_CMD_START_ADC_CONVERSION_SELF_TEST_2 0x1F



/* Global variables and structures */
unsigned char MON_configuration_register[MON_SIZE_OF_CONF_REG];
unsigned char MON_configuration_register_local[MON_SIZE_OF_CONF_REG];
int MON_voltages[MON_BOARD_COUNT * 12];

int MON_DIAG_reference_voltage;
unsigned char MON_DIAG_revision_number;
boolean MON_DIAG_muxfail;





void printVoltage(int volt_in) {
  int i = 0;
  int voltage = (volt_in-512) * 1.5;
  Serial.print("Orig val: ");
  Serial.print(volt_in , DEC);
  Serial.print(", Volt: ");
  Serial.print(voltage , DEC);
  Serial.println("mV");
}


void printByte(unsigned char byte_in) {
  int i = 0;
  Serial.print("Byte: ");
  while( i < 8 ) {
    Serial.print(bitRead(byte_in,7-i));
    i++;
  }
  Serial.print(" , 0x");
  Serial.print(byte_in,HEX);
  Serial.print(" , ");
  Serial.println(byte_in,DEC);
}



void printWord(word word_in) {
  int i = 0;
  Serial.print("Word: ");
  while( i < 16 ) {
    Serial.print(bitRead(word_in,15-i));
    i++;
  }
  Serial.print(" , 0x");
  Serial.print(word_in,HEX);
  Serial.print(" , ");
  Serial.println(word_in,DEC);
}
