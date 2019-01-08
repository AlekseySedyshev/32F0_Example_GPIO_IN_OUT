#include "stm32f0xx.h"        // Device header

#define LED_ON()  GPIOB->BRR  |=1
#define LED_OFF() GPIOB->BSRR |=1

#define PB1_READ() (GPIOB->IDR & 1<<1)


void delay_ms (uint16_t value) {
    TIM17->ARR = value;
    TIM17->CNT = 0;
    TIM17->CR1 = TIM_CR1_CEN;
    while((TIM17->SR & TIM_SR_UIF)==0){}
		TIM17->SR &= ~TIM_SR_UIF;
}

void initial (void)
{
	/*timer config*/
  RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;    						//HSI 8 MHz - 1 msek
  TIM17->PSC = 8000-1;
  TIM17->CR1 |= TIM_CR1_OPM;                          //One time run.
	
	/*GPIOB CONFIG */ 
	RCC->AHBENR  |= RCC_AHBENR_GPIOBEN; 								//
	
	GPIOB->MODER |= GPIO_MODER_MODER0_0; 								// PB0 - Output mode
	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR1_0;                //PB1 - Input, PullUp.

} 

int main(void)
{
initial();

//-----------------------------initial data----------------------------------

while (1)  /* Main loop */
{

if(!(GPIOB->IDR & 1<<1))	{
									//GPIOB->BRR  |=(1<<0);													//  00000000
								    GPIOB->ODR  &=~(1<<0);												//	00000001
							}
else  				  {
								  //GPIOB->BSRR |=(1<<0);
								    GPIOB->ODR  |=(1<<0);
							}

	
} // end - main loop 
} // end - Main  
	
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ while (1)  {  } }
#endif
