/***************************** Copyright by Vango ***********************************
	�ļ�����SetMChannel.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h,intrins.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
#include <INTRINSICS.H>
//#include "pmWrite.h"
/*
	�������ܣ�һ������ϵ�ִ�У����������м����Ĵ���������������ֵ
*/

void InitMeter(void)
{
    unsigned char i;
    volatile unsigned char xdata *p;
	p = &PMCtrl1;//ȡ��ַ
	*p = 0x80;
    p  = &(*((volatile unsigned char xdata*)0x10e8));
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    for( i = 0x00; i <= 0xe3; i++)
    {

	    p  = (&(*((volatile unsigned char xdata*)0x1000)))+i;
	    *p = 0;
	    __no_operation();__no_operation();__no_operation();
	}
   for( i = 0xf0; i <= 0xfd; i++)
    {
	    
	    p  = (&(*((volatile unsigned char xdata*)0x1000)))+i;
	    *p = 0;
	    __no_operation();__no_operation();__no_operation();
	}
    p  = (&(*((volatile unsigned char xdata*)0x10e8)));
    *p = 0xbc;
    p++;
    *p = 0x74;
    p++;
    *p = 0x93;
    p++;
    *p = 0x88;
    p++;
    *p = 0;
    for( i = 0xe4; i <= 0xe6; i++)
    {

	    p  = ((volatile unsigned char xdata*)0x1000)+i;
	    *p = 0;
	    __no_operation();__no_operation();__no_operation();
	}

    p  = (volatile unsigned char xdata*)0x10e8;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0x8c;
    p++;
    *p = 0x01;
    p  = (volatile unsigned char xdata *)0x10f4;
    *p = 0;
    __no_operation();__no_operation();__no_operation();
    p  = (volatile unsigned char xdata *)0x10fa;
    *p = 0;
    __no_operation();__no_operation();__no_operation();
    p  = (volatile unsigned char xdata *)0x10e8;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0x00;
   p  = (volatile unsigned char xdata *)0x10f5;
    *p = 0;
    __no_operation();__no_operation();__no_operation();
   p  = (volatile unsigned char xdata *)0x10fb;
    *p = 0;
    __no_operation();__no_operation();__no_operation();	
	p =(volatile unsigned char xdata *) 0x2878;
	*p = 0x00;

	
}