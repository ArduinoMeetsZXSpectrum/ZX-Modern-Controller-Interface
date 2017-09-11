/*
 * KeyboardMapping.cpp
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#include "KeyboardMapping.h"

KeyboardMapping::KeyboardMapping(uint8_t keyUp, uint8_t keyDown, uint8_t keyLeft, uint8_t keyRight, uint8_t keyFire1)
{
	this->keyUp = keyUp;
	this->keyDown = keyDown;
	this->keyLeft = keyLeft;
	this->keyRight = keyRight;
	this->keyFire1 = keyFire1;
}

KeyboardMapping::~KeyboardMapping()
{

}

uint8_t KeyboardMapping::getKeyUp()
{
	return keyUp;
}

uint8_t KeyboardMapping::getKeyDown()
{
	return keyDown;
}

uint8_t KeyboardMapping::getKeyLeft()
{
	return keyLeft;
}

uint8_t KeyboardMapping::getKeyRight()
{
	return keyRight;
}

uint8_t KeyboardMapping::getKeyFire1()
{
	return keyFire1;
}
