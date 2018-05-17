/*
 * AutoFire.cpp
 *
 *  Created on: 15. 5. 2018
 *      Author: aluchava
 */

#include "AutoFire.h"

AutoFire::AutoFire(CallBackType onFire, void *context)
{
	this->onFire = onFire;
	this->context = context;

	// init timer;
	timer = new Timer(onStateDuration, this);
	timer->setOnTimer(&AutoFire::OnTimer);
	timer->setSingleShot(true);
}

AutoFire::~AutoFire()
{
}

//------------------------------------------------------------
//
// Methods
//
//------------------------------------------------------------

bool AutoFire::getState()
{
	return state;
}

void AutoFire::Start()
{
	state = true;
	timer->setInterval(onStateDuration);
	timer->Start();
}

void AutoFire::Stop()
{
	state = false;
	timer->Stop();
}

void AutoFire::Update()
{
	timer->Update();
}

void AutoFire::Callback()
{
	// switch state;
	state = !state;

	// callback;
	onFire(this->context);

	// new cycle;
	if(state)
	{
		timer->setInterval(onStateDuration);
	}
	else
	{
		timer->setInterval(offStateDuration);
	}
	timer->Start();
}

void AutoFire::OnTimer(void *context)
{
	AutoFire *autoFire = (AutoFire *)context;
	autoFire->Callback();
}
