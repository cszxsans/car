#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	TIM_InternalClockConfig(TIM8);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM8, ENABLE);
}

//void Timer_Init(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
//	
//	TIM_InternalClockConfig(TIM5);
//	
//	TIM_TimeBaseInitTypeDef TimeBaseStruct;
//	TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	TimeBaseStruct.TIM_Period = 1000 - 1;
//	TimeBaseStruct.TIM_Prescaler = 72 - 1;
//	TimeBaseStruct.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM5,&TimeBaseStruct);
//	
//	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
//	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitTypeDef NVIC_InitStruct;
//	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStruct);
//	
//	TIM_Cmd(TIM5,ENABLE);
//}
