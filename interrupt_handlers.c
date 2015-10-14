#include <stdint.h>

#include <stdbool.h>



#include "efm32gg.h"



uint8_t button_mapper();

void button_handler();



/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 

{  

	*TIMER1_IFC = 0x1;

//	(*GPIO_PA_DOUT)++;

  /*

    TODO feed new samples to the DAC

    remember to clear the pending interrupt by writing 1 to TIMER1_IFC

  */  

}



/* GPIO even pin interrupt handler */

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 

{

	*GPIO_IFC = 0x1;

	button_handler();

    /* TODO handle button pressed event, remember to clear pending interrupt */

}



/* GPIO odd pin interrupt handler */

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 

{

	*GPIO_IFC = 0x1;

	button_handler();

	

    /* TODO handle button pressed event, remember to clear pending interrupt */

}





void button_handler(){

	//int input = button_mapper();

	//*GPIO_PA_DOUT= *GPIO_PC_DIN <<8;

	int input = button_mapper();

	if(input!=0){

		(*GPIO_PA_DOUT)++;

	}

}





uint8_t button_mapper(){

	uint8_t input = ~(*GPIO_PC_DIN);



	switch(input){

		case 0x1:

			return 1;



		case 0x2:

			return 2;



		case 0x4:

			return 3;



		case 0x8:

			return 4;



		case 0x10:

			return 5;



		case 0x20:

			return 6;



		case 0x40:		

			return 7;

		

		case 0x80:

			return 8;



		default:

			break;

 

	}

	return 0;

}
