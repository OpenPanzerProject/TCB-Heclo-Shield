union byteToInt
{
  struct
  {
    byte b0 : 8;
    byte b1 : 8;
  } bytes;
  uint16_t i;
};

/*static byte receivedData[30];   // an array to store the received data

void recvWithStartEndMarkers() {
  boolean recvInProgress = false;
  byte ndx = 0;
  char startMarker = 0xF9;
  char endMarker;
  char rc;
  byte tempData[30];   // an array to store the received data temporary
  //Serial.print(tempData[1], HEX);
  //Serial.println("");

  while (AuxSerial.available() > 0) {
    rc = AuxSerial.read();
    if (recvInProgress == true) {
      if (rc != startMarker) {
        tempData[ndx] = rc;
        ndx++;
      }
      else {
        tempData[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }


  uint16_t crclong = crc_calculate(tempData, 2 + tempData[0]);

  byteToInt tmpCRC;                                                   // Bryder 16 bit int op i 2 bytes
  tmpCRC.i = crclong;

  if (tempData[tempData[0] + 2] == tmpCRC.bytes.b0 && tempData[tempData[0] + 3] == tmpCRC.bytes.b1) {
    for (uint8_t i = 0; i <= tempData[0] + 2; i++) {
      receivedData[i] = tempData[i];
    }
  }
  else {
    memset(receivedData, 0, sizeof(receivedData));
  }
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void replyStatus() {
  /*dataFromStorm();
    recvWithStartEndMarkers();
    //Serial.print(receivedData[0], HEX);
    //Serial.println("");
    if (receivedData[0] == 0x01 && receivedData[1] == 0x0F && receivedData[2] == 0x15) {
      uint16_t statusVoltage = ReadVoltage() * 100;
      uint16_t statusWatt = engine_watts * 100;
    /*Serial.print("sending this ");
    Serial.print("statusVoltage ");
    Serial.print(statusVoltage);
    Serial.print(" statusWatt ");
    Serial.print(statusWatt);
    Serial.println("");
      byteToInt tmpWatt;
      tmpWatt.i = statusWatt;

      byteToInt tmpVolt;
      tmpVolt.i = statusVoltage;

      byte pbuffer[] = {0x04, 0x0F, tmpWatt.bytes.b0, tmpWatt.bytes.b1, tmpVolt.bytes.b0, tmpVolt.bytes.b1};
      uint16_t crclong = crc_calculate(pbuffer, sizeof(pbuffer));

      byteToInt tmpCRC;                                                   // Bryder 16 bit int op i 2 bytes
      tmpCRC.i = crclong;

      byte buf[] = {0xFB, 0x04, 0x0F, tmpWatt.bytes.b0, tmpWatt.bytes.b1, tmpVolt.bytes.b0, tmpVolt.bytes.b1, tmpCRC.bytes.b0, tmpCRC.bytes.b1};
      AuxSerial.write(buf, sizeof(buf));
    }
    /*else if (receivedData[0] != 0){
      AuxSerial.write(receivedData, sizeof(receivedData));
    }*/
  uint16_t statusVoltage = ReadVoltage() * 100;
  uint16_t statusWatt = Driver.GetEngineWatts * 100;
  static uint16_t lastStatusVoltage;
  static uint16_t lastStatusWatt;
  /*Serial.print("sending this ");
  Serial.print("statusVoltage ");
  Serial.print(statusVoltage);
  Serial.print(" statusWatt ");
  Serial.print(Driver.GetEngineWatts);
  Serial.println("");*/
  if (statusWatt != lastStatusWatt || statusVoltage != lastStatusVoltage) {
    lastStatusWatt = statusWatt;
    lastStatusVoltage = statusVoltage;

    byteToInt tmpWatt;
    tmpWatt.i = statusWatt;

    byteToInt tmpVolt;
    tmpVolt.i = statusVoltage;

    /*byte pbuffer[] = {0x04, 0x0F, tmpWatt.bytes.b0, tmpWatt.bytes.b1, tmpVolt.bytes.b0, tmpVolt.bytes.b1};
      uint16_t crclong = crc_calculate(pbuffer, sizeof(pbuffer));

      byteToInt tmpCRC;                                                   // Bryder 16 bit int op i 2 bytes
      tmpCRC.i = crclong;*/

    byte buf[] = {0xFB, /*0x04, 0x0F,*/ tmpWatt.bytes.b0, tmpWatt.bytes.b1, tmpVolt.bytes.b0, tmpVolt.bytes.b1/*, tmpCRC.bytes.b0, tmpCRC.bytes.b1*/};
    AuxSerial.write(buf, sizeof(buf));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dataFromStorm() {
  //Serial.println("start of data");
  while (AuxSerial.available() > 0) {
    Serial.print(AuxSerial.read(), HEX);
    Serial.println("");
  }
  //Serial.println("end of data");
}
