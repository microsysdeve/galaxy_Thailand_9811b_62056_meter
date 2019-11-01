
/***************************** Copyright by Vango ***********************************

	�ļ����ͣ�V9801TEST C51 Keil3��д����
	�ļ����ã���Ҫ����SuperDebug���ز���,������ɺ�������LED��������500ms��˸3�Σ�ͣ��2S
			  ʱ�����300ms���������˸5�Σ��ٴ�ͣ��1.8Sʱ�����200ms���������˸7�Ρ���ͣ��1.7S��
			  �����µ�ѭ������FLASH���سɹ���SuperDebug�ɳɹ�������V9801��4��CODE BANK��ȥ��

	�� �� �ˣ�DL
	�������ڣ�2011��12��31��
	��ǰ�汾��V9801Test_Ver1.0
	
	�汾��Ϣ��V9801Test_ver1.0
**************************************************************************************/
#include "delay.h"
#include "V98xx.h"
#include "TestFunc.h"
#include "bank1.h"
#include "bank2.h"
#include "bank3.h"
 /*=========================================================================================\n
* @function_name: CrcTab
* @function_file: Api.c
* @����: X16+X12+X5+1 ��ʽ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-02-29)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
const uint16 code CrcTab[256]={ // X16+X12+X5+1 ��ʽ��
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};
void GPIO_INIT()//�˿ڳ�ʼ��
{
 	P0OE = 0XFF;
	P0IE = 0X00;
	P1OE = 0XFF;
	P1IE = 0X00;
	P2OE = 0XFF;
	P2IE = 0X00;
	P3OE = 0XFF;
	P3IE = 0X00;
	P4OE = 0XFF;
	P4IE = 0X00;
	P5OE = 0XFF;
	P5IE = 0X00;
	P6OE = 0XFF;
	P6IE = 0X00;
	P7OE = 0XFF;
	P7IE = 0X00;
	P8OE = 0XFF;
	P8IE = 0X00;
	P9OE = 0XFF;
	P9IE = 0X00;
	P10OE = 0XFF;
	P10IE = 0X00;
}
/*=========================================================================================\n
* @function_name: do_CRC
* @function_file: Api.c
* @����: ��CRCУ��
* 
* 
* @����: 
* @param:data  ���ݵ�ַ
* @param:len  ���ݳ���
* 
* @����: 
* @return: uint16 CRCУ��ֵ
* @����:   lwb (2012-02-29)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  susan
* @�޸�����: 1,crc��ֵ��Ϊ�������룬��ʼ��ֵ��Ϊ0x5555.���ں������ݣ���֮ǰ���������crcֵ��Ϊ��ֵ��
*            2����չlen��������Ϊuint32
===========================================================================================*/
uint16 do_CRC_root(uint16 initcrc,uint32 nStartAddr,uint32 len)
{

    uint16 data crc,nlen;
    uint8 code *point;
    nlen = len;
    point = (uint8 code *)nStartAddr;
    crc = initcrc;

   /* for( ;nlen > 0; nlen--)
    {
        ucData = (uint8) (crc>>8);    //�ݴ�crc��8λ
        crc <<= 8;
        crc ^= CrcTab[ucData ^ (*point++)];     //���ֽں͵�ǰ����XOR�ٲ��

    }  */
	while(nlen--)
		crc = (crc << 8) ^ CrcTab[((crc>>8) ^(*point++)) & 0xff];

    return crc;
}

uint16 GetCRCData(void)
{
  uint16 u16Ret;
  uint8 code *point;
  point = (uint8 code *)0xffff;
  u16Ret = *point;
  u16Ret = u16Ret<<8;
   point = (uint8 code *)0xfffe;
  u16Ret += *point; 
  return u16Ret;
}

uint32 GetCRCLen(void)
{
  uint32 u32Ret;
  uint8 code *point;
  point = (uint8 code *)0xfffd;
  u32Ret = *point;
  u32Ret = u32Ret<<8;
   point = (uint8 code *)0xfffc;
  u32Ret += *point; 
  u32Ret = u32Ret<<8;
   point = (uint8 code *)0xfffb;
  u32Ret += *point; 
  u32Ret = u32Ret<<8;
   point = (uint8 code *)0xfffa;
  u32Ret += *point; 
  return u32Ret;
  
}

uint8 checkCRC(void)
{
    uint16 u16CrcData,u16CalCRCData;
    uint32 u32CrcLen;
	CBANK = 3;
    u16CrcData = GetCRCData();
    u32CrcLen = GetCRCLen();

   if(u32CrcLen<0x20000&&u32CrcLen>=0x18000)
    {
	  CBANK = 1;
      u16CalCRCData = do_CRC_root(0x5555,0,0x400);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x600,0x8000-0x600);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,0x8000);
	  CBANK = 2;
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,0x8000);
	  CBANK = 3;
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,u32CrcLen-0x18000);
    }
	 else if(u32CrcLen<0x18000&&u32CrcLen>=0x10000)
    {
	  CBANK = 1;
      u16CalCRCData = do_CRC_root(0x5555,0,0x400);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x600,0x8000-0x600);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,0x8000);
	  CBANK = 2;
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,u32CrcLen-0x10000);

    }
	else if(u32CrcLen<0x10000&&u32CrcLen>=0x8000)
    {
	  CBANK = 1;
      u16CalCRCData = do_CRC_root(0x5555,0,0x400);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x600,0x8000-0x600);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x8000,u32CrcLen-0x8000);
    }
	else if(u32CrcLen<0x8000&&u32CrcLen>=0x600)
    {
	  CBANK = 1;
      u16CalCRCData = do_CRC_root(0x5555,0,0x400);
      u16CalCRCData = do_CRC_root(u16CalCRCData,0x600,u32CrcLen-0x600);

    }
	else if(u32CrcLen<=0x400)
	{
		CBANK = 1;
      u16CalCRCData = do_CRC_root(0x5555,0,u32CrcLen);
	}
	else
	{
	   return 0;
	}  
    if(u16CalCRCData!=u16CrcData)
    {
     return 0;
    }
    else
    {
      return 1;
    }
}

void main()
{
	FSC=0; //�������߿��ƣ�0�ر�
	FWC=1;//���ٻ���1������0�ر�
	MCUFRQ=1;//���ܼ���ģ��ʱ��Դ��1ѡ��PLLʱ�ӣ�0ѡ��OSCʱ��
	SetPLL(SETPLL_6_4M);  //�������ԣ�F11���˺�����ʧȥ��������
	CtrlPLL = 0X40;	   //MCU 13M
	Flash_LowPowerConsum();//����FLASH�͹���ģʽ
//	SetRTCInt(RTC_DAY);//����1�컽��
	GPIO_INIT();  //�˿ڳ�ʼ��
	CtrlADC6 =0x0f ;//�����ĸ�ADCͨ��
    ClearWDT();
	LED_ON();
    if(checkCRC()!=1)
    {
      while(1)
      {
        ClearWDT();
      }
    }
	LED_OFF();
	while(1)
	{
		call_bank1(3);
		delayms(500);
		delayms(500);//����Ҫ����call_bank1��ƽ����ĺ����ʱ��������ʱΪ1.5S+���Ƽ��ʱ��=2S
		delayms(500);
		ClearWDT();

		call_bank2(5);
		delayms(500);
		delayms(500);//ͬ��1.8S
		delayms(500);
		ClearWDT();

		call_bank3(7);
		delayms(500);//1.7s
		delayms(500);
		delayms(500);
		ClearWDT();

	}		
}