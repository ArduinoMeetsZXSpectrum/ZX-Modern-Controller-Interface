/*
 * JoystickMapping.h
 *
 *  Created on: 11. 9. 2017
 *      Author: aluchava
 */

#ifndef JOYSTICKMAPPING_H_
#define JOYSTICKMAPPING_H_

#include <Arduino.h>

class JoystickMapping
{
	private:
		uint8_t up;
		uint8_t upRight;
		uint8_t right;
		uint8_t rightDown;
		uint8_t down;
		uint8_t downLeft;
		uint8_t left;
		uint8_t leftUp;
		uint8_t fire1;

	public:
		JoystickMapping(uint8_t up, uint8_t upRight, uint8_t right, uint8_t rightDown, uint8_t down,
				uint8_t downLeft, uint8_t left, uint8_t leftUp, uint8_t fire1);
		virtual ~JoystickMapping();

		uint8_t getUp();
		uint8_t getUpRight();
		uint8_t getRight();
		uint8_t getRightDown();
		uint8_t getDown();
		uint8_t getDownLeft();
		uint8_t getLeft();
		uint8_t getLeftUp();
		uint8_t getFire1();
};

#endif /* JOYSTICKMAPPING_H_ */
