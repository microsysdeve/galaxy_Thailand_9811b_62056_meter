 
#ifndef _API_H_
#define _API_H_

#ifndef API_EXT
#define API_EXT extern
#endif

enum
{
    CMP_EQU = 0,    //���
    CMP_LG,         //large than ����
    CMP_LT          //little than С��
};
 

enum
{//���ݴ��������Ͷ���
    Const_Data_OK = 0,      //������Ч
    Const_Data_Err,         //������Ч
    Const_DataID_Err,       //�Ҳ���id
    Const_DataPswd_Err = 4, //�����Ȩ�޴���
    Const_DataNot_Ret = 20  //ͨѶ����Ҫ��Ӧ
};

 
void Uint16_To_Uint8(uint16 x, uint8 * buff);
uint16 Uint8_To_Uint16(uint8 * buff);
void Uint24_To_Uint8(uint32 x, uint8 * buff);
uint32 Uint8_To_Uint24(uint8 * buff);
void Uint32_To_Uint8(uint32 x, uint8 * buff);
void Int32_To_Uint8(int32 x, uint8 * buff);
uint32 Uint8_To_Uint32(uint8 * buff);
int32 Uint8_To_Int32(uint8 * buff);
uint32 Hex2BIN(uint8 x);
uint16 getPower(uint16 x, uint16 y);
uint32 Hex2BCD(uint32 hex);
uint32 BCD2Hex(uint32);
uint16 IntHex2BCD(uint16 hex);
uint16 do_CRC(uint8 xdata *str,uint8 len);
uint8 ApiBufCmp(uint8* pucCompare, uint8* pucCompared, uint8 ucLen);
uint8 ApiRevBufCmp(uint8* pucCompare, uint8* pucCompared, uint8 ucLen);
uint8 ApiCodeBufCmp(uint8 code  *pucCompare, const uint8 * pucCompared, uint8 ucLen);
void ApiConData(uint8* buff, uint8 Len);
uint8 JudgeIsNum(uint8* pucBuf, uint8 ucLen);
uint8 APIByteBCD2HEX(uint8 ucBCD);
uint8 APIByteHEX2BCD(uint8 ucHEX);
void SumplementNegtive(uint8 ucLen, uint8* p);
uint16 IntBCD2Hex(uint16 x);
void MoveBuffer(uint8* sbuff, uint8* tbuff, uint16 length);
uint8 CompareTime(uint8  *Tm1,uint8 *Tm2);
//void MemInvertCpy(uint8 *des,uint8 *src,uint8 len);
#define MemInvertCpy(des,src,len)  RevCopyRam(des,(char *)src,(unsigned short)len)
//void MemCpy(uint8 *des,uint8 *src,uint8 len);
#define MemCpy(des,src, len)   CopyRam(des,(char *)src,(unsigned short)len)
void MemSet(uint8* des,uint8 value,uint8 len);
//void FCpyTMem(uint8x *des,const uint8 code *src,uint8 len);
void CopyRam(unsigned char  *Dst, unsigned char  const *Src, unsigned short  Length); //Public.c
#define FCpyTMem(des,src,len) CopyRam((unsigned char  *)des,(unsigned char *)src ,(uint16)len)
void FCpyTMem1(uint8x *des,const uint8 code *src,uint8 len);
void FCpyTMem2(uint8x *des,const uint8 code *src,uint8 len);
void DelayXms(uint8 num);
void ApiReverseData(uint8* buff, uint8 Len);
uint8 CalCBRCount(uint8 xdata* str1,uint8 xdata* str2,uint8 xdata ucDay,uint8 xdata ucHour);
uint8 CalRDJCount(uint8 xdata* str1,uint8 xdata* str2,uint8 xdata ucHour,uint8 xdata ucMin);
uint16 HourAndMinToMin(uint8*Data);

uint8 StrLen(const uint8 code *src);
void StrCpy(uint8* des,const uint8 code *src);


#define 		INTERRUPT_DISABLE()			{    EA = 0;}
#define 		INTERRUPT_ENABLE()			{    EA = 1;}
#define 		NOP_ASM()					{nop();}

#endif

