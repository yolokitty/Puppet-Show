

#ifndef INC_FND_H_
#define INC_FND_H_

#include "main.h"
#include "button.h"
#include "led.h"
#include "tim.h"
#include "bt.h"



typedef struct
{
  GPIO_TypeDef  *port;
  uint16_t      number;
  GPIO_PinState onState;
  GPIO_PinState offState;
}FND_LED;


//void SEG_WRITE(uint8_t num);
void DIG_ON(uint8_t idx);

void FND_ScanOnce();

extern void DAY_1();
extern void Day_2();
extern void Day_3();
extern void Day_4();

extern void FND_CONTROL();


#endif /* INC_FND_H_ */
