/*
 * bt.h
 *
 *  Created on: Jan 28, 2026
 *      Author: appletea
 */

#ifndef INC_BT_H_
#define INC_BT_H_

#include "main.h"
#include "usart.h"
#include "led.h"

extern uint8_t rxData[10];


extern volatile uint8_t g_day;        // 1~4 (초기 DAY1)
extern volatile uint8_t g_day_next_req; // BT에서 '4' 오면 1로 세팅(원샷)

extern volatile uint8_t Flag;
extern volatile uint8_t Flag1;
extern volatile uint8_t Flag2;
extern volatile uint8_t Flag3;


void Check();


#endif /* INC_BT_H_ */
