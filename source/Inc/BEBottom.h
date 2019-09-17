#ifndef __BEBottom_H__
#define __BEBottom_H__

#define _SW_SE_Type     0

#define _SW_BE_Type  Const_AT24C256    //Const_AT24C04_08_16

#define Const_AT24C04_08_16     16
#define Const_AT24C64           64
#define Const_AT24C256          256
#define Const_AT24C512          512

//常量定义
#if(_SW_BE_Type==Const_AT24C04_08_16)
    #define BE_Const_DyClk      0       // 延时10us的时间（每个单位是5us）
    #define BE_Const_DyWrite    10      // 延时2ms的时间（每个单位是5us）
    #define BE_Const_Page       16      // 大容量E2的一页里面字节数
    #define BE_Const_ID         0xa0    // 大容量E2的器件地址
#elif(_SW_BE_Type==Const_AT24C64)
    #define BE_Const_DyClk      0       // 延时10us的时间（每个单位是5us）
    #define BE_Const_DyWrite    40      // 延时2ms的时间（每个单位是5us）
    #define BE_Const_Page       32      // 大容量E2的一页里面字节数
    #define BE_Const_ID         0xa0    // 大容量E2的器件地址
#else
    #define BE_Const_DyClk      1       // 延时10us的时间（每个单位是5us）
    #define BE_Const_DyWrite    40      // 延时5ms的时间（每个单位是5us） 
    #define BE_Const_Page       64      // 大容量E2的一页里面字节数
    #define BE_Const_ID         0xa0    // 大容量E2的器件地址
#endif



//端口定义
//端口定义

#define                 _I2CSCL_PINBITDEF_          BIT2
#define                 _I2CSDA_PINBITDEF_          BIT1

#define BE_I2C_CLK_1()      {P9OD |=_I2CSCL_PINBITDEF_;}// P9IE &=~_I2CSCL_PINBITDEF_;P9OE &=~_I2CSCL_PINBITDEF_; }   //CLK=1
#define BE_I2C_CLK_0()      {P9OD &=~_I2CSCL_PINBITDEF_;}//P9IE &=~_I2CSCL_PINBITDEF_;P9OE &=~_I2CSCL_PINBITDEF_; }   //CLK=0


#define BE_I2C_SDA_1()      {P9OD |=_I2CSDA_PINBITDEF_;};// P9OE &=~_I2CSDA_PINBITDEF_; }   //SDA=1 P9IE &=~BIT1;
#define BE_I2C_SDA_0()      {P9OD &=~_I2CSDA_PINBITDEF_;};//P9OE &=~_I2CSDA_PINBITDEF_; }   //SDA=0 P9IE &=~BIT1;

#define BE_I2C_SDA_IN()     {P9OE |=_I2CSDA_PINBITDEF_;P9IE |=_I2CSDA_PINBITDEF_;}                  //设置成输入模式
#define BE_I2C_SDA_ST       (P9ID & _I2CSDA_PINBITDEF_)                                 //读取数据线上的信号


#define BE_WP_1()           {BE_I2C_SDA_1();BE_I2C_CLK_1();}
#define BE_WP_0()           {}

uint8 BE_WriteP(uint32 address,uint8 *buff,uint16 Len);       
uint8 BE_ReadP(uint32 address,uint8 *buff,uint16 Len);
uint8 BE_ReadB(uint32 address,uint8 *buff);
uint8 BE_ReadW(uint32 address,uint16 *buff);


#define Feed_WDT()     ;//CLRWDT() 
 

#endif


