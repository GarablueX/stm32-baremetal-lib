

#include "main.h"
#include "LCD_Fonctions.h"






void clock_Init(void){

	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
}










int main(void)
{
	HAL_Init();
	clock_Init();
	LCD_INIT();
	LCDReset();





  while (1){



	  }


  }






