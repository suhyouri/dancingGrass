// 모터 A 핀 정의
int Dir1Pin_A = 8;      // 제어 신호 1번 핀 (IN1)
int Dir2Pin_A = 9;      // 제어 신호 2번 핀 (IN2)
int SpeedPin_A = 10;    // 모터 속도 제어를 위한 PWM 핀 (ENA)

// 모터 B 핀 정의
int Dir1Pin_B = 4;      // 제어 신호 1번 핀 (IN1)
int Dir2Pin_B = 5;      // 제어 신호 2번 핀 (IN2)
int SpeedPin_B = 6;     // 모터 속도 제어를 위한 PWM 핀 (ENA)

// 모터 A 상태를 나타내는 플래그
enum MotorState { FORWARD, STOP1, REVERSE, STOP2 };
MotorState motorState = FORWARD;

unsigned long previousMillis = 0;  // 이전 시간 저장
const unsigned long interval1 = 500;  // FORWARD, REVERSE 상태 지속 시간 (500ms)
const unsigned long interval2 = 100;  // STOP 상태 지속 시간 (100ms)

void setup() {
  // 모터 A 핀 모드 설정
  pinMode(Dir1Pin_A, OUTPUT);
  pinMode(Dir2Pin_A, OUTPUT);
  pinMode(SpeedPin_A, OUTPUT);

  // 모터 B 핀 모드 설정
  pinMode(Dir1Pin_B, OUTPUT);
  pinMode(Dir2Pin_B, OUTPUT);
  pinMode(SpeedPin_B, OUTPUT);

  // 모터 B 정방향 회전 초기화
  digitalWrite(Dir1Pin_B, HIGH);  // IN1 신호 ON
  digitalWrite(Dir2Pin_B, LOW);   // IN2 신호 OFF
  analogWrite(SpeedPin_B, 255);   // 속도 255
}

void loop() {
  unsigned long currentMillis = millis();

  // 모터 A 상태에 따른 동작 수행
  switch (motorState) {
    case FORWARD:
      // 모터 A 정방향 회전
      digitalWrite(Dir1Pin_A, HIGH);  // IN1 신호 ON
      digitalWrite(Dir2Pin_A, LOW);   // IN2 신호 OFF
      analogWrite(SpeedPin_A, 255);   // 속도 255

      // 일정 시간이 지나면 STOP1 상태로 전환
      if (currentMillis - previousMillis >= interval1) {
        previousMillis = currentMillis;
        motorState = STOP1;
      }
      break;

    case STOP1:
      // 모터 A 정지
      digitalWrite(Dir1Pin_A, LOW);
      digitalWrite(Dir2Pin_A, LOW);

      // 일정 시간이 지나면 REVERSE 상태로 전환
      if (currentMillis - previousMillis >= interval2) {
        previousMillis = currentMillis;
        motorState = REVERSE;
      }
      break;

    case REVERSE:
      // 모터 A 역방향 회전
      digitalWrite(Dir1Pin_A, LOW);   // IN1 신호 OFF
      digitalWrite(Dir2Pin_A, HIGH);  // IN2 신호 ON
      analogWrite(SpeedPin_A, 255);   // 속도 255

      // 일정 시간이 지나면 STOP2 상태로 전환
      if (currentMillis - previousMillis >= interval1) {
        previousMillis = currentMillis;
        motorState = STOP2;
      }
      break;

    case STOP2:
      // 모터 A 정지
      digitalWrite(Dir1Pin_A, LOW);
      digitalWrite(Dir2Pin_A, LOW);

      // 일정 시간이 지나면 FORWARD 상태로 전환
      if (currentMillis - previousMillis >= interval2) {
        previousMillis = currentMillis;
        motorState = FORWARD;
      }
      break;
  }

  // 모터 B는 멈춤 없이 계속 정방향 회전
  digitalWrite(Dir1Pin_B, HIGH);  // IN1 신호 ON
  digitalWrite(Dir2Pin_B, LOW);   // IN2 신호 OFF
  analogWrite(SpeedPin_B, 255);   // 속도 255
}
