#ifndef _E2ADDRTAB_H_
#define _E2ADDRTAB_H_
/***********************************E2��ַ�Ų�����**************************************/
//���º궨�����ݶ�Ϊ���ڵ�������E2�еĴ洢��ַ,ʵ�����ݳ��ȿ��Դ���������ĵ�ַ��õ�,
//����Բ鿴����E2�Ų��������ϸ����ĵ�
/****************************************************************************************/
#define EEP_BAK_LEN         0x00C0

//�����ǵ�0~1ҳ��ַ 
//У����� 
#define EEP_JBTOTAL         0x0000  //У������׵�ַ
#define EEP_JBBCS           0x0000  //����
#define EEP_JBBCDY          0x0002  //��Ƶ�ѹ
#define EEP_JBBCDL          0x0004  //��Ƶ���

//�����ǵ�1.5ҳ��ַ
//�����ǵ�ǰ��������
#define EEP_EPS             0x0060  //��ǰ�й���������

//�����ǵ�2ҳ��ַ
//#define EEP_COMADD          0x0080  //ͨѶ��ַ,6Bytes
#define EEP_UARTBDM         0x0086  //ͨ�ſ�1ͨ������������
#define EEP_MAX_LX_NUM      0x0087  //�Զ�ѭ����ʾ����
#define EEP_LXTM            0x0088  //ÿ����ʾʱ��
#define EEP_EDEC            0x0089  //��ʾ����С��λ��
#define EEP_PDEC            0x008A  //��ʾ����(���������ʾλ��)
#define EEP_MAX_JX_NUM      0x008B  //����ѭ����ʾ����
#define EEP_SHOWERRPOS      0x008C  //ERR��������ʾλ��
#define EEP_POWUPJXTM       0x008D  //�е��¼�����ʾʱ��(����)
#define EEP_POWDWJXTM       0x008E  //ͣ���¼�����ʾʱ��(����)
#define EEP_POWOFFXSTM      0x008F  //ͣ����ʾʱ��(����)
#define EEP_FULLSHOWTM      0x0091  //ȫ����ʾʱ��(����)
#define EEP_POWUPBGTM       0x0092  //�ϵ米����ʱ��(����)
#define EEP_IRBGTM          0x0093  //���ⴥ��������ʱ��(����)
#define EEP_KEYBGTM         0x0094  //��������������ʱ��(����)
#define EEP_ESAMERRBGTM     0x0095  //ESAM���󱳹���ʱ��(����)
#define EEP_LEDSFCKTM       0x0096  //LED�Լ�ʱ��(����)
#define EEP_CFSAVECFG       0x0097  //CF���������������
#define EEP_CBRCFG          0x0098  //�����ղ��������������
#define EEP_DJCFG           0x0099  //���Ჹ�������������
#define EEP_PWLCFG          0x009A  //����ȼ���Ч�����������
#define EEP_SQSDCFG         0x009C  //ʱ����ʱ���л�ʱ�������б������������
#define EEP_ENSHOWCFG       0x009D  //������ʾ��ʽ�����������
#define EEP_TMSHOWCFG       0x009E  //ʱ����ʾ��ʽ�����������
#define EEP_PWOFFSHOWMDCFG  0x009F  //ͣ����ʾģʽ�����������
#define EEP_JDQCKCFG        0x00A0  //�̵�����ⷽʽ�����������
#define EEP_METERCLRCNT     0x00A1  //������������������
#define EEP_METERCLFENGVAL  0x00A2  //������������ֵ��������
//����3~5ҳ������ı��ݵ�ַ

//�����ǵ�6ҳ��ַ
//��ʾ����
#define EEP_LXTABLE         0x0180    //ѭ�Ա�    32�ֽ� 
#define EEP_JXTABLE         0x0180    //���Ա�    ��ͬ����

//�����ǵ�7ҳ��ַ 
#define EEP_MAXDEMAND       0x01C0    //
#define EEP_AUTOCAL         0x01CC    //�Զ�У��ȶ�����

#define EEP_DATETIME        0x01E0
//�����ǵ�7.5ҳ��ַ 
#define EEP_POWDWENERGY     0x01E0      //���籣���������
//#define EEP_POWDWCURFEE     0x0ED6      //����ʱ����
//#define EEP_POWDWCURTIME    0x0ED7      //����ʱʱ��
//#define EEP_POWDWCFCNT      0x0EDD      //����ʱCF��
//#define EEP_POWDWCFENERGY   0x0EE7      //����ʱCF��Ӧ������
//#define EEP_PRGLEFTTM       0x0EF1      //���ʣ��ʱ��(��ʱʹ��)(����)
//#define EEP_PRODUCELEFTTM   0x0EF3      //����ʱ�䣨��ʱʹ�ã�(����)
//#define EEP_PW2BSTM         0x0EF5      //2���������ʱ��
//#define EEP_PW4BSTM         0x0EF7      //4���������ʱ��
//#define EEP_POWERDWTM       0x0EF9      //ͣ��ʱ��
//#define EEP_ESAMKEYST       0x0C2E      //Esam��Կ״̬



     /*                          

//�����ǵ�3ҳ��ַ
enum  {
 EEP_COMADD =    _Dftset_start_	,//((unsigned short)&FlashInfo.SafeInfo.TRx_Num),  // 0x0080  //ͨѶ��ַ,6Bytes
  EEP_CBR1  =  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[0][0]),  //     //������        0x01
     EEP_CBR2  =  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[1][0]),  //      //������        0x02
     EEP_CBR3=  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[2][0])  //     //������        0x03
    }��
    
    */
#define EEP_METERNO     0x0086  //��� ,6Bytes
#define EEP_645PASSWD1  0x008C  //��0������
#define EEP_645PASSWD2  0x008F  //��1������
#define EEP_645PASSWD3  0x0092  //��2������
#define EEP_645PASSWD4  0x0095  //��3������
#define EEP_645PASSWD5  0x0098  //��4������


//�����ǵ�6ҳ��ַ 
//ʵʱʱ�ӱ���
//#define EEP_DATETIME    0x0180  //��ǰʱ�ӱ���(����)
//#define EEP_AUTOCAL     0x0190  //�Զ�У��ȶ�����




//�����ǵ�59ҳ��ַ 
//#define EEP_POWDWENERGY     0x0EC0      //���籣���������
//#define EEP_POWDWCURFEE     0x0ED6      //����ʱ����
//#define EEP_POWDWCURTIME    0x0ED7      //����ʱʱ��
//#define EEP_POWDWCFCNT      0x0EDD      //����ʱCF��
//#define EEP_POWDWCFENERGY   0x0EE7      //����ʱCF��Ӧ������
//#define EEP_PRGLEFTTM       0x0EF1      //���ʣ��ʱ��(��ʱʹ��)(����)
//#define EEP_PRODUCELEFTTM   0x0EF3      //����ʱ�䣨��ʱʹ�ã�(����)
//#define EEP_PW2BSTM         0x0EF5      //2���������ʱ��
//#define EEP_PW4BSTM         0x0EF7      //4���������ʱ��
//#define EEP_POWERDWTM       0x0EF9      //ͣ��ʱ��




#endif

