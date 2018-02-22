/*
 * ZX_Modern_Controller_Interface.cpp
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#include "ZX_Modern_Controller_Interface.h"

using namespace ZX;

// mappings O, P, Q, A, SPACE;
KeyboardMapping keyboardMapping1 = KeyboardMapping(Keys::Q, Keys::A, Keys::O, Keys::P, Keys::SPACE);
JoystickMapping joystickMapping = JoystickMapping(DPADEnum::DPAD_UP, DPADEnum::DPAD_UP_RIGHT, DPADEnum::DPAD_RIGHT, DPADEnum::DPAD_RIGHT_DOWN,
		DPADEnum::DPAD_DOWN, DPADEnum::DPAD_DOWN_LEFT, DPADEnum::DPAD_LEFT, DPADEnum::DPAD_LEFT_UP, ButtonsEnum::BUTTON_1);

// sinclair connector digital pins;
uint8_t upPin1 = 9;//11;
uint8_t downPin1 = 10;
uint8_t leftPin1 = 11; //9;
uint8_t rightPin1 = 12; //8;
uint8_t fire1Pin1 = 13; //7;
JoystickConnector connector1 = JoystickConnector(upPin1, downPin1, leftPin1, rightPin1, fire1Pin1, &keyboardMapping1, &joystickMapping);

// kempston connector digital pins;
uint8_t upPin2 = 4; //6;
uint8_t downPin2 = 5; //5;
uint8_t leftPin2 = 6; //4;
uint8_t rightPin2 = 7; //12;
uint8_t fire1Pin2 = 8; //13;
JoystickConnector connector2 = JoystickConnector(upPin2, downPin2, leftPin2, rightPin2, fire1Pin2, &keyboardMapping1, &joystickMapping);

// LED
uint8_t ledRedPin = 2;
uint8_t ledGreenPin = 3;

USB usb = USB();
USBHub hub = USBHub(&usb);

// hid keyboard;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hidKeyboard = HIDBoot<USB_HID_PROTOCOL_KEYBOARD>(&usb);
KeyboardReportParserImpl keyboardListener = KeyboardReportParserImpl(&connector1, &connector2);

// hid gamepad;
UniversalJoystick hidJoystick = UniversalJoystick(&usb);
JoystickListener joystickListener = JoystickListener(&connector1, &connector2);

// Xbox360USBGamepad
XBox360USBGamepad xbox360usb = XBox360USBGamepad(&usb);

// XboxOneUSBGamepad
XBoxOneUSBGamepad xboxOneusb = XBoxOneUSBGamepad(&usb);

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(upPin1, OUTPUT);
	pinMode(downPin1, OUTPUT);
	pinMode(leftPin1, OUTPUT);
	pinMode(rightPin1, OUTPUT);
	pinMode(fire1Pin1, OUTPUT);

	pinMode(upPin2, OUTPUT);
	pinMode(downPin2, OUTPUT);
	pinMode(leftPin2, OUTPUT);
	pinMode(rightPin2, OUTPUT);
	pinMode(fire1Pin2, OUTPUT);

	// LED
	pinMode(ledRedPin, OUTPUT);
	pinMode(ledGreenPin, OUTPUT);
	digitalWrite(ledRedPin, HIGH);
	digitalWrite(ledGreenPin, LOW);

	digitalWrite(upPin1, LOW);
	digitalWrite(downPin1, LOW);
	digitalWrite(leftPin1, LOW);
	digitalWrite(rightPin1, LOW);
	digitalWrite(fire1Pin1, LOW);

	digitalWrite(upPin2, LOW);
	digitalWrite(downPin2, LOW);
	digitalWrite(leftPin2, LOW);
	digitalWrite(rightPin2, LOW);
	digitalWrite(fire1Pin2, LOW);

	#if !defined(__MIPSEL__)
		while (!Serial)
		{
			// Wait for serial port to connect - used on Leonardo,
			// Teensy and other boards with built-in USB CDC serial connection
		}
	#endif

	Serial.begin( 115200 );
	Serial.println("ZX Modern Controller Interface Start");

	if (usb.Init() == -1) Serial.println("OSC did not start.");

	delay(200);

	hidKeyboard.SetReportParser(0, &keyboardListener);
	hidJoystick.setListener(&joystickListener);
	xbox360usb.setListener(&joystickListener);
	xboxOneusb.setListener(&joystickListener);
}

// The loop function is called in an endless loop
void loop()
{
	usb.Task();
}
