#include "HobbyRadioReceiver.h"
#include <Servo.h>

#define PIN_COUNT 5
#define MIN_SIGNAL 700
#define MAX_SIGNAL 2000

int Receiver_pins[PIN_COUNT] = {A0, A1, A5, A4, A3};
HobbyRadioReceiver rec(PIN_COUNT, Receiver_pins);
int Receiver_vals[PIN_COUNT];
String buffer;
Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;
void setup()
{
  Serial.begin(9600);
  while (rec.check(4)==-255);
  Serial.read();
  Serial.print('c');
} 

void loop()
{
  buffer = "";
  
  for(int i = 0; i < 5; i++){
    Receiver_vals[i] = rec.check(i+1); 
    buffer += (char)(Receiver_vals[i]/5+52);
  }
  if((int)buffer[1] != 0){
    Serial.print(buffer);
  }
}

void motor_calibration(){
  motor0.attach(2);
  motor1.attach(3);
  motor2.attach(4);
  motor3.attach(5);
 
  motor0.writeMicroseconds(MAX_SIGNAL);
  motor1.writeMicroseconds(MAX_SIGNAL);
  motor2.writeMicroseconds(MAX_SIGNAL);
  motor3.writeMicroseconds(MAX_SIGNAL);
 
  // Wait for input
  while (rec.check(4)==-255);
  Serial.read();
 
  // Send min output
  /*
  motor0.writeMicroseconds(MIN_SIGNAL);
  motor1.writeMicroseconds(MIN_SIGNAL);
  motor2.writeMicroseconds(MIN_SIGNAL);
  motor3.writeMicroseconds(MIN_SIGNAL);
  */
  
  delay(5000);
  motor0.detach();
  motor1.detach();
  motor2.detach();
  motor3.detach();
  Serial.print('c');
}
