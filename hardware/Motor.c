#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//将PA4和PA5引脚初始化为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	PWM_Init();		
}

void Motor_Setspeed1(int8_t speed)
{
	if(speed > 0){
		GPIO_SetBits(GPIOB,GPIO_Pin_10);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
		PWM_SetCompare1(speed);
	}
	else{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		PWM_SetCompare1(-speed);
	}
}
void Motor_Setspeed2(int8_t speed)
{
	if(speed > 0){
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		PWM_SetCompare2(speed);
	}
	else{
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		PWM_SetCompare2(-speed);
	}
}
void Motor_Setspeed3(int8_t speed)
{
	if(speed > 0){
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(speed);
	}
	else{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		PWM_SetCompare3(-speed);
	}
}
