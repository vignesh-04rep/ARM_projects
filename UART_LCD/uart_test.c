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
char uart_data_rx(void)
{
	unsigned char rec;
	while((U1LSR & 0x01)==0);
	rec=U1RBR;
	return rec;
	
}
void uart_service_routine(void)__irq
{
	unsigned char data;
	unsigned int looper=0;
	
	
	if((U1IIR&0x0E)==0x04)
	{
		data=uart_data_rx(); 
		looper++;
		 data = U1RBR;
		 
     wait(2);
		if(looper<8)
		{
			lcd_cmd(0x80+looper);
     data_display(data);
			uart_data_tx(data);
		}
		else
		{
			lcd_cmd(0xc0+(looper-8));
			data_display(data);
			if(looper==16)
			{
				looper=0;
			}
		}
        
		
	}
	VICVectAddr=0;
}
	



void uart_config(void)
{
	PINSEL0 &= ~(0xF00);              
	PINSEL0 |= (1 << 18) | (1 << 16); 

	
	U1LCR=0x83;
	U1DLL=78;
	U1DLM=0;
	U1LCR=0x03;
	
	U1IER=1<<0;
	
	VICIntSelect=0;
	VICVectCntl4=0x20|7;
	VICVectAddr4=(unsigned long)uart_service_routine;
	VICIntEnable=1<<7;
	
	
	
}
int main()
{
		lcd_config();
		uart_config();
		
		
	
		
	while(1)
	{
		
		while(1);
	}
}

