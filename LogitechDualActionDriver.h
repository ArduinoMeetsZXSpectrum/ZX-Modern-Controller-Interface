/*
 * LogitechDualActionDriver.h
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */

#ifndef LOGITECHDUALACTIONDRIVER_H_
#define LOGITECHDUALACTIONDRIVER_H_

#include "JoystickDriver.h"
#include "ZX_DPAD_Enum.h"

using namespace ZX;

class LogitechDualActionDriver : public JoystickDriver
{
	private:
		uint16_t oldDpadShifted;
		uint8_t oldStartButtons;
		uint8_t oldFaceButtons;
		uint8_t oldHatButtons;
		uint8_t oldAnalog;			// [left,right,up,down,left,right,up,down]
		ZX_DPAD_Enum zxAnalog[4];

	public:
		LogitechDualActionDriver();
		virtual ~LogitechDualActionDriver();

		void virtual ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf, JoystickListener* listener);
};

#endif /* LOGITECHDUALACTIONDRIVER_H_ */
