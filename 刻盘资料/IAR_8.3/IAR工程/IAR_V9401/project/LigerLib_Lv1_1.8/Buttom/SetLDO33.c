
/***************************** Copyright by Vango ***********************************
	�ļ�����SetLDO33.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�JJJ
	�������ڣ�2011-02-21
	��ǰ�汾��1.4

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����
	

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"

//��������SetLDO33
//�������ã�����LDO33������ر�
//��ڲ���:
//			0,�ر�LDO33
//			1������LDO33
//			
//���ڲ�������
//
void SetLDO33(unsigned char Val_LDO33)
{
	
	if(!Val_LDO33)
		CtrlMEAS |= 0x80;
	else
		CtrlMEAS &= ~0x80;		
}