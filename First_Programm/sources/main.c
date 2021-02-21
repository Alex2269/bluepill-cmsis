#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"


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

  while (1)
  {
    /* Toggle LED which connected to PC13*/
    GPIOC->ODR ^= GPIO_Pin_13;

    /* delay */
    _delay_ms(500);
  }
}
