#include <Servo.h>

#define MODE_STAY 0
#define MODE_JUMP 1
#define MODE_BEFORE 9

Servo servo1, servo2;
int num1 = 0, num2 = 0;
int val = 0, pre = 0, diff = 0;
int cnt = 0;
int vals[3] = {0, 0, 0};
int mode = MODE_STAY;
unsigned long jump_start_time = 0;
 
void setup(){
  servo1.attach(7);
  servo2.attach(8);
  num1 = 80;
  num2 = 80;
  motor1(num1);
  motor2(num2);
  Serial.begin(9600);
  
  jump_start_time = millis();
  mode = MODE_BEFORE;
}

void loop(){
  vals[cnt] = analogRead(0);
  val = calcAve();
  diff = val - pre;
  Serial.println(diff);
   
  if (diff > 100 && mode == MODE_STAY) {
    mode = MODE_JUMP;
    Serial.println("JUMP!!!!");
    jump_start_time = millis();
    num1 = 40;
    num2 = 120;
  } 
  else if (diff < -100 && mode == MODE_STAY) {
    Serial.println("STAY!!!!");
    num1 = 80;
    num2 = 80;
  }
  motor1(num1);
  motor2(num2);

  if ((mode == MODE_JUMP || mode == MODE_BEFORE) && millis() - jump_start_time > 300) {
    mode = MODE_STAY;
    Serial.println("RESET MODE");
  }

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
