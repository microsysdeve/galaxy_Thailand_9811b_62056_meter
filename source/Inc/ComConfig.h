#ifndef __ComConfig_H__
#define __ComConfig_H__


#define Const_BPS_600       0               // bps����
#define Const_BPS_1200      1               //
#define Const_BPS_2400      2               //
#define Const_BPS_4800      3               //
#define Const_BPS_9600      4               //
/*
#define Const_MaxComNum     1               // ����Ϊ��Ӧ��buf��ţ������������һ��buf����ȫ��Ϊ0������ֿ��������ʵ�ʷֿ�
#define ComIndex_Uart4      _R485_Chanel_               //  485
#define ComIndex_Uart2      1               //  ����
#define ComIndex_Uart1      2               //  �ز�
*/
//�˿�
//#define Const_MaxPortNum    1               // �ܵĶ˿���
//#define Port_Uart4          0               // �˿���COM�Ķ�Ӧ��ϵ
//#define Port_Uart2          1               //
//#define Port_Uart1          2               //
#define Port_Idle           0xff            // ��COMĿǰû��ʹ�ã�������������д�뵽��COM��Ӧ��buf��

//��ʱʱ��
#define Const_DyUartOut     0xff            // ��ʱ����
#define Const_DyRvPack      50              // 500ms,���ճ�ʱʱ�䣬�����ʾһ�����ݰ��ӽ�����־

//COM�ڵ�״̬
#define ComStt_Recv         01              // COM���ڽ���״̬�����ж��д���
#define ComStt_Send         02              // COM���ڷ���״̬�����ж��д���
#define ComStt_Idle         03              // COM���ڿ���״̬
#define ComStt_WaitProc     04              // COM���ڵȴ�����״̬�����������д���

//�봮��BUFF���
#define Const_MaxBufLen     255             // ����������

#endif
