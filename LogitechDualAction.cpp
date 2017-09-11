/*
 * HIDUniversalJoystick.cpp
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */
#include "LogitechDualAction.h"

LogitechDualAction::LogitechDualAction(USB *p) : HIDUniversal(p), oldDpadShifted(0)
{

}

LogitechDualAction::~LogitechDualAction()
{
}

bool LogitechDualAction::connected()
{
	return HIDUniversal::isReady() && HIDUniversal::VID == LOGITECH_VENDOR_ID
	        && HIDUniversal::PID == DUAL_ACTION_PRODUCT_ID;
};

uint8_t LogitechDualAction::OnInitSuccessful()
{
	// Called by the HIDUniversal library on success
	if (HIDUniversal::VID != LOGITECH_VENDOR_ID || HIDUniversal::PID != DUAL_ACTION_PRODUCT_ID)
	{
		// Make sure the right device is actually connected
		return 0;
	}
	else
	{
		Serial.println("LogitechDualAction::OnInitSuccessful");
		return 1;
	}
};

void LogitechDualAction::ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	//PrintHex<uint8_t>(buf[4], 0x80);
	//PrintHex<uint8_t>(buf[5], 0x80);
	//PrintHex<uint8_t>(buf[6], 0x80);
	//Serial.println("...");


	uint8_t dpad = (buf[4] & 0xF);
	uint8_t faceButtons = (buf[4] & 0xF0) >> 4;
	uint8_t hatButtons = (buf[5] & 0xF);
	uint8_t startButtons = (buf[5] & 0xF0) >> 4;

	/*
	// startButtons (two buttons);
	for (uint8_t i = 0; i <= 1; i++)
	{
		uint16_t mask = (0x0001 << i);

		PrintHex<uint16_t>(mask, 0x80);
		Serial.println("< mask");

		uint16_t res = startButtons & mask;
		PrintHex<uint16_t>(startButtons, 0x80);
		Serial.println("< startButtons");
		PrintHex<uint16_t>(res, 0x80);
		Serial.println("< res");
	}
	*/

	PrintHex<uint8_t>(dpad, 0x80);
	Serial.println("< dpad");

	// dpad (8 buttons);
	uint16_t dpadShifted = 1 << dpad;
	uint16_t dpadShiftedChanges = (dpadShifted ^ oldDpadShifted);
	uint8_t dpadReleases[8] = {0};
	uint8_t dpadPresses[8] = {0};
	if (dpadShiftedChanges)
	{
		for (uint8_t i = 0; i <= 7; i++)
		{
			uint16_t mask = (0x0001 << i);
			if (((mask & dpadShiftedChanges) > 0))
			{
				if ((dpadShifted & mask) > 0)
				{
					dpadPresses[i] = 1;
				}
				else
				{
					dpadReleases[i] = 1;
				}
			}
		}
		oldDpadShifted = dpadShifted;
	}

	for (uint8_t i = 0; i <= 7; i++)
	{
		if(dpadReleases[i] > 0)
		{
			PrintHex<uint8_t>(i, 0x80);
			Serial.println(" < release");
		}
	}

	for (uint8_t i = 0; i <= 7; i++)
	{
		if(dpadPresses[i] > 0)
		{
			PrintHex<uint8_t>(i, 0x80);
			Serial.println(" < press");
		}
	}

}
