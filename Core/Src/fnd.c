///*
// * fnd.c
// *
// *  Created on: Jan 29, 2026
// *      Author: appletea
// */
//
//

#include "fnd.h"

/* =======================
 *  Digit polarity (FIXED)
 *  ======================= */
#define DIG_ON   GPIO_PIN_RESET   //common-cathode 방식이라 0일때 ON
#define DIG_OFF  GPIO_PIN_SET	  //1일때 OFF


#define SEG_d  0x5E		//d
#define SEG_A  0x77		//A
#define SEG_Y  0x6E		//y



FND_LED FNDLed[11] = {
    { GPIOC, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET }, // idx0 : SEG a
    { GPIOC, GPIO_PIN_12, GPIO_PIN_SET, GPIO_PIN_RESET }, // idx1 : SEG b
    { GPIOC, GPIO_PIN_11, GPIO_PIN_SET, GPIO_PIN_RESET }, // idx2 : SEG c
    { GPIOD, GPIO_PIN_2,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx3 : SEG d
    { GPIOA, GPIO_PIN_4,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx4 : DIG 1
    { GPIOA, GPIO_PIN_15, GPIO_PIN_SET, GPIO_PIN_RESET }, // idx5 : SEG e
    { GPIOC, GPIO_PIN_1,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx6 : DIG 2
    { GPIOC, GPIO_PIN_2,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx7 : DIG 3
    { GPIOB, GPIO_PIN_7,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx8 : SEG f
    { GPIOC, GPIO_PIN_0,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx9 : SEG g
    { GPIOC, GPIO_PIN_3,  GPIO_PIN_SET, GPIO_PIN_RESET }, // idx10: DIG 4
};


/* 0~9 segment patterns */
static const uint8_t FND2_NUMBER[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x27, 0x7F, 0x67
};

//SEG 핀 7개
static const uint8_t SEG_INDEX[7] = {0, 1, 2, 3, 5, 8, 9};

//DIG 핀 7개
static const uint8_t DIG_INDEX[4] = {4, 6, 7, 10};

//SEG 패턴 기억 배열
static volatile uint8_t g_disp[4] = {0, 0, 0, 0};



static void Seg_Write(uint8_t pat)		//SEG에 숫자나 패턴 출력
{
    for (int i = 0; i < 7; i++)
    {
        GPIO_PinState st = (pat & (1 << i)) ? FNDLed[SEG_INDEX[i]].onState
                                             : FNDLed[SEG_INDEX[i]].offState;

        HAL_GPIO_WritePin(FNDLed[SEG_INDEX[i]].port,
                          FNDLed[SEG_INDEX[i]].number,
                          st);
    }
}

static void Dig_AllOff(void)
{
    for (int i = 0; i < 4; i++)
    {
        HAL_GPIO_WritePin(FNDLed[DIG_INDEX[i]].port,
                          FNDLed[DIG_INDEX[i]].number,
                          DIG_OFF);
    }
}

static void Dig_On(uint8_t d) // 0~3
{
    HAL_GPIO_WritePin(FNDLed[DIG_INDEX[d]].port,
                      FNDLed[DIG_INDEX[d]].number,
                      DIG_ON);
}


static inline void tiny_delay()		//고스트(잔상)방지
{
    for (volatile int i = 0; i < 80; i++) { __NOP(); }
    //
    //임베디드 언어 {__NOP();} haldelay(1);을 대체
}

void FND_ScanOnce()		//FND dig 1,2,3,4를 1ms씩 점등하여 전체가 점등한것처럼 보이게 하는 함수
{
    static uint8_t scan = 0;

    Dig_AllOff();			//모든 dig off
    tiny_delay();			//잔상방지

    Seg_Write(g_disp[scan]);
    //scan자리에 표시할 SEG_Pattern 출력 1번 d, 2번 A, 3번 y, 4번 숫자
    tiny_delay();

    Dig_On(scan);
    //딱 1자리의 DIG 출력

    scan = (scan + 1) & 0x03;

    //다음에 켤자리 로 이동 0x03 -> 0~3 순환
}

//DAY 함수 선언
void DAY_1(void)
{
    g_disp[0] = SEG_d;
    g_disp[1] = SEG_A;
    g_disp[2] = SEG_Y;
    g_disp[3] = FND2_NUMBER[1];
}

void DAY_2(void)
{
    g_disp[0] = SEG_d;
    g_disp[1] = SEG_A;
    g_disp[2] = SEG_Y;
    g_disp[3] = FND2_NUMBER[2];
}

void DAY_3(void)
{
    g_disp[0] = SEG_d;
    g_disp[1] = SEG_A;
    g_disp[2] = SEG_Y;
    g_disp[3] = FND2_NUMBER[3];
}

void DAY_4(void)
{
    g_disp[0] = SEG_d;
    g_disp[1] = SEG_A;
    g_disp[2] = SEG_Y;
    g_disp[3] = FND2_NUMBER[4];
}




void FND_CONTROL(void)
{

	    if (g_day_next_req) //g_day_next_req가 0이아닌 1,2,3값이므로 실행됨
	    	//서브모터가 1주기를 왕복하면 g_date_next_req가 1이상으로 올라감
	    {
	        g_day_next_req = 0;

	        g_day++;
	        if (g_day > 4) g_day = 1;
	        //4이상일시 초기화 하면서 순환
	    }


	    switch (g_day)
	    {
	        case 1: DAY_1(); break;
	        case 2: DAY_2(); break;
	        case 3: DAY_3(); break;
	        case 4: DAY_4(); break;
	        default: g_day = 1; DAY_1(); break;
	    }


	    FND_ScanOnce();
}


