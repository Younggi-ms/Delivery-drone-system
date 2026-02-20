//-------------------------------------------------------------
// class

void Motor_Setup(){
  Calibration_in_mega();
}

void Calibration_in_mega(){
  motors[0].attach(MOTOR0);
  motors[1].attach(MOTOR1);
  motors[2].attach(MOTOR2);
  motors[3].attach(MOTOR3);
  for(int i = 0; i < 5; i++){
    motors[i].writeMicroseconds(MOTOR_MAX);
  }
  while (!Serial2.available()){
    Serial.println("wait...");
  }
  Serial2.read();
  for(int i = 0; i < 5; i++){
    motors[i].writeMicroseconds(MOTOR_MIN);
  }
  delay(5000);
}

void Calibration_in_nano(){
  while (!Serial3.available()){
    Serial.println("wait...");
  }
  Serial3.read();
  
  motors[0].attach(MOTOR0);
  motors[1].attach(MOTOR1);
  motors[2].attach(MOTOR2);
  motors[3].attach(MOTOR3);
  for(int i = 0; i < 5; i++){
    motors[i].writeMicroseconds(MOTOR_MIN);
  }

  for(int i = 0; i < 5; i++){
    motors[i].writeMicroseconds(MOTOR_MIN);
  }
  for(int i = 0; i < 5; i++){
    motors[i].write(MOTOR_MIN);
  }
  delay(5000);
}

void Motor_Move(){
  for(int i = 0; i < 4; i++){
    motors[i].write(constrain(throttle + calculated_speed[i], 800, 2000));
    //Serial.print(String(constrain(throttle + calculated_speed[i], 800, 2000)) + " ");
  }
  //Serial.println("");
}

void Motor_Move(int speed){
  motors[0].write(speed);
  motors[1].write(speed);
  motors[2].write(speed);
  motors[3].write(speed);
}

void Motor_Standby(){
  if(!fly_standby){
    if(Receiver_vals[0] == 0 && Receiver_vals[1] == 0 && Receiver_vals[2] == 0 && Receiver_vals[4] == 0){
      fly_standby = true;
    }
  }
  else{
    if(Receiver_vals[2] > 0){
      fly_standby = false;
      fly_mode = 1;
      Manual_control();
    }
  }
}

void Manual_control(){
  if(is_updated == 1){
    PID_control_y();
    PID_control_x();
    //PID_control_z();
  }
  if(Receiver_vals[2] == 0){
    Motor_Move(800);
    fly_mode = 0;
    PID_Variable_Clear();
  }
  else if(Receiver_vals[4] == 99){
    fly_mode = 2;
  }
  else{
    for(int i = 0; i < 4; i++){
      motors[i].write(constrain(throttle + calculated_speed[i], 800, 2000));
      //Serial.print(String(constrain(throttle + calculated_speed[i], 850, 2000)) + " ");
    }
    //Serial.println("");
  }
}

void Auto_control(){
  if(is_updated == 1){
    PID_control_y();
    PID_control_x();
    //PID_control_z();
  }
  if(Receiver_vals[4] == 0){
    fly_mode = 1;
  }
}

void Auto_Take_Off(){
  if(is_updated == 1){
    PID_control_y();
    PID_control_x();
    //PID_control_z();
  }
  if(last_take_off_time + take_off_delay_time <= present_time){
    if(throttle < auto_target_throttle){
      throttle = constrain(throttle+5, 800, 2000);
    }
    else{
      throttle = auto_target_throttle;
      fly_mode = 2;
    }
  }
}

void Auto_Landing(){
  if(is_updated == 1){
    PID_control_y();
    PID_control_x();
    //PID_control_z();
  }
  if(last_landing_time + landing_delay_time <= present_time){
    if(throttle > 800){
      throttle = constrain(throttle-5, 800, 2000);
    }
    else{
      fly_mode = 0;
      PID_Variable_Clear();
    }
  }
}