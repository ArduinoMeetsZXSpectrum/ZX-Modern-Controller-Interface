/*
 * UniversalJoystick.h
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#ifndef UNIVERSALJOYSTICK_H_
#define UNIVERSALJOYSTICK_H_

#include <hiduniversal.h>
#include "JoystickListener.h"
#include "LogitechDualActionDriver.h"

// vendors;
#define LOGITECH_VENDOR_ID 0x46D

// products;
#define LOGITECH_DUAL_ACTION_PRODUCT_ID 0xC216

class UniversalJoystick: public HIDUniversal
{
	JoystickDriver* connectedJoystick;
	JoystickListener* listener;

	public:
		UniversalJoystick(USB *p);
		virtual ~UniversalJoystick();

		void setListener(JoystickListener* listener);

	private:
		uint8_t OnInitSuccessful();
		void ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif /* UNIVERSALJOYSTICK_H_ */
