/***************************** Copyright by Vango ***********************************
	�ļ�����SetMeterCfg.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h,intrins.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//#include "pmWrite.h"
#include <INTRINSICS.H>

/*
	���ܣ����ü�����·���������
	����������ȫ�ֱ���u32PMdatal��8PMdatah
	val_addr�������Ĵ�����ַ
*/


void SetMeterCfg(unsigned int addr)
{
    volatile unsigned char xdata *p;
    
  //  mt_wr_buff(dat_h, dat_l);
    p  = (volatile unsigned char xdata *)0x10e8;
    *p = (unsigned char)(u32PMdatal);
    p++;
    *p = (unsigned char)(u32PMdatal>>8);
    p++;
    *p = (unsigned char)(u32PMdatal>>16);
    p++;
    *p = (unsigned char)(u32PMdatal>>24);
    p++;
    *p = (unsigned char)(u8PMdatah);
    p  = (volatile unsigned char xdata *)addr;
    *p = 0;
    __no_operation();__no_operation();__no_operation();
}
