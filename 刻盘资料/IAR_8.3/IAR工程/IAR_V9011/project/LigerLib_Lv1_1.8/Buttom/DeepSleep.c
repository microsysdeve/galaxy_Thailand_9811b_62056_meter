/***************************** Copyright by Vango ***********************************
	�ļ�����DeepSleep.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"


/*���ܣ�
	�ر�LDO33��
	����LDO25�����ѹ��� ��Լ2.1V��
	��AD��
	��SEG�������LCD����LCDʱ�ӣ�
	��ֹ������·����˫��ram���ر����м���ͨ������PMʱ�ӣ�
	��ϵͳ�е���Ƶ������
	��PLL��
	��ϵͳ���ٽ�����˯�ߡ�
*/

void DeepSleep(void)
{
	volatile unsigned char xdata *point;
	F0 = 0;
	CtrlMEAS = 0x80;
	CtrlLDO &= ~0x07;
	CtrlLDO |= LDOVSEL1;//LDO25�����ѹ��� ��Լ2.1V	
	CtrlADC =  0;//��AD
//��SEG�������LCD����LCDʱ��
	point = &LCDCtrl;
	*point = 0;
	point++;
	*point = 0;
	point++;
	*point = 0;
	point++;
	*point = 0;
	point++;
	*point = 0;
	point++;
	*point = 0;
	
	LCDG = 1;
//��ֹ������·����˫��ram���ر����м���ͨ������PMʱ��

	PMCtrl1 = 0;
	PMCtrl4 = 0;
	PMG = 1;
	CLKFRQ = 0;//����ʱ���л���32k
	while(CLKFRQ);
	CtrlCLK = 0;//��PLL
	SLEEP0 = 0;
	SLEEP1 = 1;// ϵͳ������˯��
	while(1);
}
