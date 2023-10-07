#include <Servo.h>
#include <NewPing.h>
Servo servo;

//sensor pins
#define trig_pin A3
#define echo_pin A2

//motor pins
const int LMotorF = 5;
const int LMotorB = 4;
const int RMotorF = 3;
const int RMotorB = 2;

//타겟이 정해졌는가.
boolean target = false;

//경기장의 출발선을 고려해서 회전은 오른쪽으로 해야함.
//회전 => 목표물 발견 => 모터 작동 
void setup() {
  pinMode(LMotorF, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(RMotorF, OUTPUT);
  pinMode(RMotorB, OUTPUT);
}

void loop() {
  //거리 측정
  if(target == false){
    rotate();
  }
}

void reset() {
  
}

void rotate(){
  digitalWrite(LMotorF, HIGH);
  digitalWrite(RMotorB, HIGH);
}

void move_forward(){
  digitalWrite(LMotorF, HIGH);
  digitalWrite(RMotorF, HIGH);
}
