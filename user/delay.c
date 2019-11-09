#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "inttypes.h"

void _delay_ms(uint32_t ms)
{
  volatile uint32_t nCount;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);

  nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
  for (; nCount!=0; nCount--);
}

void _delay_us(uint32_t mc)
{
  volatile uint32_t nCount;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);

  nCount=(RCC_Clocks.HCLK_Frequency/10000000)*mc;
  for (; nCount!=0; nCount--);
}

uint32_t get_cpuFreq ()
 {
  volatile uint32_t frqz;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  frqz = (RCC_Clocks.HCLK_Frequency);

 return frqz;
}

