#include "ZX_Modern_Controller_Interface.h"

// sinclair
uint8_t upPin1 = 11;
uint8_t downPin1 = 10;
uint8_t leftPin1 = 9;
uint8_t rightPin1 = 8;
uint8_t fire1Pin1 = 7;
KeyboardMapping keyboardMapping1 = KeyboardMapping(20, 4, 18, 19, 44);
JoystickConnector connector1 = JoystickConnector(upPin1, downPin1, leftPin1, rightPin1, fire1Pin1, &keyboardMapping1);

// kempston;
uint8_t upPin2 = 6;
uint8_t downPin2 = 5;
uint8_t leftPin2 = 4;
uint8_t rightPin2 = 12;
uint8_t fire1Pin2 = 13;
JoystickConnector connector2 = JoystickConnector(upPin2, downPin2, leftPin2, rightPin2, fire1Pin2, &keyboardMapping1);

// LED
uint8_t ledRedPin = 2;
uint8_t ledGreenPin = 3;

USB usb = USB();
USBHub hub = USBHub(&usb);

// keyboard;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hidKeyboard = HIDBoot<USB_HID_PROTOCOL_KEYBOARD>(&usb);

// gamepads;
LogitechDualAction logitechDualAction = LogitechDualAction(&usb);


JoystickEvents JoyEvents = JoystickEvents();
JoystickReportParserImpl Joy = JoystickReportParserImpl(&JoyEvents);

KeyboardReportParserImpl keyboardListener = KeyboardReportParserImpl(&connector1, &connector2);

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

	Serial.begin(9600);

#if !defined(__MIPSEL__)
	while (!Serial)
	{
		// Wait for serial port to connect - used on Leonardo,
		// Teensy and other boards with built-in USB CDC serial connection
	}
#endif

	Serial.println("ZX Modern Controller Interface Start");

	if (usb.Init() == -1) Serial.println("OSC did not start.");

	delay(200);

	hidKeyboard.SetReportParser(0, &keyboardListener);

	/*
	if (!logitechDualAction.SetReportParser(0, &Joy))
	{
		ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);
	}
	*/
}

// The loop function is called in an endless loop
void loop()
{
	usb.Task();

	if (logitechDualAction.connected())
	{

	}
}
