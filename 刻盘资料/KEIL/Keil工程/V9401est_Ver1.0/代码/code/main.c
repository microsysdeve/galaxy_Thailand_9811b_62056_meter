 /***************************** Copyright by Vango ***********************************

	�ļ����ͣ�V9401TEST C51 Keil3��д����
	�ļ����ã���Ҫ����SuperDebug����ʵ��,������ɺ�������LED�������300ms��˸4�Σ�ͣ��1.8S����
			  ������˸�����Դ�Ϊѭ������ʵ��ɹ���

	�� �� �ˣ�DL
	�������ڣ�2011��12��31��
	��ǰ�汾��V9401Test_Ver1.0
	
	�汾��Ϣ��V9401Test_ver1.0
**************************************************************************************/
#include "dw8051.h"
#include "ExLigReg.h"
#include "ExLigLib.h"
#include "delay.h"
#include "func.h"


void main()
{
	Init_Port();
	SetPLL(SETPLL_3_2M);//����3.2M��MCUʱ�ӣ��������ԣ�F11���˺�����ʧȥ��������
	ClearWDT();
	while(1)
	{
		Led_Twin(4);
		ClearWDT();
		delayms(500);//���������ʱ��300ms���ԣ����Ϊ1.8s
		delayms(500);
		delayms(500);
		ClearWDT();
	}
		
}