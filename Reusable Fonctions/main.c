#include <LCD_Fonctions.h>
#include "stm32f4xx.h"
#include "fonctions.h"


int main(void) {
    //testing the clocks
    Port_Clocks(GPIOA);
    Port_Clocks(GPIOB);


	HAL_Init();
	LCD_INIT();
	LCDReset();
	//testing inputs and types of the pins
	Port_Clocks(GPIOC);
	Port_Mode(GPIOC, INPUT, 1);
	Input_types(GPIOC, PD, 1);
	Port_Mode(GPIOC, OUTPUT, 2);
	Output_Speed(GPIOC, HIGH, 2);
	Output_Types(GPIOC, OD, 2);
	/////////////////////////////////////////



    while(1) {
    	//testing the read and the set/reset fonctions
    	if(Read_Pin(GPIOC, 1)){
    		Set_Reset_Pin(GPIOC, 2, 1);
    	}
    	else{
    		Set_Reset_Pin(GPIOC, 2, 0);
    	}
        // === ADC on PA0 (pin 0, channel 10, 12-bit, 84 cycles) ===
        uint16_t adc_val = Port_ADC(GPIOC, 0, 10, 12, 112);

        // --- First line: show raw ADC value ---
        LCDsetCursor(1, 0);
        LCDsendAstring("ADC:       ");   // Overwrite old text
        LCDsetCursor(1, 5);
        LCDsendINT(adc_val,6);

        // --- Second line: show voltage as float ---
        float voltage = (adc_val / 4095.0) * 3.3;
        LCDsetCursor(2, 0);

        LCDsetCursor(2, 3);
        LCDsendFloat(voltage, 7);



    }
}
