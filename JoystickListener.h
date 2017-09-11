/*
 * JoystickListener.h
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#ifndef JoystickListener_H_
#define JoystickListener_H_

#include <hiduniversal.h>
#include "JoystickConnector.h"

struct GamePadEventData
{
		uint8_t X, Y, Z1, Z2, Rz;
};

enum DPADEnum
{
	DPAD_UP = 0x0,
	DPAD_UP_RIGHT = 0x1,
	DPAD_RIGHT = 0x2,
	DPAD_RIGHT_DOWN = 0x3,
	DPAD_DOWN = 0x4,
	DPAD_DOWN_LEFT = 0x5,
	DPAD_LEFT = 0x6,
	DPAD_LEFT_UP = 0x7
};

enum ButtonsEnum
{
	BUTTON_1 = 0x1,
	BUTTON_2 = 0x2,
	BUTTON_3 = 0x3,
	BUTTON_4 = 0x4,
	BUTTON_5 = 0x5,
	BUTTON_6 = 0x6,
	BUTTON_7 = 0x7,
	BUTTON_8 = 0x8,
	BUTTON_9 = 0x9,
	BUTTON_10 = 0x10
};

class JoystickListener
{
	private:
		JoystickConnector *connector1;
		JoystickConnector *connector2;

	public:
		JoystickListener(JoystickConnector *connector1, JoystickConnector *connector2);
		virtual ~JoystickListener();

		virtual void onGamePadChanged(const GamePadEventData *evt);
		virtual void onDPadDown(uint8_t dpad);
		virtual void onDPadUp(uint8_t dpad);
		virtual void onButtonDown(uint8_t button);
		virtual void onButtonUp(uint8_t button);
};

#endif /* JoystickListener_H_ */
