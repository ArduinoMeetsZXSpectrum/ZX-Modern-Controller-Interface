/*
 * LogitechDualActionDriver.cpp
 *
 *  Created on: 10. 9. 2017
 *      Author: aluchava
 */
#include "LogitechDualActionDriver.h"

LogitechDualActionDriver::LogitechDualActionDriver() : JoystickDriver(),  oldDpadShifted(0), oldStartButtons(0), oldFaceButtons(0), oldHatButtons(0)
{
}

LogitechDualActionDriver::~LogitechDualActionDriver()
{
}

void LogitechDualActionDriver::ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf, JoystickListener* listener)
{
	Serial.println("LogitechDualActionDriver::ParseHIDData");
	//PrintHex<uint8_t>(buf[4], 0x80);
	//PrintHex<uint8_t>(buf[5], 0x80);
	//Serial.println("...");

	uint8_t dpad = (buf[4] & 0xF);
	uint8_t faceButtons = (buf[4] & 0xF0) >> 4;
	uint8_t hatButtons = (buf[5] & 0xF);
	uint8_t startButtons = (buf[5] & 0xF0) >> 4;

	// startButtons (two buttons - 9,10);
	uint8_t startButtonsChanges = (startButtons ^ oldStartButtons);
	for (uint8_t i = 0; i < 2; i++)
	{
		uint8_t mask = (0x0001 << i);
		if (((mask & startButtonsChanges) > 0))
		{
			if ((startButtons & mask) > 0)
			{
				PrintHex<uint8_t>(i+9, 0x80);
				Serial.println(" < press button");
				listener->onButtonDown(i+9);
			}
			else
			{
				PrintHex<uint8_t>(i+9, 0x80);
				Serial.println(" < release button");
				listener->onButtonUp(i+9);
			}
		}

		oldStartButtons = startButtons;
	}

	// faceButtons (four buttons - 1,2,3,4);
	uint8_t faceButtonsChanges = (faceButtons ^ oldFaceButtons);
	for (uint8_t i = 0; i < 4; i++)
	{
		uint8_t mask = (0x0001 << i);
		if (((mask & faceButtonsChanges) > 0))
		{
			if ((faceButtons & mask) > 0)
			{
				PrintHex<uint8_t>(i+1, 0x80);
				Serial.println(" < press face button");
				listener->onButtonDown(i+1);
			}
			else
			{
				PrintHex<uint8_t>(i+1, 0x80);
				Serial.println(" < release face button");
				listener->onButtonUp(i+1);
			}
		}
		oldFaceButtons = faceButtons;
	}

	// hatButtons (four buttons - 5,6,7,8);
	uint8_t hatButtonsChanges = (hatButtons ^ oldHatButtons);
	for (uint8_t i = 0; i < 4; i++)
	{
		uint8_t mask = (0x0001 << i);
		if (((mask & hatButtonsChanges) > 0))
		{
			if ((hatButtons & mask) > 0)
			{
				PrintHex<uint8_t>(i+5, 0x80);
				Serial.println(" < press hat button");
				listener->onButtonDown(i+5);
			}
			else
			{
				PrintHex<uint8_t>(i+5, 0x80);
				Serial.println(" < release hat button");
				listener->onButtonUp(i+5);
			}
		}
		oldHatButtons = hatButtons;
	}

	// dpad (8 buttons);
	uint16_t dpadShifted = 1 << dpad;
	uint16_t dpadShiftedChanges = (dpadShifted ^ oldDpadShifted);
	uint8_t dpadReleases[8] = {0};
	uint8_t dpadPresses[8] = {0};
	if (dpadShiftedChanges)
	{
		for (uint8_t i = 0; i < 8; i++)
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

		for (uint8_t i = 0; i < 8; i++)
		{
			if(dpadReleases[i] > 0)
			{
				PrintHex<uint8_t>(i, 0x80);
				Serial.println(" < dpad release");
				listener->onDPadUp(i);
			}
		}

		for (uint8_t i = 0; i < 8; i++)
		{
			if(dpadPresses[i] > 0)
			{
				PrintHex<uint8_t>(i, 0x80);
				Serial.println(" < dpad press");
				listener->onDPadDown(i);
			}
		}

		oldDpadShifted = dpadShifted;
	}

}
