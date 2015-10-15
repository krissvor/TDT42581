#include <stdint.h>

#include <stdbool.h>



#include "efm32gg.h"



uint8_t button_mapper();

void button_handler();

uint16_t sound1();

uint16_t sound2();

uint16_t sound3();

uint16_t sound4();

int m = 0;

uint16_t sample;

uint16_t z = 0x888;

uint16_t n = 0xfff;

int x = 0;

int k = 0;

int freq1 = 20;

int freq4 = 200;

int sound1Length = 25000;

int sound2Length = 100000;

int sound3Length = 30000;

int sound4Length = 25000;





/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler(int sound) 

{  

	*TIMER1_IFC = 0x1;

	//(*GPIO_PA_DOUT)++;



	sample = sound1();



		*DAC0_CH0DATA = sample;

		*DAC0_CH1DATA = sample;

	

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

	uint8_t input = button_mapper();

	if(input!=0){

		*GPIO_PA_DOUT= *GPIO_PC_DIN <<8;

		//sound1();

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



uint16_t sound4(){

	if(k<=sound4Length){

		if(m<=25000){

			m+=1;

			x+=1;

			if(m%4000==0){

				freq4-=5; 

			}

			if(x<=freq1){

				z = z+n;

			}

			else if(x<=freq4*2){

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else{

		 	m=0;

		}

		k++;

	}

	else{

		//k = 0;

	} 

	return z;

}





uint16_t sound3(){

	if(k<=sound3Length){

		if(m<=7500){

			m+=1;

			x+=1;

			if(x<=40){

				z = z+n;

			}

			else if(x<=80){

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>7500 && m<=15000){

				m+=1;

				x+=1;

			if(x<=30){

				z = z+n;

			}

			else if(x<=60){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>15000 && m<=22500){

				m+=1;

				x+=1;

			if(x<=20){

				z = z+n;

			}

			else if(x<=40){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>22500 && m<=30000){

				m+=1;

				x+=1;

			if(x<=10){

				z = z+n;

			}

			else if(x<=20){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else{

			m=0;

		}

	k++;

	}

	else{

		//k=0;

	}

	return z;

}









uint16_t sound2(){

	if(k<=sound2Length){

		if(m<=20000){

			m+=1;

			x+=1;

			if(x<=50){

				z = z+n;

			}

			else if(x<=100){

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>20000 && m<=40000){

				m+=1;

				x+=1;

			if(x<=75){

				z = z+n;

			}

			else if(x<=150){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>40000 && m<=60000){

				m+=1;

				x+=1;

			if(x<=80){

				z = z+n;

			}

			else if(x<=160){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else if(m>60000 && m<=80000){

				m+=1;

				x+=1;

			if(x<=100){

				z = z+n;

			}

			else if(x<=200){ 

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else{

			m=0;

		}

		k++;

	}

	else{

		k=0;

	}

	return z;



}





uint16_t sound1(){

	if(k<=sound1Length){

		if(m<=25000){

			m+=1;

			x+=1;

			if(m%1000==0){

				freq1+=5; 

			}

			if(x<=freq1){

				z = z+n;

			}

			else if(x<=freq1*2){

				z = z-n;

			}

			else{

				x=0;

			}

		}

		else{

		 	m=0;

		}

		k++;

	}

	else{

		//k = 0;

	} 

	return z;

}











