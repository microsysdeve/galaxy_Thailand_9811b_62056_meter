/***************************** Copyright by Vango ***********************************
	�ļ�����SetMChannel.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h


	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*���ܣ�����Mͨ��
��ڣ�val_channel��M ͨ���Ĳ���ͨ��ѡ��
	0x0: measure the ground;
	0x1: measure temperature
	0x22: measure battery SETM_VBAT1// ��ѹ��
	0x23: measure battery SETM_VBAT2//  ��ѹ��
	0x03: measure external input VM//  ����ѹ
	0x04: measure SEG33//  ����ѹ
	0x05: measure SEG34//  ����ѹ
	0x06: measure SEG35//  ����ѹ
	0x07: measure SEG36//  ����ѹ
	0x24: measure SEG33//  ��ѹ��
	0x25: measure SEG34//  ��ѹ��
	0x26: measure SEG35//  ��ѹ��
	0x27: measure SEG36//  ��ѹ��
	val_para��M ͨ������ѡ��
		SETM_T1 ��Ӧ1������
		SETM_T2 ��Ӧ2������
		SETM_CLOSE ��ʾ�ر�Mͨ��

	val_para��M ͨ������ѡ��0��1��0x11��0x31 �ֱ��Ӧ1��2��4��8 ������
								0x80��ʾ�ر�Mͨ��
���ڣ���*/

void SetMChannel(unsigned char val_channel,unsigned char val_para)
{

	if(val_para&0x80)
	{
		CtrlADC &= ~0x08;//��mͨ��
		CtrlMEAS = 0;	
		return;
	}
	
	CtrlADC |= 0x08;//��mͨ��
	CtrlGM = val_para&0x01;
	CtrlMEAS &= 0x80;
	CtrlMEAS |= val_channel;	
}