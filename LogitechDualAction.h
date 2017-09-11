/*
 * HIDUniversalJoystick.h
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */

#ifndef LOGITECHDUALACTION_H_
#define LOGITECHDUALACTION_H_

#include "hiduniversal.h"

#define LOGITECH_VENDOR_ID 0x46D
#define DUAL_ACTION_PRODUCT_ID 0xC216

class LogitechDualAction: public HIDUniversal
{
	uint16_t oldDpadShifted;

	public:
		LogitechDualAction(USB *p);
		virtual ~LogitechDualAction();bool connected();

	private:
		uint8_t OnInitSuccessful();
		void ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif /* LOGITECHDUALACTION_H_ */
