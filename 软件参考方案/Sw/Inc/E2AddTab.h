#ifndef _E2ADDRTAB_H_
#define _E2ADDRTAB_H_


/***********************************E2��ַ�Ų�����**************************************/
//���º궨�����ݶ�Ϊ���ڵ�������E2�еĴ洢��ַ,ʵ�����ݳ��ȿ��Դ���������ĵ�ַ��õ�,
//����Բ鿴����E2�Ų��������ϸ����ĵ�
/****************************************************************************************/
#define EEP_BAK_LEN       0x0180

//��0ҳ
#define EEP_COMADD        0x0000  //���
#define EEP_XLZQ          0x0007  //��������
#define EEP_FHQXZQ        0x0008  //������������
#define EEP_MANUDATE      0x0009  //��������
#define EEP_JBDATE        0x000c  //У������
#define EEP_FEEMDATE      0x000f  //�����޸�����
#define EEP_RDPASSWORD    0x0014  //����1
#define EEP_WRPASSWORD    0x001c  //����2
#define EEP_CBR1          0x0024  //��1������
#define EEP_CBR2          0x0026  //��2������
#define EEP_CBR3          0x0028  //��3������
#define EEP_BATTERYSTAT   0x002a  //���״̬

//��1ҳ
#define EEP_WORK_FEE_TIME 0x0040  //�����շ���ʱ��
#define EEP_SAT_FEE_TIME  0x0050  //����������ʱ��
#define EEP_SUN_FEE_TIME  0x0060  //�����շ���ʱ��

//��2ҳ
#define EEP_WORK_FEE      0x0080  //�����շ���
#define EEP_SAT_FEE       0x0088  //����������
#define EEP_SUN_FEE       0x0090  //�����շ���

//��3ҳ
#define EEP_JBTOTAL       0x00C0  //У������׵�ַ
#define EEP_JBBCS         0x00C0  //����
#define EEP_JBBCDY        0x00C2  //��Ƶ�ѹ
#define EEP_JBBCDL        0x00C4  //��Ƶ���


//��4ҳ
#define EEP_EPS             0x0100  //��ǰ��������


//��12ҳ
#define EEP_EPHIS_PT        0x0300  //��ʷ����ָ��
#define EEP_EPHIS           0x0301  //��ʷ�й�������E2����ʼ��ַ


//��16ҳ
#define EEP_XULIANGHIS_PT   0x0400  //��ʷ����ָ��
#define EEP_XULIANGHIS      0x0401  //��ʷ�����׵�ַ

//��18ҳ
#define EEP_XGEVENT_PT      0x0480  //���߸Ǽ�¼ָ��
#define EEP_XGEVENT         0x0481
//��20ҳ
#define EEP_BGEVENT_PT      0x0500  //����Ǽ�¼ָ��
#define EEP_BGEVENT         0x0501

//�����¼ ��22ҳ
#define EEP_DDETNO          0x0580      //�����ܴ���
#define EEP_DDET_PT         0x0582      //�����¼ָ��
#define EEP_DDET            0x0583      //�����¼��E2�е���ʼ��ַ


#define EEP_POWDWENERGY     0x0640




#endif

