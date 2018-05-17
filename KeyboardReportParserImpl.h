/*
 * KeyboardReportParserImpl.h
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#ifndef KEYBOARDREPORTPARSERIMPL_H_
#define KEYBOARDREPORTPARSERIMPL_H_

#include <hidboot.h>
#include "JoystickConnector.h"
#include "AutoFire.h"

class KeyboardReportParserImpl: public KeyboardReportParser
{
	private:
		JoystickConnector *connector1;
		JoystickConnector *connector2;
		AutoFire *autoFire1;
		AutoFire *autoFire2;
		bool con1Fire1Pressed = false;
		bool con2Fire1Pressed = false;

	protected:
		void OnControlKeysChanged(uint8_t before, uint8_t after);
		void OnKeyDown(uint8_t mod, uint8_t key);
		void OnKeyUp(uint8_t mod, uint8_t key);
		uint8_t OemToVirtualKeyCode(uint8_t key);

	public:
		KeyboardReportParserImpl(JoystickConnector *connector1, JoystickConnector *connector2);
		virtual ~KeyboardReportParserImpl();

		void Update();
		static void OnAutoFire1(void *context);
		static void OnAutoFire2(void *context);
		void ProcessAutoFire1();
		void ProcessAutoFire2();
};

#endif /* KEYBOARDREPORTPARSERIMPL_H_ */
