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
	// ������� ���������� AFIO (������������ ������� �����-������)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// �������� SWJ_JTAG. ����� � ������� ������� ���������� �� JTAG ���� PB3.
	// ϳ��� ����� PB3 ����� ��������������� �� ��� �����
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
