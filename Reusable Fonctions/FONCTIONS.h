

#ifndef INC_FONCTIONS_H_
#define INC_FONCTIONS_H_

#ifndef GPIOF
#define GPIOF   ((GPIO_TypeDef *) 0x40021400) // address for STM32F401 (see datasheet)
#endif
#ifndef GPIOG
#define GPIOG   ((GPIO_TypeDef *) 0x40021800) // not present on all STM32F4, can comment if not needed
#endif

// PINS MODES
#define INPUT 0
#define OUTPUT 1
#define ANALOG 2
#define ALTER 3
/////////////////////////////////
//OUTPUT TYPES
// Output Speed
#define LOW     0
#define MEDIUM  1
#define FAST    2
#define HIGH    3

// Input Types
#define NO      0
#define PU      1
#define PD      2

#define PP 0
#define OD 1



static inline void Port_Mode(GPIO_TypeDef *Port , uint8_t type , int pinNumber){
	if(type==INPUT){
		Port->MODER &=~(0x3<< (pinNumber * 2 ));

	}
	else if(type==OUTPUT){
		Port->MODER &=~(0x3<< (pinNumber * 2 ));
		Port->MODER |=(0x1<< (pinNumber * 2 ));
	}

	else if(type==ANALOG){
		Port->MODER &=~(0x3<< (pinNumber * 2 ));
		Port->MODER |=(0x3<< (pinNumber * 2 ));
	}
	else if(type==ALTER)
	{
		Port->MODER &=~(0x3<< (pinNumber * 2 ));
		Port->MODER |=(0x2<< (pinNumber * 2 ));
	}
	else{

	}
}


static inline void Output_Types(GPIO_TypeDef *Port , uint8_t type , int pinNumber){
	if(type==PP){
		Port->OTYPER &=~(0x1<< (pinNumber  ));

	}
	else if (type==OD)
	{
		Port->OTYPER &=~(0x1<< (pinNumber  ));
		Port->OTYPER |=(0x1<< (pinNumber  ));
	}
	else {

	}

}


static inline void Output_Speed(GPIO_TypeDef *Port , uint8_t type , int pinNumber){

	uint8_t Value;
	switch(type){
	case LOW : Value=0;break;
	case MEDIUM : Value=1 ; break;
	case FAST : Value=2;break;
	case HIGH : Value=3 ; break;
	default : Value=0; // LOW
	}
	Port->OSPEEDR &=~(0x3<< (pinNumber * 2 ));
	Port->OSPEEDR |=(Value<< (pinNumber * 2 ));


}

static inline void Input_types(GPIO_TypeDef *Port , uint8_t type , int pinNumber){


	uint8_t Value;

	switch(type){
	case NO : Value=0;break;
	case PU : Value=1;break;
	case PD : Value=2;break;
	}
	Port->PUPDR &=~(0x3<< (pinNumber * 2 ));
	Port->PUPDR |=(Value << (pinNumber * 2 ));



}

static inline uint8_t Read_Pin(GPIO_TypeDef *Port  , int pinNumber){

	uint8_t Value =  Port->IDR &  (1<< pinNumber);

	return Value;
}


static inline void Port_Clocks(GPIO_TypeDef *port){

	if(port==GPIOA){

	RCC->AHB1ENR |=(0x1 <<0);
	}
	else if(port== GPIOB){

	RCC->AHB1ENR |=(0x1 <<1);
	}
	else if(port==GPIOC){

	RCC->AHB1ENR |=(0x1 <<2);
	}

	else if(port==GPIOD){

	RCC->AHB1ENR |=(0x1 <<3);
	}
	else if(port==GPIOE){

	RCC->AHB1ENR |=(0x1 <<4);
	}
	else if(port==GPIOF){

	RCC->AHB1ENR |=(0x1 <<5);
	}
	else if(port==GPIOG){

	RCC->AHB1ENR |=(0x1 <<6);
	}
	else if(port==GPIOH){

	RCC->AHB1ENR |=(0x1 <<7);
	}

	else{}
}

inline static uint16_t Port_ADC(GPIO_TypeDef *Port , int pinNumber , int Channel, int Resolution , int Samples ){


	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	Port_Clocks(Port);
	Port_Mode(Port, ANALOG, pinNumber);
	Input_types(Port, NO, pinNumber);

	uint8_t Value;

	switch(Resolution){
	case 6 : Value =3; break;
	case 8 : Value =2; break;
	case 10 :Value =1; break;
	case 12 :Value =0;break;
	default :Value=3;
	}
	ADC1->CR1 &=~(0x3<< 24);
	ADC1->CR1 |=(Value<< 24 );

	uint8_t Value1;
	switch(Samples){
	case 3:Value1=0;break;
	case 15:Value1=1;break;
	case 28:Value1=2;break;
	case 56:Value1=3;break;
	case 84:Value1=4;break;
	case 112:Value1=5;break;
	case 144:Value1=6;break;
	case 480:Value1=7;break;
	default :Value1=5;
	}
	if(Channel<=9){
		ADC1->SMPR2 &=~(0x7<<(Channel*3));
		ADC1->SMPR2 |=(Value1<<(Channel*3));

	}else{
		ADC1->SMPR1 &=~(0x7<<(Channel - 10)*3);
		ADC1->SMPR1 |=(Value1<<(Channel - 10)*3);

	}
	ADC1->SQR3 &= ~(0x1F);

	ADC1->SQR3 |=Channel;

	ADC1->SQR1 &= ~(0xF << 20);

	ADC1->CR2 |=ADC_CR2_SWSTART;

	while(!(ADC1->SR & ADC_SR_EOC)){}

	uint16_t ADCValue;

	ADCValue=ADC1->DR;

	return ADCValue;

}




#endif
