#define KEY_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: KeyInit
* @function_file: Key.c
* @����: ������ʼ��
*
* @����:
* @����:
* @����:   lwb (2012-03-20)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void KeyInit(void)
{
    KeyPortIn();                                        // �����˿����ó�����ģʽ
    if(_SYS_IS_PWR_OFF)
    {
        for(uint8 i=0;i<KeyNums;i++)
        {
            gs_KeyCtr[i].KeyThd=1;
            gs_KeyCtr[i].LgKeyThd=12;
        }
    }else
    {
        for(uint8 i=0;i<KeyNums;i++)
        {
            gs_KeyCtr[i].KeyThd=1;
            gs_KeyCtr[i].LgKeyThd=12;
        }
    }
}
/*=========================================================================================\n
* @function_name: KeyScan
* @function_file: Key.c
* @����: ����ɨ��
*
* @����:
* @����:
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void KeyScan(void)
{
    if(KeyStUp())                                   //�Ϸ�����ʱ����
    {
        if((gs_KeyCtr[UpKey].DlyCnt>=gs_KeyCtr[UpKey].KeyThd)&&
           gs_KeyCtr[UpKey].Status==KeyRls)
        {
//          OpenBeiGuang();
//          guc_DyBgLed = gs_DispCont.ucKeyBgTm;     // ���ñ�����ʱʱ��
            guc_KeyEvent|=flgEtKey_Up;              // ���Ϸ������
            gs_KeyCtr[UpKey].Status=KeyDw;          //�Ϸ���Ϊ����״̬
        }
        if( gs_KeyCtr[UpKey].Status !=KeyDWLong)
        {
            gs_KeyCtr[UpKey].DlyCnt++;              //��ʱ��������1
        }
        if((gs_KeyCtr[UpKey].DlyCnt>=gs_KeyCtr[UpKey].LgKeyThd)&&
                 (gs_KeyCtr[UpKey].Status==KeyDw))
        {                                           //�����״̬Ϊ���£�������ʱ��������2sΪ����
            gs_KeyCtr[UpKey].Status=KeyDWLong;      //����״̬Ϊ����
            //LongKeyProc();                          //����������
        }
    }
    else
    {
        gs_KeyCtr[UpKey].DlyCnt=0;                  //��ʱ��������
        gs_KeyCtr[UpKey].Status=KeyRls;             //����Ϊ�ͷ�
    }

    if(KeyStPr())                                   //�Ϸ�����ʱ����
    {
        if((gs_KeyCtr[PrKey].DlyCnt>=gs_KeyCtr[PrKey].KeyThd)&&
           gs_KeyCtr[PrKey].Status==KeyRls)
        {
            guc_KeyEvent|=flgEtKey_Pr;              // ���Ϸ������
            gs_KeyCtr[PrKey].Status=KeyDw;          //�Ϸ���Ϊ����״̬
        }

        if( gs_KeyCtr[PrKey].Status !=KeyDw)
        {
            gs_KeyCtr[PrKey].DlyCnt++;              //��ʱ��������1
        }
    }
    else
    {
        gs_KeyCtr[PrKey].DlyCnt=0;                  //��ʱ��������
        gs_KeyCtr[PrKey].Status=KeyRls;             //����Ϊ�ͷ�
    }
}

/*=========================================================================================\n
* @function_name: KeyProc
* @function_file: Key.c
* @����: ����������
* 
* @����: 
* @����: 
* @����:   lwb (2012-02-27)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void KeyProc(void)
{
    if(guc_KeyEvent & flgEtKey_Up)
    {
        ShowKeyProc();
        guc_KeyEvent &=~ flgEtKey_Up;               // �����־
    }else if(guc_KeyEvent & flgEtKey_Pr)                  // ���״̬����
    {                                               //
        if(gui_SystemState & flgStSys_Program)      // �����б��Ƿ��ڱ��״̬
        {
//          guc_PrKeyNewDown=0;
            gui_SystemState &= ~flgStSys_Program;   // �Ѿ����ڱ��״̬���������־
//          gui_DyPgmOut = 0x00;                     // ��̳�ʱ�˳�ʱ������
//          gs_MeterState.ui_MeterState3.RunCode3Word.Program=false;
        }                                           //
        else                                        //
        {                                           //
            gui_SystemState |= flgStSys_Program;    // ���ñ��״̬��־
//          guc_PrKeyNewDown=0x55;
//          BE_ReadP(EEP_PROTIME,(uint8*)&gui_DyPgmOut,0x02);       // ��̳�ʱ�˳�ʱ������
//          if(gui_DyPgmOut==0xffff)                                // ���E2û�г�ʼ���Ļ���Ĭ��Ϊ240����
//          {
                gui_DyPgmOut=20;
//          }
//          gs_MeterState.ui_MeterState3.RunCode3Word.Program=true;
        }                                           //
        guc_KeyEvent &= ~flgEtKey_Pr;               //
//        BE_WriteP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);    //д����ʣ��ʱ��
    }                                               //
    else                                            //
    {                                               //
        guc_KeyEvent =0x0;                          //  ��ֹ����λ����������Ƶ��������¼�
    }                                               //
}

