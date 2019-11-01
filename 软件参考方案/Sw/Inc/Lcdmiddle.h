#ifndef __LCDMIDDLE_H__
#define __LCDMIDDLE_H__


#ifndef LCDMIDDLEEXT
    #define LCDMIDDLEEXT extern
#else
    #define LCDMIDDLESELF
#endif

//Ӧ�ò�ӿں���
void Disp_Numb(uint32 data,uint32 type);
//void Disp_String(uint16 para);
//void Disp_UnitPoint(uint16 para);
//void Disp_State(uint32 data);

#ifdef LCDMIDDLESELF

//COM�ں�SEG�ڶ�Ӧ��RAM����
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
˵��������Ϊ������ʾ���ֵĶ��壬����������ʹ�������
====================================================*/
//��������������ڵ�RAM���ֽ�λ��
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
˵��������Ϊ������ʾ���ֵĶ��壬����������ʹ�������
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
//#define LCD_CHARH_o  (N_c+N_d)          //Сд��ĸ'o',������
//#define LCD_CHARL_C  (N_e+N_f)          //'C'
//#define LCD_CHARH_C  (N_a+N_d)          //'C'
//#define LCD_CHARL_E  (N_e+N_f+N_g)      //'E'
//#define LCD_CHARH_E  (N_a+N_d)          //'E'


///*==================================================
//˵����״̬��ʾλ
//===================================================*/
////8��ʾ��ַ����ڸ�5λ������3λ��,������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ
//
//#define     St_jian            (S29+COM4)      //��
//#define     St_feng            (S29+COM3)      //��
//#define     St_ping            (S29+COM2)      //ƽ
//#define     St_gu              (S29+COM1)      //��
//#define     St_quan1           (S28+COM1)      //Ȧ1
//#define     St_quan2           (S28+COM3)      //Ȧ2
//#define     St_dianhua         (S06+COM4)      //�绰����
//#define     St_zaib            (S06+COM3)      //�ز�ͨѶ����
//#define     St_dianchi         (S28+COM2)      //��ط���
//#define     St_glfanx          (S00+COM1)      //���ʷ���
//
////����Ϊ��ʾ���ݣ�ͨ��16��λ��ʵ��
//#define     St_Len     10
//const   uint8 code St_Table[St_Len]=
//{
//    St_jian,        //��
//    St_feng,        //��
//    St_ping,        //ƽ
//    St_gu,          //��
//    St_quan1,       //Ȧ1
//    St_quan2,       //Ȧ2
//    St_dianhua,     //�绰����
//    St_zaib,        //�ز�ͨѶ����
//    St_dianchi,     //��ط���
//    St_glfanx,      //���ʷ���
//};

///*======================================================
//˵����С������ŵ���ʾ
//========================================================*/
////���ż�С����ĸ���λ�εĶ���,P��ʾPOINT
////8��ʾ��ַ����ڸ�5λ������3λ����������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ
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
////С���㣨����"-"������ʾ��ֵ���еĵ�ַ�Ͷ�Ӧλ����5λ��ʾ��ַ����3λ��ʾ�ڶ�Ӧ�ڴ��ĳһλ
////��󳤶���16��Ŀǰֻ����9��������
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
////��λ���ŵ��������Ԫ�Ķ�ӦRAM��ַ�ռ�
//
//#define     Ut_KW       (S23+COM2)// KW
//#define     Ut_H        (S23+COM1)// h
//#define     Ut_yuan     (S23+COM3)// Ԫ
//#define     Ut_Reserved (S40+COM6)//Ԥ��
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
////������ʾ����16����λ��������ڲ���(0x00��0x0f)ȷ��
//const uint16 code UnitTable[16]=
//{ //bit15--------------------------------------->bit0
//    0x00,
//    0x01+0x02,  //KWh
//    0x01,       //KW
//    0x04,       //Ԫ
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
//˵����������ʾ����
//================================================*/
////�����ַ��ĸ�����Ӧλ�εĶ��壬��Ӧ��RAM��ַ�ռ䣬����ʾ��������
////8��ʾ��ַ����ڸ�5λ������3λ����������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ
//
//
//#define     Cn_Dandqian     (S06+COM2) //��ǰ
//#define     Cn_Zong         (S10+COM2) //��
//#define     Cn_Jian         (S10+COM1) //��
//#define     Cn_Feng         (S11+COM1) //��
//#define     Cn_Ping         (S12+COM1) //ƽ
//#define     Cn_Gu           (S12+COM2) //��
//#define     Cn_Yong         (S09+COM3) //��
//#define     Cn_Dian         (S09+COM2) //��
//#define     Cn_Liang        (S10+COM3) //��
//#define     Cn_Jia          (S11+COM2) //��
//#define     Cn_Shang        (S06+COM1) //��
//#define     Cn_Yue          (S09+COM1) //��
//#define     Cn_shi          (S11+COM3) // ʱ
//#define     Cn_jian         (S11+COM4) // ��
//#define     Cn_duan         (S12+COM3) // ��
//#define     Cn_she          (S23+COM4) // ��
//#define     Cn_qian         (S09+COM4) // Ƿ
//
//
//#define Len_ChineseTable 17
////�����ַ�����ʾ��ֵ���еĵ�ַ�Ͷ�Ӧλ����5λ��ʾ��ַ����3λ��ʾ�ڶ�Ӧ�ڴ��ĳһλ
//const   uint8 code ChineseTable[Len_ChineseTable]=
//{
//    Cn_Dandqian,        //  0x01    ��ǰ
//    Cn_Zong,            //  0x02    ��
//    Cn_Jian,            //  0x04    ��
//    Cn_Feng,            //  0x08    ��
//    Cn_Ping,            //  0X10    ƽ
//    Cn_Gu,              //  0x20    ��
//    Cn_Yong,            //  0x40    ��
//    Cn_Dian,            //  0x80    ��
//    Cn_Liang,           //  0x100   ��
//    Cn_Jia,             //  0x200   ��
//    Cn_Shang,           //  0x400   ��
//    Cn_Yue,             //  0x800   ��
//    Cn_shi,             //  0x1000  ʱ
//    Cn_jian,            //  0x2000  ��
//    Cn_duan ,           //  0x4000  ��
//    Cn_she,             //  0x8000  ��
//    Cn_qian ,           //  0x10000 Ƿ
//
//};
//
//
//
////������ʾ 0x96�����ݣ�ͨ��һ���ֽڵ���ڲ�����ʵ��
//#define Len_LCDChinaCode    0x14
//const uint32 code LCD_ChinaCode[Len_LCDChinaCode] =
//{
//    0x0000,                         //              00h
//    0x01+0x02+0x80+0x100,           // ��ǰ������   01h
//    0x01+0x04+0x80+0x100,           // ��ǰ������   02h
//    0x01+0x08+0x80+0x100,           // ��ǰ������   03h
//    0x01+0x10+0x80+0x100,           // ��ǰ����ƽ   04h
//    0x01+0x20+0x80+0x100,           // ��ǰ������   05h
//
//    0x400+0x800+0x02+0x80+0x100,    // �ϣ��µ����� 06h
//    0x400+0x800+0x04+0x80+0x100,    // �ϣ��µ����� 07h
//    0x400+0x800+0x08+0x80+0x100,    // �ϣ��µ����� 08h
//    0x400+0x800+0x10+0x80+0x100,    // �ϣ��µ���ƽ 09h
//    0x400+0x800+0x20+0x80+0x100,    // �ϣ��µ����� 0ah
//    0x1000+0x4000,                  //ʱ��          0bh
//    0x1000+0x2000,                  //ʱ��          0ch
//    0x8000+0x10000,                 //��Ƿ          0dh
//};
//
////��������8���壬���±�ʾÿһ����1�����еĺ���
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
//#define LCD_CODE_o  (C_c+C_d+C_e+C_g)       //Сд��ĸ'o',������
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
