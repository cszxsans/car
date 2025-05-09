#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "PWM.h"
#include "Motor.h"
#include "OLED.h"
#include "Encoder.h"
#include "Timer.h"
#include "Delay.h"
#include "Serial.h"
#include "Key.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int16_t Speed1,Speed2,Speed3;
int16_t Location1,Location2,Location3;

float Target1,Actual1,Out1;
float Kp1 = 0.28,Ki1 = 0.25,Kd1;
float Error01,Error11,Error21;

float Target2,Actual2,Out2;
float Kp2 = 0.28,Ki2 = 0.26,Kd2;
float Error02,Error12,Error22;

float Target3,Actual3,Out3;
float Kp3 = 0.28,Ki3 = 0.26,Kd3;
float Error03,Error13,Error23;

int16_t current;
float time,nt;
uint8_t state = 0;
uint8_t Keynum = 0,a = 0;

void Circular(float *vx,float *vy,float start_time,float speed){
	float t = time/1000.0f - start_time;
	float w = speed/50;
	
	*vx = -50*w*sinf(w*t);
	*vy = 50*w*cosf(w*t);
}

int main()
{
    
	Motor_Init();
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	Key_Init();
	
	Motor_Setspeed1(0);
	Motor_Setspeed2(0);
	Motor_Setspeed3(0);
	OLED_Clear();
	
	
	while(1)
	{
		float vx,vy;
		Keynum = Key_Getnum(Keynum);
		if(Keynum % 4 == 1){
	        if(!a){
				Location1 = 0;
				Location2 = 0;
				Location3 = 0;
				Target1 = -0.5/0.033;
				Target2 = 1/0.033;
				Target3 = -0.5/0.033;
				current = Location2;
				state = 0;
				a = 1;
			}
			if(abs(Location2 - current) <= 2*1500 + 50 && abs(Location2 - current) >= 2*1500 - 50 && state == 0){
				current = Location1;
				Target1 = 1.155/0.033;
				Target2 = 0;
				Target3 = -1.155/0.033;
				state++;
			}
			if(abs(Location1 - current) <= 2*1500 + 50 && abs(Location1 - current) >= 2*1500 - 50 && state == 1){
				current = Location2;
				Target1 = 0.5/0.033;
				Target2 = -1/0.033;
				Target3 = 0.5/0.033;
				state++;
			}
			if(abs(Location2 - current) <= 2*1500 + 50 && abs(Location2 - current) >= 2*1500 - 50 && state == 2){
				current = Location1;
				Target1 = -1.155/0.033;
				Target2 = 0;
				Target3 = 1.155/0.033;
				state++;
			}
			if(abs(Location1 - current) <= 2*1500 + 50 && abs(Location1 - current) >= 2*1500 - 50 && state == 3){
				Target1 = 0;
				Target2 = 0;
				Target3 = 0;
			}
		}
		if(Keynum % 4 == 2){
	        if(a){
				Location1 = 0;
				Location2 = 0;
				Location3 = 0;
				Target1 = -0.5/0.033;
				Target2 = 1/0.033;
				Target3 = -0.5/0.033;
				current = Location2;
				state = 0;
				a = 0;
			}
			if(abs(Location2 - current) <= 2*1500 + 50 && abs(Location2 - current) >= 2*1500 - 50 && state == 0){
				current = Location1;
				Target1 = 1/0.033;
				Target2 = -0.5/0.033;
				Target3 = -0.5/0.033;
				state++;
			}
			if(abs(Location1 - current) <= 2*1500 + 50 && abs(Location1 - current) >= 2*1500 - 50 && state == 1){
				current = Location3;
				Target1 = -0.5/0.033;
				Target2 = -0.5/0.033;
				Target3 = 1/0.033;
				state++;
			}
			if(abs(Location3 - current) <= 2*1500 + 50 && abs(Location3 - current) >= 2*1500 - 50 && state == 2){
				Target1 = 0;
				Target2 = 0;
				Target3 = 0;
			}
		}
		if(Keynum % 4 == 3){
			if(!a){
				nt = time/1000.0f;
				a = 1;
			}
			Circular(&vx,&vy,nt,30);
			Target1 = (vy*sqrt(3)/2 - vx/2);
			Target2 = vx;
			Target3 = (-vy*sqrt(3)/2 - vx/2);
		}
		if(Keynum % 4 == 0){
			Target1 = 0;
			Target2 = 0;
			Target3 = 0;
		}
		OLED_ShowSignedNum(2,1,vx,5);
        OLED_ShowSignedNum(1,1,vy,5);   
        OLED_ShowSignedNum(3,1,Keynum,5);
		OLED_ShowSignedNum(4,1,a,5);
		OLED_ShowSignedNum(2,8,Actual3,5);   
        OLED_ShowSignedNum(1,8,Location2 - current,5);
//		OLED_ShowSignedNum(3,8,abs(Location2 - current),5);   
//        OLED_ShowSignedNum(4,8,25555,5);
    }
}

void TIM8_UP_IRQHandler(void)
{
	static uint16_t Count;
	time++;
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) == SET)
	{
		time++;
		Count ++;
		if (Count >= 40)
		{
			Count = 0;
			
			Actual1 = Get1Encoder();
			
			Error21 = Error11;
			Error11 = Error01;
			Error01 = Target1 - Actual1;
			
			Out1 += Kp1*(Error01 - Error11) + Ki1*Error01 + Kd1*(Error01 - 2*Error11 + Error21);
			
			if(Out1 > 100) Out1 = 100;
			if(Out1 < -100) Out1 = -100;
			
			Motor_Setspeed1(Out1);
			
			Actual2 = Get2Encoder();
			
			Error22 = Error12;
			Error12 = Error02;
			Error02 = Target2 - Actual2;
			
			Out2 += Kp2*(Error02 - Error12) + Ki2*Error02 + Kd2*(Error02 - 2*Error12 + Error22);
			
			if(Out2 > 100) Out2 = 100;
			if(Out2 < -100) Out2 = -100;
			
			Motor_Setspeed2(Out2);
			
			Actual3 = Get3Encoder();
			
			Error23 = Error13;
			Error13 = Error03;
			Error03 = Target3 - Actual3;
			
			Out3 += Kp3*(Error03 - Error13) + Ki3*Error03 + Kd3*(Error03 - 2*Error13 + Error23);
				
			if(Out3 > 100) Out3 = 100;
			if(Out3 < -100) Out3 = -100;
			
			Motor_Setspeed3(Out3);
			
			Speed1 = Get1Encoder();
			Speed2 = Get2Encoder();
			Speed3 = Get3Encoder();
		
		
			Location1 += Actual1;
			Location2 += Actual2;
			Location3 += Actual3;
			
	}
	
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
	}
}
