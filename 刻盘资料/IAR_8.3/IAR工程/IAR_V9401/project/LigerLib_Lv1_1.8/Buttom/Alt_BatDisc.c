/***************************** Copyright by Vango ***********************************
	�ļ�����Alt_BatDisc.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*���ܣ� ��طŵ�ѡ��
��ڣ� val_para��0----�رյ�طŵ繦�ܣ�1----�򿪵�طŵ繦��
���ڣ���
#define Enable_BatDisc 1
#define Disable_BatDisc 0
����س�ʱ�䲻ʹ��ʱ��ʹ�ܵ�طŵ�Alt_BatDisc(Enable_BatDisc)���Է�ֹ��ؽ��жۻ�״̬��
��طŵ�����У���������ĵĵ���ԼΪ3mA,��Լ��500ms���رյ�طŵ繦��Alt_BatDisc(Disable_BatDis),
����ʱ������������ء�
*/

void Alt_BatDisc(unsigned char val_para)
{
	if(val_para==0)
		CtrlBAT &= ~0x08;
	else CtrlBAT |= 0x08;
}
