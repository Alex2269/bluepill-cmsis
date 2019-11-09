#include <stm32f10x.h>
#include "misc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define SYSCLK 72000000
#define PRESCALER 72
#define PWM_FREQ 1000

void led_init(void)
{
  // enable clock on APB2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  // configure port A1 for driving an LED
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // output push-pull mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // highest speed
  GPIO_Init(GPIOC, &GPIO_InitStructure) ;
}

int main(void) 
{
  led_init();
  // main loop
  while(1) 
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13); // turn the LED on
    _delay_ms(250);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13); // turn the LED off
    _delay_ms(250);
  }
}

