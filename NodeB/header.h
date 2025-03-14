/*----------Defining datatypes shortcuts-----------*/
typedef struct can1_frame
 {
 	int id;
	int rtr;
	int dlc;
	int byteA;
	int byteB;
 }CAN1;

/*----------Function declarations-----------*/

/*----------Uart functions-----------*/
void uart0_tx_float(float );
extern void uart0_init(unsigned int );
extern void uart0_tx(unsigned char );
extern void uart0_tx_string(char *);
extern void uart0_tx_float(float );
extern int uart0_rx_int(void);

/*----------Delay functions-----------*/
extern void delay_sec(unsigned int );
extern void delay_ms(unsigned int );

/*----------Lcd functions-----------*/
extern void lcd_data(unsigned char );
extern void lcd_init(void);
extern void lcd_string(unsigned char *);
extern void lcd_cmd(unsigned char );

/*----------ADC functions-----------*/
extern short int adc_read(unsigned char );
extern void adc_init(void);

/*----------I2C functions-----------*/
extern unsigned char i2c_byte_read_frame(unsigned char, unsigned char);
extern void i2c_byte_write_frame(unsigned char ,unsigned char ,unsigned char );
extern void i2c_init(void);

/*----------CAN functions-----------*/
extern void can1_init(void);
extern void can1_tx(CAN1 );
extern void can1_rx(CAN1 *);
extern void config_vic_for_can1(void);


