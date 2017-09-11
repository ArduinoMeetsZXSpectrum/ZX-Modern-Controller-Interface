/*
 * JoystickMapping.cpp
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#include "JoystickMapping.h"

JoystickMapping::JoystickMapping(uint8_t up, uint8_t upRight, uint8_t right, uint8_t rightDown, uint8_t down,
		uint8_t downLeft, uint8_t left, uint8_t leftUp, uint8_t fire1)
{
	this->up = up;
	this->upRight = upRight;
	this->right = right;
	this->rightDown = rightDown;
	this->down = down;
	this->downLeft = downLeft;
	this->left = left;
	this->leftUp = leftUp;
	this->fire1 = fire1;
}

JoystickMapping::~JoystickMapping()
{
}

uint8_t JoystickMapping::getUp()
{
	return up;
}

uint8_t JoystickMapping::getUpRight()
{
	return upRight;
}

uint8_t JoystickMapping::getRight()
{
	return right;
}

uint8_t JoystickMapping::getRightDown()
{
	return rightDown;
}

uint8_t JoystickMapping::getDown()
{
	return down;
}

uint8_t JoystickMapping::getDownLeft()
{
	return downLeft;
}

uint8_t JoystickMapping::getLeft()
{
	return left;
}

uint8_t JoystickMapping::getLeftUp()
{
	return leftUp;
}

uint8_t JoystickMapping::getFire1()
{
	return fire1;
}
