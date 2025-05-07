#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIOInitstruct;
	GPIOInitstruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIOInitstruct.GPIO_Pin = GPIO_Pin_8;
	GPIOInitstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIOInitstruct);
}

uint8_t Key_Getnum(void)
{
	uint8_t Keynum;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8) == 1){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8) == 1)Delay_ms(20);
		Keynum = 1;
	}
	return Keynum;
}
