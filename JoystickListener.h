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
#include "AutoFire.h"

struct GamePadEventData
{
	uint8_t X, Y, Z1, Z2, Rz;
};

class JoystickListener
{
	private:
		JoystickConnector *connector1;
		JoystickConnector *connector2;
		AutoFire *autoFire1;
		AutoFire *autoFire2;
		bool con1Fire1Pressed = false;
		bool con2Fire1Pressed = false;

	public:
		JoystickListener(JoystickConnector *connector1, JoystickConnector *connector2);
		virtual ~JoystickListener();

		virtual void onGamePadChanged(const GamePadEventData *evt);
		virtual void onDPadDown(uint8_t dpad);
		virtual void onDPadUp(uint8_t dpad);
		virtual void onButtonDown(uint8_t button);
		virtual void onButtonUp(uint8_t button);

		void Update();
		static void OnAutoFire1(void *context);
		static void OnAutoFire2(void *context);
		void ProcessAutoFire1();
		void ProcessAutoFire2();
};

#endif /* JoystickListener_H_ */
