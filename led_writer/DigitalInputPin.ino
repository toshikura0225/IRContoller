#include "DigitalInputPin.h"

#define KEEPING_TIMER 10

DigitalInputPin::DigitalInputPin(int argNumber)
{
	(*this).pinNumber = argNumber;
	(*this).keepingTimer = 10;
}

DigitalInputPin::DigitalInputPin(int argNumber, int argTimer)
{
	(*this).pinNumber = argNumber;
	(*this).keepingTimer = argTimer;
}


int DigitalInputPin::GetState()
{
  // digitalRead((*this).pinNumber);
  static int keepingCount = 0;		// 状態が連続して安定した回数を
  static int preState = digitalRead((*this).pinNumber);		// 前回の状態
  int currentState = digitalRead((*this).pinNumber);	// 今回測定分の状態
  
  // 状態が連続して安定した回数をインクリメント
  if (currentState == preState)
  {
	  keepingCount++;
  }
  else
  {
	  keepingCount = 0;
  }
  
  // 閾値を超えたら状態変更とする
  if (keepingCount >=(*this).keepingTimer)
  {
	  preState = currentState;
	  keepingCount = (*this).keepingTimer;
  }
  
  return preState;
}

// ピンの状態が変更となったら変更になった状態を返す。
// 変更がない場合は-1を返す
int DigitalInputPin::IsShifted()
{
	static int preState = digitalRead((*this).pinNumber);
	int currentState = (*this).GetState();
	int retValue = -1;
	if (preState != currentState)
	{
		retValue = currentState;
	}
	return retValue;
}
