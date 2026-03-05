/*
 * interrupt.h
 *
 *  Created on: 2026. 1. 29.
 *      Author: junwoo
 */

#ifndef INC_INTERRUPT_H_
#define INC_INTERRUPT_H_

#include "stm32f4xx_hal.h"
#include "main.h"

extern volatile uint8_t Flag;
extern volatile uint8_t Flag1;
extern volatile uint8_t Flag2;
extern volatile uint8_t Flag3;
extern volatile uint8_t Flag4;

/* --- 디바운싱용 시간 변수 공유 --- */
extern volatile uint32_t last_tick;
extern volatile uint32_t last_tick1;
extern volatile uint32_t last_tick2;
extern volatile uint32_t last_tick3;
extern volatile uint32_t last_tick4;

#endif /* INC_INTERRUPT_H_ */
