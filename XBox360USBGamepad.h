/*
 * XBox360USBGamepad.h
 *
 *  Created on: 17. 9. 2017
 *      Author: aluchava
 */

#ifndef XBOX360USBGAMEPAD_H_
#define XBOX360USBGAMEPAD_H_

#include <XBOXUSB.h>
#include "JoystickListener.h"
#include "ZX_BUTTON_Enum.h"
#include "ZX_DPAD_Enum.h"

using namespace ZX;

class XBox360USBGamepad : public XBOXUSB
{
	uint8_t oldDpadState;
	uint8_t oldButtonsState;
	uint8_t oldAnalogState;
	JoystickListener* listener;

	ButtonEnum hwDpad[4];
	ButtonEnum hwButtons[4];

	ZX_DPAD_Enum zxDpad[4];
	ZX_DPAD_Enum zxAnalog[4];
	ZX_BUTTON_Enum zxButtons[4];

	public:
		XBox360USBGamepad(USB *pUsb);
		virtual ~XBox360USBGamepad();

		void setListener(JoystickListener* listener);

		uint8_t Poll();
};

#endif /* XBOX360USBGAMEPAD_H_ */
