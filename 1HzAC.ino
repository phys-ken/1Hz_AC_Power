//モータードライバーとして、DRV8835を使用
//TODO:OLEDに表示する

#define PIN_IN1 4
#define PIN_IN2 5
#define PIN_VREF 3 // PWM
const int INPUT_PIN = A0;
int VOLUME;

int val = 0;
int old_val = 0;
int state = 0;
float fq = 1;
float volvol;

void setup()
{
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  VOLUME = analogRead(INPUT_PIN); // アナログ値の読み取り
  Serial.print("Volume: ");       // シリアルモニタに出力
  Serial.println(VOLUME);

  fq = map(VOLUME, 0, 1023, 1, 10); //VOLUMEに合わせて振動数を1～10に変更
  Serial.println(fq);

  //前進
  Serial.println("forward!");
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  delay(500 / fq);

  //後進
  Serial.println("back!");
  // 逆回転
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  delay(500 / fq);
}

//void loop(){
//
//    // モーターの回転速度を中間にする
//    analogWrite(PIN_VREF,127);
//
//    if(digitalRead(INPUT_PIN) == HIGH){ // 入力ピン(タクトスイッチ)の状態を読み取る
//      Serial.println("forward!");
//      // 回転
//      digitalWrite(PIN_IN1,HIGH);
//      digitalWrite(PIN_IN2,LOW);
//    } else {
//      Serial.println("back!");
//      // 逆回転
//      digitalWrite(PIN_IN1,LOW);
//      digitalWrite(PIN_IN2,HIGH);
//    }

//
//    // 回転
//    digitalWrite(PIN_IN1,HIGH);
//    digitalWrite(PIN_IN2,LOW);
//    delay(5000);
//
//    // ブレーキ
//    digitalWrite(PIN_IN1,HIGH);
//    digitalWrite(PIN_IN2,HIGH);
//
//    // 逆回転
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(5000);
//
//    // ブレーキ
//    digitalWrite(PIN_IN1,HIGH);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(2000);
//
//    // モーターの回転速度を最大にする
//    analogWrite(PIN_VREF,255);
//
//    // 逆回転　
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,HIGH);
//    delay(5000);
//
//    // ストップ
//    digitalWrite(PIN_IN1,LOW);
//    digitalWrite(PIN_IN2,LOW);
//    delay(2000);
//}
