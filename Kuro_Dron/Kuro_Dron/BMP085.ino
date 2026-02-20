//BMP085 기압센서
/*
void BMP085_Setup(){
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	  while (1) {}
  }
  start_altitude = bmp.readAltitude();
}

void BMP085_Get_Values(){
  //pressure = bmp.readPressure();
  altitude = bmp.readAltitude() - start_altitude;
}

void BMP085_Get_advensed_Values(){
  pressure = bmp.readPressure();
  pressure_at_sealevel = bmp.readSealevelPressure();
  altitude = bmp.readAltitude();
  real_altitude = bmp.readAltitude(101500);
}

void BMP085_Debug(){
  Serial.print("Altitude = ");
  Serial.println(altitude);
}

void BMP085_advensed_Debug(){
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");
    
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(pressure_at_sealevel);
  Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(real_altitude);
  Serial.println(" meters");
    
  Serial.println();
}
*/