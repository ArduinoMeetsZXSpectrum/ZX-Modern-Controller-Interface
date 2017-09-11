/*
 * LogitechDualActionDriver.h
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */

#ifndef LOGITECHDUALACTIONDRIVER_H_
#define LOGITECHDUALACTIONDRIVER_H_

#include "JoystickDriver.h"

class LogitechDualActionDriver : public JoystickDriver
{
	uint16_t oldDpadShifted;
	uint8_t oldStartButtons;
	uint8_t oldFaceButtons;
	uint8_t oldHatButtons;

	public:
		LogitechDualActionDriver();
		virtual ~LogitechDualActionDriver();

		void virtual ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf, JoystickListener* listener);
};

#endif /* LOGITECHDUALACTIONDRIVER_H_ */
