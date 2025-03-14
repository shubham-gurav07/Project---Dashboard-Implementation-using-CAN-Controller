#include <LPC21xx.H>
#include "header.h"
CAN1 v1,v2;
int temp1,temp2;

main()
{
	can1_init();
	adc_init();
	timer2_config();
	while(1)
	{ 
		temp1=adc_read(2); 	// reading the data
		temp2=adc_read(1); 	// reading the data
		delay_ms(200);
		v1.id=0x500;
		v1.dlc=4;
		v1.byteA=((temp2/3.65)-32);
		can1_tx(v1);
		delay_ms(200);
	}

}

