/*
 * XBoxOneUSBGamepad.h
 *
 *  Created on: 17. 9. 2017
 *      Author: aluchava
 */

#ifndef XBoxOneUSBGamepad_H_
#define XBoxOneUSBGamepad_H_

#include <XBOXONE.h>
#include "JoystickListener.h"
#include "ZX_BUTTON_Enum.h"
#include "ZX_DPAD_Enum.h"

using namespace ZX;

class XBoxOneUSBGamepad : public XBOXONE
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
		XBoxOneUSBGamepad(USB *pUsb);
		virtual ~XBoxOneUSBGamepad();

		void setListener(JoystickListener* listener);

		uint8_t Poll();
};

#endif /* XBOXOneUSBGAMEPAD_H_ */
