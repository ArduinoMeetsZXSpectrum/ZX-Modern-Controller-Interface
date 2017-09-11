/*
 * UniversalJoystick.cpp
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#include "UniversalJoystick.h"

UniversalJoystick::UniversalJoystick(USB *p) : HIDUniversal(p), connectedJoystick(0), listener(0)
{
}

UniversalJoystick::~UniversalJoystick()
{
}

uint8_t UniversalJoystick::OnInitSuccessful()
{
	// Called by the HIDUniversal library on success
	if (HIDUniversal::VID == LOGITECH_VENDOR_ID && HIDUniversal::PID == LOGITECH_DUAL_ACTION_PRODUCT_ID)
	{
		connectedJoystick = new LogitechDualActionDriver();
		Serial.println("LogitechDualAction::OnInitSuccessful");
	}
	else
	{
		delete connectedJoystick;
	}

	return 0;
};

void UniversalJoystick::setListener(JoystickListener* listener)
{
	this->listener = listener;
}

void UniversalJoystick::ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	if (!listener)
	{
		Serial.println("no listener defined");
		return;
	}

	if(connectedJoystick)
	{
		connectedJoystick->ParseHIDData(hid, is_rpt_id, len, buf, listener);
	}
	else
	{
		// fallback to universal driver;
		Serial.println("fallback to universal driver");
	}


}
