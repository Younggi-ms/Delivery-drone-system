void Receiver_Get(){
  //Serial.println(time_interval);
  String buffer = "";
  while (Serial2.available()) {
    buffer += (char)Serial2.read();
    delay(1);
  }

  if (buffer.length() > 0) {
    for(int i = 0; i < 5; i++){
      Receiver_vals[i] = buffer[i]-1;
    }
    if(Receiver_vals[0] == -1){
      throttle = MOTOR_MIN;
      Serial.println(MOTOR_MIN);
    }
    else {
      throttle = MOTOR_MIN+(int)(Receiver_vals[2]*12);
      desired_angle_x = Receiver_vals[1] / 10.0 - 5;
      desired_angle_y = Receiver_vals[0] / 10.0 - 5;
      desired_angle_z = Receiver_vals[3] / 10.0 - 5;
      //Serial.println(MOTOR_MIN+(int)(Receiver_vals[2]*12));
    }
    //Serial.println("real received : " + buffer);
    Receiver_debug();
  }
}

void Receiver_debug(){
  
  Serial.print("M7 : ");
  for(int i = 0; i < 5; i++){
    Serial.print(Receiver_vals[i]);
    Serial.print(" ");
  }
  Serial.println("");
}