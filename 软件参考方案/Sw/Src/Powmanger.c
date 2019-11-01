
#define POWMANGE_EXT

#include "Include.h"

uint8 guc_ChkPowDn;                 // �µ���Ĵ���
/*=========================================================================================\n
* @function_name: PowDownChk
* @function_file: Powmanger.c
* @����:
*
* @����:
* @����:
* @����:   lwb (2012-03-23)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void PowDownChk(void)
{
    if (!(gui_SystemState & flgStSys_PowOff))   // �Ƿ��ڵ���״̬
    {                                           // �е�Ž��к������ж�
        guc_ChkPowDn <<= 1;

        if(!(Systate&BIT0))                      // �ж��Ƿ��ѹ��
        {
            guc_ChkPowDn |=0x1;                 // �ѵ�ǰ��ѹ״̬����Ĵ�����ֻ�������е͵�ƽ�ſ����ж����µ�
        }

        if(0x0f == (guc_ChkPowDn&0x0f))         // ��������4�Σ�Ҳ����8ms�͵�ƽ�������µ��¼�
        {
            gui_SystemEvent |= flgEtGlb_PowDown;
            guc_ChkPowDn =0x0;
        }
    }
}
/*=========================================================================================\n
* @function_name: PowerDnPro
* @function_file: System.c
* @����: ���紦����
*
* @����:
* @����:
* @����:   lwb (2012-01-31)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void PowerDnPro(void)
{
    //�������������E2�д���
    //IO�ڴ���
    uint16 CRC;
    EA=0;                   //���ж�
    PMCtrl4 &=~0x18;                        //�ر�CF 
    IdleIO();
    IntOFF();
    UARTOFF();

    MemCpy(XDATA_RAMZONE,   (uint8*)&gs_EnergyData.uiEP,    4);          //��ǰ��������
    MemCpy(XDATA_RAMZONE+4, (uint8*)&gs_PowerCf.uc_P,       1);         //��ǰCF��
    MemCpy(XDATA_RAMZONE+5, (uint8*)&gs_Energy.ucP,         1);         //��ǰCF���ڵ�����
    MemCpy(XDATA_RAMZONE+6, (uint8*)&gs_FeeData.uc_FeeNo,   1);         //��ǰ����

    CRC=do_CRC(XDATA_RAMZONE, 7);
    MemCpy(XDATA_RAMZONE+7,(uint8*)&CRC,2);
    BE_WriteP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,9);

    //�͹��Ĵ���
//  gs_DispStt.ucIndex=0;
//  gs_DispStt.ucTmr=0;
//  ShowRefresh();
    //�ر���ʾ
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();
    LCD_Off();
    Init_RTC(RTC_DAY);                      //��ʼ��ΪDAY RTC����
    gui_SystemState |= flgStSys_PowOff;

    Sleep();
}





