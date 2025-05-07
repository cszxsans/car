#include "led.h"
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void LED_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个结构体
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA,PD时钟
    //定义PA8,GPIO设置
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;        //设置引脚
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; // 设置输出速度
    GPIO_Init(GPIOA,&GPIO_InitStructure);          //初始化GPIO
}
