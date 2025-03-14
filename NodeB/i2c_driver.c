#include <LPC21xx.H>
#include "header.h"
#define SI ((I2CONSET>>3)&1)

void i2c_byte_write_frame(unsigned char ad,unsigned char mr,unsigned char data)
{

	/* START CONDITION  */

	I2CONSET=(1<<5);//STA bit is 1
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	I2CONCLR=(1<<5);//Clear STA flag
	if(I2STAT!=0x08)
	{
		uart0_tx_string("START Err...\r\n");
		goto exit;
	}

	/* Slave Address +	Write mode (SA+W) */

	I2DAT=ad;  //Add data in I2DAT register
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	if(I2STAT!=0x18)
	{
		uart0_tx_string("SA+W Err...\r\n");
		goto exit;
	}

	/* Memory Address */

	I2DAT=mr;//sending memory address to slave
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);
	if(I2STAT!=0x28)
	{
		uart0_tx_string("mr Err...\r\n");
		goto exit;
	}

	/* DATA */

	I2DAT=data;//sending data to slave
	I2CONCLR=(1<<3);//clear SI Flag
	while(SI==0);
	if(I2STAT!=0X28)
	{
		uart0_tx_string("DATA Err...\r\n");
		goto exit;
	}

	/* STOP Condition */

exit:
	I2CONSET=(1<<4);//STOP bit setting
	I2CONCLR=(1<<3);//clear SI Flag
}

unsigned char i2c_byte_read_frame(unsigned char ad,unsigned char mr)
{
	unsigned char temp;

	/* START CONDITION  */

	I2CONSET=(1<<5);//STA bit is 1
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	I2CONCLR=(1<<5);//Clear STA flag
	if(I2STAT!=0x08)
	{
		uart0_tx_string("START Err...\r\n");
		goto exit;
	}

	/* Slave Address +	Write mode (SA+W) */

	I2DAT=ad;  //Add data in I2DAT register
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	if(I2STAT!=0x18)
	{
		uart0_tx_string("SA+W Err...\r\n");
		goto exit;
	}

	/* Memory Address */

	I2DAT=mr;//sending memory address to slave
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);
	if(I2STAT!=0x28)

	{
		uart0_tx_string("mr Err...\r\n");
		goto exit;
	}

	/* RE-START CONDITION  */
	I2CONSET=(1<<5);//STA bit is 1
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	I2CONCLR=(1<<5);//Clear STA flag
	if(I2STAT!=0x10)
	{
		uart0_tx_string("RE-START Err...\r\n");
		goto exit;
	}

	/* Slave Address +	Write mode (SA+R) */
	I2DAT=ad|1;  //Add data in I2DAT register
	I2CONCLR=(1<<3);//Clear SI Flag
	while(SI==0);
	if(I2STAT!=0x40)
	{
		uart0_tx_string("SA+R Err...\r\n");
		goto exit;
	}

	/* Read data & send ACK */
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);	//waiting for data received
	temp=I2DAT;

	/* STOP Condition */
exit:
	I2CONSET=(1<<4);//STOP bit setting
	I2CONCLR=(1<<3);//clear SI Flag
	return temp;
}

void i2c_init(void)
{
	PINSEL0|=0X50;//P0.2->SCL, P0.3->SDA
	I2SCLL=I2SCLH=75;//100kbps Frequency is set
	I2CONSET=(1<<6);//Enable I2C interface
}

