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

class KeyboardReportParserImpl: public KeyboardReportParser
{
	private:
		JoystickConnector *connector1;
		JoystickConnector *connector2;

	protected:
		void OnControlKeysChanged(uint8_t before, uint8_t after);
		void OnKeyDown(uint8_t mod, uint8_t key);
		void OnKeyUp(uint8_t mod, uint8_t key);

	public:
		KeyboardReportParserImpl(JoystickConnector *connector1, JoystickConnector *connector2);
		virtual ~KeyboardReportParserImpl();
};

#endif /* KEYBOARDREPORTPARSERIMPL_H_ */
