#ifndef __LCDMIDDLE_H__
#define __LCDMIDDLE_H__


#ifndef LCDMIDDLEEXT
    #define LCDMIDDLEEXT extern
#else
    #define LCDMIDDLESELF
#endif

//应用层接口函数
void Disp_Numb(uint32 data,uint32 type);
void Disp_String(uint16 para);
void Disp_UnitPoint(uint8 unitpoint);
void Disp_State(uint32 data);




//COM口和SEG口对应的RAM区间
//COM口和SEG口对应的RAM区间
//#define     COM6        0x05
//#define     COM5        0x04
#define     COM4        0x03
#define     COM3        0x02
#define     COM2        0x01
#define     COM1        0x00


#define     S00         (0*8)
#define     S01         (0*8+4)

#define     S08         (1*8)
#define     S09         (1*8+4)
#define     S10         (2*8)
#define     S11         (2*8+4)
#define     S12         (3*8)
#define     S13         (3*8+4)
#define     S14         (4*8)
#define     S15         (4*8+4)

#define     S24         (5*8)
#define     S25         (5*8+4)
#define     S26         (6*8)
#define     S27         (6*8+4)
#define     S28         (7*8)
#define     S29         (7*8+4)

 
#ifdef LCDMIDDLESELF
/*==================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
====================================================*/
//定义各个数字所在的RAM的字节位置
//#define     number11H    10
//#define     number11L    10
//#define     number10H    9
//#define     number10L    9
#define     number9H     5
#define     number9L     6
#define     number8H     4
#define     number8L     5
#define     number7H     3
#define     number7L     4
#define     number6H     2
#define     number6L     3
#define     number5H     1
#define     number5L     2
#define     number4H     0
#define     number4L     1
//#define     number3H     2
//#define     number3L     3
//#define     number2H     1
//#define     number2L     2
//#define     number1H     0
//#define     number1L     0

const uint8 code NumAddr[12] = 

//{number9H,number9L,number8H,number8L,number7H,number7L,number6H,number6L,
//  number5H,number5L,number4H,number4L,number3H,number3L,number2H,number2L};
{number9H,number9L,number8H,number8L,number7H,number7L,number6H,number6L,
  number5H,number5L,number4H,number4L};

/*=======================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
=========================================================*/

#define NUM1A    BIT0
#define NUM1B    BIT1
#define NUM1C    BIT2
#define NUM1D    BIT3
#define NUM1E    BIT6
#define NUM1F    BIT4
#define NUM1G    BIT5

#define  N_Resd1H 0x8F
#define  N_Resd1L 0xF0 

const uint8 code NUMTABLE_1L[]=
{
    NUM1A+NUM1B+NUM1C+NUM1D,            //0
    NUM1B+NUM1C,                        //1
    NUM1A+NUM1B+NUM1D,                  //2
    NUM1A+NUM1B+NUM1C+NUM1D,            //3
    NUM1B+NUM1C,                        //4
    NUM1A+NUM1C+NUM1D,                  //5
    NUM1A+NUM1C+NUM1D,                  //6
    NUM1A+NUM1B+NUM1C,                  //7
    NUM1A+NUM1B+NUM1C+NUM1D,            //8
    NUM1A+NUM1B+NUM1C+NUM1D,            //9

    NUM1A+NUM1B+NUM1C,                  //A
    NUM1C+NUM1D,                        //B
    NUM1A+NUM1D,                        //C
    NUM1B+NUM1C+NUM1D,                  //D
    NUM1A+NUM1D,                        //E
    NUM1A,                              //F
};

const uint8 code NUMTABLE_1H[]=
{
    NUM1E+NUM1F,                        //0
    0,                                  //1
    NUM1E+NUM1G,                        //2
    NUM1G,                              //3
    NUM1F+NUM1G,                        //4
    NUM1F+NUM1G,                        //5
    NUM1E+NUM1F+NUM1G,                  //6
    0,                                  //7
    NUM1E+NUM1F+NUM1G,                  //8
    NUM1F+NUM1G,                        //9

    NUM1E+NUM1F+NUM1G,                  //A
    NUM1E+NUM1F+NUM1G,                  //B
    NUM1E+NUM1F,                        //C
    NUM1E+NUM1G,                        //D
    NUM1E+NUM1F+NUM1G,                  //E
    NUM1E+NUM1F+NUM1G,                  //F
};

#define LCD_CHAR1L_G  (0)                           //'-'
#define LCD_CHAR1H_G  (NUM1G)                       //'-'
#define LCD_CHAR1L_L  (0)                           //'L'
#define LCD_CHAR1H_L  (NUM1D+NUM1E+NUM1F)           //'L'
#define LCD_CHAR1L_r  (0)                           //'r'
#define LCD_CHAR1H_r  (NUM1E+NUM1G)                 //'r'
#define LCD_CHAR1L_n  (NUM1C)                       //'n'
#define LCD_CHAR1H_n  (NUM1E+NUM1G)                 //'n'
#define LCD_CHAR1L_o  (NUM1C+NUM1D)                 //小写字母'o',不是零
#define LCD_CHAR1H_o  (NUM1E+NUM1G)                 //小写字母'o',不是零
#define LCD_CHAR1L_C  (NUM1A+NUM1D)                 //'C'
#define LCD_CHAR1H_C  (NUM1E+NUM1F)                 //'C'
#define LCD_CHAR1L_E  (NUM1A+NUM1D)                 //'E'
#define LCD_CHAR1H_E  (NUM1E+NUM1F+NUM1G)           //'E'

/*==================================================
说明：状态显示位
===================================================*/
#define     St_M               (S00+COM1)      //
#define     St_I               (S00+COM1)      //
#define     St_D               (S00+COM1)      //
#define     St_T               (S00+COM1)      //

#define     St_S5              (S00+COM4)      //
#define     St_S6              (S00+COM1)      //
#define     St_S7              (S00+COM1)      //
#define     St_S8              (S00+COM1)      //
#define     St_S9              (S00+COM1)      //
#define     St_S10             (S00+COM1)      //
#define     St_S11             (S09+COM4)      //
#define     St_Bat             (S29+COM2)      //
#define     St_Total           (S29+COM1)      //


//以下为显示内容，通过32个位来实现
#define     St_Len     13
const   uint16 code St_Table[St_Len]=
{
    St_M,      // gul_ShowState =  0x0001 
    St_I,      //0x0002   
    St_D,      //0x0004     
    St_T,      //0x0008     
    St_S5,     //0x0010     
    St_S6,     //0x0020    
    St_S7,     //0x0040
    St_S8,     //0x0080    
    St_S9,     //0x0100 
    St_S10,    //0x0200   
    St_S11,    //0x0400  
    St_Bat,    //0x0800       
    St_Total,  //0x1000 
};

/*======================================================
说明：小数点及符号的显示
========================================================*/
#define     Ut_P1       (S11+COM4)//P1 时间
#define     Ut_P2       (S29+COM3)//P2 4位小数
#define     Ut_P3       (S13+COM4)//P3 3位小数
#define     Ut_P4       (S15+COM4)//P4 时间
#define     Ut_P5       (S29+COM4)//P5 2位小数
#define     Ut_P6       (S25+COM4)//P6 1位小数

//最大长度是16，目前只用了5，其他空
#define Len_PointBit   6
const   uint8 code PointBitTable[Len_PointBit]=
{
    Ut_P1,      //  0x01  BIT0
    Ut_P2,      //  0x02  BIT1
    Ut_P3,      //  0x04 
    Ut_P4,      //  0x08
    Ut_P5,      //  0x10  BIT4
    Ut_P6       //  0x20  BIT5
}; 

//作为Disp_UnitPoint()函数实参  高4位
#define PointLen    7
const   uint16 code PointTable[PointLen]=
{
    0x00,      //  不显示
    0x02,      //  P2
    0x04,      //  P3
    0x10,      //  P5
    0x20,      //  P6
    0x02+0x10,      //  P2+P5
    0x01+0x02+0x08+0x10, //  P1+P2+P4+P5
};

//单位符号的最基本单元的对应RAM地址空间
#define     Ut_K        (S28+COM1)// K
#define     Ut_V        (S28+COM2)// V
#define     Ut_S16      (S28+COM3)//
#define     Ut_S17      (S28+COM4)//
#define     Ut_S18      (S27+COM4)//
#define     Ut_h        (S27+COM3)// h
#define     Ut_S20      (S27+COM2)//
#define     Ut_S21      (S27+COM1)// z


#define     Len_UnitBit 8
const uint8 code UnitBitTable[Len_UnitBit]=
{
    Ut_K,        //  0x01
    Ut_V,        //  0x02
    Ut_S16,      //  0x04
    Ut_S17,      //  0X08
    Ut_S18,      //  0X10
    Ut_h,        //  0X20
    Ut_S20,      //  0X40
    Ut_S21,      //  0X80
};

//作为Disp_UnitPoint()函数实参 低4位
#define UnitTableLen 6
const uint16 code UnitTable[UnitTableLen]=
{ 
    0x00,                      //不显示
    0x01+0x02+0x04+0x08+0x20,  //KWh
    0x01+0x02+0x04+0x08,       //KW
    0x02,                      //V
    0x08+0x10,                 //A
    0x20+0x40+0x80,            //Hz
};

#endif

#endif
