#ifndef DigitalInputPin_h
#define DigitalInputPin_h


class DigitalInputPin
{
	public:
		DigitalInputPin(int argNumber);
		DigitalInputPin(int argNumber, int argTimer);
		int GetState();
		int IsShifted();
		int IsShifted(int keepingTimer);
		
	protected:
		int pinNumber;
		int keepingTimer;
};

#endif
