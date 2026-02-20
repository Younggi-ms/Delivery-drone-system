#include <Wire.h>
#include <TinyGPS++.h>
#include <Servo.h>
//#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
//#include <Adafruit_MPU6050.h>
//#include <MPU6050_6Axis_MotionApps20.h>
//#include "MPU6050.h"
#include "MPU9250.h"
#include <math.h>

#define MPU_6050_address 0x68
#define BMP085_address 0x77
#define MOTOR_MIN 800
#define MOTOR_MAX 2000

//-------------------------------------------------------------
//moter values
#define MOTOR0 2
#define MOTOR1 3
#define MOTOR2 4
#define MOTOR3 5
Servo motors[4];
int val = 800;
int calculated_speed[4];
int fly_mode = 0;
//0 : 모터의 구동이 완전히 중지된 상태
//1 : 수동 조종 모드
//2 : 자동 조종 모드
//3 : 자동 이륙 모드
//4 : 자동 착륙 모드
bool fly_standby = false;
int landing_delay_time = 500, take_off_delay_time = 500;
unsigned long last_landing_time= 0, last_take_off_time = 0;
int auto_target_throttle = 1400;
//-------------------------------------------------------------
//GPS values
TinyGPSPlus gps;
//-------------------------------------------------------------
//MPU-6050 가속도/자이로 센서 values
MPU9250 mpu;
//Adafruit_MPU6050 mpu;
//sensors_event_t a, g, temp;
double ypr[3]; // 3축 각 값
double gyro[3]; // 각속도 값
int is_updated = 0;
double x_base, y_base;
//-------------------------------------------------------------
//BMP085 기압센서 values
/*
Adafruit_BMP085 bmp;
int32_t pressure, pressure_at_sealevel;
float altitude, real_altitude;
float start_altitude;
*/
//-------------------------------------------------------------
//리시버 통신
int Receiver_vals[5];
int throttle;
//-------------------------------------------------------------
//pid 제어
unsigned long last_time, present_time, time_interval;
//int throttle;
//float ypr[3];
float yprLast[3];
//int16_t gyro[3];

double P_angle_gain_y = 6.5; double P_gain_y = 4.5; double I_gain_y = 0.7; double D_gain_y = 0.135;
double P_angle_gain_x = 6.5; double P_gain_x = 4.5;  double I_gain_x = 0.7; double D_gain_x = 0.135;
double P_angle_gain_z = 4.5; double P_gain_z = 4.5;  double I_gain_z = 0.7; double D_gain_z = 0.135;

/*No need to change*/
double error_y;
double error_pid_y, previous_error_pid_y = 0;
double P_angle_pid_y;
double P_y, I_y, D_y, PID_y;
double desired_angle_y = 0;

/*No need to change*/
double error_x;
double error_pid_x, previous_error_pid_x = 0;
double P_angle_pid_x;
double P_x, I_x, D_x, PID_x;
double desired_angle_x = 0;

/*No need to change*/
double error_z;
double error_pid_z, previous_error_pid_z = 0;
double P_angle_pid_z;
double P_z, I_z, D_z, PID_z;
double desired_angle_z = 0;
//-------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Wire.begin();
  Motor_Setup();
  //MPU_6050_Setup();
  MPU_9250_Setup();
  //BMP085_Setup();
  NEO_6M_Setup();
  last_time = millis();
}

void loop() {
  present_time = millis();
  time_interval = present_time - last_time;
  is_updated = 1;
  //Serial.println(time_interval);
  // put your main code here, to run repeatedly:
  //MPU_6050_Get();
  //MPU_6050_Debug();
  mpu.update();
  MPU_9250_Get();
  //BMP085_Get_Values();
  //BMP085_Debug();
  mpu.update();
  NEO_6M_Get();
  mpu.update();
  Receiver_Get();
  mpu.update();
  //Motor_Move();
  switch (fly_mode) {
    case 0 :
      Motor_Standby();
      break;
    case 1 :
      Manual_control();
      break;
    case 2 :
      Auto_control();
      break;
    case 3 :
      Auto_Take_Off();
      break;
    case 4 :
      Auto_Landing();
      break;
  }
  mpu.update();
  MPU_9250_Debug();
  //mpu.update();
  last_time = present_time;
}