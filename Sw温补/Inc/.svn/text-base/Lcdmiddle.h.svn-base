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
void Disp_UnitPoint(uint16 para);
void Disp_State(uint32 data);




//COM口和SEG口对应的RAM区间
//COM口和SEG口对应的RAM区间
#define     COM6        0x05
#define     COM5        0x04
#define     COM4        0x03
#define     COM3        0x02
#define     COM2        0x01
#define     COM1        0x00

#define     S00         (0*8)
#define     S01         (1*8)
#define     S02         (2*8)
#define     S03         (3*8)
#define     S04         (4*8)
#define     S05         (5*8)
#define     S06         (6*8)
#define     S07         (7*8)
#define     S08         (8*8)
#define     S09         (9*8)
#define     S10         (10*8)
#define     S11         (11*8)
#define     S12         (12*8)
#define     S13         (13*8)
#define     S14         (14*8)
#define     S15         (15*8)
#define     S16         (16*8)
#define     S17         (17*8)
#define     S18         (18*8)
#define     S19         (19*8)
#define     S20         (20*8)
#define     S21         (21*8)
#define     S22         (22*8)
#define     S23         (23*8)
#define     S24         (24*8)
#define     S25         (25*8)
#define     S26         (26*8)
#define     S27         (27*8)
#define     S28         (28*8)
#define     S29         (28*8)
#define     S30         (30*8)
#define     S31         (31*8)
#define     S32         (32*8)
#define     S33         (33*8)
#define     S34         (34*8)
#define     S35         (35*8)
#define     S36         (36*8)
#define     S37         (37*8)
#define     S38         (38*8)
 
#ifdef LCDMIDDLESELF
/*==================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
====================================================*/
//定义各个数字所在的RAM的字节位置
#define     number9H     36
#define     number9L     37
#define     number8H     20
#define     number8L     21
#define     number7H     18
#define     number7L     19
#define     number6H     16
#define     number6L     17
#define     number5H     12
#define     number5L     13
#define     number4H     10
#define     number4L     11
#define     number3H     8
#define     number3L     9
#define     number2H     6
#define     number2L     7


const uint8 code NumAddr[16] = {number9H,number9L,number8H,number8L,number7H,number7L,number6H,number6L,number5H,
                           number5L,number4H,number4L,number3H,number3L,number2H,number2L};




/*=======================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
=========================================================*/

#define NUM1A    BIT3
#define NUM1B    BIT2
#define NUM1C    BIT1
#define NUM1D    BIT0
#define NUM1E    BIT1
#define NUM1F    BIT3
#define NUM1G    BIT2

#define  N_Resd1H 0xf1
#define  N_Resd1L 0xf0
                          
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

#define LCD_CHAR1H_G  (NUM1G)                       //'-'
#define LCD_CHAR1L_G  (0)                           //'-'
#define LCD_CHAR1H_L  (NUM1E+NUM1F)                 //'L'
#define LCD_CHAR1L_L  (NUM1D)                       //'L'
#define LCD_CHAR1H_r  (NUM1E+NUM1G)                 //'r'
#define LCD_CHAR1L_r  (0)                           //'r'
#define LCD_CHAR1H_n  (NUM1C)                       //'n'
#define LCD_CHAR1L_n  (NUM1E+NUM1G)                 //'n'
#define LCD_CHAR1H_o  (NUM1C+NUM1D)                 //小写字母'o',不是零
#define LCD_CHAR1L_o  (NUM1E+NUM1G)                 //小写字母'o',不是零
#define LCD_CHAR1H_C  (NUM1E+NUM1F)                 //'C'
#define LCD_CHAR1L_C  (NUM1A+NUM1D)                 //'C'
#define LCD_CHAR1H_E  (NUM1E+NUM1F+NUM1G)           //'E'
#define LCD_CHAR1L_E  (NUM1A+NUM1D)                 //'E'

/*==================================================
说明：状态显示位
===================================================*/
//8表示地址存放于高5位（左移3位）,后面加上的值表示在这个地址中对应存放的位

#define     St_jian            (S28+COM4)      //尖
#define     St_feng            (S28+COM3)      //峰
#define     St_ping            (S28+COM2)      //平
#define     St_gu              (S28+COM1)      //谷
#define     St_quan1           (S28+COM6)      //圈1
#define     St_quan2           (S06+COM5)      //圈2
//#define     St_fangzi          (0)      //房子
#define     St_dianhua         (S07+COM6)      //电话符号
//#define     St_zaib            (0)      //载波通讯符号
#define     St_biancheng       (S36+COM5)      //编程符号
#define     St_dianchi         (S19+COM5)      //电池符号
#define     St_glfanx          (S06+COM6)      //功率反向
#define     St_suo             (S21+COM5)      //锁符号
//#define     St_kuang1          (0)      //框1
//#define     St_kuang2          (0)      //框2
//#define     St_kuang3          (0)      //框3
//#define     St_kuang4          (0)      //框4
//#define     St_sanjiao1        (0)      //三角1
//#define     St_sanjiao2        (0)      //三角2
//#define     St_duka            (0)      //读卡
//#define     St_zhong           (0)      //中
//#define     St_chenggong       (0)      //成功
//#define     St_shibai          (0)      //失败
//#define     St_qingoudian      (0)      //请购电
//#define     St_lazha           (0)      //拉闸
//#define     St_touzi           (0)      //透支
//#define     St_tunji           (0)      //囤积
#define     St_NumFu           (S06+COM1)       //负号
//#define     St_Reserved        (0)
//以下为显示内容，通过16个位来实现
#define     St_Len     12
const   uint16 code St_Table[St_Len]=
{
    St_jian,        //尖
    St_feng,        //峰
    St_ping,        //平
    St_gu,          //谷
    St_quan1,       //圈1
    St_quan2,       //圈2
    St_dianhua,     //电话符号
    //St_zaib,        //载波通讯符号
    St_biancheng,   //编程符号
    St_dianchi,     //电池符号
    St_glfanx,      //功率反向
    St_suo,         //锁符号
    //St_kuang1,      //框1
    //St_kuang2,      //框2
    //St_kuang3,      //框3
    //St_kuang4,      //框4
    //St_sanjiao1,    //三角1
    //St_sanjiao2,    //三角2
    //St_Reserved,    //保留
    //St_duka,        //读卡
    //St_zhong,       //中
    //St_chenggong,   //成功
    //St_shibai,      //失败
    //St_qingoudian,  //请购电
    //St_lazha,       //拉闸
    //St_touzi,       //透支
    //St_tunji,       //囤积
    //St_fangzi,      //房子
    St_NumFu,       //负号
};

/*======================================================
说明：小数点符号的显示
========================================================*/
//负号及小数点的各个位段的定义,P表示POINT
//8表示地址存放于高5位（左移3位），后面加上的值表示在这个地址中对应存放的位
#define     Ut_P1       (S08+COM1)//
#define     Ut_P2       (S10+COM1)//
#define     Ut_P3       (S12+COM1)//
#define     Ut_P4       (S16+COM1)//
#define     Ut_P5       (S18+COM1)//
#define     Ut_P6       (S20+COM1)//
#define     Ut_P7       (S36+COM1)//
#define     Ut_P8       (S20+COM5)//
#define     Ut_P9       (S16+COM5)//
#define     Ut_P10      (0)//
//#define     St_fanx            (S19+COM5)      //反向符号
#define     Pt_Reserved (0)//


//小数点（包括"-"）在显示真值表中的地址和对应位，高5位表示地址，低3位表示在对应内存的某一位
//最大长度是16，目前只用了9，其他空
#define PointLen    9
const   uint16 code PointTable[PointLen]=
{
    Ut_P1,      //  0x01
    Ut_P2,      //  0x02
    Ut_P3,      //  0x04
    Ut_P4,      //  0x08
    Ut_P5,      //  0x10
    Ut_P6,      //  0x20
    Ut_P7,      //  0x40
    Ut_P8,      //  0x80
    Ut_P9,      //  0x100
    //Ut_P10,     //  0x200
};

//单位符号的最基本单元的对应RAM地址空间

#define     Ut_KW       (S37+COM6)// KW
#define     Ut_H        (S37+COM5)// h
//#define     Ut_cos      (0)// cos
//#define     Ut_yuan     (0)// 元
//#define     Ut_Reserved (0)//预留

#define     Len_UnitBit 2
const uint16 code UnitBitTable[Len_UnitBit]=
{
    Ut_KW,      //  0x01
    Ut_H,       //  0x02
    //Ut_yuan,    //  0x04
    //Ut_cos,     //  0X08
};

//最多可显示如下16个单位，根据入口参数(0x00到0x0f)确定
#define UnitTableLen 3
const uint16 code UnitTable[UnitTableLen]=
{ //bit15--------------------------------------->bit0
    0x00,
    0x01+0x02,  //KWh
    0x01,       //KW
    //0x08,       //cos
    //0x04,       //元
};


/*==============================================
说明：中文显示内容
================================================*/
//中文字符的各个对应位段的定义，对应的RAM地址空间，当显示屏调整后
//8表示地址存放于高5位（左移3位），后面加上的值表示在这个地址中对应存放的位


#define     Cn_Dandqian     (S07+COM5) //当前
#define     Cn_Zong         (S13+COM5) //总     //因真值表反
#define     Cn_Jian         (S13+COM6) //尖
#define     Cn_Feng         (S17+COM6) //峰
#define     Cn_Ping         (S17+COM5) //平
#define     Cn_Gu           (S18+COM5) //谷
//#define     Cn_Yong         (S16+COM1) //用
#define     Cn_Dianliang         (S18+COM6) //电
//#define     Cn_Liang        (S11+COM3) //量
//#define     Cn_Jia          (0) //价
#define     Cn_Shang        (S08+COM5) //上
#define     Cn_Yue          (S12+COM6) //月
//#define     Cn_ZhuH         (0) //组合
//#define     Cn_Zheng        (S04+COM6) //正
//#define     Cn_Fan          (S14+COM6) //反
//#define     Cn_Xiang        (S05+COM6) //向
//#define     Cn_ling         (0) //零
//#define     Cn_huo          (S01+COM4) //火
//#define      Cn_shijian       (S28+COM5) // 时
//#define     Cn_jian         (S00+COM2) // 间
//#define     Cn_duan         (S07+COM1) // 段
//#define     Cn_biao         (S14+COM1) // 表
//#define     Cn_hao          (S17+COM1) // 号
//#define     Cn_hu           (S12+COM1) // 户
//#define     Cn_jine         (S09+COM1) // 金额
//#define     Cn_cs           (S15+COM1) // 常数
//#define     Cn_sy           (S13+COM1) // 剩余
//#define     Cn_GL           (S16+COM1) // 功率
//#define     Cn_she          (S18+COM1) // 赊
//#define     Cn_qian         (S17+COM1) // 欠
//#define     Cn_jt           (S20+COM1) // 阶梯
//#define     Cn_V        (S00+COM5)// V
//#define     Cn_A        (S00+COM4)// A
//#define     Cn_Reserved     (S23+COM6) //预留


#define Len_ChineseTable 9
//中文字符在显示真值表中的地址和对应位，高5位表示地址，低3位表示在对应内存的某一位
const   uint8 code ChineseTable[Len_ChineseTable]=
{
    Cn_Dandqian,        //  0x01    当前
    Cn_Zong,            //  0x02    总
    Cn_Jian,            //  0x04    尖
    Cn_Feng,            //  0x08    峰
    Cn_Ping,            //  0X10    平
    Cn_Gu,              //  0x20    谷
    Cn_Dianliang,       //  0x40    电量
    //Cn_Liang,           //  0x80    量
    //Cn_Jia,             //  0x100   价
    Cn_Shang,        //  0x80   上月
    Cn_Yue,             //  0x100   月
    //Cn_ZhuH,            //  0x800  组合
    //Cn_ling,            //  0x1000 零
    //Cn_shijian,         //  0x200   时间
    //Cn_jian,            //  0x4000间
    //Cn_duan ,           //  0x8000段
    //Cn_biao,            //  0x10000表
    //Cn_hao,             //  0x20000号
    //Cn_hu ,             //  0x40000户
    //Cn_jine,            //  0x80000金额
    //Cn_cs ,             //  0x100000常数
    //Cn_sy ,             //  0x200000剩余
    //Cn_jt ,             //  0x400000阶梯
    //Cn_V,               //  0x800000 压
    //Cn_A,               //  0x1000000 流
    //Cn_GL,              //  0x2000000 功率
    //Cn_Yong,            //  0x40    用
    //Cn_Zheng,           //  0x2000  正
    //Cn_Fan,             //  0x4000  反
    //Cn_Xiang,           //  0x8000  向
    //Cn_huo,             //  0x20000火
    //Cn_she,             //  0x8000000赊
    //Cn_qian ,           //  0x10000000欠

};


//最多可显示 0x96项内容，通过一个字节的入口参数来实现
#define Len_LCDChinaCode    13
const uint32 code LCD_ChinaCode[Len_LCDChinaCode] =
{
    0x0000,                             //              00h
    0x01+0x02+0x40,                     // 当前电量总   01h
    0x01+0x04+0x40,                     // 当前电量尖   02h
    0x01+0x08+0x40,                     // 当前电量峰   03h
    0x01+0x10+0x40,                     // 当前电量平   04h
    0x01+0x20+0x40,                     // 当前电量谷   05h

    0x02+0x40+0x80+0x100,                     // 上Ｘ月电量总 06h
    0x04+0x40+0x80+0x100,                     // 上Ｘ月电量尖 07h
    0x08+0x40+0x80+0x100,                     // 上Ｘ月电量峰 08h
    0x10+0x40+0x80+0x100,                     // 上Ｘ月电量平 09h
    0x20+0x40+0x80+0x100,                     // 上Ｘ月电量谷 0ah
    
    0x01+0x200,                         //当前时间          0bh
    0x200,                              //时间              0ch
};

//汉字区的8定义，以下表示每一段在1个字中的含义
#define     C_a         (S09+COM6)
#define     C_b         (S10+COM6)
#define     C_c         (S11+COM6)
#define     C_d         (S12+COM5)
#define     C_e         (S11+COM5)
#define     C_f         (S09+COM5)
#define     C_g         (S10+COM5)
#define     C_1         (S08+COM6)


#define LCD_CODE_L  (C_d+C_e+C_f)           //'L'
#define LCD_CODE_r  (C_e+C_g)               //'r'
#define LCD_CODE_n  (C_c+C_e+C_g)           //'n'
#define LCD_CODE_o  (C_c+C_d+C_e+C_g)       //小写字母'o',不是零
#define Len_Strnum 8
const   uint16  code BITStrnum[Len_Strnum]=
{
    C_a,        //0x01
    C_b,        //0x02
    C_c,        //0x04
    C_d,        //0x08
    C_e,        //0x10
    C_f,        //0x20
    C_g,        //0x40
    C_1,        //0x80
};

const   uint8 code Strnum[19] =
{
    0x00,
    0x02+0x04,                                  // 1
    0x01+0x02+0x08+0x10+0x40,                   // 2
    0x01+0x02+0x04+0x08+0x40,                   // 3
    0x02+0x04+0x20+0x40,                        // 4
    0x01+0x04+0x08+0x20+0x40,                   // 5
    0x01+0x04+0x08+0x10+0x20+0x40,              // 6
    0x01+0x02+0x04,                             // 7
    0x01+0x02+0x04+0x08+0x10+0x20+0x40,         // 8
    0x01+0x02+0x04+0x08+0x20+0x40,              // 9
    0x01+0x02+0x04+0x10+0x20+0x40,              // A
    0x04+0x08+0x10+0x20+0x40,                   // b
    0x01+0x08+0x10+0x20,                        // c
    0x02+0x04+0x08+0x10+0x40,                   // d
    0x01+0x08+0x10+0x20+0x40,                   // e
    0x01+0x10+0x20+0x40,                        // f
    0x01+0x02+0x04+0x08+0x10+0x20+0x80,         // 10
    0x02+0x04+0x80,                             // 11
    0x01+0x02+0x08+0x10+0x40+0x80,              // 12
};


#endif

#endif
