#include "stm32f10x.h"                  // Device header
#include<math.h>

volatile uint32_t system_time = 0;
//1ms中断
void SysTick_Init(void){
	SysTick_Config(SystemCoreClock/1000);
}
float GetCurrentTime(void){
	return (float)system_time/1000.0f;
}
void SysTick_Handler(void){
	system_time++;
}
void Circular(float *vx,float *vy,float start_time,float speed){
	float t = GetCurrentTime() - start_time;
	float w = speed/50;
	
	*vx = -50*w*sinf(w*t);
	*vy = 50*w*cosf(w*t);
}

