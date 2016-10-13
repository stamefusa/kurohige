#include <Servo.h>

Servo servo1, servo2;
int num1 = 0, num2 = 0;
int val = 0, pre = 0, diff = 0;
int cnt = 0;
int vals[3] = {0, 0, 0};
 
void setup(){
  servo1.attach(7);
  servo2.attach(8);
  num1 = 100;
  motor1(num1);
  num2 = 60;
  motor2(num2);
  Serial.begin(9600);
}

void loop(){
  //val = analogRead(0);
  vals[cnt] = analogRead(0);
  val = calcAve();
  diff = val - pre;
  Serial.println(diff);
   
  if (diff > 200) {
    num1 = 60;
    num2 = 100;
  } 
  else if (diff < -200) {
    num1 = 100;
    num2 = 60;
  }
  motor1(num1);
  motor2(num2);

  pre = val;
  cnt = (cnt+1)%3;

  delay(30);
}

void motor1(int num) {
  servo1.write(num);
}

void motor2(int num) {
  servo2.write(num);
}

int calcAve()
{
  int tmp = 0;
  for (int i=0; i<3; i++) {
    tmp += vals[i];
  }
  return (int)tmp/3;
}

