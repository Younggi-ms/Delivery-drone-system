//NEO_6M GPS센서
void NEO_6M_Setup(){
  Serial1.begin(9600);
  //Serial.println("NEO_6M_Setup");
}
void NEO_6M_Get(){
  while(Serial1.available())
 {
  gps.encode(Serial1.read());
 }
 if(gps.location.isUpdated())
 {
  Serial.print("Satellite Count:");
  Serial.println(gps.satellites.value());
  Serial.print("Latitude:");
  Serial.println(gps.location.lat(),6);
  Serial.print("Longitude:");
  Serial.println(gps.location.lng(),6);
  Serial.print("Speed MPH:");
  Serial.println(gps.speed.mph());
  Serial.print("Altitiude Feet:");
  Serial.println(gps.altitude.feet());
 }
}

void NEO_6M_Serial_Debug(){
  //Serial.println(Serial2.available());
  while(Serial1.available() > 0)     // While there is data on the RX pin...
    { 
      //Serial.println("Serial1.available()");
      char c = Serial1.read();    // load the data into a variable...
      Serial1.print(c);
    }
}