
#ifndef _FUNC_H_
#define _FUNC_H

//****************��λ��־�궨��*******************************
#define BIT0 0X01
#define BIT1 0X02
#define BIT2 0X04
#define BIT3 0X08
#define BIT4 0X10
#define BIT5 0X20
#define BIT6 0X40
#define BIT7 0X80
//**************************************************************
#define LED_ON() {P1OE &= (~BIT4);P1IE &= ~BIT4; P1OD |= BIT4;}//����LED��PCBIO1.4
#define LED_OFF() {P1OE &= (~BIT4);P1IE &= ~BIT4;P1OD &= (~BIT4);}//�ر�LED
/*****************************************************************************
//*****************************************************************************

/******************************************************************************
 * @brief 
 * ι������
 * ע�⣺�ڵ���ģʽ�£����Ź�ʧЧ���벻Ҫ��⿴�Ź��Ƿ�λ��
 * ���Ź�����û��ι��1.5�븴λһ�Σ�ͨ�������ж�ʱ���WDT ����ֵ.
 *******************************************************************************/
#define ClearWDT() {WDTEN=0xa5;WDTCLR=0x5a;}

extern void Led_Twin(unsigned char i);//����LED����

extern void delay(unsigned int sec);//��ʱ����
extern void delayms(unsigned int j);//��ʱ
extern void Init_Port(void);

 #endif
