//モータードライバーとして、DRV8835を使用
//TODO:OLEDに表示する
//ESP32用で作成

#define PIN_IN1 32 //esp32の32pin
#define PIN_IN2 33 //esp33の33pin
const int INPUT_PIN = A19; //esp32の26pin
int VOLUME;

int val = 0;
int old_val = 0;
int state = 0;
float fq = 1;
float volvol;

int setsize = 10;
int sinw[10]; //180の約数じゃないとだめ,配列数はsetsizeとそろえる。

int InductorU = 0;
int InductorV = setsize / 2;
int ang;
int MODE;
int mag;
float d;
float in1, in2;

void setup()
{

  Serial.begin(9600);
  Serial.println("start");

  //esp32用のPWM設定
  ledcSetup(0, 12800, 8);
  ledcAttachPin(PIN_IN1, 0);

  ledcSetup(1, 12800, 8);
  ledcAttachPin(PIN_IN2, 1);

  //setsizeに分割したsinのテーブルを作成
  mag = 170; //0～255の範囲で設定
  int stepsize = 360 / setsize;
  for (ang = 0; ang < 360; ang = ang + stepsize)
  {
    sinw[ang / stepsize] = mag * (sin(ang * 3.14 / 180));
  }
}

void loop()
{

  VOLUME = analogRead(INPUT_PIN); // アナログ値の読み取り
  //Serial.print("Volume: ");       // シリアルモニタに出力
  //Serial.println(VOLUME);

  fq = map(VOLUME, 0, 4095, 1, 10); //VOLUMEに合わせて振動数を1～3に変更
  Serial.print("freq[Hz]: ");
  Serial.println(fq);
  if (fq >= 0.001)
  {
    d = 1.0 / (fq * setsize);
    //Serial.print("DelayTime[ms]: ");
    //Serial.println(d * 1000);
  }
  else if (fq < 0.001) //0で割らないように
  {
    d = 0.01;
  }

  //sinwが負のときには出力しない
  if (sinw[InductorU] < 1)
  {
    in1 = 0;
  }
  else
  {
    in1 = sinw[InductorU];
  }

  if (sinw[InductorV] < 1)
  {
    in2 = 0;
  }
  else
  {
    in2 = sinw[InductorV];
  }

  //sinw[]で指定した強度で、PWM出力
  ledcWrite(0, in1);
  ledcWrite(1, in2);
  InductorV = update_phase(InductorV);
  InductorU = update_phase(InductorU);

  //dだけ遅延する。
  delay(d * 1000);

  //delay(1000);//debug用
}

//inductorを進める
int update_phase(int Inductor)
{
  Inductor = Inductor + 1;
  if (Inductor >= setsize)
    Inductor = 0;
  return Inductor;
}
