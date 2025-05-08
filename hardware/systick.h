#ifndef __SYSTICK_H
#define __STYTICK_H

void SysTick_Init(void);
float GetCurrentTime(void);
void Circular(float *vx,float *vy,float start_time,float speed);
void SysTick_Handler(void);
#endif
