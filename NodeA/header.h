/*--------------Header file-------------*/

typedef  unsigned int u32;
typedef   int s32;
typedef unsigned char u8 ;
typedef  char s8;
typedef  unsigned short int u16;
typedef  short int s16;

#define sw1 ((IOPIN0>>14)&1)

typedef struct can1_frame
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN1;

extern void can1_init(void);
extern void can1_tx(CAN1 );

extern void timer2_config(void);

extern unsigned short int adc_read(unsigned char );
extern void adc_init(void);

extern void delay_sec(unsigned int );
extern void delay_ms(unsigned int );

