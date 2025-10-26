#include<lpc21xx.h>
#include"header_test.h"
void wait(int ms)
{
	T0PR=15000-1;
	T0TCR=0x02;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TC=0;
	T0TCR=0x00;
}

void uart_data_tx(unsigned char inputer)
{
	while((U1LSR & (1<<5) )== 0);
	U1THR=inputer;
}
void uart_service_routine(void)__irq//irq keyword
{
	unsigned char data;
	if(U0IIR&0x04)
	{
		data=U0RBR;
		data_display(data);
		uart_data_tx(data);
		if(data=='y')
		{
			
			IOSET0=0xFF;
			
			
			
		}
		if(data=='n')
		{
			IOCLR0=0xFF;
			wait(100);
			
		}
	}
	VICVectAddr=0;
}


char uart_data_rx(void)
{
	unsigned char rec;
	while((U1LSR & 0x01)==0);
	rec=U1RBR;
	return rec;
	
}
void uart_config(void)
{
	PINSEL0 &= ~(0xF00);              
	PINSEL0 |= (1 << 18) | (1 << 16); 

	
	U1LCR=0x83;
	U1DLL=97;
	U1DLM=0;
	U1LCR=0x03;
	
	//U0IER=1<<0;
	
	VICIntSelect=0;
	VICVectCntl4=0x20|6;
	VICVectAddr4=(unsigned long)uart_service_routine;
	VICIntEnable=1<<6;
	
	
	
}
int main()
{
		unsigned char buffer=0;
		lcd_config();
		uart_config();
		
		
	
		
	while(1)
	{
		wait(100);
		buffer=uart_data_rx();
		lcd_cmd(0x80);
		uart_data_tx(buffer);
		data_display(buffer);
		wait(100);
		
		
	}
}

