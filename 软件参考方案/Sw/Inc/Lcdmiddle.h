#ifndef __LCDMIDDLE_H__
#define __LCDMIDDLE_H__


#ifndef LCDMIDDLEEXT
    #define LCDMIDDLEEXT extern
#else
    #define LCDMIDDLESELF
#endif

//应用层接口函数
void Disp_Numb(uint32 data,uint32 type);
//void Disp_String(uint16 para);
//void Disp_UnitPoint(uint16 para);
//void Disp_State(uint32 data);

#ifdef LCDMIDDLESELF

//COM口和SEG口对应的RAM区间
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
#define     S29         (29*8)




/*==================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
====================================================*/
//定义各个数字所在的RAM的字节位置
#define     number8    8
#define     number7    7
#define     number6    6
#define     number5    5
#define     number4    4
#define     number3    3
#define     number2    2
#define     number1    1


const uint8 code NumAddr[8] = {number8,number7,number6,number5,number4,number3,number2,
                           number1,};




/*=======================================================
说明：以下为数字显示部分的定义，有数字区域和代码区域
=========================================================*/

//num number seg define
#define N_a    BIT1
#define N_b    BIT2
#define N_c    BIT3
#define N_d    BIT4

#define N_e    BIT5
#define N_f    BIT6
#define N_g    BIT7

#define N_x    BIT0



                           //ABCD
const uint8 code NUMTABLE[]=
{
    N_a+N_b+N_c+N_d+N_e+N_f,        //0
    N_b+N_c,                        //1
    N_a+N_b+N_d+N_e+N_g,            //2
    N_a+N_b+N_c+N_d+N_g,            //3
    N_b+N_c+N_f+N_g,                //4
    N_a+N_c+N_d+N_f+N_g,            //5
    N_a+N_c+N_d+N_e+N_f+N_g,        //6
    N_a+N_b+N_c,                    //7
    N_a+N_b+N_c+N_d+N_e+N_f+N_g,    //8
    N_a+N_b+N_c+N_d+N_f+N_g,        //9
    N_a+N_b+N_c+N_e+N_f+N_g,        //A
    N_c+N_d+N_e+N_f+N_g,            //B
    N_a+N_d+N_e+N_f,                //C
    N_b+N_c+N_d+N_e+ N_g,           //D
    N_a+N_d+N_e+N_f+N_g,            //E
    N_a+N_e+N_f+N_g,                //F
};



//#define LCD_CHARL_G  (N_g)              //'-'
//#define LCD_CHARH_G  (0)                //'-'
//#define LCD_CHARL_L  (N_e+N_f)          //'L'
//#define LCD_CHARH_L  (N_d)              //'L'
#define LCD_CHARL_r  (N_e+N_g)          //'r'
#define LCD_CHARH_A  (N_a+N_b+N_c+N_e+N_f+N_g)                //'r'
#define LCD_CHARH_E  (N_a+N_d+N_e+N_f+N_g)              //'E'
#define LCD_CHARL_D  (N_b+N_c+N_d+N_e+ N_g)          //D
//#define LCD_CHARH_o  (N_c+N_d)          //小写字母'o',不是零
//#define LCD_CHARL_C  (N_e+N_f)          //'C'
//#define LCD_CHARH_C  (N_a+N_d)          //'C'
//#define LCD_CHARL_E  (N_e+N_f+N_g)      //'E'
//#define LCD_CHARH_E  (N_a+N_d)          //'E'


///*==================================================
//说明：状态显示位
//===================================================*/
////8表示地址存放于高5位（左移3位）,后面加上的值表示在这个地址中对应存放的位
//
//#define     St_jian            (S29+COM4)      //尖
//#define     St_feng            (S29+COM3)      //峰
//#define     St_ping            (S29+COM2)      //平
//#define     St_gu              (S29+COM1)      //谷
//#define     St_quan1           (S28+COM1)      //圈1
//#define     St_quan2           (S28+COM3)      //圈2
//#define     St_dianhua         (S06+COM4)      //电话符号
//#define     St_zaib            (S06+COM3)      //载波通讯符号
//#define     St_dianchi         (S28+COM2)      //电池符号
//#define     St_glfanx          (S00+COM1)      //功率反向
//
////以下为显示内容，通过16个位来实现
//#define     St_Len     10
//const   uint8 code St_Table[St_Len]=
//{
//    St_jian,        //尖
//    St_feng,        //峰
//    St_ping,        //平
//    St_gu,          //谷
//    St_quan1,       //圈1
//    St_quan2,       //圈2
//    St_dianhua,     //电话符号
//    St_zaib,        //载波通讯符号
//    St_dianchi,     //电池符号
//    St_glfanx,      //功率反向
//};

///*======================================================
//说明：小数点符号的显示
//========================================================*/
////负号及小数点的各个位段的定义,P表示POINT
////8表示地址存放于高5位（左移3位），后面加上的值表示在这个地址中对应存放的位
//#define     Ut_T1       (S02+COM1)//
//#define     Ut_T2       (S04+COM1)//
//#define     Ut_T3       (S13+COM1)//
//#define     Ut_P4       (S15+COM1)//
//#define     Ut_P5       (S17+COM1)//
//#define     Ut_P6       (S19+COM1)//
//#define     Ut_P7       (S21+COM1)//
//#define     Ut_P2       (S10+COM4)//
//#define     Ut_P3       (S12+COM4)//
//
//
////小数点（包括"-"）在显示真值表中的地址和对应位，高5位表示地址，低3位表示在对应内存的某一位
////最大长度是16，目前只用了9，其他空
//#define PointLen    10
//const   uint8 code PointTable[PointLen]=
//{
//    Ut_T1,      //  0x01
//    Ut_T2,      //  0x02
//    Ut_T3,      //  0x04
//    Ut_P4,      //  0x08
//    Ut_P5,      //  0x10
//    Ut_P6,      //  0x20
//    Ut_P7,      //  0x40
//    Ut_P2,      //  0x80
//    Ut_P3,      //  0x100
//};
//
////单位符号的最基本单元的对应RAM地址空间
//
//#define     Ut_KW       (S23+COM2)// KW
//#define     Ut_H        (S23+COM1)// h
//#define     Ut_yuan     (S23+COM3)// 元
//#define     Ut_Reserved (S40+COM6)//预留
//
//#define     Len_UnitBit 3
//const uint8 code UnitBitTable[Len_UnitBit]=
//{
//    Ut_KW,      //  0x01
//    Ut_H,       //  0x02
//    Ut_yuan,    //  0x04
//
//};
//
////最多可显示如下16个单位，根据入口参数(0x00到0x0f)确定
//const uint16 code UnitTable[16]=
//{ //bit15--------------------------------------->bit0
//    0x00,
//    0x01+0x02,  //KWh
//    0x01,       //KW
//    0x04,       //元
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//    0x00,
//};
//
//
///*==============================================
//说明：中文显示内容
//================================================*/
////中文字符的各个对应位段的定义，对应的RAM地址空间，当显示屏调整后
////8表示地址存放于高5位（左移3位），后面加上的值表示在这个地址中对应存放的位
//
//
//#define     Cn_Dandqian     (S06+COM2) //当前
//#define     Cn_Zong         (S10+COM2) //总
//#define     Cn_Jian         (S10+COM1) //尖
//#define     Cn_Feng         (S11+COM1) //峰
//#define     Cn_Ping         (S12+COM1) //平
//#define     Cn_Gu           (S12+COM2) //谷
//#define     Cn_Yong         (S09+COM3) //用
//#define     Cn_Dian         (S09+COM2) //电
//#define     Cn_Liang        (S10+COM3) //量
//#define     Cn_Jia          (S11+COM2) //价
//#define     Cn_Shang        (S06+COM1) //上
//#define     Cn_Yue          (S09+COM1) //月
//#define     Cn_shi          (S11+COM3) // 时
//#define     Cn_jian         (S11+COM4) // 间
//#define     Cn_duan         (S12+COM3) // 段
//#define     Cn_she          (S23+COM4) // 赊
//#define     Cn_qian         (S09+COM4) // 欠
//
//
//#define Len_ChineseTable 17
////中文字符在显示真值表中的地址和对应位，高5位表示地址，低3位表示在对应内存的某一位
//const   uint8 code ChineseTable[Len_ChineseTable]=
//{
//    Cn_Dandqian,        //  0x01    当前
//    Cn_Zong,            //  0x02    总
//    Cn_Jian,            //  0x04    尖
//    Cn_Feng,            //  0x08    峰
//    Cn_Ping,            //  0X10    平
//    Cn_Gu,              //  0x20    谷
//    Cn_Yong,            //  0x40    用
//    Cn_Dian,            //  0x80    电
//    Cn_Liang,           //  0x100   量
//    Cn_Jia,             //  0x200   价
//    Cn_Shang,           //  0x400   上
//    Cn_Yue,             //  0x800   月
//    Cn_shi,             //  0x1000  时
//    Cn_jian,            //  0x2000  间
//    Cn_duan ,           //  0x4000  段
//    Cn_she,             //  0x8000  赊
//    Cn_qian ,           //  0x10000 欠
//
//};
//
//
//
////最多可显示 0x96项内容，通过一个字节的入口参数来实现
//#define Len_LCDChinaCode    0x14
//const uint32 code LCD_ChinaCode[Len_LCDChinaCode] =
//{
//    0x0000,                         //              00h
//    0x01+0x02+0x80+0x100,           // 当前电量总   01h
//    0x01+0x04+0x80+0x100,           // 当前电量尖   02h
//    0x01+0x08+0x80+0x100,           // 当前电量峰   03h
//    0x01+0x10+0x80+0x100,           // 当前电量平   04h
//    0x01+0x20+0x80+0x100,           // 当前电量谷   05h
//
//    0x400+0x800+0x02+0x80+0x100,    // 上Ｘ月电量总 06h
//    0x400+0x800+0x04+0x80+0x100,    // 上Ｘ月电量尖 07h
//    0x400+0x800+0x08+0x80+0x100,    // 上Ｘ月电量峰 08h
//    0x400+0x800+0x10+0x80+0x100,    // 上Ｘ月电量平 09h
//    0x400+0x800+0x20+0x80+0x100,    // 上Ｘ月电量谷 0ah
//    0x1000+0x4000,                  //时段          0bh
//    0x1000+0x2000,                  //时间          0ch
//    0x8000+0x10000,                 //赊欠          0dh
//};
//
////汉字区的8定义，以下表示每一段在1个字中的含义
//#define     C_a         (S08+COM4)
//#define     C_b         (S08+COM3)
//#define     C_c         (S08+COM2)
//#define     C_d         (S08+COM1)
//#define     C_e         (S07+COM2)
//#define     C_f         (S07+COM4)
//#define     C_g         (S07+COM3)
//#define     C_x         (S07+COM1)
//
//
//#define LCD_CODE_L  (C_d+C_e+C_f)           //'L'
//#define LCD_CODE_r  (C_e+C_g)               //'r'
//#define LCD_CODE_n  (C_c+C_e+C_g)           //'n'
//#define LCD_CODE_o  (C_c+C_d+C_e+C_g)       //小写字母'o',不是零
//#define Len_Strnum 8
//const   uint16  code BITStrnum[Len_Strnum]=
//{
//    C_a,        //0x01
//    C_b,        //0x02
//    C_c,        //0x04
//    C_d,        //0x08
//    C_e,        //0x10
//    C_f,        //0x20
//    C_g,        //0x40
//    C_x,        //0x80
//};
//
//const   uint8 code Strnum[19] =
//{
//    0x00,
//    0x02+0x04,                                  // 1
//    0x01+0x02+0x08+0x10+0x40,                   // 2
//    0x01+0x02+0x04+0x08+0x40,                   // 3
//    0x02+0x04+0x20+0x40,                        // 4
//    0x01+0x04+0x08+0x20+0x40,                   // 5
//    0x01+0x04+0x08+0x10+0x20+0x40,              // 6
//    0x01+0x02+0x04,                             // 7
//    0x01+0x02+0x04+0x08+0x10+0x20+0x40,         // 8
//    0x01+0x02+0x04+0x08+0x20+0x40,              // 9
//    0x01+0x02+0x04+0x10+0x20+0x40,              // A
//    0x04+0x08+0x10+0x20+0x40,                   // b
//    0x01+0x08+0x10+0x20,                        // c
//    0x02+0x04+0x08+0x10+0x40,                   // d
//    0x01+0x08+0x10+0x20+0x40,                   // e
//    0x01+0x10+0x20+0x40,                        // f
//    0x01+0x02+0x04+0x08+0x10+0x20+0x80,         // 10
//    0x02+0x04+0x80,                             // 11
//    0x01+0x02+0x08+0x10+0x40+0x80,              // 12
//};
//
//
#endif

#endif
