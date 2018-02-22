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
		Serial.println("connector1 up down");
		digitalWrite(this->connector1->getUpPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down down");
		digitalWrite(this->connector1->getDownPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left down");
		digitalWrite(this->connector1->getLeftPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right down");
		digitalWrite(this->connector1->getRightPin(), HIGH);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 down");
		digitalWrite(this->connector1->getFire1Pin(), HIGH);
	}

	// connector2;

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up down");
		digitalWrite(this->connector2->getUpPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down down");
		digitalWrite(this->connector2->getDownPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left down");
		digitalWrite(this->connector2->getLeftPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right down");
		digitalWrite(this->connector2->getRightPin(), HIGH);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 down");
		digitalWrite(this->connector2->getFire1Pin(), HIGH);
	}
}

void KeyboardReportParserImpl::OnKeyUp(uint8_t mod, uint8_t key)
{
	uint8_t virtualCode = OemToVirtualKeyCode(key);

	// connector1;

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector1 up up");
		digitalWrite(this->connector1->getUpPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector1 down up");
		digitalWrite(this->connector1->getDownPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector1 left up");
		digitalWrite(this->connector1->getLeftPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector1 right up");
		digitalWrite(this->connector1->getRightPin(), LOW);
	}

	if (virtualCode == this->connector1->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector1 fire1 up");
		digitalWrite(this->connector1->getFire1Pin(), LOW);
	}

	// connector2;

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyUp())
	{
		Serial.println("connector2 up up");
		digitalWrite(this->connector2->getUpPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyDown())
	{
		Serial.println("connector2 down up");
		digitalWrite(this->connector2->getDownPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyLeft())
	{
		Serial.println("connector2 left up");
		digitalWrite(this->connector2->getLeftPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyRight())
	{
		Serial.println("connector2 right up");
		digitalWrite(this->connector2->getRightPin(), LOW);
	}

	if (virtualCode == this->connector2->getKeyboardMapping()->getKeyFire1())
	{
		Serial.println("connector2 fire1 up");
		digitalWrite(this->connector2->getFire1Pin(), LOW);
	}
}

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
	// functioanl keys

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

