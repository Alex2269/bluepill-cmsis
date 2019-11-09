#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "n3310.h"
#include "picture.h"

inline void delay(__IO uint32_t tck)
{
  while(tck)
  {
    tck--;
  }  
}

int main(void)
{
	//=== REMAP ===
	// Вмикаємо тактування AFIO (альтернвтивні функції вводу-виводу)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// Ремапимо SWJ_JTAG. Тобто в данному випадку відключаемо від JTAG ногу PB3.
	// Після цього PB3 можна використовувати як лінію порта
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//=============

	LcdInit();
	LcdClear();
	LcdImage(Picture);
	LcdUpdate();

	// delay
    delay(1000000);

	LcdClear();

	LcdGotoXYFont(1,1);
	LcdStr(FONT_1X, (unsigned char *)"Hello World!");

	LcdGotoXYFont(1,4);
	LcdStr(FONT_2X, (unsigned char *)"Hello!");

	LcdUpdate();
    while(1)
    {
    	//LcdPixel(10,10, PIXEL_ON);
    	//LcdUpdate();
    }
}
