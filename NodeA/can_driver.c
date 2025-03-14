#include <LPC21xx.H>
#include "header.h"
#define TCS ((C2GSR>>3)&1)

void can1_init(void)
{
	VPBDIV=1;	          // PCLK=60MHZ
	PINSEL1|=0X00014000;  // P0.25(RD1)
	C2MOD=1;		      // RESET MODE ON
	C2BTR=0X001C001D;	  // SET THE BAUDRATE 125Kbps
	AFMR=2;			      // ACCEPT ALL INCOMING MESSAGE
	C2MOD=0;		      // RESET MODE OFF
}


void can1_tx(CAN1 v)
{
	C2TID1=v.id;
	C2TFI1=(v.dlc<<16);

	if(v.rtr==0)
	{
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else
	{
		C2TFI1|=(1<<0);
		//	 C2CMR=0X21;
		//	 while(TCS==0);
	}
	C2CMR=1|(1<<5);
	while(((C2GSR>>3)&1)==0);
}

