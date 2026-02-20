// MPU-6050 가속도/자이로 센서

//<Adafruit_MPU6050.h>
/*
void MPU_6050_Setup(){ // MPU-6050 가속도/자이로 센서 초기화 함수
  while(1){
    if (!mpu.begin()){
      Serial.println("Failed to find MPU6050 chip");
      delay(10);
    }
    else{
      break;
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}

void MPU_6050_Get(){
  mpu.getEvent(&a, &g, &temp);
  ypr[1] = a.acceleration.x;
  ypr[2] = a.acceleration.y;
  ypr[0] = a.acceleration.z;
  gyro[0] = g.gyro.x;
  gyro[1] = g.gyro.y;
  gyro[2] = g.gyro.z;
}

void MPU_6050_Debug(){ 
  //Print out the values 
  
  Serial.println("yprX:" + String(ypr[1], 3) + " yprY:" + String(ypr[2], 3) + " yprZ:" + String(ypr[0], 3));
  Serial.println("gyroX:" + String(gyro[0], 3) + " gyroY:" + String(gyro[1], 3) + " gyroZ:" + String(gyro[2], 3));
}


//<MPU6050_6Axis_MotionApps20.h>
/*
void MPU_6050_Setup(){
  while (!Serial);
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(33);
  mpu.setYGyroOffset(-13);
  mpu.setZGyroOffset(8);
  mpu.setZAccelOffset(1416);



  if (devStatus == 0) {
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}

void MPU_6050_Get(){
  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize) {
  }
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    // Serial.println(F("FIFO overflow!"));
  } 
  else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetGyro(gyro, fifoBuffer);
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    ypr[1] = (ypr[1] * 180 / M_PI); //x
    ypr[2] = (ypr[2] * 180 / M_PI); //y
    ypr[0] = (ypr[0] * 180 / M_PI); //z
    //gyro[0],gyro[1],gyro[2]//x,y,z 각속도값
  }
}
*/