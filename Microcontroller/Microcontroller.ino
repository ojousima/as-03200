#define __DEBUG__ true
#define __PEC_DEBUG__ false

#define MON_CMD_START_ADC_CONVERSION_ALL 0x10
#define MON_CMD_START_ADC_CONVERSION_SELF_TEST_1 0x1E
#define MON_CMD_START_ADC_CONVERSION_SELF_TEST_2 0x1F


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
