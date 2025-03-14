#include <LPC21xx.H>
#include "header.h"
#define TCS ((C2GSR>>3)&1)

int flag1,flag2;
extern CAN1 v1,v2;

void can1_init(void)
{
	VPBDIV=1;	          // PCLK=60MHZ
	PINSEL1|=0X00014000;  // P0.25(RD1)
	C2MOD=1;		      // RESET MODE ON
	C2BTR=0X001C001D;	  // SET THE BAUDRATE 125Kbps
	AFMR=2;			      // ACCEPT ALL INCOMING MESSAGE
	C2MOD=0;		      // RESET MODE OFF
}

void can1_rx_handler(void)__irq
{
	v1.id=C2RID;
	v1.rtr=((C2RFS>>30)&1);
	v1.dlc=((C2RFS>>16)&0xf);

	v2.id=C2RID;
	v2.rtr=((C2RFS>>30)&1);
	v2.dlc=((C2RFS>>16)&0xf);

	if(v1.rtr==0)
	{
		if(v1.id==0x500)
		{
			flag1=1;
			v1.byteA=C2RDA;
			v1.byteB=C2RDB;
		}
	}

	if(v2.rtr==0)
	{
		if(v2.id==0x501)
		{
			flag2=1;
			v2.byteA=C2RDA;
			v2.byteB=C2RDB;
		}
	}
	C2CMR=(1<<2);
	VICVectAddr=0;
}

void config_vic_for_can1(void)
{
	VICIntSelect=0;
	VICVectAddr1=(unsigned int)can1_rx_handler;
	VICVectCntl1=27|(1<<5);
	VICIntEnable|=(1<<27);
	C2IER=1;  // EN CAN1 RX INTRRUPT
}


