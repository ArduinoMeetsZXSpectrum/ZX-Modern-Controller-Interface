/*
 * XBox360USBGamepad.cpp
 *
 *  Created on: 17. 9. 2017
 *      Author: aluchava
 */

#include "XBox360USBGamepad.h"

XBox360USBGamepad::XBox360USBGamepad(USB *pUsb) : XBOXUSB(pUsb)
{
	oldDpadState = 0;
	oldButtonsState = 0;
	oldAnalogState = 0;
	listener = 0;

	zxDpad[0] = ZX_DPAD_Enum::DPAD_UP;
	zxDpad[1] = ZX_DPAD_Enum::DPAD_RIGHT;
	zxDpad[2] = ZX_DPAD_Enum::DPAD_DOWN;
	zxDpad[3] = ZX_DPAD_Enum::DPAD_LEFT;

	zxButtons[0] = ZX_BUTTON_Enum::BUTTON_1;
	zxButtons[1] = ZX_BUTTON_Enum::BUTTON_2;
	zxButtons[2] = ZX_BUTTON_Enum::BUTTON_3;
	zxButtons[3] = ZX_BUTTON_Enum::BUTTON_4;

	zxAnalog[0] = ZX_DPAD_Enum::DPAD_LEFT;
	zxAnalog[1] = ZX_DPAD_Enum::DPAD_RIGHT;
	zxAnalog[2] = ZX_DPAD_Enum::DPAD_DOWN;
	zxAnalog[3] = ZX_DPAD_Enum::DPAD_UP;

	hwDpad[0] = ButtonEnum::UP;
	hwDpad[1] = ButtonEnum::RIGHT;
	hwDpad[2] = ButtonEnum::DOWN;
	hwDpad[3] = ButtonEnum::LEFT;

	hwButtons[0] = ButtonEnum::X;
	hwButtons[1] = ButtonEnum::A;
	hwButtons[2] = ButtonEnum::B;
	hwButtons[3] = ButtonEnum::Y;
}

XBox360USBGamepad::~XBox360USBGamepad()
{

}

uint8_t XBox360USBGamepad::Poll()
{
	//Serial.println("XBox360USBGamepad::poll");
	uint8_t status = XBOXUSB::Poll();

	// dpad;
	for(int i = 0; i<4; i++)
	{
		ButtonEnum hwbutton = hwDpad[i];
		ZX_DPAD_Enum zxButton = zxDpad[i];
		uint8_t buttonState = this->getButtonPress(hwbutton);

		uint8_t mask = (0x1 << zxButton);
		if(buttonState && !(oldDpadState & mask))
		{
			// set;
			oldDpadState |= mask;
			listener->onDPadDown(zxButton);
		}
		else if(!buttonState && (oldDpadState & mask))
		{
			// unset;
			oldDpadState ^= mask;
			listener->onDPadUp(zxButton);
		}
	}

	// face buttons;
	for(int i = 0; i<4; i++)
	{
		ButtonEnum hwbutton = hwButtons[i];
		ZX_BUTTON_Enum zxButton = zxButtons[i];
		uint8_t buttonState = this->getButtonPress(hwbutton);

		uint8_t mask = (0x1 << zxButton);
		if(buttonState && !(oldButtonsState & mask))
		{
			// set;
			oldButtonsState |= mask;
			listener->onButtonDown(zxButton);
		}
		else if(!buttonState && (oldButtonsState & mask))
		{
			// unset;
			oldButtonsState ^= mask;
			listener->onButtonUp(zxButton);
		}
	}

	// left analog - dpad emulation;
	uint16_t leftAnalogX = this->getAnalogHat(AnalogHatEnum::LeftHatX) - 0x8000;
	uint16_t leftAnalogY = this->getAnalogHat(AnalogHatEnum::LeftHatY) - 0x8000;
	uint16_t LeftAnalog[] = {leftAnalogX, leftAnalogY};
	uint8_t offset = 0;
	uint16_t const analogCenter = 0x7fff;
	uint16_t const analogSensitivity = 0x36ff;
	for(int i = 0; i<=1; i++)
	{
		uint16_t analogValue = LeftAnalog[i];
		uint8_t mask0 = (0x1 << (i + offset));
		uint8_t mask1 = (0x1 << (i + offset + 1));
		ZX_DPAD_Enum zxDpadButton0 = zxAnalog[i + offset];
		ZX_DPAD_Enum zxDpadButton1 = zxAnalog[i + offset + 1];
		if(analogValue < (analogCenter - analogSensitivity))
		{
			// low;
			if(!(oldAnalogState & mask0))
			{
				// set;
				oldAnalogState |= mask0;
				listener->onDPadDown(zxDpadButton0);
			}
		}
		else if(analogValue > (analogCenter + analogSensitivity))
		{
			// high;
			if(!(oldAnalogState & mask1))
			{
				// set;
				oldAnalogState |= mask1;
				listener->onDPadDown(zxDpadButton1);
			}
		}
		else
		{
			// center;
			if(oldAnalogState & mask0)
			{
				// unset;
				oldAnalogState ^= mask0;
				listener->onDPadUp(zxDpadButton0);
			}
			if(oldAnalogState & mask1)
			{
				// unset;
				oldAnalogState ^= mask1;
				listener->onDPadUp(zxDpadButton1);
			}
		}
		// next pair;
		offset += 1;
	}

	/*
	PrintHex<uint16_t>(dpadUp,  0x80);
	Serial.println("");
	*/
	return status;
}

void XBox360USBGamepad::setListener(JoystickListener* listener)
{
	this->listener = listener;
}

