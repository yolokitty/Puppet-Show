/*
 * fan.h
 *
 *  Created on: Jan 28, 2026
 *      Author: appletea
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include "main.h"
#include "button.h"
#include "tim.h"
#include "interrupt.h"

typedef struct
{
  GPIO_TypeDef  *port;
  uint16_t      number;
  GPIO_PinState onState;
  GPIO_PinState offState;
}Segment_LED;


void Fan();
void LED_Write(uint8_t value);


extern volatile uint8_t Flag1;
extern volatile uint8_t Flag2;
extern volatile uint8_t Flag3;

#endif /* INC_FAN_H_ */
