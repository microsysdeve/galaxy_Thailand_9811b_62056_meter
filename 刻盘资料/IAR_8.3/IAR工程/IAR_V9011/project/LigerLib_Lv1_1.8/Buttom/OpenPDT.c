/***************************** Copyright by Vango ***********************************
	�ļ�����OpenPDT.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2008��12-0
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*���ܣ���BGP����powerdown ��⡣
���ڣ���
*/
void OpenPDT(void)
{
	CtrlCLK |= BGPPDN;//��BGP
	CtrlLDO |= DGEN;
}