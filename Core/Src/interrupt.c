/*
 * interrupt.c
 *
 *  Created on: 2026. 1. 29.
 *      Author: junwoo
 */

#include "interrupt.h"

volatile uint8_t Flag = 0;
volatile uint8_t Flag1 = 0;
volatile uint8_t Flag2 = 0;
volatile uint8_t Flag3 = 0;
volatile uint8_t Flag4 = 0;

volatile uint32_t last_tick = 0;
volatile uint32_t last_tick1 = 0;
volatile uint32_t last_tick2 = 0;
volatile uint32_t last_tick3 = 0;
volatile uint32_t last_tick4 = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t current_tick = HAL_GetTick();

    // 1. 전원 버튼 (PA1)
    if (GPIO_Pin == GPIO_PIN_1) {
        if (current_tick - last_tick1 > 500) { // 전원은 0.5초로 넉넉하게
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) {
                Flag1 = 1;
                last_tick1 = current_tick;
            }
        }
    }

    // 2. UP 버튼 (PC13 - 보통 보드 내장 버튼이 13번인 경우가 많음)
    // 핀 번호(GPIO_PIN_13)에 맞춰 Port도 확인하세요 (GPIOC인지 확인!)
    else if (GPIO_Pin == GPIO_PIN_13) {
        if (current_tick - last_tick2 > 300) {
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
                Flag2 = 1;
                last_tick2 = current_tick;
            }
        }
    }

    // 3. DOWN 버튼 (PA4)
    else if (GPIO_Pin == GPIO_PIN_4) {
        if (current_tick - last_tick3 > 300) {
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET) {
                Flag3 = 1;
                last_tick3 = current_tick;
            }
        }
    }

    // 4. 회전 버튼 (PA7)
    else if (GPIO_Pin == GPIO_PIN_7) {
        // [수정] 전용 last_tick 변수를 쓰도록 바꿨습니다.
        // 기존에 last_tick1을 써서 전원 버튼과 간섭이 있었을 거예요.
        if (current_tick - last_tick4 > 300) {
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_RESET) {
                Flag = !Flag; // 회전 토글
                last_tick4 = current_tick;
            }
        }
    }
}
