/*
 * JoystickConnector.cpp
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#include "JoystickConnector.h"

JoystickConnector::JoystickConnector(uint8_t upPin, uint8_t downPin, uint8_t leftPin, uint8_t rightPin, uint8_t fire1Pin,
		KeyboardMapping *keyboardMappings, JoystickMapping *joystickMapping)
{
	this->upPin = upPin;
	this->downPin = downPin;
	this->leftPin = leftPin;
	this->rightPin = rightPin;
	this->fire1Pin = fire1Pin;
	this->keyboardMappings = keyboardMappings;
	this->activeKeyboardMapping = this->keyboardMappings;
	this->joystickMapping = joystickMapping;
}

JoystickConnector::~JoystickConnector()
{
}

uint8_t JoystickConnector::getUpPin()
{
	return upPin;
}

uint8_t JoystickConnector::getDownPin()
{
	return downPin;
}

uint8_t JoystickConnector::getLeftPin()
{
	return leftPin;
}

uint8_t JoystickConnector::getRightPin()
{
	return rightPin;
}

uint8_t JoystickConnector::getFire1Pin()
{
	return fire1Pin;
}

KeyboardMapping *JoystickConnector::getKeyboardMapping()
{
	return activeKeyboardMapping;
}

JoystickMapping *JoystickConnector::getJoystickMapping()
{
	return joystickMapping;
}

void JoystickConnector::ChangeActiveKeyboardMapping(uint8_t mapping)
{
	Serial.println("ChangeActiveKeyboardMapping: ");
	PrintHex<uint8_t>(mapping, 0x80);
	Serial.println();

	KeyboardMapping *keyboardMapping = (this->keyboardMappings + mapping);
	activeKeyboardMapping = keyboardMapping;
}
