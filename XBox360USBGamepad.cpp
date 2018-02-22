/*
 * XBox360USBGamepad.cpp
 *
 *  Created on: 17. 9. 2017
 *      Author: aluchava
 */

#include "XBox360USBGamepad.h"

XBox360USBGamepad::XBox360USBGamepad(USB *pUsb) : XBOXUSB(pUsb), oldDpadState(0), oldButtonsState(0), listener(0)
{
	zxDpad[0] = DPADEnum::DPAD_UP;
	zxDpad[1] = DPADEnum::DPAD_RIGHT;
	zxDpad[2] = DPADEnum::DPAD_DOWN;
	zxDpad[3] = DPADEnum::DPAD_LEFT;

	zxButtons[0] = ButtonsEnum::BUTTON_1;
	zxButtons[1] = ButtonsEnum::BUTTON_2;
	zxButtons[2] = ButtonsEnum::BUTTON_3;
	zxButtons[3] = ButtonsEnum::BUTTON_4;

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

	for(int i = 0; i<4; i++)
	{
		ButtonEnum hwbutton = hwDpad[i];
		DPADEnum zxButton = zxDpad[i];
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

	for(int i = 0; i<4; i++)
	{
		ButtonEnum hwbutton = hwButtons[i];
		ButtonsEnum zxButton = zxButtons[i];
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

	/*
	PrintHex<uint8_t>(dpadUp,  0x80);
	Serial.println("");
	*/
	return status;
}

void XBox360USBGamepad::setListener(JoystickListener* listener)
{
	this->listener = listener;
}

