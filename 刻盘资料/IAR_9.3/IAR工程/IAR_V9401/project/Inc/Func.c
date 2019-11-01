
#include "dw8051.h"
#include "ExLigReg.h"
#include "ExLigLib.h"
#include "Func.h"
#include "delay.h"

void Init_Port(void)
{
/// 上电时IO口 配置为屏蔽输入，禁止输出
	P0IE = 0x00;
	P0OE = 0xff;
	P1IE = 0x00;
	P1OE = 0xff;
	P2IE = 0x00;
	P2OE = 0xff;
	P3IE = 0x00;
	P3OE = 0xff;
	P4IE = 0x00;
	P4OE = 0xff;
	P5IE = 0x00;
	P5OE = 0xff;
	P6IE = 0x00;
	P6OE = 0xff;
	P7IE = 0x00;
	P7OE = 0xff;
	P8IE = 0x00;
	P8OE = 0xff;
	//LCD显示，必须配置为禁止输入输出
}
//*************************************************/
void Led_Twin(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//
	{  
		LED_ON();
		delay_100ms(3);
		LED_OFF();
		delay_100ms(3);		  
	}
}
