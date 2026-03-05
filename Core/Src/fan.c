/*
 * fan.c
 *
 *  Created on: Jan 28, 2026
 *      Author: appletea
 */

#include "fan.h"

const int COUNT_MIN = 1;
const int COUNT_MAX = 5;

static int Count = 0;
static int Save = 1;
static int isPowerOn = 0;		//Fan이 동작중인지 확인


extern volatile uint8_t Flag1;
extern volatile uint8_t Flag2;
extern volatile uint8_t Flag3;


Segment_LED SegLed[7]=
    {
        {GPIOC, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},      // 0
        {GPIOC, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},      // 1
        {GPIOC, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},      // 2
        {GPIOA, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_2, GPIO_PIN_SET, GPIO_PIN_RESET},
//        {GPIOB, GPIO_PIN_1, GPIO_PIN_SET, GPIO_PIN_RESET}       // 7
    };

void LED_Write(uint8_t value)
{
    for (uint8_t i = 0; i < 7; i++)
    {
        HAL_GPIO_WritePin(SegLed[i].port,SegLed[i].number,
        		(value & (1 << i)) ? SegLed[i].onState : SegLed[i].offState);
    }
}

uint8_t FND_NUMBER[] =
    {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
    };

uint32_t FAN_SPEED[] =
{
		0, 25, 30, 35, 40, 45
		};

void Fan()
{
    // 1. 전원 버튼 처리 (Flag1)
    if (Flag1)
    {
        Flag1 = 0;
        if (isPowerOn)		//Fan이 동작중이라면
        {
            Save = Count;  // 현재 단수(1~5) 저장
            Count = 0;     // 꺼질 때는 0단
            isPowerOn = 0;

            Flag = 0;
        } else {
            // 켤 때는 저장된 값으로 복구 (저장된 게 없으면 1단)
            Count = (Save >= 1) ? Save : 1;
            isPowerOn = 1;
        }
    }

    // 2. 속도 조절 (전원이 켜져 있을 때만 동작)
    if (isPowerOn)
    {
        if (Flag2) { // UP 버튼
            Flag2 = 0;
            if (Count < 5) { // 5 미만일 때만 올림 (즉, 4에서 누르면 5가 됨)
                Count++;
            }
        }
        if (Flag3) { // DOWN 버튼
            Flag3 = 0;
            if (Count > 1) { // 1 초과일 때만 내림 (즉, 2에서 누르면 1이 됨)
                Count--;
            }
        }
    }
    else
    {
        // 전원 꺼져 있으면 플래그만 계속 비워줌
        Flag2 = 0;
        Flag3 = 0;
        Count = 0; // 꺼짐 상태 유지
    }

    // 3. 출력부 (안전장치 추가)

    LED_Write(FND_NUMBER[Count]);
    TIM2->CCR1 = FAN_SPEED[Count];
}

