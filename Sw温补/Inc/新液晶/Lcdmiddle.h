#ifndef __LCDMIDDLE_H__
#define __LCDMIDDLE_H__


#ifndef LCDMIDDLEEXT
    #define LCDMIDDLEEXT extern
#else
    #define LCDMIDDLESELF
#endif

//Ӧ�ò�ӿں���
void Disp_Numb(uint32 data,uint32 type);
void Disp_String(uint16 para);
void Disp_UnitPoint(uint16 para);
void Disp_State(uint32 data);




//COM�ں�SEG�ڶ�Ӧ��RAM����
//COM�ں�SEG�ڶ�Ӧ��RAM����
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
˵��������Ϊ������ʾ���ֵĶ��壬����������ʹ�������
====================================================*/
//��������������ڵ�RAM���ֽ�λ��
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
˵��������Ϊ������ʾ���ֵĶ��壬����������ʹ�������
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
#define LCD_CHAR1H_o  (NUM1C+NUM1D)                 //Сд��ĸ'o',������
#define LCD_CHAR1L_o  (NUM1E+NUM1G)                 //Сд��ĸ'o',������
#define LCD_CHAR1H_C  (NUM1E+NUM1F)                 //'C'
#define LCD_CHAR1L_C  (NUM1A+NUM1D)                 //'C'
#define LCD_CHAR1H_E  (NUM1E+NUM1F+NUM1G)           //'E'
#define LCD_CHAR1L_E  (NUM1A+NUM1D)                 //'E'

/*==================================================
˵����״̬��ʾλ
===================================================*/
//8��ʾ��ַ����ڸ�5λ������3λ��,������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ

#define     St_jian            (S28+COM4)      //��
#define     St_feng            (S28+COM3)      //��
#define     St_ping            (S28+COM2)      //ƽ
#define     St_gu              (S28+COM1)      //��
#define     St_quan1           (S28+COM6)      //Ȧ1
#define     St_quan2           (S06+COM5)      //Ȧ2
//#define     St_fangzi          (0)      //����
#define     St_dianhua         (S07+COM6)      //�绰����
//#define     St_zaib            (0)      //�ز�ͨѶ����
#define     St_biancheng       (S36+COM5)      //��̷���
#define     St_dianchi         (S19+COM5)      //��ط���
#define     St_glfanx          (S06+COM6)      //���ʷ���
#define     St_suo             (S21+COM5)      //������
//#define     St_kuang1          (0)      //��1
//#define     St_kuang2          (0)      //��2
//#define     St_kuang3          (0)      //��3
//#define     St_kuang4          (0)      //��4
//#define     St_sanjiao1        (0)      //����1
//#define     St_sanjiao2        (0)      //����2
//#define     St_duka            (0)      //����
//#define     St_zhong           (0)      //��
//#define     St_chenggong       (0)      //�ɹ�
//#define     St_shibai          (0)      //ʧ��
//#define     St_qingoudian      (0)      //�빺��
//#define     St_lazha           (0)      //��բ
//#define     St_touzi           (0)      //͸֧
//#define     St_tunji           (0)      //�ڻ�
#define     St_NumFu           (S06+COM1)       //����
//#define     St_Reserved        (0)
//����Ϊ��ʾ���ݣ�ͨ��16��λ��ʵ��
#define     St_Len     12
const   uint16 code St_Table[St_Len]=
{
    St_jian,        //��
    St_feng,        //��
    St_ping,        //ƽ
    St_gu,          //��
    St_quan1,       //Ȧ1
    St_quan2,       //Ȧ2
    St_dianhua,     //�绰����
    //St_zaib,        //�ز�ͨѶ����
    St_biancheng,   //��̷���
    St_dianchi,     //��ط���
    St_glfanx,      //���ʷ���
    St_suo,         //������
    //St_kuang1,      //��1
    //St_kuang2,      //��2
    //St_kuang3,      //��3
    //St_kuang4,      //��4
    //St_sanjiao1,    //����1
    //St_sanjiao2,    //����2
    //St_Reserved,    //����
    //St_duka,        //����
    //St_zhong,       //��
    //St_chenggong,   //�ɹ�
    //St_shibai,      //ʧ��
    //St_qingoudian,  //�빺��
    //St_lazha,       //��բ
    //St_touzi,       //͸֧
    //St_tunji,       //�ڻ�
    //St_fangzi,      //����
    St_NumFu,       //����
};

/*======================================================
˵����С������ŵ���ʾ
========================================================*/
//���ż�С����ĸ���λ�εĶ���,P��ʾPOINT
//8��ʾ��ַ����ڸ�5λ������3λ����������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ
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
//#define     St_fanx            (S19+COM5)      //�������
#define     Pt_Reserved (0)//


//С���㣨����"-"������ʾ��ֵ���еĵ�ַ�Ͷ�Ӧλ����5λ��ʾ��ַ����3λ��ʾ�ڶ�Ӧ�ڴ��ĳһλ
//��󳤶���16��Ŀǰֻ����9��������
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

//��λ���ŵ��������Ԫ�Ķ�ӦRAM��ַ�ռ�

#define     Ut_KW       (S37+COM6)// KW
#define     Ut_H        (S37+COM5)// h
//#define     Ut_cos      (0)// cos
//#define     Ut_yuan     (0)// Ԫ
//#define     Ut_Reserved (0)//Ԥ��

#define     Len_UnitBit 2
const uint16 code UnitBitTable[Len_UnitBit]=
{
    Ut_KW,      //  0x01
    Ut_H,       //  0x02
    //Ut_yuan,    //  0x04
    //Ut_cos,     //  0X08
};

//������ʾ����16����λ��������ڲ���(0x00��0x0f)ȷ��
#define UnitTableLen 3
const uint16 code UnitTable[UnitTableLen]=
{ //bit15--------------------------------------->bit0
    0x00,
    0x01+0x02,  //KWh
    0x01,       //KW
    //0x08,       //cos
    //0x04,       //Ԫ
};


/*==============================================
˵����������ʾ����
================================================*/
//�����ַ��ĸ�����Ӧλ�εĶ��壬��Ӧ��RAM��ַ�ռ䣬����ʾ��������
//8��ʾ��ַ����ڸ�5λ������3λ����������ϵ�ֵ��ʾ�������ַ�ж�Ӧ��ŵ�λ


#define     Cn_Dandqian     (S07+COM5) //��ǰ
#define     Cn_Zong         (S13+COM5) //��     //����ֵ��
#define     Cn_Jian         (S13+COM6) //��
#define     Cn_Feng         (S17+COM6) //��
#define     Cn_Ping         (S17+COM5) //ƽ
#define     Cn_Gu           (S18+COM5) //��
//#define     Cn_Yong         (S16+COM1) //��
#define     Cn_Dianliang         (S18+COM6) //��
//#define     Cn_Liang        (S11+COM3) //��
//#define     Cn_Jia          (0) //��
#define     Cn_Shang        (S08+COM5) //��
#define     Cn_Yue          (S12+COM6) //��
//#define     Cn_ZhuH         (0) //���
//#define     Cn_Zheng        (S04+COM6) //��
//#define     Cn_Fan          (S14+COM6) //��
//#define     Cn_Xiang        (S05+COM6) //��
//#define     Cn_ling         (0) //��
//#define     Cn_huo          (S01+COM4) //��
//#define      Cn_shijian       (S28+COM5) // ʱ
//#define     Cn_jian         (S00+COM2) // ��
//#define     Cn_duan         (S07+COM1) // ��
//#define     Cn_biao         (S14+COM1) // ��
//#define     Cn_hao          (S17+COM1) // ��
//#define     Cn_hu           (S12+COM1) // ��
//#define     Cn_jine         (S09+COM1) // ���
//#define     Cn_cs           (S15+COM1) // ����
//#define     Cn_sy           (S13+COM1) // ʣ��
//#define     Cn_GL           (S16+COM1) // ����
//#define     Cn_she          (S18+COM1) // ��
//#define     Cn_qian         (S17+COM1) // Ƿ
//#define     Cn_jt           (S20+COM1) // ����
//#define     Cn_V        (S00+COM5)// V
//#define     Cn_A        (S00+COM4)// A
//#define     Cn_Reserved     (S23+COM6) //Ԥ��


#define Len_ChineseTable 9
//�����ַ�����ʾ��ֵ���еĵ�ַ�Ͷ�Ӧλ����5λ��ʾ��ַ����3λ��ʾ�ڶ�Ӧ�ڴ��ĳһλ
const   uint8 code ChineseTable[Len_ChineseTable]=
{
    Cn_Dandqian,        //  0x01    ��ǰ
    Cn_Zong,            //  0x02    ��
    Cn_Jian,            //  0x04    ��
    Cn_Feng,            //  0x08    ��
    Cn_Ping,            //  0X10    ƽ
    Cn_Gu,              //  0x20    ��
    Cn_Dianliang,       //  0x40    ����
    //Cn_Liang,           //  0x80    ��
    //Cn_Jia,             //  0x100   ��
    Cn_Shang,        //  0x80   ����
    Cn_Yue,             //  0x100   ��
    //Cn_ZhuH,            //  0x800  ���
    //Cn_ling,            //  0x1000 ��
    //Cn_shijian,         //  0x200   ʱ��
    //Cn_jian,            //  0x4000��
    //Cn_duan ,           //  0x8000��
    //Cn_biao,            //  0x10000��
    //Cn_hao,             //  0x20000��
    //Cn_hu ,             //  0x40000��
    //Cn_jine,            //  0x80000���
    //Cn_cs ,             //  0x100000����
    //Cn_sy ,             //  0x200000ʣ��
    //Cn_jt ,             //  0x400000����
    //Cn_V,               //  0x800000 ѹ
    //Cn_A,               //  0x1000000 ��
    //Cn_GL,              //  0x2000000 ����
    //Cn_Yong,            //  0x40    ��
    //Cn_Zheng,           //  0x2000  ��
    //Cn_Fan,             //  0x4000  ��
    //Cn_Xiang,           //  0x8000  ��
    //Cn_huo,             //  0x20000��
    //Cn_she,             //  0x8000000��
    //Cn_qian ,           //  0x10000000Ƿ

};


//������ʾ 0x96�����ݣ�ͨ��һ���ֽڵ���ڲ�����ʵ��
#define Len_LCDChinaCode    13
const uint32 code LCD_ChinaCode[Len_LCDChinaCode] =
{
    0x0000,                             //              00h
    0x01+0x02+0x40,                     // ��ǰ������   01h
    0x01+0x04+0x40,                     // ��ǰ������   02h
    0x01+0x08+0x40,                     // ��ǰ������   03h
    0x01+0x10+0x40,                     // ��ǰ����ƽ   04h
    0x01+0x20+0x40,                     // ��ǰ������   05h

    0x02+0x40+0x80+0x100,                     // �ϣ��µ����� 06h
    0x04+0x40+0x80+0x100,                     // �ϣ��µ����� 07h
    0x08+0x40+0x80+0x100,                     // �ϣ��µ����� 08h
    0x10+0x40+0x80+0x100,                     // �ϣ��µ���ƽ 09h
    0x20+0x40+0x80+0x100,                     // �ϣ��µ����� 0ah
    
    0x01+0x200,                         //��ǰʱ��          0bh
    0x200,                              //ʱ��              0ch
};

//��������8���壬���±�ʾÿһ����1�����еĺ���
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
#define LCD_CODE_o  (C_c+C_d+C_e+C_g)       //Сд��ĸ'o',������
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
