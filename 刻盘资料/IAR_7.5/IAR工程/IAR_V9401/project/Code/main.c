 /***************************** Copyright by Vango ***********************************

	�ļ����ͣ�V9401 ��IAR5.30��д����
	�ļ����ã���Ҫ����SuperDebug����ʵ��,������ɺ�������LED�������300ms��˸4�Σ�ͣ��1.8S����
			  ������˸�����Դ�Ϊѭ������ʵ��ɹ���

	�� �� �ˣ�DL
	�������ڣ�2012��6��19��
        �޸����ڣ�2013��1��8��
	��ǰ�汾��IAR_V9401_Ver2.0
	
	�汾��Ϣ��IAR_V9401_ver2.0
**************************************************************************************/
#include "dw8051.h"
#include "ExLigReg.h"
#include "ExLigLib.h"
#include "delay.h"
#include "func.h"
__root const unsigned char __code codepsword[1]@0x400=
{ 
  0xff
};

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