#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Initialize LED which connected to PC13 */
  // Enable PORTC Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")
  GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")

  /* Initialize Button input PB0 */
  // Enable PORTB Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* Configure the GPIO_BUTTON pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  while (1) {

	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) != 0) {
    	/* Toggle LED which connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13; // Invert C13

    	/* delay */
    	_delay_ms(500);

    	/* Toggle LED which connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13;

    	/* delay */
    	_delay_ms(500);
    }
    else {
    	GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }

  }
}
