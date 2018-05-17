
#include "Timer.h"

Timer::Timer(unsigned long int ms, void *context){
	this->context = context;
	Create(ms, NULL, false);
}

Timer::Timer(unsigned long int ms, CallBackType callback, void *context){
	this->context = context;
	Create(ms, callback, false);
}

Timer::Timer(unsigned long int ms, CallBackType callback, void *context, bool isSingle){
	this->context = context;
	Create(ms, callback, isSingle);
}

void Timer::Create(unsigned long int ms, CallBackType callback, bool isSingle){
	setInterval(ms);
	setEnabled(false);
	setSingleShot(isSingle);
	setOnTimer(callback);
	LastTime = 0;
}

void Timer::setInterval(unsigned long int ms){
	msInterval = (ms > 0) ? ms : 0;
}

void Timer::setEnabled(bool Enabled){
	blEnabled = Enabled;
}

void Timer::setSingleShot(bool isSingle){
	blSingleShot = isSingle;
}

void Timer::setOnTimer(CallBackType callback){
	onRun = callback;
}

void Timer::Start(){
	LastTime = millis();
	setEnabled(true);
}

void Timer::Resume(){
	LastTime = millis() - DiffTime;
	setEnabled(true);
}

void Timer::Stop(){
	setEnabled(false);

}

void Timer::Pause(){
	DiffTime = millis() - LastTime;
	setEnabled(false);

}

void Timer::Update(){
	if(Tick())
		onRun(this->context);
}

bool Timer::Tick(){
	if(!blEnabled)
		return false;
	if(LastTime > millis()*2)//millis restarted
		LastTime = 0;
	if ((unsigned long int)(millis() - LastTime) >= msInterval) {
		LastTime = millis();
		if(isSingleShot())
			setEnabled(false);
	    return true;
	}
	return false;
}


unsigned long int Timer::getInterval(){
	return msInterval;
}

unsigned long int Timer::getCurrentTime(){
	return (unsigned long int)(millis() - LastTime);
}

unsigned long int Timer::getRemaining() {
	if (blEnabled) {
		return msInterval - (unsigned long int)(millis() - LastTime);
	} else {
		return msInterval - (unsigned long int)(millis() - (millis() - DiffTime));
	}
}

CallBackType Timer::getOnTimerCallback(){
	return onRun;
}

bool Timer::isEnabled(){
	return blEnabled;
}

bool Timer::isSingleShot(){
	return blSingleShot;
}
