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

	// init autoFire;
	autoFire1 = new AutoFire(&KeyboardReportParserImpl::OnAutoFire1, this);
	autoFire2 = new AutoFire(&KeyboardReportParserImpl::OnAutoFire2, this);
}

KeyboardReportParserImpl::~KeyboardReportParserImpl()
{
}

//------------------------------------------------------------
//
// Methods: KeyboardReportParser
//
//------------------------------------------------------------

void KeyboardReportParserImpl::OnControlKeysChanged(uint8_t before, uint8_t after)
{
}

void KeyboardReportParserImpl::OnKeyDown(uint8_t mod, uint8_t key)
{
	Serial.print("oem: ");
	PrintHex<uint8_t>(key, 0x80);
	Serial.println("...");

	uint8_t virtualCode = OemToVirtualKeyCode(key);
	Serial.print("key: ");
	PrintHex<uint8_t>(virtualCode, 0x80);
	Serial.println("...");

	// connector1;

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector1 up pressed");
		digitalWrite(this->connector1->getUpPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down pressed");
		digitalWrite(this->connector1->getDownPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left pressed");
		digitalWrite(this->connector1->getLeftPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right pressed");
		digitalWrite(this->connector1->getRightPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 pressed");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
		con1Fire1Pressed = true;
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyAutoFire1())
	{
		Serial.println("connector1 autoFire1 pressed");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
		autoFire1->Start();
	}

	// connector2;

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up pressed");
		digitalWrite(this->connector2->getUpPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down pressed");
		digitalWrite(this->connector2->getDownPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left pressed");
		digitalWrite(this->connector2->getLeftPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right pressed");
		digitalWrite(this->connector2->getRightPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 pressed");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
		con2Fire1Pressed = true;
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyAutoFire1())
	{
		Serial.println("connector2 autoFire1 pressed");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
		autoFire2->Start();
	}
}

void KeyboardReportParserImpl::OnKeyUp(uint8_t mod, uint8_t key)
{
	uint8_t virtualCode = OemToVirtualKeyCode(key);

	// connector1;

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector1 up released");
		digitalWrite(this->connector1->getUpPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down released");
		digitalWrite(this->connector1->getDownPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left released");
		digitalWrite(this->connector1->getLeftPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right released");
		digitalWrite(this->connector1->getRightPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 released");
		con1Fire1Pressed = false;
		if(!autoFire1->getState())
			digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyAutoFire1())
	{
		Serial.println("connector1 autoFire1 released");
		autoFire1->Stop();
		if(!con1Fire1Pressed)
			digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	// connector2;

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up released");
		digitalWrite(this->connector2->getUpPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down released");
		digitalWrite(this->connector2->getDownPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left released");
		digitalWrite(this->connector2->getLeftPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right released");
		digitalWrite(this->connector2->getRightPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 released");
		con2Fire1Pressed = false;
		if(!autoFire2->getState())
			digitalWrite(this->connector2->getFire1Pin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyAutoFire1())
	{
		Serial.println("connector2 autoFire1 released");
		autoFire2->Stop();
		if(!con2Fire1Pressed)
			digitalWrite(this->connector2->getFire1Pin(), LOW);
	}
}

//------------------------------------------------------------
//
// Methods
//
//------------------------------------------------------------

uint8_t KeyboardReportParserImpl::OemToVirtualKeyCode(uint8_t key)
{
	// [a-z]
	if (VALUE_WITHIN(key, 0x04, 0x1d))
	{
		return (key - 0x04 + 0x41);
	}
	// Numbers
	else if (VALUE_WITHIN(key, 0x1e, 0x27))
	{
		return ((key == UHS_HID_BOOT_KEY_ZERO) ? 48 : key - 0x1e + 0x31);
	}
	// Keypad Numbers
	else if (VALUE_WITHIN(key, 0x59, 0x61))
	{
		return (key - 0x59 + 0x61);
	} else if (VALUE_WITHIN(key, 0x2d, 0x38))
		/*
		return ((shift) ?
				(uint8_t) pgm_read_byte(&getSymKeysUp()[key - 0x2d]) :
				(uint8_t) pgm_read_byte(&getSymKeysLo()[key - 0x2d]));
		*/
		return 0;
	else if (VALUE_WITHIN(key, 0x54, 0x58))
	{
		// return (uint8_t) pgm_read_byte(&getPadKeys()[key - 0x54]);
		return 0;
	}
	// functional keys

	// cursor keys
	else if (VALUE_WITHIN(key, 0x4F, 0x52))
	{
		switch (key) {
			case 0x4f:
				return 0x27;

			case 0x50:
				return 0x25;

			case 0x51:
				return 0x28;

			case 0x52:
				return 0x26;
		}
	}
	else
	{
		switch (key) {
			case UHS_HID_BOOT_KEY_SPACE:
				return 0x20;

			case UHS_HID_BOOT_KEY_ENTER:
				return 0x0d;

			case UHS_HID_BOOT_KEY_ZERO2:
				return 0x60;

			case UHS_HID_BOOT_KEY_PERIOD:
				return 0x6e;
		}
	}
	return 0;
}

void KeyboardReportParserImpl::Update()
{
	// tick autofire timers;
	autoFire1->Update();
	autoFire2->Update();
}

// static
void KeyboardReportParserImpl::OnAutoFire1(void *context)
{
	KeyboardReportParserImpl *joystick = (KeyboardReportParserImpl *)context;
	joystick->ProcessAutoFire1();
}

// static
void KeyboardReportParserImpl::OnAutoFire2(void *context)
{
	KeyboardReportParserImpl *joystick = (KeyboardReportParserImpl *)context;
	joystick->ProcessAutoFire2();
}

void KeyboardReportParserImpl::ProcessAutoFire1()
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

void KeyboardReportParserImpl::ProcessAutoFire2()
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

