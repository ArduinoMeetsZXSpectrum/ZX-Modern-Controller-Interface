/*
 * JoystickDriver.h
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#ifndef JOYSTICKDRIVER_H_
#define JOYSTICKDRIVER_H_

#include <usbhid.h>
#include "JoystickListener.h"

class JoystickDriver
{
	public:
		JoystickDriver();
		virtual ~JoystickDriver();

		virtual void ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf, JoystickListener* listener) {};
};

#endif /* JOYSTICKDRIVER_H_ */
