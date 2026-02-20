
void MPU_9250_Setup(){ // MPU-9250 가속도/자이로 센서 초기화 함수
  if (!mpu.setup(0x68)) {  // change to your own address
    while (1) {
        Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
        delay(5000);
    }
  }
  while (1) {
    if(mpu.update()){
      static uint32_t prev_ms = millis();
      if (millis() > prev_ms + 25) {
        prev_ms = millis();
        x_base = mpu.getAccX() * 180 / M_PI;
        y_base = mpu.getAccY() * 180 / M_PI;
        break;
      }
    }
    Serial.println("loop..");
  }
}

void MPU_9250_Get(){
/*
    if (mpu.getAccX() < 0) {
      [1] = -1*(sqrt(pow((mpu.getAccX() * 180 / M_PI - x_base),2)));
    }
    else {ypr[1] = sqrt(mpu.getAccX() * 180 / M_PI - x_base);}
    if (mpu.getAccY() < 0) {
      ypr[2] = -1*(sqrt(pow((mpu.getAccY() * 180 / M_PI - x_base),2)));
    }
    else {ypr[2] = sqrt(mpu.getAccY() * 180 / M_PI - y_base);}
    */
    ypr[1] = mpu.getAccX() * 180 / M_PI - x_base;
    ypr[2] = mpu.getAccY() * 180 / M_PI - y_base;
    ypr[0] = mpu.getYaw();
    gyro[0] = mpu.getGyroX();
    gyro[1] = mpu.getGyroY();
    gyro[2] = mpu.getGyroZ();
}

void MPU_9250_Debug(){ 
  //Serial.println(" yprZ:" + String(ypr[0], 3));
  Serial.println("yprX:" + String(ypr[1], 3) + " yprY:" + String(ypr[2], 3) + " yprZ:" + String(ypr[0], 3));
  //Serial.println("gyroX:" + String(gyro[0], 3) + " gyroY:" + String(gyro[1], 3) + " gyroZ:" + String(gyro[2], 3));
}
