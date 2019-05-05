/*
 * GccApplication1.c
 *
 * Created: 5/5/2019 3:00:55 PM
 * Author : regis
 */ 

#include <avr/io.h>

void i2c_write(unsighned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
}

void i2c_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR & (TWINT)) == 0);
}

void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2c_init(void)
{
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = 0x04;
}

unsigned char i2c_read(unsigned char isLast)
{
	if(isLast == 0)
		TWCR = (1<<TWINT|)|(1<<TWEN)|(1<<TWEA);
	else
		TWCR = (1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
	
	return TWDR;
}

void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);/* Write start location address from where to read */
	I2C_Repeated_Start(0xD1);/* I2C start with device read address */
}

void Read_RawValue()
{
	MPU_Start_Loc();/* Read Gyro values */
	Acc_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	//.. Read other registers
	i2c_stop();
}

int main(void)
{
    char buffer[20], float_[10];
    float Xa;
    I2C_Init();/* Initialize I2C */
    MPU6050_Init();/* Initialize MPU6050 */
    USART_Init(9600);/* Initialize USART with 9600 baud rate */
    while(1)
    {
	    Read_RawValue();
	    /* Divide raw value by sensitivity scale factor to get real values */
	    Xa = Acc_x/16384.0;
	    /* Take values in buffer to send all parameters over USART */
	    dtostrf( Xa, 3, 2, float_ );
	    sprintf(buffer," Ax = %s g\t",float_);
	    USART_SendString(buffer);
    }
}

