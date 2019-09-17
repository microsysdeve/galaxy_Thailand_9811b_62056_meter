#define INIT_EXT
#include"Include.h"


enum   ENUMDEF 
{
       _VolK_      =    0x5F6290b2,
      _Curr_L_K_     =    0x389d9999,
       _Curr_N_K_     =  0x389d9999,
         _PowerL_K_      =            0x84f431,
         _PowerN_K_       =           0x84f431,//803d04,
         _PluseConst_ =1200,
         _StandVol_= 230,
         _Ib_= 5,
         _HFCONST_L_ =0x17c6254,//0x1d5584a ,
         _HFCONST_N_ =0x17c6254,//0x1d5584a ,
         _HFCONST800K_ =0x2336761b ,
         _QDConst_L_= 0xfec164,
         _QDConst_N_= 0xfec164,
};

#define      _format4(n)      (n&0xff),((n>>8)&0xff),((n>>16)&0xff),((n>>24)&0xff)
#define      _format2(n)      (n&0xff),((n>>8)&0xff)


const uint8 code InitPara0[sizeof(S_JBPM)-2]=
{
    _format2(1200),//0xb0,0x04,     //���� 1200
    _format2( _StandVol_*100),//0xd8,0x59,     //��Ƶ�ѹ 240.00
    _format2( _Ib_ *1000) ,// 0x88,0x13,     //��Ƶ��� 5.000
    _format4(_HFCONST_L_),//0x4a,0x58,0xd5,0x01,//�й�������������ֵ
    _format4(_HFCONST800K_),//0x1B,0x76,0x36,0x23,//800K������������
    
    _format4(_QDConst_L_),//0x00,0x1B,0xB7,0x00,//�й�����Ǳ������ֵ
    _format4(_HFCONST_N_),//0x4a,0x58,0xd5,0x01,//I2��������
    0x00,0x00,0x00,0x00,//�й��Ȳ�ֵ
    0x00,0x00,0x00,0x00,//�޹��Ȳ�ֵ
     _format4(0x03130463),//   0x00,0x00,0x00,0x00,//��ѹ��Чֵ�Ȳ�
    0x00,0x00,0x00,0x00,//ͨ��I1������Чֵ�Ȳ�  
    0x00,0x00,0x00,0x00,//ͨ��I2������Чֵ�Ȳ�  
    0x00,0x00,0x00,0x00,//�й����ʶ��β���ֵ
    0x00,0x00,0x00,0x00,//�޹����ʶ��β���ֵ
    0x00,               //ͨ��I1�ǲ�У��ֵ
    0x00,               //ͨ��I2�ǲ�У��ֵ
    _format4(_PowerL_K_),// 0x45,0x0c,0xa4,0x00,//����1��ʾ����ϵ��k
    _format4(_PowerN_K_),// 0x45,0x0c,0xa4,0x00,//����2��ʾ����ϵ��k
    _format4(_VolK_) ,//     0x85,0xA3,0xB3,0x65,//��ѹ��ʾ����ϵ��k
    _format4(_Curr_L_K_) ,//����I1��ʾ����ϵ��k
    _format4(_Curr_N_K_) ,//����I2��ʾ����ϵ��k ��I1������ϵ
    0x00,0x00,0x00,0x00,//ͨ��I1_800K������Чֵ�Ȳ�0xC29AAE81
    0x00,0x00,0x00,0x00,//ͨ��I2_800K������Чֵ�Ȳ�0xBE7E151F 0xBE85787B
    (((0) << 6)| ((2)<<3) | ((2)<<0)),// 0x0C,               //ͨ������
    //CRC
};

 
const uint8 code InitPara1[]=
{
    0x11,0x11,0x11,0x11,0x11,0x11,  //ͨѶ��ַ
    0x04,               //ͨ�ſ����� ����1200
    0x05,               //�Զ�ѭ����ʾ����
    0x05,               //������ʾʱ��
    0x02,               //��ʾ����С��λ��
    0x04,               //��ʾ����С��λ��
    0x05,               //����ѭ����ʾ����
    0x1a,               //������ʾ��λ��
    0x3c,               //�е��¼�����ʾʱ��(����)
    0x1E,               //ͣ���¼�����ʾʱ��(����)
    0x00,0x00,          //ͣ����ʾʱ��(����)
    0x05,               //�ϵ�ȫ��ʱ�䣨������
    0x05,               //�ϵ翪����ʱ��(����)
    0x14,               //���ⴥ������ʱ��(����)
    0x3C,               //������������ʱ��(����)
    0x05,               //ESAM��������ʾʱ�䣨������ʱ�䣩(����)
    0x02,               //��բ���Լ�ʱ��(����)
    0x50,//CF���������������
    0x00,//�����ղ��������������
    0x00,//���Ჹ�������������
    0x00,0x00,//����ȼ���Ч�����������
    0x00,//ʱ����ʱ���л�ʱ�������жϷ�ʽ��������
    0x02,//������ʾ��ʽ���������������
    0x00,//ʱ����ʾ��ʽ���������������
    0x00,//ͣ����ʾģʽ���������������
    0x00,//�̵�����ⷽʽ���������������
    0x00,//������������������
    0x00,0x00,0x00,0x00,//������������ֵ��������
};

const uint8 code InitPara2[]=
{
    0x00,0x00,0x00,0x00,0x00,       //����1  ��ǰ�ܵ���
    0x00,0x01,0x01,0x02,0x00,       //��ѹ
    0x00,0x01,0x02,0x02,0x00,       //����
    0x01,0x00,0x80,0x02,0x00,       //���ߵ���
//    0x01,0x01,0x00,0x04,0x00,       //����2  ����
//    0x02,0x01,0x00,0x04,0x00,       //����3  ʱ��
//    0x02,0x04,0x00,0x04,0x01,       //����4  ��ŵ�8λ
//    0x02,0x04,0x00,0x04,0x00,       //����5  ��Ÿ�4λ
//    0x01,0x00,0x00,0x00,0x00,       //ѭ��6  �����ܵ���
};

//const uint8 code InitPara3[]=
//{
//    0x00,0x00,0x00,0x00,0x00,       //�ܵ���
//    0x00,0x00,0x01,0x01,0x00,       //�������
//    0x00,0x01,0x01,0x02,0x00,       //��ѹ
//    0x00,0x01,0x02,0x02,0x00,       //����   
//};
const uint8 code InitADK[]=
{
    0x11,0x11,0x11,0x11,0x11,0x11,  //ͨѶ��ַ
    0x01,0x00,0x00,0x00,0x00,0x00,  //���
        
    0x11,0x11,0x11,     //��0������
    0x11,0x11,0x11,     //��1������
    0x00,0x00,0x00,     //��2������
    0x00,0x00,0x00,     //��3������  ����
    0x00,0x00,0x00,     //��4������
        
    0,0,'V','0','3','2',    //���ѹ
    0,0,0,'A','0','1',        //�����
    0,0,0,'A','0','6',      //������
    0x00,0x16,0x00,         //���峣��
};

const uint8 code InitFwVer[]=
{
    //RDKWMNW60V1.0
 //RDKDDS155-9821YWG.1
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    '2','.','V','X','S','-','1', 
    '2','8','9','V','-','5',
    '5','1','S','D','D',
    //��������汾��
};


const uint8 code InitHwVer[]=
{
    //V9811-M-YWGV1.0
   //DDS155-9821
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
    'X','S','-','1',
    '2','8','9','V','-','5',
    '5','1','S','D','D',   
       //����Ӳ���汾��
};

typedef struct 
{
    const uint8 code* E2ParaTabAdrr;   //E2��������ַ
    uint16 E2Adrr;          //E2��ַ
    uint8  uclen;           //���ݳ���
}GS_E2PARA;

const  GS_E2PARA code PageCRCAddr[]=
{
    {InitPara0,     EEP_JBTOTAL,    sizeof(InitPara0),  },
    {InitADK,       EEP_COMADD,     sizeof(InitADK)-21, },   
//    {InitPara2,     EEP_LXTABLE,    sizeof(InitPara2),  },
    //{InitPara3,     EEP_JXTABLE,    sizeof(InitPara3),  },
};

/*=========================================================================================\n
* @function_name: InitE2Data
* @function_file: InitPara.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-04)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void InitE2Data(void)
{
    Word16 CRC;
    ClRCRCWord(guc_InitWd);
    //У����������ж�,�����ж�E2�е�CRC�Ƿ���ȷ�������ȷ������Ҫ��ʼ��
    BE_ReadP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));
    if(Uint8_To_Uint16(XDATA_RAMZONE+sizeof(S_JBPM)-2) != do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2))
    {
        CLRWDT();               //ι��
        FCpyTMem(XDATA_RAMZONE, InitPara0, sizeof(S_JBPM)-2);                   //����Flash���ݵ�RAM��
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //����CRC��RAM��
        BE_WriteP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));                    //д�뵽E2��
    }
    
    for(uint8 i=1;i<sizeof(PageCRCAddr)/sizeof(GS_E2PARA);i++)
    {
        CLRWDT();                           //ι��
        MemSet(XDATA_RAMZONE,0x00,64);
        FCpyTMem(XDATA_RAMZONE,PageCRCAddr[i].E2ParaTabAdrr,PageCRCAddr[i].uclen);//����Flash���ݵ�RAM��
        CRC.word=do_CRC(XDATA_RAMZONE,62);
        XDATA_RAMZONE[62]=CRC.byte[0];
        XDATA_RAMZONE[63]=CRC.byte[1];                          //����CRC��RAM��
        BE_WriteP(PageCRCAddr[i].E2Adrr,XDATA_RAMZONE,64);      //д�뵽E2��
    }    
    
    SetCRCWord(guc_ClearWd);
    Data_ClearMeter();                                          //�������
    gui_RefreshEvent|=(flgEtPara_EnyBottom+flgEtPara_Config+flgEtPara_Show);
}
/*=========================================================================================\n
* @function_name: InitE2Data
* @function_file: InitPara.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-04)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void E2DataChk(void)
{
    Word16 CRC;
    
    //У����������ж�,�����ж�E2�е�CRC�Ƿ���ȷ�������ȷ������Ҫ��ʼ��
    BE_ReadP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));
    if(Uint8_To_Uint16(XDATA_RAMZONE+sizeof(S_JBPM)-2) != do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2))
    {
        CLRWDT();               //ι��
        FCpyTMem(XDATA_RAMZONE, InitPara0, sizeof(S_JBPM)-2);                   //����Flash���ݵ�RAM��
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //����CRC��RAM��
        BE_WriteP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));                    //д�뵽E2��
//        for(uint8 i=1;i<sizeof(PageCRCAddr)/sizeof(GS_E2PARA);i++)
//        {
//            CLRWDT();                           //ι��
//            MemSet(XDATA_RAMZONE,0x00,64);
//            FCpyTMem(XDATA_RAMZONE,PageCRCAddr[i].E2ParaTabAdrr,PageCRCAddr[i].uclen);//����Flash���ݵ�RAM��
//            CRC.word=do_CRC(XDATA_RAMZONE,62);
//            XDATA_RAMZONE[62]=CRC.byte[0];
//            XDATA_RAMZONE[63]=CRC.byte[1];                          //����CRC��RAM��
//            BE_WriteP(PageCRCAddr[i].E2Adrr,XDATA_RAMZONE,64);      //д�뵽E2��
//        }
    }      
    CLRWDT();
//    gui_RefreshEvent|=(flgEtPara_Config+flgEtPara_Show);
}