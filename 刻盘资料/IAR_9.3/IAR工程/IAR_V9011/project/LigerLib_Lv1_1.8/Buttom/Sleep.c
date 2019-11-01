/***************************** Copyright by Vango ***********************************
	�ļ�����Sleep.c
	���ͷ�ļ��EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"



/*���ܣ�
	��LDO33
	����LDO25�����ѹ��� ��Լ2.1V��
	��AD��
	��ֹ������·����˫��ram���ر����м���ͨ������PMʱ�ӣ�
	��ϵͳ�е���Ƶ������
	��PLL��
	��ϵͳ���ٽ���ǳ˯�ߡ�
*/

void Sleep(void)
{
	F0 = 0;
	CtrlMEAS = 0x80;
	CtrlLDO  &= ~0x07;
	CtrlLDO  |= LDOVSEL1;//LDO25�����ѹ��� ��Լ2.1V
	CtrlADC = 0;	//��AD
	//�ر����м���ͨ������PMʱ��
	PMCtrl1 = 0;
	PMCtrl4 = 0;
	PMG = 1;
//	switch_clk = 0;//����ʱ���л���OSC
//	F1 = 1;// PLL�л���OSC���ر�PLL��ϵͳ����ǳ˯��
	CLKFRQ = 0;//����ʱ���л���32k
	while(CLKFRQ);
	CtrlCLK = 0;//��PLL
	SLEEP1 = 0;
	SLEEP0 = 1;// ϵͳ���ٽ�����˯��
	while(1);
}