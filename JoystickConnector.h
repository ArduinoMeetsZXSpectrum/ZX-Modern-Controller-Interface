/*
 * JoystickConnector.h
 *
 *  Created on: 11. 8. 2017
 *      Author: aluchava
 */

#ifndef JOYSTICKCONNECTOR_H_
#define JOYSTICKCONNECTOR_H_

#include <stdint.h>
#include "KeyboardMapping.h"

class JoystickConnector
{
	private:
		uint8_t upPin;
		uint8_t downPin;
		uint8_t leftPin;
		uint8_t rightPin;
		uint8_t fire1Pin;
		KeyboardMapping *keyboardMapping;

	public:
		JoystickConnector(uint8_t upPin, uint8_t downPin, uint8_t leftPin, uint8_t rightPin, uint8_t fire1Pin,
				KeyboardMapping *keyboardMapping);
		virtual ~JoystickConnector();

		uint8_t getUpPin();
		uint8_t getDownPin();
		uint8_t getLeftPin();
		uint8_t getRightPin();
		uint8_t getFire1Pin();
		KeyboardMapping *getKeyboardMapping();
};

#endif /* JOYSTICKCONNECTOR_H_ */
