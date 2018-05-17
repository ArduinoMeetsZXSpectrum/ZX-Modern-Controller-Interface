
#include "stdlib.h"
#include "Arduino.h"

#ifndef TIMER_H
#define TIMER_H
typedef void (*CallBackType)(void *context);


class Timer{
private:
	void Create(unsigned long int ms, CallBackType callback, bool isSingle);
	unsigned long int msInterval;
	bool blEnabled;
	bool blSingleShot;
	CallBackType onRun;
	bool Tick();
	unsigned long LastTime;
	unsigned long DiffTime;//used when I pause the Timer and need to resume
	void *context;

public:
	Timer(unsigned long int ms, void *context);
	Timer(unsigned long int ms, CallBackType callback, void *context);
	Timer(unsigned long int ms, CallBackType callback, void *context, bool isSingle);
	~Timer();

	void setInterval(unsigned long int ms);
	void setEnabled(bool Enabled);
	void setSingleShot(bool isSingle);
	void setOnTimer(CallBackType callback);
	void Start();
	void Resume();
	void Pause();
	void Stop();
	void Update();

	unsigned long int getInterval();
	unsigned long int getCurrentTime();
	unsigned long int getRemaining();
	CallBackType getOnTimerCallback();

	bool isEnabled();
	bool isSingleShot();

};


#endif // TIMER_H
