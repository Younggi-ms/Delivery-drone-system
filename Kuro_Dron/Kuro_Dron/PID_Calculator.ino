/*
  0
3 + 1
  2
*/

/* Y-direction P + PID */

void PID_control_y() {

  error_y = desired_angle_y - ypr[1]; //angle def
  P_angle_pid_y = P_angle_gain_y * error_y; //angle def + outer P control

  error_pid_y = P_angle_pid_y + gyro[1]; // Pcontrol_angle - angle rate = PID Goal

  P_y = error_pid_y * P_gain_y; // Inner P control
  D_y = (error_pid_y - previous_error_pid_y) / time_interval * D_gain_y / 1000; // Inner D control
  I_y += (error_pid_y) * time_interval * I_gain_y / 1000; // Inner I control
  I_y = constrain(I_y, -100, 100); // I control must be limited to prevent being jerk.

  PID_y = P_y + D_y + I_y;
  calculated_speed[0] = PID_y;
  calculated_speed[2] = -PID_y;
  
  previous_error_pid_y = error_pid_y;

}


/* X-direction P + PID */

void PID_control_x() {
  error_x = desired_angle_x - ypr[2]; //angle def
  P_angle_pid_x = P_angle_gain_x * error_x; //angle def + outer P control

  error_pid_x = P_angle_pid_x - gyro[0]; // Pcontrol_angle - angle rate = PID Goal

  P_x = error_pid_x * P_gain_x; // Inner P control
  D_x = (error_pid_x - previous_error_pid_x) / time_interval * D_gain_x / 1000; // Inner D control
  I_x += (error_pid_x) * time_interval * I_gain_x / 1000; // Inner I control
  I_x = constrain(I_x, -100, 100); // I control must be limited to prevent being jerk.

  PID_x = P_x + D_x + I_x;
  calculated_speed[1] = PID_x;
  calculated_speed[3] = -PID_x;

  previous_error_pid_x = error_pid_x;

}

/* Z-direction P + PID */

void PID_control_z() {
  error_z = desired_angle_z - ypr[0]; //angle def
  P_angle_pid_z = P_angle_gain_z * error_z; //angle def + outer P control

  error_pid_z = P_angle_pid_z - gyro[2]; // Pcontrol_angle - angle rate = PID Goal

  P_z = error_pid_z * P_gain_z; // Inner P control
  D_z = (error_pid_z - previous_error_pid_z) / time_interval * D_gain_z / 1000; // Inner D control
  I_z += (error_pid_z) * time_interval * I_gain_z / 1000; // Inner I control
  I_z = constrain(I_z, -100, 100); // I control must be limited to prevent being jerk.

  PID_z = P_z + D_z + I_z;
  calculated_speed[0] += PID_z;
  calculated_speed[1] -= PID_z;
  calculated_speed[2] += PID_z;
  calculated_speed[3] -= PID_z;

  previous_error_pid_z = error_pid_z;

}

void PID_Variable_Clear(){
  I_x = 0;
  I_y = 0;
  I_z = 0;
}
