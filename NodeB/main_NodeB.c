#include <LPC21xx.H>
#include "header.h"

CAN1 v1,v2;
extern int flag1,flag2;
main()
{
	unsigned char hr,min,dd,mm,yy,ss;
	can1_init();
	//uart0_init(9600);
	config_vic_for_can1();
	lcd_init();
	i2c_init();
	i2c_byte_write_frame(0xD0,0x2,0x42);//hr
	i2c_byte_write_frame(0xD0,0x1,0x13);//min
	i2c_byte_write_frame(0xD0,0x4,0x03);//dd
	i2c_byte_write_frame(0xD0,0x5,0x07);//mm
	i2c_byte_write_frame(0xD0,0x6,0x24);//yyyy
	i2c_byte_write_frame(0xD0,0x0,0x50); //ss
	while(1)
	{
		hr=i2c_byte_read_frame(0xD0,0x2);
		min=i2c_byte_read_frame(0xD0,0x1);
		dd=i2c_byte_read_frame(0xD0,0x4);
		mm=i2c_byte_read_frame(0xD0,0x5);
		yy=i2c_byte_read_frame(0xD0,0x6);
		ss=i2c_byte_read_frame(0xD0,0x0);

		if((hr>>6)&1)
			hr=hr^(1<<6);
		if((hr>>5)&1)
			hr=hr^(1<<5);
		lcd_cmd(0x80);
		lcd_data((hr/0x10)+48);
		lcd_data((hr%0x10)+48);
		lcd_data(':');
		lcd_data((min/0x10)+48);
		lcd_data((min%0x10)+48);
		lcd_data(' ');
		lcd_data((dd/0x10)+48);
		lcd_data((dd%0x10)+48);
		lcd_data(':');
		lcd_data((mm/0x10)+48);
		lcd_data((mm%0x10)+48);
		lcd_data(':');
		lcd_data('2');
		lcd_data('0');
		lcd_data((yy/0x10)+48);
		lcd_data((yy%0x10)+48);


		if(flag1==1)
		{
			flag1=0;
			lcd_cmd(0xc0);
			lcd_string("T:");
			lcd_data(((v1.byteA)/10)+48);
			lcd_data(((v1.byteA)%10)+48);
			lcd_data('C');

		}
		if(flag2==1)
		{
			flag2=0;
			lcd_cmd(0xc8);
			lcd_string("Kmph:");
			lcd_data(((v2.byteA)/100)+48);
			lcd_data((((v2.byteA)/10)%10)+48);
			lcd_data(((v2.byteA)%10)+48);
		}
	}
}

