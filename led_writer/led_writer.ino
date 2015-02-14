#include "DigitalInputPin.h"

int ir_out = 2;
int led = 9;
 
// テレビリモコン
unsigned int powerON[] = {899,446,57,54,58,54,58,166,58,54,57,54,58,54,58,54,57,166,58,54,58,54,58,54,58,54,57,54,57,166,58,166,57,165,58,54,57,54,57,54,58,54,57,54,58,166,58,54,58,54,57,166,58,166,58,166,58,166,57,166,57,54,58,166,57,166,58,4320,898,223,57,4829,29};
unsigned int volumeUP[] = {901,442,61,51,63,49,63,160,60,52,60,52,60,52,63,49,60,163,60,52,63,49,60,51,60,51,60,52,60,163,60,163,60,164,60,51,60,52,60,52,63,49,60,52,60,164,63,160,60,52,60,163,60,163,60,163,63,160,60,164,62,49,60,51,63,160,60,4318,904,218,55}; 
unsigned int volumeDOWN[] = {898,446,57,54,58,54,58,166,58,54,58,54,58,54,57,54,58,166,57,54,58,54,58,54,57,54,58,54,57,166,58,166,58,166,58,166,58,54,57,54,58,54,58,54,58,166,58,166,58,54,57,55,57,166,57,166,58,166,58,165,58,54,58,54,58,166,58,4321,898,223,58};
unsigned int channelUP[] = {883,445,57,52,57,52,57,164,57,165,65,44,58,52,57,52,57,52,58,52,57,52,57,165,57,51,58,164,58,164,58,165,57,55,57,165,64,44,58,165,57,52,57,165,57,52,57,52,57,168,57,52,57,165,57,52,57,165,57,52,57,165,57,165,57,53,57,4227,883,222,57};
unsigned int channelDOWN[] = {891,437,58,52,57,52,58,164,58,165,57,52,57,53,56,52,57,51,58,53,57,52,57,165,57,52,58,164,57,164,57,165,57,55,58,52,64,156,57,165,57,52,57,164,57,52,57,51,58,168,57,165,57,52,57,51,58,165,57,52,57,164,58,165,57,53,58,4226,884,222,57};


DigitalInputPin pinPowerON(2);
DigitalInputPin pinVolumeUP(3);
DigitalInputPin pinVolumeDOWN(4);
DigitalInputPin pinChannelUP(5);
DigitalInputPin pinChannelDOWN(6);

unsigned long us = micros();
 
// セットアップ
void setup() {
  pinMode(ir_out, OUTPUT);
  pinMode(led, OUTPUT);
  
}
 
// dataからリモコン信号を送信
void sendSignal(unsigned int data[], int dataSize) {
//  int dataSize = sizeof(data) / sizeof(data[0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); // cntが偶数なら赤外線ON、奇数ならOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
  }
}
 
void loop() {
  
  if(pinPowerON.IsShifted() == HIGH)
  {
    digitalWrite(led, HIGH);
    sendSignal(powerON, sizeof(powerON) / sizeof(powerON[0]));
    digitalWrite(led, LOW);
  }
  else if(pinVolumeUP.IsShifted() == HIGH)
  {
    digitalWrite(led, HIGH);
    sendSignal(volumeUP, sizeof(volumeUP) / sizeof(volumeUP[0]));
    digitalWrite(led, LOW);
  }
  else if(pinVolumeDOWN.IsShifted() == HIGH)
  {
    digitalWrite(led, HIGH);
    sendSignal(volumeDOWN, sizeof(volumeDOWN) / sizeof(volumeDOWN[0]));
    digitalWrite(led, LOW);
  }
  else if(pinChannelUP.IsShifted() == HIGH)
  {
    digitalWrite(led, HIGH);
    sendSignal(channelUP, sizeof(channelUP) / sizeof(channelUP[0]));
    digitalWrite(led, LOW);
  }  
  else if(pinChannelDOWN.IsShifted() == HIGH)
  {
    digitalWrite(led, HIGH);
    sendSignal(channelDOWN, sizeof(channelDOWN) / sizeof(channelDOWN[0]));
    digitalWrite(led, LOW);
  }

}
