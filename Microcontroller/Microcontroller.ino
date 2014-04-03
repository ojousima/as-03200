#define __DEBUG__ true



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
