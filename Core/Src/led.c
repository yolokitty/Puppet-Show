 /* led.c
 *
 *  Created on: Jan 22, 2026
 *      Author: mujukpopo
 */


#include "led.h"



LED_CONTROL led[8]=
    {
        {GPIOC, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},      // 0 a 7
        {GPIOC, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},      // 1 b 6
        {GPIOC, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},      // 2 c 4
        {GPIOA, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET},		// d 2
        {GPIOA, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET},		//e 1
        {GPIOB, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET}, 	//f 9
        {GPIOB, GPIO_PIN_2, GPIO_PIN_SET, GPIO_PIN_RESET},		//g 10
        {GPIOB, GPIO_PIN_1, GPIO_PIN_SET, GPIO_PIN_RESET}       //
    };



void ledOn(uint8_t num)
{
  for(uint8_t i = 0; i < num; i++)    // led를 num개 만큼 켜는거
  {
    HAL_GPIO_WritePin(led[i].port, led[i].number, led[i].onState);
  }
}

void ledOff(uint8_t num)
{
  for(uint8_t i = 0; i < num; i++)    // led를 num개 만큼 끄는거
    {
      HAL_GPIO_WritePin(led[i].port, led[i].number, led[i].offState);
    }
}

void ledToggle(uint8_t num)   // 지정된 핀만 토글
{
  HAL_GPIO_TogglePin(led[num].port, led[num].number);
}

void ledLeftShift(uint8_t num)
{
  for(uint8_t i = 0; i < num+1; i++)
  {
    ledOn(i);
    HAL_Delay(100);
  }
  HAL_Delay(500);
  for(uint8_t i = 0; i < num+1; i++)
  {
    ledOff(i);
    HAL_Delay(100);
  }
  HAL_Delay(500);
}


void SOn(uint8_t num)
{
	HAL_GPIO_WritePin(led[num].port, led[num].number, led[num].onState);
}
