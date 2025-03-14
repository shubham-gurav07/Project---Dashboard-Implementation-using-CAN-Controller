#include <LPC21xx.H>
#include "header.h"
#define RS 1<<17
#define RW 1<<18
#define EN 1<<19
#define LED ((0xfe)<<16)
void lcd_data(unsigned char data)
{

	IOCLR1=LED;
	IOSET1=((data & 0xf0)<<16);
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;

	IOCLR1=LED;
	IOSET1=((data & 0x0f)<<20);
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void lcd_cmd(unsigned char cmd)
{
	IOCLR1=LED;
	IOSET1=((cmd & 0xf0)<<16);
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;

	IOCLR1=LED;
	IOSET1=((cmd & 0x0f)<<20);
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void lcd_init(void)
{
	IODIR1=LED;
	PINSEL2|=0X0;
	IOCLR1=EN;
	lcd_cmd(0x02);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
}

//printing string in LCD
void lcd_string(unsigned char *ptr)
{
	while(*ptr)
		lcd_data(*ptr++);
}

//pritnig the Integer Number on LCD
void lcd_int(int num)
{
	int a[16],i;

	if(num==0)
	{
		lcd_data('0');
		return;
	}

	if(num<0)
	{
		num=-num;
		lcd_data('-');
	}

	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}

	for(i=i-1 ; i>=0 ; i--)
		lcd_data(a[i]);

}

