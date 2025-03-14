#include <lpc21xx.h>
#include "header.h"
extern int temp1,temp2;
extern CAN1 v1,v2;
//extern int flag0;

void timer1_handler(void)__irq
{
	float vout;
	v2.id=0x501;
	v2.rtr=0;
	v2.dlc=4;
	vout=((((temp1*3.3)/1023)-0.5)/0.01);
	v2.byteA=vout;
	can1_tx(v2);
	T1IR = 1;
	T1TC=T1PC=0;
	VICVectAddr = 0;
}

void timer2_config(void)
{
	VICIntSelect = 0;
	VICIntEnable|=(1<<5);
	VICVectCntl0=5|(1<<5);
	VICVectAddr0=(unsigned int)timer1_handler;

	T1PC=0;
	T1PR=15000000-1;
	T1TC=0;
	T1MCR=3;	   //reset
	T1MR0=1;	  //1sec
	T1TCR=1;
}

