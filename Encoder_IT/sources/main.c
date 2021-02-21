#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stdio.h"
#include "misc.h"

#define FORWARD		0
#define BACKWARD	1

#define NOREADY		0
#define READY		1
#define INIT		3

volatile uint8_t encoder_status = INIT;
volatile uint8_t encoder_direction = FORWARD;

void usart_init(void)
{
	    /* Enable USART1 and GPIOA clock */
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	    /* Configure the GPIOs */
	    GPIO_InitTypeDef GPIO_InitStructure;

	    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    /* Configure USART1 Rx (PA.10) as input floating */
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    /* Configure the USART1 */
	    USART_InitTypeDef USART_InitStructure;

	  /* USART1 configuration ------------------------------------------------------*/
	    /* USART1 configured as follow:
	          - BaudRate = 115200 baud
	          - Word Length = 8 Bits
	          - One Stop Bit
	          - No parity
	          - Hardware flow control disabled (RTS and CTS signals)
	          - Receive and transmit enabled
	          - USART Clock disabled
	          - USART CPOL: Clock is active low
	          - USART CPHA: Data is captured on the middle
	          - USART LastBit: The clock pulse of the last data bit is not output to
	                           the SCLK pin
	    */
	    USART_InitStructure.USART_BaudRate = 115200;
	    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	    USART_InitStructure.USART_StopBits = USART_StopBits_1;
	    USART_InitStructure.USART_Parity = USART_Parity_No;
	    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	    USART_Init(USART1, &USART_InitStructure);

	    /* Enable USART1 */
	    USART_Cmd(USART1, ENABLE);
}

void USARTSend(char *pucBuffer)
{
    while (*pucBuffer)
    {
        USART_SendData(USART1, *pucBuffer++);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        {
        }
    }
}

void encoder_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//������ TIM3_CH1, TIM3_CH2 �� ���� � ��������
	GPIO_InitTypeDef gpio_cfg;
	gpio_cfg.GPIO_Mode = GPIO_Mode_IPU;
	gpio_cfg.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_cfg.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio_cfg);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// ����������� TIM3
	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
	TIM_TimeBaseStructInit(&TIMER_InitStructure);
	// ������������ TIM_Period = 1. ������ ���������� �� 1. ����������� ���� ����������� ��� ����� ��� ��������� ��������
	TIMER_InitStructure.TIM_Period = 1;
	TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up | TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM3, &TIMER_InitStructure);

	// ����������� Encoder Interface �� ���������� �����������
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		// ����� ����������� ��������. encoder_status == INIT ���� ���� ����� ���� ���
		if (encoder_status == INIT)
			encoder_status = NOREADY;
		else
			encoder_status = READY;

		/* � ������ TIM3_CR1 �� TIM_CR1_DIR ���� �������� ��������� ��������*/
		encoder_direction = (TIM3->CR1 & TIM_CR1_DIR ? BACKWARD : FORWARD);
	}
}

int main(void)
{
	char buffer[80] = {'\0'};

	usart_init();
	encoder_init();

	while (1)
	{
		if (encoder_status)
		{
			encoder_status = NOREADY;

			if (encoder_direction == FORWARD){
				sprintf(buffer, "FORWARD\r\n");
				//....
			}
			else{
				sprintf(buffer, "BACKWARD\r\n");
				//....
			}
			USARTSend(buffer);
		}
	}
}

