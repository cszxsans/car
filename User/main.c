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
float Kp1 = 0.58,Ki1 = 0.1,Kd1;
float Error01,Error11,Error21;

float Target2,Actual2,Out2;
float Kp2 = 0.58,Ki2 = 0.1,Kd2;
float Error02,Error12,Error22;

float Target3,Actual3,Out3;
float Kp3 = 0.58,Ki3 = 0.1,Kd3;
float Error03,Error13,Error23;
int main()
{
    
	Motor_Init();
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	
	Motor_Setspeed1(0);
	Motor_Setspeed2(0);
	Motor_Setspeed3(0);
	OLED_Clear();
	int16_t current = Location2;
	uint8_t state = 0;
	Target1 = -0.5/0.033;
	Target2 = 1/0.033;
	Target3 = -0.5/0.033;
	while(1)
	{
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
		//}
		OLED_ShowSignedNum(2,1,Actual1,5);
        OLED_ShowSignedNum(1,1,Location1,5);
		OLED_ShowSignedNum(4,1,Actual2,5);   
        OLED_ShowSignedNum(3,1,Location2,5);
		OLED_ShowSignedNum(2,8,Actual3,5);   
        OLED_ShowSignedNum(1,8,Location3,5);
		OLED_ShowSignedNum(3,8,abs(Location2 - current),5);   
        OLED_ShowSignedNum(4,8,state,5);
    }
     
    
}

void TIM8_UP_IRQHandler(void)
{
	static uint16_t Count;
	
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) == SET)
	{
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
//void TIM5_IRQHandler(void)
//{
//	static uint16_t Count;
//	if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
//	{
//		Count++;
//		if(Count >= 40)
//		{
//			Speed1 = Get1Encoder();
//			Speed2 = Get2Encoder();
//			Speed3 = Get3Encoder();
//		
//		
//			Location1 += Speed1;
//			Location2 += Speed2;
//			Location3 += Speed3;
//		}
//		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
//	}
//}
