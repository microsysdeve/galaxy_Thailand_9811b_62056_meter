/***************************** Copyright by Vango ***********************************
	�ļ�����InitAnalog.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//��û���õ����ļĴ���λ����
void InitAnalog(void)
{
	volatile unsigned char xdata *point;
	point = &CtrlSHORT;
	*point = 0;
	point++;
	point++;
	*point = 0;	
	point = &CtrlPLL;
	*point = 0;	
}