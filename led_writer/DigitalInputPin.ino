#include "DigitalInputPin.h"

#define KEEPING_TIMER 10

DigitalInputPin::DigitalInputPin(int argNumber)
{
	(*this).pinNumber = argNumber;
	(*this).keepingTimer = 10;
        pinMode(pinNumber, INPUT_PULLUP);
}

DigitalInputPin::DigitalInputPin(int argNumber, int argTimer)
{
	(*this).pinNumber = argNumber;
	(*this).keepingTimer = argTimer;
        pinMode(pinNumber, INPUT_PULLUP);
}


int DigitalInputPin::GetState()
{
  // digitalRead((*this).pinNumber);
  static int keepingCount = 0;		// 状態が連続して安定した回数を
  static int preState = digitalRead((*this).pinNumber);		// 前回の状態
  static int keepingState = preState;
  int currentState = digitalRead((*this).pinNumber);	// 今回測定分の状態
  
  // 状態が連続して安定した回数をインクリメント
  if (preState == currentState)
  {
	  keepingCount++;

      // 閾値を超えたら状態変更とする
      if (keepingCount >=(*this).keepingTimer)
      {
              keepingState = currentState;
    	  keepingCount = (*this).keepingTimer;
      }
  }
  else
  {
	  keepingCount = 0;
  }
  
  Serial.println(keepingCount);
    

  
  preState = currentState;
  
  return keepingState;
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
	preState = currentState;
	return retValue;
}
