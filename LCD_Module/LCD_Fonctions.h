


#ifndef LLCD_Fonctions

#define LCD_Fonctions

#include "stm32f4xx_hal.h"

#include "stdio.h"





#define LCDD0Pin 12
#define LCDD0Port GPIOA

#define LCDD1Pin 13
#define LCDD1Port GPIOA

#define LCDD2Pin 14
#define LCDD2Port GPIOA

#define LCDD3Pin 15
#define LCDD3Port GPIOA

#define LCDD4Pin 0
#define LCDD4Port GPIOB

#define LCDD5Pin 1
#define LCDD5Port GPIOB

#define LCDD6Pin 2
#define LCDD6Port GPIOB


#define LCDD7Pin 3
#define LCDD7Port GPIOB

#define LCDRSPin 9
#define LCDRSPort GPIOA


#define LCDRWPin 10
#define LCDRWPort GPIOA

#define LCDENPin 11
#define LCDENPort GPIOA


static inline void NETimeDelay(int TIME ){

	for(int i =0 ;i<TIME;i++){
	}

}



static inline void settingPortAndPinForOutput(GPIO_TypeDef *port,int pinNumber){

	port->MODER &= ~(3 << (pinNumber * 2));
	port->MODER |=  (1 << (pinNumber * 2));

	port->OSPEEDR |=(1<<(pinNumber*2 +1));
	port->OSPEEDR |=(1<<(pinNumber*2 ));

	port->OTYPER &=~(1<<pinNumber);
	port->PUPDR &=~(3<<pinNumber*2);

}



static inline void sendBitToPortAndPin(uint8_t a,GPIO_TypeDef *port,int pinNumber,uint8_t Mask){

	if(a & Mask){
		port->BSRR =1 << pinNumber;
	}
	else
	{
		port->BSRR =1<<(pinNumber+16);
	}
}



static inline void SetToReadOrWrite(int mode ){
    if (mode == 0){
        LCDRWPort->BSRR = (1 << (LCDRWPin + 16));
    }
    else if (mode == 1){
        LCDRWPort->BSRR = (1 << LCDRWPin);
    }
    NETimeDelay(10000);
}



static inline void Command_Charactermode(int mode ){
	 if (mode==0){

		 LCDRSPort->BSRR=(1<<(LCDRSPin+16));
	 }
	 else if (mode==1){
		 LCDRSPort->BSRR=(1<<LCDRSPin);
	 }
	 NETimeDelay(10000);
}





static inline void sendByteToLCD(uint8_t x){
	sendBitToPortAndPin(x ,LCDD0Port,LCDD0Pin,0b00000001);
	sendBitToPortAndPin(x ,LCDD1Port,LCDD1Pin,0b00000010);
	sendBitToPortAndPin(x ,LCDD2Port,LCDD2Pin,0b00000100);
	sendBitToPortAndPin(x ,LCDD3Port,LCDD3Pin,0b00001000);
	sendBitToPortAndPin(x ,LCDD4Port,LCDD4Pin,0b00010000);
	sendBitToPortAndPin(x ,LCDD5Port,LCDD5Pin,0b00100000);
	sendBitToPortAndPin(x ,LCDD6Port,LCDD6Pin,0b01000000);
	sendBitToPortAndPin(x ,LCDD7Port,LCDD7Pin,0b10000000);


	// E pulse roughly  accroding to datasheet
	LCDENPort->BSRR = (1 << LCDENPin);
	NETimeDelay(1500);
	LCDENPort->BSRR = (1 << (LCDENPin+16));
	NETimeDelay(1500);

}


static inline void LCDsendAcharacter(uint8_t character){

	SetToReadOrWrite(0);
	Command_Charactermode(1);
	sendByteToLCD(character);
}






static inline void LCDsendAstring(char *String){

	while(*String){

	LCDsendAcharacter(*String++);

	}



}

static inline void LCDsendINT(int integer, unsigned int  length ){

	char String[length];
	sprintf(String,"%d",integer);
	LCDsendAstring(String);

}

static inline void LCDsendAcommand(uint8_t command){
	SetToReadOrWrite(0);
	Command_Charactermode(0);
	sendByteToLCD(command);

}
static inline void LCDReset(){

	LCDsendAcommand(0x01);

}



static inline void LCDsendFloat(float FloatNumber, unsigned int MAXlength)
{
    char String[MAXlength];
    sprintf(String, "%.2f", FloatNumber);  // Changed %e to %.2f
    LCDsendAstring(String);
}




static inline void LCDLine2Enable(){


	LCDsendAcommand(0x38);
}


inline static void LCDTESTLCDCASES(){
	LCDLine2Enable();
	for(int i =0 ; i<32;i++){
		if(i<16){
		LCDsendAcommand(0x80 + i );
		LCDsendAstring("X");
		}
		else{
		LCDsendAcommand(0x80 + i + 48 );
		LCDsendAstring("X");
		}
	}
	LCDReset();
	LCDsendAcommand(0x80);
	LCDsendAstring("Test done !! ");
	LCDsendAcommand(0x80 + 64);
	LCDsendAstring("Test done !! ");
}

static inline void LCDsetCursor(int line , int column){
	// there is 2 LINE and 16 columns
	//each line comes from 0--15 ( columns start from index 0 to 15)
	LCDLine2Enable();
	if(column>=0 && column<=15){

	if(line==1){
		LCDsendAcommand(0X80 + column);

	}
	if(line==2){

		LCDsendAcommand(0X80 + 64 + column);

	}
	else {
		return ;
	}


	}
}




















static inline void LCD_INIT(void){
	settingPortAndPinForOutput(LCDD0Port,LCDD0Pin);
	settingPortAndPinForOutput(LCDD1Port,LCDD1Pin);
	settingPortAndPinForOutput(LCDD2Port,LCDD2Pin);
	settingPortAndPinForOutput(LCDD3Port,LCDD3Pin);
	settingPortAndPinForOutput(LCDD4Port,LCDD4Pin);
	settingPortAndPinForOutput(LCDD5Port,LCDD5Pin);
	settingPortAndPinForOutput(LCDD6Port,LCDD6Pin);
	settingPortAndPinForOutput(LCDD7Port,LCDD7Pin);
	settingPortAndPinForOutput(LCDRSPort,LCDRSPin);
	settingPortAndPinForOutput(LCDRWPort,LCDRWPin);
	settingPortAndPinForOutput(LCDENPort,LCDENPin);

	sendByteToLCD(0x0C);   // display ON

}



#endif
