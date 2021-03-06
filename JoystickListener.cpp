/*
 * JoystickReportParserImpl.cpp
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */

#include "JoystickListener.h"

JoystickListener::JoystickListener(JoystickConnector *connector1, JoystickConnector *connector2)
{
	this->connector1 = connector1;
	this->connector2 = connector2;

	// init autoFire;
	autoFire1 = new AutoFire(&JoystickListener::OnAutoFire1, this);
	autoFire2 = new AutoFire(&JoystickListener::OnAutoFire2, this);
}

JoystickListener::~JoystickListener()
{
}

//------------------------------------------------------------
//
// Methods
//
//------------------------------------------------------------

void JoystickListener::onGamePadChanged(const GamePadEventData *evt)
{
	Serial.print("X1: ");
	PrintHex<uint8_t>(evt->X, 0x80);
	Serial.print("\tY1: ");
	PrintHex<uint8_t>(evt->Y, 0x80);
	Serial.print("\tX2: ");
	PrintHex<uint8_t>(evt->Z1, 0x80);
	Serial.print("\tY2: ");
	PrintHex<uint8_t>(evt->Z2, 0x80);
	Serial.print("\tRz: ");
	PrintHex<uint8_t>(evt->Rz, 0x80);
	Serial.println("");
}

void JoystickListener::onButtonUp(uint8_t button)
{
	// connector1;
	if (button == this->connector1->getJoystickMapping()->getFire1())
	{
		Serial.println("connector1 fire1 released");
		con1Fire1Pressed = false;
		if(!autoFire1->getState())
			digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	if (button == this->connector1->getJoystickMapping()->getAutoFire1())
	{
		Serial.println("connector1 autoFire1 released");
		autoFire1->Stop();
		if(!con1Fire1Pressed)
			digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	// connector2;
	if (button == this->connector2->getJoystickMapping()->getFire1())
	{
		Serial.println("connector2 fire1 released");
		con2Fire1Pressed = false;
		if(!autoFire2->getState())
			digitalWrite(this->connector2->getFire1Pin(), LOW);
	}

	if (button == this->connector2->getJoystickMapping()->getAutoFire1())
	{
		Serial.println("connector2 autoFire1 released");
		autoFire2->Stop();
		if(!con2Fire1Pressed)
			digitalWrite(this->connector2->getFire1Pin(), LOW);
	}
}

void JoystickListener::onButtonDown(uint8_t button)
{
	// connector1;
	if (button == this->connector1->getJoystickMapping()->getFire1())
	{
		Serial.println("connector1 fire1 pressed");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
		con1Fire1Pressed = true;
	}

	if (button == this->connector1->getJoystickMapping()->getAutoFire1())
	{
		Serial.println("connector1 autoFire1 pressed");
		autoFire1->Start();
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
	}

	// connector2;
	if (button == this->connector2->getJoystickMapping()->getFire1())
	{
		Serial.println("connector2 fire1 pressed");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
		con2Fire1Pressed = true;
	}

	if (button == this->connector2->getJoystickMapping()->getAutoFire1())
	{
		Serial.println("connector2 autoFire1 pressed");
		autoFire2->Start();
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
	}
}

void JoystickListener::onDPadDown(uint8_t dpad)
{
	// connector1;

	if (dpad == this->connector1->getJoystickMapping()->getUp())
	{
		Serial.println("connector1 up pressed");
		digitalWrite(this->connector1->getUpPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getUpRight())
	{
		Serial.println("connector1 up-right pressed");
		digitalWrite(this->connector1->getUpPin(), HIGH);
		digitalWrite(this->connector1->getRightPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getRight())
	{
		Serial.println("connector1 right pressed");
		digitalWrite(this->connector1->getRightPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getRightDown())
	{
		Serial.println("connector1 right-down pressed");
		digitalWrite(this->connector1->getRightPin(), HIGH);
		digitalWrite(this->connector1->getDownPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getDown())
	{
		Serial.println("connector1 down pressed");
		digitalWrite(this->connector1->getDownPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getDownLeft())
	{
		Serial.println("connector1 down-left pressed");
		digitalWrite(this->connector1->getDownPin(), HIGH);
		digitalWrite(this->connector1->getLeftPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getLeft())
	{
		Serial.println("connector1 left pressed");
		digitalWrite(this->connector1->getLeftPin(), HIGH);
	}

	if (dpad == this->connector1->getJoystickMapping()->getLeftUp())
	{
		Serial.println("connector1 left-up pressed");
		digitalWrite(this->connector1->getLeftPin(), HIGH);
		digitalWrite(this->connector1->getUpPin(), HIGH);
	}

	// connector2;

	if (dpad == this->connector2->getJoystickMapping()->getUp())
	{
		Serial.println("connector2 up pressed");
		digitalWrite(this->connector2->getUpPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getUpRight())
	{
		Serial.println("connector2 up-right pressed");
		digitalWrite(this->connector2->getUpPin(), HIGH);
		digitalWrite(this->connector2->getRightPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getRight())
	{
		Serial.println("connector2 right pressed");
		digitalWrite(this->connector2->getRightPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getRightDown())
	{
		Serial.println("connector2 right-down pressed");
		digitalWrite(this->connector2->getRightPin(), HIGH);
		digitalWrite(this->connector2->getDownPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getDown())
	{
		Serial.println("connector2 down pressed");
		digitalWrite(this->connector2->getDownPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getDownLeft())
	{
		Serial.println("connector2 down-left pressed");
		digitalWrite(this->connector2->getDownPin(), HIGH);
		digitalWrite(this->connector2->getLeftPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getLeft())
	{
		Serial.println("connector2 left pressed");
		digitalWrite(this->connector2->getLeftPin(), HIGH);
	}

	if (dpad == this->connector2->getJoystickMapping()->getLeftUp())
	{
		Serial.println("connector2 left-up pressed");
		digitalWrite(this->connector2->getLeftPin(), HIGH);
		digitalWrite(this->connector2->getUpPin(), HIGH);
	}
}

void JoystickListener::onDPadUp(uint8_t dpad)
{
	// connector1;

	if (dpad == this->connector1->getJoystickMapping()->getUp())
	{
		Serial.println("connector1 up released");
		digitalWrite(this->connector1->getUpPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getUpRight())
	{
		Serial.println("connector1 up-right released");
		digitalWrite(this->connector1->getUpPin(), LOW);
		digitalWrite(this->connector1->getRightPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getRight())
	{
		Serial.println("connector1 right released");
		digitalWrite(this->connector1->getRightPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getRightDown())
	{
		Serial.println("connector1 right-down released");
		digitalWrite(this->connector1->getRightPin(), LOW);
		digitalWrite(this->connector1->getDownPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getDown())
	{
		Serial.println("connector1 down released");
		digitalWrite(this->connector1->getDownPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getDownLeft())
	{
		Serial.println("connector1 down-left released");
		digitalWrite(this->connector1->getDownPin(), LOW);
		digitalWrite(this->connector1->getLeftPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getLeft())
	{
		Serial.println("connector1 left released");
		digitalWrite(this->connector1->getLeftPin(), LOW);
	}

	if (dpad == this->connector1->getJoystickMapping()->getLeftUp())
	{
		Serial.println("connector1 left-up released");
		digitalWrite(this->connector1->getLeftPin(), LOW);
		digitalWrite(this->connector1->getUpPin(), LOW);
	}

	// connector2;

	if (dpad == this->connector2->getJoystickMapping()->getUp())
	{
		Serial.println("connector2 up released");
		digitalWrite(this->connector2->getUpPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getUpRight())
	{
		Serial.println("connector2 up-right released");
		digitalWrite(this->connector2->getUpPin(), LOW);
		digitalWrite(this->connector2->getRightPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getRight())
	{
		Serial.println("connector2 right released");
		digitalWrite(this->connector2->getRightPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getRightDown())
	{
		Serial.println("connector2 right-down released");
		digitalWrite(this->connector2->getRightPin(), LOW);
		digitalWrite(this->connector2->getDownPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getDown())
	{
		Serial.println("connector2 down released");
		digitalWrite(this->connector2->getDownPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getDownLeft())
	{
		Serial.println("connector2 down-left released");
		digitalWrite(this->connector2->getDownPin(), LOW);
		digitalWrite(this->connector2->getLeftPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getLeft())
	{
		Serial.println("connector2 left released");
		digitalWrite(this->connector2->getLeftPin(), LOW);
	}

	if (dpad == this->connector2->getJoystickMapping()->getLeftUp())
	{
		Serial.println("connector2 left-up released");
		digitalWrite(this->connector2->getLeftPin(), LOW);
		digitalWrite(this->connector2->getUpPin(), LOW);
	}
}

void JoystickListener::Update()
{
	// tick autofire timers;
	autoFire1->Update();
	autoFire2->Update();
}

// static
void JoystickListener::OnAutoFire1(void *context)
{
	JoystickListener *joystick = (JoystickListener *)context;
	joystick->ProcessAutoFire1();
}

// static
void JoystickListener::OnAutoFire2(void *context)
{
	JoystickListener *joystick = (JoystickListener *)context;
	joystick->ProcessAutoFire2();
}

void JoystickListener::ProcessAutoFire1()
{
	if(autoFire1->getState())
	{
		Serial.println("connector 1 autofire1 cycle press");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
	}
	else if (!con1Fire1Pressed)
	{
		Serial.println("connector 1 autofire1 cycle release");
		digitalWrite(this->connector1->getFire1Pin(), LOW);
	}
}

void JoystickListener::ProcessAutoFire2()
{
	if(autoFire2->getState())
	{
		Serial.println("connector 2 autofire1 cycle press");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
	}
	else if(!con2Fire1Pressed)
	{
		Serial.println("connector 2 autofire1 cycle release");
		digitalWrite(this->connector2->getFire1Pin(), LOW);
	}
}
