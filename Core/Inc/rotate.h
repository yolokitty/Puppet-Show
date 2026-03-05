/*
 * rotate.h
 *
 *  Created on: 2026. 1. 28.
 *      Author: junwoo
 */

#ifndef INC_ROTATE_H_
#define INC_ROTATE_H_

#include "main.h"
#include "led.h"
#include "interrupt.h"

//extern volatile bool Flag;
//extern volatile bool Flag1;
//extern volatile uint8_t curr;
//extern volatile uint8_t direction;
//extern volatile uint32_t last_tick;

extern volatile uint8_t Flag;
extern volatile uint8_t Flag1;
extern volatile uint8_t Flag2;
extern volatile uint8_t Flag3;
extern volatile uint8_t Flag4;

void rotate(void);

#endif /* INC_ROTATE_H_ */
