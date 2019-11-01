
#include "dw8051.h"
#include "ExLigReg.h"
#include "ExLigLib.h"
#include "Func.h"
#include "delay.h"

void Init_Port(void)
{
/// �ϵ�ʱIO�� ����Ϊ�������룬��ֹ���
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
	//LCD��ʾ����������Ϊ��ֹ�������
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
