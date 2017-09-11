/*
 * KeyboardMapping.h
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#ifndef KEYBOARDMAPPING_H_
#define KEYBOARDMAPPING_H_

#include <stdint.h>

class KeyboardMapping
{
	private:
		uint8_t keyUp;
		uint8_t keyDown;
		uint8_t keyLeft;
		uint8_t keyRight;
		uint8_t keyFire1;

	public:
		KeyboardMapping(uint8_t keyUp, uint8_t keyDown,	uint8_t keyLeft, uint8_t keyRight, uint8_t keyFire1);
		virtual ~KeyboardMapping();

		uint8_t getKeyUp();
		uint8_t getKeyDown();
		uint8_t getKeyLeft();
		uint8_t getKeyRight();
		uint8_t getKeyFire1();
};

#endif /* KEYBOARDMAPPING_H_ */
