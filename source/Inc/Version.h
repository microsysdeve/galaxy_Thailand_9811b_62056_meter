/*
*�汾����
*ÿ���һ���汾��ע����ǰ�汾����һ�汾��֮ͬ��,���ļ���Դ�ļ����б䶯,����ָ��
*
*/
#ifndef __VERSION_H__
#define __VERSION_H__
//ϵͳ������ѹ
#define CONFIG_VCC      0               //0-3.3V����ϵͳ 1-5V����ϵͳ
//�ϵ��ȶ�ʱ��
#define CONFIG_DELAY    1              //�ϵ��жϵ�Դ�ȶ���ʱ����λ20ms��
//ͨ������
#define CONFIG_CH       2               //1-��ͨ�� 2-˫ͨ��
#define CONFIG_CH_DLY   2               //ͨ���л���ʱ����λS
//PT����
#define CONFIG_PT       1               //0-����PT 1-��PT
//�������߷�ʽ
#define CONFIG_JUNC     1              //0-���� 1-����
#define CONFIG_POW_DLY  1               //���������ж���ʱ
//RTC����
#define CONFIG_RTC      1               //0-�� 1-�ڲ� 2-�ⲿ
//SOCʱ��Դ���ã�Ĭ��0Ϊȫ��
#define CONFIG_PRCTRL0  0               //
#define CONFIG_PRCTRL1  0               //
//Uart������ü�ComConfig.h
//���ֵײ����ü�McuDriver.h
//�����������
#define MEA_AMUL        12800*2979      //3.2M/800K����������32K�������޲�ֵ����ϵ��
#define MEA_BMUL        1               //����ͨ��1�����ͨ��2�����źű�����ϵ A>B-* A<B-/

#define MEA_SLP_PLL     1               //����ʱ�ļ���ʱ������    0-800K,   1-3.2M
#define MEA_SLP_FMCU    1               //����ʱ��MCUʱ������    0-800K,   1-3.2M
#define MEA_SLP_CF      1               //���߼����Ƿ��CF����    0-����,   1-��
#define POW_OFF_DISP    0               //���߻���ʱ�Ƿ���ʾ      0-����ʾ, 1-��ʾ
#define POW_OFF_ENYPROC  1              //���߻���ʱ�Ƿ��������  0-������, 1-����


#define START_TH_1A       0x01
#define START_TH_0A5     0x02

#define START_TH   START_TH_0A5   //�������޺궨��

#if( START_TH == START_TH_1A)  //1A����

  #define IDET_STARTA     10608000           //A·���ٵ�����ֵⷧ 1A x 0.8
  #define IDET_STARTB     11040000           //B·���ٵ�����ֵⷧ 1A x 0.8
  #define RMSII1_TH       6538500     //1A x 0.9  Ҫ��֤RMSII1���ڴ����޵�ʱ�� ���ٵ��������һֱ��⵽����

#elif( START_TH == START_TH_0A5)  //0.5A����

  #define IDET_STARTA     3978000           //A·���ٵ�����ֵⷧ 1A x 0.3
  #define IDET_STARTB     4140000           //B·���ٵ�����ֵⷧ 1A x 0.3
  #define RMSII1_TH       (2906000 *8)    //1A x 0.4

#endif

//���ٵ�����ֵⷧ���������ڱȲ�Ϊ0ʱ�õ��ļĴ���RMSII1��RMSII2��ֵ
//#define IDET_STARTA     6600000           //A·���ٵ�����ֵⷧ 1A
//#define IDET_STARTB     6800000           //B·���ٵ�����ֵⷧ 1A

//#define IDET_STARTA     5280000           //A·���ٵ�����ֵⷧ 1A x 0.8
//#define IDET_STARTB     5440000           //B·���ٵ�����ֵⷧ 1A x 0.8

//#define IDET_STARTA     1980000           //A·���ٵ�����ֵⷧ 1A x 0.3
//#define IDET_STARTB     2040000           //B·���ٵ�����ֵⷧ 1A x 0.3

//x.xA����ʱ�Ĵ���RMSII1��ֵ(�����Ȳ����֮���ֵ)
//#define RMSII1_TH       3620000   //1A

//#define RMSII1_TH       3258000     //1A x 0.9  Ҫ��֤RMSII1���ڴ����޵�ʱ�� ���ٵ��������һֱ��⵽����

//#define RMSII1_TH       1448000     //1A x 0.4

//�������
#define CONST_A_METER   0               //����Һ����
#define CONST_B_METER   1               //�����
#define CONST_C_METER   2


#define __D143__                     //������Ե�

/**���ѡ��Ͱ汾����
�汾����
*/

#if defined(__D143__)
    #define __METER_TYPE__ CONST_B_METER
#endif

#if (__METER_TYPE__ != CONST_B_METER)
    #error "VersionExt.h: system not define B meter type!!!"
#endif

#define __VER_SOFT_B__  "D143F9821S03"      //��ǰ����汾
#define __VER_HARD_B__  0x01            //��ǰӲ���汾

extern const __root uint8 code gCuc_VerSoft[];
extern const __root uint8 code gCuc_VerHard[];


#endif

