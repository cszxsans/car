#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIOInitstruct;
	GPIOInitstruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIOInitstruct.GPIO_Pin = GPIO_Pin_10;
	GPIOInitstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOInitstruct);
}

uint8_t Key_Getnum(uint8_t Keynum)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10) == 0)Delay_ms(20);
		Keynum++;
	}
	return Keynum;
}
