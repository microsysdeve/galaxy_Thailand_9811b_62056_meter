/***************************** Copyright by Vango ***********************************
	�ļ�����ReadMeterPara.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h,intrins.h


	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//#include "pmRead.h"
#include <INTRINSICS.H>

/*���ܣ���ȡ����ģ�����
	addr�������Ĵ�����ַ
	��ȡ���ݴ����ȫ�ֱ���u32PMdatal��8PMdatah
	
*/

void ReadMeterPara(unsigned int addr)
{
      volatile unsigned char xdata* u8Point;
      volatile unsigned long xdata* u32Point;
      unsigned long u32Data;
     // unsigned char i;


      u8Point = (volatile unsigned char xdata*)addr;
    //  i  = *u8Point;
       __no_operation();__no_operation();__no_operation();
    
 //   mt_rd_buff();
    u8Point = (volatile unsigned char xdata*)0x10ec;
    u8PMdatah = *u8Point;
    u32Point = (volatile unsigned long xdata*)0x10e8;
    u32Data = *u32Point;
    u32PMdatal = ((u32Data&0xff)<<24)|((u32Data&0xff00)<<8)|((u32Data&0xff0000)>>8)|((u32Data)>>24);

}

