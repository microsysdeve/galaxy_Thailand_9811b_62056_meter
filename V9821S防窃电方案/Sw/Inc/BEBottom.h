#ifndef __BEBottom_H__
#define __BEBottom_H__

#define _SW_SE_Type     0

#define _SW_BE_Type  Const_AT24C04_08_16

#define Const_AT24C04_08_16     16
#define Const_AT24C64           64
#define Const_AT24C256          256
#define Const_AT24C512          512

//��������
#if(_SW_BE_Type==Const_AT24C04_08_16)
    #define BE_Const_DyClk      0       // ��ʱ10us��ʱ�䣨ÿ����λ��5us��
    #define BE_Const_DyWrite    10      // ��ʱ2ms��ʱ�䣨ÿ����λ��5us��
    #define BE_Const_Page       16      // ������E2��һҳ�����ֽ���
    #define BE_Const_ID         0xa0    // ������E2��������ַ
#elif(_SW_BE_Type==Const_AT24C64)
    #define BE_Const_DyClk      0       // ��ʱ10us��ʱ�䣨ÿ����λ��5us��
    #define BE_Const_DyWrite    40      // ��ʱ2ms��ʱ�䣨ÿ����λ��5us��
    #define BE_Const_Page       32      // ������E2��һҳ�����ֽ���
    #define BE_Const_ID         0xa0    // ������E2��������ַ
#else
    #define BE_Const_DyClk      1       // ��ʱ10us��ʱ�䣨ÿ����λ��5us��
    #define BE_Const_DyWrite    40      // ��ʱ5ms��ʱ�䣨ÿ����λ��5us�� 
    #define BE_Const_Page       64      // ������E2��һҳ�����ֽ���
    #define BE_Const_ID         0xa0    // ������E2��������ַ
#endif



//�˿ڶ���
//�˿ڶ���
#define BE_I2C_CLK_1()      {P0OD |=BIT3; P0IE &=~BIT3;P0OE &=~BIT3; }   //CLK=1
#define BE_I2C_CLK_0()      {P0OD &=~BIT3;P0IE &=~BIT3;P0OE &=~BIT3; }   //CLK=0


#define BE_I2C_SDA_1()      {P8OD |=BIT2; P8OE &=~BIT2; }   //SDA=1 P9IE &=~BIT1;
#define BE_I2C_SDA_0()      {P8OD &=~BIT2;P8OE &=~BIT2; }   //SDA=0 P9IE &=~BIT1;

#define BE_I2C_SDA_IN()     {P8OE |=BIT2;P8IE |=BIT2;}                  //���ó�����ģʽ
#define BE_I2C_SDA_ST       (P8ID&BIT2)                                 //��ȡ�������ϵ��ź�


#define BE_WP_1()           {BE_I2C_SDA_1();BE_I2C_CLK_1();}
#define BE_WP_0()           {}

uint8 BE_WriteP(uint32 address,uint8 *buff,uint8 Len);



       
uint8 BE_ReadP(uint32 address,uint8 *buff,uint8 Len);
uint8 BE_ReadB(uint32 address,uint8 *buff);
uint8 BE_ReadW(uint32 address,uint16 *buff);


#define Feed_WDT()     ;//CLRWDT() 


#endif


