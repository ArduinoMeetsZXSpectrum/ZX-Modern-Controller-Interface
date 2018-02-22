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

class XBoxOneUSBGamepad : public XBOXONE
{
	uint8_t oldDpadState;
	uint8_t oldButtonsState;
	JoystickListener* listener;

	ButtonEnum hwDpad[4];
	ButtonEnum hwButtons[4];

	DPADEnum zxDpad[4];
	ButtonsEnum zxButtons[4];

	public:
		XBoxOneUSBGamepad(USB *pUsb);
		virtual ~XBoxOneUSBGamepad();

		void setListener(JoystickListener* listener);

		uint8_t Poll();
};

#endif /* XBOXOneUSBGAMEPAD_H_ */
