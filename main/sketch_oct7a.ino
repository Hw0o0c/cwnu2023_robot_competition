/*
모터 드라이브 : MDD10A
모터:
적외선 센서:  GP2Y0D805Z0F
아두이노: 아두이노 우노(아마)
*/

//sensor pins
#define infrared_L A7 // 왼쪽 적외선 센서
#define infrared_R A6 // 오른쪽 적외선 센서

int trig_ff = 6; // 정면 초음파 트리거
int echo_ff = 5; // 정면 초음파 에코
int trig_fr = 4; // 우측 초음파 트리거
int echo_fr = 3;// 우측 초음파 에코
int trig_fl = 2; // 좌측 초음파 트리거
int echo_fl = 1;// 좌측 초음파 에코
//motor pins(dir = 방향, pwm = 속도(0~255))
int L_dir = 10;
int L_pwm = 9;
int R_dir = 8;
int R_pwm = 7;


//목표물과의 최대 거리, 600은 임시로 넣은 것
int enemy_dis = 400;
int vh = 500;
//경기장의 출발선을 고려해서 회전은 오른쪽으로 해야함. 
//우측 회전을 기본으로 하되 정면센서가 감지가 안되고 좌측센서가 감지가 되었다면 정면이 감지될 때까지 좌회전
//회전 => 목표물 발견 => 모터 작동 
void setup() {
  pinMode(echo_ff, INPUT);
  pinMode(trig_ff, OUTPUT);
  pinMode(echo_fr, INPUT);
  pinMode(trig_fr, OUTPUT);
  pinMode(echo_fl, INPUT);
  pinMode(trig_fl, OUTPUT);
  pinMode(infrared_L, INPUT);
  pinMode(infrared_R, INPUT);

  pinMode(L_dir, OUTPUT);
  pinMode(R_dir, OUTPUT);
  pinMode(L_pwm, OUTPUT);
  pinMode(R_pwm, OUTPUT);

  analogWrite(L_pwm, 0);
  analogWrite(R_pwm, 0);
}

//거리 측정 함수, 단위 cm
int dis_m(int trig, int echo) {
  float len, dis;

  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(2);
  digitalWrite(trig, LOW);
  
  len = pulseIn(echo, HIGH);
  dis = ((float)(340 * len) / 10000) / 2;

  return dis;
}

// 도는 함수
void rotate(){
  digitalWrite(L_dir, HIGH);
  digitalWrite(R_dir, LOW);
  analogWrite(L_pwm, 255);
  analogWrite(R_pwm, 255);
}

void rotate_left(){
  digitalWrite(L_dir, LOW);
  digitalWrite(R_dir, HIGH);
  analogWrite(L_pwm, 255);
  analogWrite(R_pwm, 255);
}

//앞으로 가는 함수
void move_forward(){
  digitalWrite(L_dir, HIGH);
  digitalWrite(R_dir, HIGH);

  analogWrite(L_pwm, 255);
  analogWrite(R_pwm, 255);
}

void loop() {
  //정면 감지를 최우선으로 함.
  if(dis_m(trig_ff, echo_ff) < enemy_dis){
    move_forward();
  }
  else{
    //우측센서가 감지했을 때를 두번째 우선순위로 둔다.(회전 방향을 바꿔야 하기 때문);
    if (dis_m(trig_fr, echo_fr) < dis_m(trig_fl, echo_fr)){
      //좌측센서나 정면센서가 감지될 때까지 반복한다.
      while(dis_m(trig_fl, echo_fr) < enemy_dis || dis_m(trig_ff, echo_ff) < enemy_dis){
        rotate_left();
      }
    }
    else rotate();
  }
}
