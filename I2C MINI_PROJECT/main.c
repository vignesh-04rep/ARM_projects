#include<lpc21xx.h>
#include"header.h"
unsigned int input;
unsigned char count;



void ext2(void) __irq
{
    EXTINT = (1<<0);     
    count++;
		data_send(0x50,0x00,count);
    input ^= 1; 
		
    VICVectAddr = 0;
}

int main()
{
    PINSEL1 |= (1<<0) | (3<<8);  
    EXTMODE |= (1<<2) | (1<<3);   
    EXTPOLAR &= ~((1<<2)|(1<<3)); 

    VICIntEnable |= (1<<14) | (1<<17);

    VICVectAddr1 = (unsigned long) ext2;
    VICVectCntl1 = (1<<5) | 14;

    i2c_init();
    lcd_config();
		count=data_read(0x50,00);
    while(1)
    {
       
        if(input == 1)
				{
						 lcd_cmd(0x80);
            string_display("LED ON....");
				}
        else
				{
						lcd_cmd(0x80);
            string_display("LED OFF...");
				}

        //lcd_cmd(0xC0);
        //string_display("count:");
        lcd_cmd(0xC0);
        data_display(count);
    }
}
