/*
 * KeyboardReportParserImpl.cpp
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#include "KeyboardReportParserImpl.h"

KeyboardReportParserImpl::KeyboardReportParserImpl(JoystickConnector *connector1, JoystickConnector *connector2)
{
	this->connector1 = connector1;
	this->connector2 = connector2;
}

KeyboardReportParserImpl::~KeyboardReportParserImpl()
{
}

void KeyboardReportParserImpl::OnControlKeysChanged(uint8_t before, uint8_t after)
{
}

void KeyboardReportParserImpl::OnKeyDown(uint8_t mod, uint8_t key)
{
	// connector1;

	if (key == this->connector1->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector1 up down");
		digitalWrite(this->connector1->getUpPin(), HIGH);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down down");
		digitalWrite(this->connector1->getDownPin(), HIGH);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left down");
		digitalWrite(this->connector1->getLeftPin(), HIGH);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right down");
		digitalWrite(this->connector1->getRightPin(), HIGH);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 down");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
	}

	// connector2;

	if (key == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up down");
		digitalWrite(this->connector2->getUpPin(), HIGH);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down down");
		digitalWrite(this->connector2->getDownPin(), HIGH);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left down");
		digitalWrite(this->connector2->getLeftPin(), HIGH);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right down");
		digitalWrite(this->connector2->getRightPin(), HIGH);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 down");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
	}

	/*
	if (key == 16)
	{
		Serial.println("fire2 down");
		digitalWrite(fire2Pin, HIGH);
	}
	*/
}

void KeyboardReportParserImpl::OnKeyUp(uint8_t mod, uint8_t key)
{
	// connector1;

	if (key == this->connector1->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector1 up up");
		digitalWrite(this->connector1->getUpPin(), LOW);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down up");
		digitalWrite(this->connector1->getDownPin(), LOW);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left up");
		digitalWrite(this->connector1->getLeftPin(), LOW);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right up");
		digitalWrite(this->connector1->getRightPin(), LOW);
	}

	if (key == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 up");
		digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	// connector2;

	if (key == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up up");
		digitalWrite(this->connector2->getUpPin(), LOW);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down up");
		digitalWrite(this->connector2->getDownPin(), LOW);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left up");
		digitalWrite(this->connector2->getLeftPin(), LOW);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right up");
		digitalWrite(this->connector2->getRightPin(), LOW);
	}

	if (key == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 up");
		digitalWrite(this->connector2->getFire1Pin(), LOW);
	}
}

