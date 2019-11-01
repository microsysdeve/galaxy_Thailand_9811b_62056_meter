/***************************** Copyright by Vango ***********************************
	�ļ�����SetPLL.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����
	2011.2.22	 1.4	  JJJ				ȥ��SetPLL�п����͹ر�LDO33�Ĳ���
	2011.3.21	 1.5	  JJJ				��SetPLL������������CtrlBGP = 0x02���޸�ΪCtrlBGP = 0x62  ��������

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//=======================================================
//��������Set_PLL
//�������ã�����PLL������ϵͳʱ���л���PLL��32k
//��ڲ�����:
//			PLLClk=0x00-- �л���32K����PLL 
//			PLLClk=0x60-- pll 800k, adc 200k,���л���800kPLL
//			PLLClk=0x65-- pll 1.6M, adc 400k,���л���1.6MPLL
//			PLLClk=0x6a-- pll 3.2M, adc 800k,���л���3.2PLL
//			PLLClk=0x6f -- pll 6.4M, adc 1.6M,���л���6.4MPLL
//			

//���ڲ�������
//
//=======================================================


void SetPLL(unsigned char PLLClk)
{
	unsigned char tmp = 0;
	unsigned char i;
//	if(Systate&0x02)
//		CtrlMEAS |= 0x80;
//	else
//	CtrlMEAS &= ~0x80;
	if(PLLClk&PLLPDN)
	{
		tmp = 1;
	}
	F0 = 0;		//F0�����ڿ��ٿ���PLL�����F0=1����CtrlCLK���޷��޸�ϵͳʱ��

	if((CtrlCLK != PLLClk))
	{
		CLKFRQ = 0;
		while(CLKFRQ);//�Ƚ�ϵͳ��ʱ���е�32k
		CtrlCLK = 0x20;
		for(i=0;i<10;i++);
		CtrlCLK = PLLClk;//���л�PLLʱ��
		for(i=0;i<5;i++);	
	}
	
	CLKFRQ = tmp;//����л���ʱ�ӵ�Ŀ��״̬	

//	CtrlBGP &= ~0xf0;//PLL��Ƶʱ������ADC�߹���
	if((PLLClk&0x0c)==0x0)
	{	
		//CtrlBGP |= ADPOWER;//PLL��Ƶʱ������ADC�͹���
		CtrlBGP = 0xe2;;
		CtrlIAT = 0x1A;
		CtrlIBT = 0x1A;
		CtrlUT = 0x1A;
		CtrlMT = 0x1A;
	}
	else
	{
		CtrlIAT = 0x0;
		CtrlIBT = 0x0;
		CtrlUT = 0x0;
		CtrlMT = 0x0;
		CtrlBGP = 0x62;		 //���ø�������
	}
	if(CLKFRQ==0)
		CtrlADC = 0;//ϵͳ32kʱ���ر�ADC

	CtrlCry &= ~0x70;//����ref��ѹ�¶�ϵ��
//	CtrlBGP |= BGPCHOP;//��BGPCHOP

}



