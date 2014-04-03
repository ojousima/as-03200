unsigned char initPEC() {
  unsigned char pec = 0;
  bitSet(pec , 0);
  bitSet(pec , 6);
  return pec;
}



unsigned char calculatePECForNextBit(boolean in_bit , unsigned char cur_pec)
{
  boolean in0 = 0;
  boolean in1 = 0;
  boolean in2 = 0;
  unsigned char new_pec = 0;
  
  in0 = (in_bit ^ bitRead(cur_pec , 7));
  in1 = (in0 ^ bitRead(cur_pec , 0));
  in2 = (in0 ^ bitRead(cur_pec , 1));
  
  bitWrite(new_pec , 7 , bitRead(cur_pec,6));
  bitWrite(new_pec , 6 , bitRead(cur_pec,5));
  bitWrite(new_pec , 5 , bitRead(cur_pec,4));
  bitWrite(new_pec , 4 , bitRead(cur_pec,3));
  bitWrite(new_pec , 3 , bitRead(cur_pec,2));
  bitWrite(new_pec , 2 , in2);
  bitWrite(new_pec , 1 , in1);
  bitWrite(new_pec , 0 , in0);
  
  return new_pec;
}



unsigned char calculatePECForByte(unsigned char input , unsigned char pec , boolean is_single_byte)
{
  int i = 0;
  boolean in_bit = 0;
  unsigned char own_pec = pec;
  if( is_single_byte ) { /* Not for an array. Init new pec */
    own_pec = initPEC();
  }
  
  while( i < 8 ) {
    in_bit = bitRead(input , 7-i);
    pec = calculatePECForNextBit(in_bit , pec);
    i++;
    delay(500);
  }
  if( __DEBUG__ )
  {
    Serial.print("PEC is: ");
    printByte(pec);
  }
  return pec;
}



int calculatePECForByteArray(unsigned char* byte_arr , int byte_count)
{
  int i = 0;
  unsigned char pec = initPEC();
  
  while( i < byte_count )
  {
    pec = calculatePECForByte(*(byte_arr + i) , pec , false);
    i++;
  }
  return pec;
}
