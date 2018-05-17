/*
 * AutoFire.h
 *
 *  Created on: 15. 5. 2018
 *      Author: aluchava
 */

#ifndef AUTOFIRE_H_
#define AUTOFIRE_H_

#include "Timer.h"

class AutoFire
{
	Timer *timer;
	CallBackType onFire;
	void *context;
	bool state = false;

	const int onStateDuration = 50;
	const int offStateDuration = 150;

	public:
		AutoFire(CallBackType onFire, void *context);
		virtual ~AutoFire();

		bool getState();

		void Start();
		void Stop();
		void Update();
		void Callback();
		static void OnTimer(void *context);
};

#endif /* AUTOFIRE_H_ */
