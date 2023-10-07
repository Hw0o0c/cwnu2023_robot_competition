/*
앞 뒤에 초음파 센서를 달아 만든 알고리즘
모터 드라이브 : MDD10A
모터:
적외선 센서:  GP2Y0D805Z0F
아두이노: 아두이노 우노(아마)
*/

//sensor pins
#define trig_f A5 // 앞쪽 초음파 트리거
#define echo_f A4 // 앞쪽 초음파 에코
#define trig_b A3 // 뒤쪽 초음파 트리거
#define echo_b A2 // 뒤쪽 초음파 에코

#define infrared_L A1 // 왼쪽 적외선 센서
#define infrared_R A0 // 오른쪽 적외선 센서

//motor pins(dir = 방향, pwm = 속도(0~255))
const int LMF_dir = 10;
const int LMF_pwm = 9;
const int LMB_dir = 8;
const int LMB_pwm = 7;
const int RMB_dir = 6;
const int RMF_pwm = 5;
const int RMB_dir = 4;
const int RMF_pwm = 3;


//목표물과의 최대 거리, 600은 임시로 넣은 것
int enemy_dis = 600;
int vh = 500;
//경기장의 출발선을 고려해서 회전은 오른쪽으로 해야함.
//회전 => 목표물 발견 => 모터 작동 
void setup() {
  pinMode(echo_f, INPUT);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_b, INPUT);
  pinMode(trig_b, OUTPUT);
  pinMode(infrared_L, INPUT);
  pinMode(infrared_R, INPUT);

  pinMode(LMF_dir, OUTPUT);
  pinMode(LMB_dir, OUTPUT);
  pinMode(RMF_dir, OUTPUT);
  pinMode(RMB_dir, OUTPUT);
  pinMode(LMF_pwm, OUTPUT);
  pinMode(LMB_pwm, OUTPUT);
  pinMode(RMF_pwm, OUTPUT);
  pinMode(RMB_pwm, OUTPUT);

  analogWrite(LMF_pwm, 0);
  analogWrite(RMF_pwm, 0);
  analogWrite(LMB_pwm, 0);
  analogWrite(RMB_pwm, 0);
}


void loop() {
  int front = dis_m(trig_f, echo_f);
  int back = dis_m(trig_b, echo_b); 
  if(front > enemy_dis && back > enemy_dis){
    //앞측과 뒤측의 거리가 설정한 거리보다 클 때
    rotate();
    int iL = analogeRead(infrared_L);
    int iR = analogeRead(infrared_R);
    if (iL > 500) escape_right();
    else if (iR > 500) escape_left();
    delay(50);
  }
  else{
    //앞측거리가 뒤측거리보다 짧을 때
    if (front < back) move_forward();
    else move_backward();
    delay(500);
  }
}

//거리 측정 함수, 단위 cm
int dis_m(trig, echo) {
  float len, dis;

  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  len = pulseIn(echo, HIGH);
  dis = ((float)(340 * len) / 10000) / 2;

  return dis;
}

// 도는 함수
void rotate(){
  digitalWrite(LMF_dir, HIGH);
  digitalWrite(RMF_dir, LOW);
  digitalWrite(LMB_dir, HIGH);
  digitalWrite(RMB_dir, LOW);

  analogWrite(LMF_pwm, 255);
  analogWrite(RMF_pwm, 255);
  analogWrite(LMB_pwm, 255);
  analogWrite(RMB_pwm, 255);
}

//앞으로 가는 함수
void move_forward(){
  digitalWrite(LMF_dir, HIGH);
  digitalWrite(RMF_dir, HIGH);
  digitalWrite(LMB_dir, HIGH);
  digitalWrite(RMB_dir, HIGH);

  analogWrite(LMF_pwm, 255);
  analogWrite(RMF_pwm, 255);
  analogWrite(LMB_pwm, 255);
  analogWrite(RMB_pwm, 255);
}

void move_backward(){
  digitalWrite(LMF_dir, LOW);
  digitalWrite(RMF_dir, LOW);
  digitalWrite(LMB_dir, LOW);
  digitalWrite(RMB_dir, LOW);

  analogWrite(LMF_pwm, 255);
  analogWrite(RMF_pwm, 255);
  analogWrite(LMB_pwm, 255);
  analogWrite(RMB_pwm, 255);
}

void escape_right(){
  digitalWrite(LMF_dir, HIGH);
  digitalWrite(RMF_dir, HIGH);
  digitalWrite(LMB_dir, HIGH);
  digitalWrite(RMB_dir, HIGH);

  analogWrite(LMF_pwm, 255);
  analogWrite(RMF_pwm, 120);
  analogWrite(LMB_pwm, 255);
  analogWrite(RMB_pwm, 120);

  delay(1000);
}

void escape_left(){
  digitalWrite(LMF_dir, HIGH);
  digitalWrite(RMF_dir, HIGH);
  digitalWrite(LMB_dir, HIGH);
  digitalWrite(RMB_dir, HIGH);

  analogWrite(LMF_pwm, 120);
  analogWrite(RMF_pwm, 255);
  analogWrite(LMB_pwm, 120);
  analogWrite(RMB_pwm, 255);

  delay(1000);
}

