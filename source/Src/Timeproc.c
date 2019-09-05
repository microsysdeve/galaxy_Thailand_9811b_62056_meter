#define TIMEPROC_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: TimerProc
* @function_file: Timeproc.c
* @����: ʵʱ�ӣ�ÿ�����1�Σ�
*
* @����:
* @����:
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void TimerProc(void)
{
    GetExtRTC();                                                            //���ⲿʱ�Ӵ�ŵ�RAMʱ�ӵ���ʱ����gs_ClkTmp֮��
    if(RTCCheck((uint8*)&gs_ClkTmp) == Const_Data_OK)                       //�ⲿʱ������,BCD���ж�,ʱ��Ϸ����ж��Ƿ���Ч
    {
        MemCpy((void*)&gs_DateTime, (void*)&gs_ClkTmp, 7);
        if (((int16)gs_LastDateTime.ucSecond - gs_DateTime.ucSecond) > 30)
        {
            guc_TimeEvent |= flgEtTim_Minute;                                 //�����¼�
        }

        if (gs_DateTime.ucMinute == 0 && gs_LastDateTime.ucMinute > 0)
        {

            guc_TimeEvent |= flgEtTim_Hour;
        }
                                                                                      
        if (gs_DateTime.ucHour == 0 && gs_LastDateTime.ucHour > 0)          // �ﵽһ��
        {
            guc_TimeEvent |= flgEtTim_Day;
        }

//      if (gs_DateTime.ucDay == 0x01 && gs_LastDateTime.ucDay > 0x01)
//      {
//      }
//
      // ����
        if (gs_DateTime.ucMonth == 0x01 && gs_LastDateTime.ucMonth > 0x01)
        {
            guc_TimeEvent |= flgEtTim_Year;
        }
    }
    else
    {
        SoftClockCheck();               //��ʱ���ж��Ƿ���ȷ
        SetExtRTC();
    }

    ClockBAK_RAM();  
//    uint8 uc_maxday;
//    uint8 uc_SoftTimer;                     // �Ƿ������ʱ�����ݣ�1-�ǣ�0-��
//    uc_SoftTimer = CheckTime();             // �����Ӳʱ��
//
//    if (uc_SoftTimer != 0)                  // ������ʱ������
//    {
//        uint8 ucSec = APIByteBCD2HEX(gs_DateTime.ucSecond);
//        ucSec++;                            //����1��
//        if(ucSec >= 60)
//        {
//            ucSec = 0;
//        }
//        gs_DateTime.ucSecond = APIByteHEX2BCD(ucSec);
//    }
//
//    // �ﵽһ����
//    // ��ǰ���ԭ����С��������30�롣
//    // ��������� 59->0��Ҳ���ܳ�������50->3���������Щ���������Ϊ����
//    if (((int16)gs_LastDateTime.ucSecond - gs_DateTime.ucSecond) > 30)
//    {
//        guc_TimeEvent|=flgEtTim_Minute;
//        //MessageSend(msg_Min);                                                     // ���ͷ���Ϣ
//        if (uc_SoftTimer != 0)                                                  // ������ʱ������
//        {
//            uint8 ucMin = APIByteBCD2HEX(gs_DateTime.ucMinute);
//            ucMin++;                                                            //����1��
//            if(ucMin >= 60)
//            {
//                ucMin = 0;
//            }
//            gs_DateTime.ucMinute = APIByteHEX2BCD(ucMin);
//        }
//
//                                                                                // �ﵽһСʱ
//        if (gs_DateTime.ucMinute == 0 && gs_LastDateTime.ucMinute > 0)
//        {
//
//            guc_TimeEvent|=flgEtTim_Hour;
//            //MessageSend(msg_Hour);                                                // ����Сʱ��Ϣ
//            if (uc_SoftTimer != 0)                                              // ������ʱ������
//            {
//                uint8 ucHour = APIByteBCD2HEX(gs_DateTime.ucHour);
//                ucHour++;                                                       //����1Сʱ
//                if(ucHour >= 24)
//                {
//                    ucHour = 0;
//                }
//                gs_DateTime.ucHour = APIByteHEX2BCD(ucHour);
//            }
//
//                                                                                // �ﵽһ��
//            if (gs_DateTime.ucHour == 0 && gs_LastDateTime.ucHour > 0)
//            {
//
//                guc_TimeEvent|=flgEtTim_Day;
//                //MessageSend(msg_Day);                                             // ���͹�����Ϣ
//                if (uc_SoftTimer != 0)                                          // ������ʱ������
//                {
//                    gs_DateTime.ucWeek ++;                                      // �� +1
//                    if (gs_DateTime.ucWeek >= 0x07)
//                    {
//                        gs_DateTime.ucWeek = 0;
//                    }
//
//                    uc_maxday = MonthDays[gs_DateTime.ucMonth];                 //�����ַ����Ļ�������Ҫ��ΪHEX����
//                    if(gs_DateTime.ucMonth == 0x02)
//                    {
//                        if((APIByteBCD2HEX(gs_DateTime.ucYear) & 0x03) == 0)      // ����
//                        {
//                            uc_maxday++;                                        //������������������1
//                        }
//                    }
//
//                    uint8 ucDay = APIByteBCD2HEX(gs_DateTime.ucDay);
//                    ucDay++;                                                    //����1��
//                    if(ucDay > uc_maxday)
//                    {
//                        ucDay = 1;
//                    }
//                    gs_DateTime.ucDay = APIByteHEX2BCD(ucDay);
//                }
//
//                //gui_DateModifyCount++;  //added by zlq 06.12.28
//                //EnergySaveEvSet(E_SAVE_ZEROEP);
//                // ����
//                if (gs_DateTime.ucDay == 0x01 && gs_LastDateTime.ucDay > 0x01)
//                {
//                    if (uc_SoftTimer != 0)                                      // ������ʱ������
//                    {
//                        uint8 ucMonth = APIByteBCD2HEX(gs_DateTime.ucMonth);
//                        ucMonth++;                                              //����1��
//                        if(ucMonth > 12)
//                        {
//                            ucMonth = 1;
//                        }
//                        gs_DateTime.ucMonth = APIByteHEX2BCD(ucMonth);
//                    }
//
//                    // ����
//                    if (gs_DateTime.ucMonth == 0x01 && gs_LastDateTime.ucMonth > 0x01)
//                    {
//                        uint8 ucYear = APIByteBCD2HEX(gs_DateTime.ucYear);
//                        ucYear++;
//                        if(ucYear > 99)
//                        {
//                            ucYear = 0;
//                        }
//                        gs_DateTime.ucYear = APIByteHEX2BCD(ucYear);
//                    }
//                }
//            }
//        }
//    }
//
//    ClockBAK_RAM();                                                             //����ʱ��
}
/**=============================================================================================\n
 * @function_name: CalcAbsDay
 * @function_file: AP_timeproc.c
 * @����:�������������վ���2000.1.1�յ�����
 *
 *
 * @param:psTm
 *
 * @����: uint16
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
uint16 CalcAbsDay(S_TIMEDATA* psTm)
{//��2000��1��1��Ϊ��׼�����ڵ���������,���ʱ�䲻����2000��֮ǰ(��ʵ2000����00��ʾ,�������϶���ȥ)
    uint8 ucYear = APIByteBCD2HEX(psTm->ucYear);        //��ת����Hex
    uint8 ucMonth = APIByteBCD2HEX(psTm->ucMonth)-1;      //��ת����Hex
    uint8 ucDay = APIByteBCD2HEX(psTm->ucDay) - 1;      //��ת����Hex

    if((ucYear & 0x03) == 0)                            //�ж��Ƿ���������2��
    {
        if(ucMonth >= 2)
            ucDay++;                                    //���ڵ���3�·ݣ�����Ӧ�ü���2��29��һ��
    }
    else
    {
        ucDay++;                                        //���������00�����¶������һ��
    }
    //year >> 2,�Ǽ��Ϲ�ȥ����4��������һ��
    return (ucYear*365 + gui_MonthBeginDay[ucMonth] + (ucDay + (ucYear>>2)));
}
/**=============================================================================================\n
 * @function_name: CalcAbsSecond
 * @function_file: AP_timeproc.c
 * @����:
 *
 *
 * @param:psTm
 *
 * @����: uint32
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
uint32 CalcAbsSecond(S_TIMEDATA* psTm)
{
    //�Ե���00ʱ00��00��Ϊ��׼��
    uint8 ucSec = APIByteBCD2HEX(psTm->ucSecond);       //��ת����Hex
    uint8 ucMin = APIByteBCD2HEX(psTm->ucMinute);       //��ת����Hex
    uint8 ucHour = APIByteBCD2HEX(psTm->ucHour);        //ʱת����Hex

    return (ucSec + ucMin*60 + (uint32)ucHour*HourSecCount);
}
/**=============================================================================================\n
 * @function_name: CalcAbsTime
 * @function_file: AP_timeproc.c
 * @����:��ȡ����ʱ�䣨�����2000��1��1�� 0:00:00 ��ʼ���룩
 *
 *
 * @param:psTm
 *
 * @����: uint32 ��ֵ
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
uint32 CalcAbsTime(S_TIMEDATA* psTm)
{
    return (CalcAbsDay(psTm)*DaySecCount + CalcAbsSecond(psTm));
}
/*=========================================================================================\n
* @function_name: CalcTimeGap
* @function_file: Timeproc.c
* @����: ������Ӳʱ����������
*
*
* @����:
* @param:psTm1
* @param:psTm2
*
* @����:
* @return: uint32
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint32 CalcTimeGap(S_TIMEDATA* psTm1, S_TIMEDATA* psTm2)
{
    int32 lGap;
    lGap = (int32)CalcAbsTime(psTm1) - (int32)CalcAbsTime(psTm2);
    if(lGap < 0)
    {
        lGap = -lGap;
    }
    return ((uint32)lGap);
}

/*=========================================================================================\n
* @function_name: ClockCheck
* @function_file: Timeproc.c
* @����: ���ʱ��CRC�����ݸ�ʽ�Ƿ���ȷ
*
*
* @����:
* @param:psTm
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 ClockCheck(S_TIMEDATA* psTm)
{
    if(do_CRC((uint8*)psTm, sizeof(S_TIMEDATA)-2) == psTm->uiCRC)
    {
        return (RTCCheck((uint8*)psTm));
    }
    return Const_Data_Err;
}
/*=========================================================================================\n
* @function_name: SoftClockCheck
* @function_file: Timeproc.c
* @����: ��ʱ�����ݺ�E2ʱ��������ȷ�Ժ���Ч�Լ���
*
* @����:
*
* @����:
* @return: uint8    SOFT_RTC_MAIN, ��ʱ��ram����������һ����ȷ
*                   SOFT_RTC_E2,   ��ʱ�ӿ�E2���ֵ���������
*                   SOFT_RTC_ERR,  ��ʱ�Ӳ�����E2���ݶ���Ч��
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 SoftClockCheck(void)
{
    uint8   ucSoftRtc = SOFT_RTC_MAIN;                                                //��ǰ��ʱ����Ч

    if(ClockCheck(&gs_DateTime) != Const_Data_OK)
    {                                                                               //��ǰ��ʱ��CRCУ�����
        if(ClockCheck(&gs_LastDateTime) != Const_Data_OK)
        {                                                                           //��ǰ��ʱ�ӱ���CRCУ�����
            //BE_ReadP(EEP_DATETIME,(uint8*)&gs_DateTime, sizeof(S_TIMEDATA));        //��E2�л�ȡʱ������
            FCpyTMem((uint8 *)&gs_DateTime, (uint8 code*)&InitTM, 7);
            gs_DateTime.uiCRC = do_CRC((uint8 *)&gs_DateTime, 7);
//            if(ClockCheck(&gs_DateTime) == Const_Data_OK)                           //���E2����ʱ�ӵ���Ч��
//            {
//                ucSoftRtc = SOFT_RTC_E2;
//            }
//            else                                                                    //��E2ʱ�����ݲ���ȷ
//            {
//            #if (_SW_SE_Type > 0)
//                SE_ReadP(EEP_DATETIME,(uint8*)&gs_DateTime,sizeof(S_TIMEDATA));     //��ȡ����ʱ������
//            #else
//                BE_ReadP(EEP_DATETIME+EEP_BAK_LEN, (uint8*)&gs_DateTime, sizeof(S_TIMEDATA));
//            #endif
//                if(ClockCheck(&gs_DateTime) == Const_Data_OK)
//                {
//                    ucSoftRtc = SOFT_RTC_E2;
//                }
//                else
//                {
//                    ucSoftRtc = SOFT_RTC_ERR;
//                }
//            }
        }
        else
        {
            MemCpy((uint8*)(&gs_DateTime), (uint8*)(&gs_LastDateTime), sizeof(S_TIMEDATA)); //��RAM���ݻָ�
        }
    }
    return ucSoftRtc;
}
/*=========================================================================================\n
* @function_name: CheckTime
* @function_file: Timeproc.c
* @����: ��ȡʵʱ��
*
* @����:
*
* @����:
* @return: uint8 0-����Ӳʱ�ӣ�1-������ʱ��
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 CheckTime(void)
{
//#ifndef _SW_EXT_RTC
//    SoftClockCheck();
//#else
//    uint8   ucSoftRtc = SoftClockCheck();
//    uint8   ucExtRtc = EXT_RTC_NO_WORK;
//    if(gs_DateTime.ucSecond == 0x33)                                        //�е�ʱÿ����33sʱ���ⲿrtc����,ͣ��ʱÿСʱ27min��33s����
//    {
//        if(_SYS_IS_PWR_OFF)
//        {
//            if(gs_DateTime.ucMinute == 0x27)                                //ͣ��ʱÿСʱ27min��33s����
//            {
//                ucExtRtc = EXT_RTC_WORK;
//            }
//        }
//        else
//        {
//            ucExtRtc = EXT_RTC_WORK;
//        }
//    }
//
//    if((ucExtRtc == EXT_RTC_NO_WORK) && (ucSoftRtc == SOFT_RTC_MAIN))       //��ʱ����ȷ��û�е���Ӳʱ�ӱȶ���ֱ�ӷ���
//    {
//        gut_SysWarn.SysWarn.TimeError=false;
//        return 1;                                                           //������ʱ��
//    }
//
//    GetExtRTC();                                                            //���ⲿʱ�Ӵ�ŵ�RAMʱ�ӵ���ʱ����gs_ClkTmp֮��
//    if(RTCCheck((uint8*)&gs_ClkTmp) == Const_Data_OK)                       //�ⲿʱ������,BCD���ж�,ʱ��Ϸ����ж��Ƿ���Ч
//    {
//        if(ucSoftRtc != SOFT_RTC_ERR)                                       //�жϵ�ǰ��ʱ���Ƿ���Ч
//        {
//            if(CalcTimeGap(&gs_ClkTmp, &gs_DateTime) > MAX_CLOCK_BAK_GAP)   //����Ӳʱ�����5S����ʱ��������ʱ��
//            {
//                ucExtRtc = EXT_RTC_INVALID;                                 //���������������ʱ��
//            }
//            else
//            {
//                ucExtRtc = EXT_RTC_VALID;                                   //�����ⲿʱ��
//            }
//        }
//        else
//        {
//            ucExtRtc = EXT_RTC_VALID;                                         //��ʱ��������Ч������Ӳʱ��
//        }
//        gs_SysRunSt.TimeFR=false;
//    }
//    else
//    {                                                                       //�ⲿʱ������
//        if(ucSoftRtc != SOFT_RTC_ERR)                                       //����ʱ�����ݺϷ�
//        {
//            ucExtRtc = EXT_RTC_INVALID;                                     //������ʱ�Ӹ���Ӳʱ��
//            gs_SysRunSt.TimeFR=false;
//        }
//        else 
//        {
//            if(gs_SysRunSt.TimeFR==false);
//            {
////      #ifdef FRCom
////            EVENTOUTHIGH();
////      #endif
//              gs_SysRunSt.TimeFR=true;
////            gs_FREventOut.FREventOutStruct.TimeFR=true;
//            }
//            gut_SysWarn.SysWarn.TimeError=true;
//        }
//        //������һ��elseû���ж�������ǡ����ʹucSoftRtc��ΪTIMERPROC_HARD
//    }
//
//    if(ucExtRtc == EXT_RTC_INVALID)                                         //Ӳʱ��������Чʱ
//    {                                                                       //����ʱ�Ӹ���Ӳʱ��
//        SetExtRTC();
//        guc_ExtRtcErrCnt++;
//    }
//    else
//    {                                                                       //Ӳʱ�Ӹ����ڲ���ʱ��
//        MemCpy((void*)&gs_DateTime, (void*)&gs_ClkTmp, 7);
//        gs_DateTime.uiCRC = do_CRC((uint8*)(&gs_DateTime), sizeof(S_TIMEDATA) - 2);     //�ȶ���ʱ����crcУ��
//        if(gs_DateTime.ucMinute==0x00)                                              //ÿ��Сʱдһ��
//        {
//            ClockBAK_E2();                                                      
//        }
//        return 0;
//    }
//#endif
    return 1;
}
/*==============================================================================
Function: CalcWeek
;����: �����㷨:2000Ϊ��׼��+��+��+������+�������꣬1��2��+1��-1 ��7
;��ڣ�year/month/day ��ǰ��������
;���أ���Ӧ���ܣ�0-6�ֱ��Ӧ����-������
;�㷨ԭ��˵��:һ��Ϊ365��,365%7=1,ǡ��ÿһ���һ��,��˴�00�꿪ʼ����ÿ���һ��,
;00����Ϊ����,��Ҫ������,ͬʱ��Ϊ��ͷ�������,������Ӧ�ü��˰�,�Ǻ�
==============================================================================*/
/**=============================================================================================\n
 * @function_name: CalcWeek
 * @function_file: AP_timeproc.c
 * @����:��������,����ʱ�ӵ�ʱ�����
 *
 *
 * @param:ucYear
 * @param:ucMonth
 * @param:ucDay
 *
 * @����: uint8
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
uint8 CalcWeek(uint8 ucYear, uint8 ucMonth, uint8 ucDay)
{
    uint8 ucWeek;
    ucMonth = APIByteBCD2HEX(ucMonth);
    ucWeek = Tab_Week_2K[ucMonth];

    ucYear = APIByteBCD2HEX(ucYear);
    if((ucYear & 0x03) != 0 && ucMonth <= 0x02) // ������ǰ2��
    {
        ucWeek++;
    }

    ucWeek += ucYear;
    ucWeek += (ucYear >> 2); //����

    ucWeek += APIByteBCD2HEX(ucDay);

    ucWeek --;
    ucWeek %= 7;

    return ucWeek;
}

/*=========================================================================================\n
* @function_name: GetSysClock
* @function_file: Timeproc.c
* @����: 1.��ȡϵͳʱ��,�����������ram�е�ֵ,���Ҫ��ȡ�ⲿʱ��,�����������Ľӿ���������
*
*
* @����:
* @param:pucBuf  ���Զ�ȡ������ָ��
* @param:ucType  ָ����ȡ�ļ�������,�������з�ʽ�ο�ucType�Ķ���
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void GetSysClock(uint8* pucBuf, uint8 ucType)
{
    switch(ucType)
    {
    case Const_YYMMDDWW:
        *(pucBuf++) = gs_DateTime.ucWeek;
        //ע��,���ﲻ��Ҫbreak
    case Const_YYMMDD:
        *(pucBuf++) = gs_DateTime.ucDay;
        *(pucBuf++) = gs_DateTime.ucMonth;
        *(pucBuf++) = gs_DateTime.ucYear;
        break;
    case Const_hhmmss:
        *(pucBuf++) = gs_DateTime.ucSecond;
        *(pucBuf++) = gs_DateTime.ucMinute;
        *(pucBuf++) = gs_DateTime.ucHour;
        break;
    case Const_YYMMDDhhmmss:
        *(pucBuf++) = gs_DateTime.ucSecond;
    case Const_YYMMDDhhmm:
        *(pucBuf++) = gs_DateTime.ucMinute;
        *(pucBuf++) = gs_DateTime.ucHour;
        *(pucBuf++) = gs_DateTime.ucDay;
        *(pucBuf++) = gs_DateTime.ucMonth;
        *(pucBuf++) = gs_DateTime.ucYear;
        break;
    case Const_hhmmssYYMMDDWW:
        *(pucBuf++) = gs_DateTime.ucSecond;
        *(pucBuf++) = gs_DateTime.ucMinute;
        *(pucBuf++) = gs_DateTime.ucHour;
        *(pucBuf++) = gs_DateTime.ucWeek;
        *(pucBuf++) = gs_DateTime.ucDay;
        *(pucBuf++) = gs_DateTime.ucMonth;
        *(pucBuf++) = gs_DateTime.ucYear;
        break;
    default:
        break;
    }
}
/**=============================================================================================\n
 * @function_name: SetSysClock
 * @function_file: AP_timeproc.c
 * @����:����ϵͳʱ��,�����������ram�е�ֵ,���Ҫ�����ⲿʱ��,�����������Ľӿ���������
 *
 *
 * @param:pucBuf  �������õ�����ָ��
 * @param:ucType  ָ�������ļ�������,�������з�ʽ�ο�ucType�Ķ���
 * @����: lwb  (2010-2-5)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-5)\n
 ================================================================================================*/
void SetSysClock(uint8* pucBuf, uint8 ucType)
{
    switch(ucType)
    {
    case Const_YYMMDDWW:
        gs_DateTime.ucWeek = *(pucBuf++);
        //ע��,���ﲻ��Ҫbreak
    case Const_YYMMDD:
        gs_DateTime.ucDay = *(pucBuf++);
        gs_DateTime.ucMonth = *(pucBuf++);
        gs_DateTime.ucYear = *(pucBuf++);
        gs_DateTime.ucWeek = CalcWeek(gs_DateTime.ucYear,gs_DateTime.ucMonth,gs_DateTime.ucDay);
        break;
    case Const_hhmmss:
        gs_DateTime.ucSecond = *(pucBuf++);
        gs_DateTime.ucMinute = *(pucBuf++);
        gs_DateTime.ucHour = *(pucBuf++);
        break;
    case Const_YYMMDDhhmmss:
        gs_DateTime.ucSecond = *(pucBuf++);
    case Const_YYMMDDhhmm:
        gs_DateTime.ucMinute = *(pucBuf++);
        gs_DateTime.ucHour = *(pucBuf++);
        gs_DateTime.ucDay = *(pucBuf++);
        gs_DateTime.ucMonth = *(pucBuf++);
        gs_DateTime.ucYear = *(pucBuf++);
        gs_DateTime.ucWeek = CalcWeek(gs_DateTime.ucYear,gs_DateTime.ucMonth,gs_DateTime.ucDay);
        break;
    case Const_hhmmssYYMMDDWW:
        gs_DateTime.ucSecond = *(pucBuf++);
        gs_DateTime.ucMinute = *(pucBuf++);
        gs_DateTime.ucHour = *(pucBuf++);
        gs_DateTime.ucWeek = *(pucBuf++);
        gs_DateTime.ucDay = *(pucBuf++);
        gs_DateTime.ucMonth = *(pucBuf++);
        gs_DateTime.ucYear = *(pucBuf++);
        gs_DateTime.ucWeek = CalcWeek(gs_DateTime.ucYear,gs_DateTime.ucMonth,gs_DateTime.ucDay);
        break;
    default:
        break;
    }
    ClockBAK_All();                             //����ram��Ӳʱ�Ӻ�E2ʱ��
}
/**=============================================================================================\n
 * @function_name: GetYYMMDDhhmm
 * @function_file: AP_timeproc.c
 * @����:��ȡ������ʱ��
 *
 *
 * @param:pucBuf
 * @����: lwb  (2010-2-5)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-5)\n
 ================================================================================================*/
void GetYYMMDDhhmm(uint8* pucBuf)
{
    GetSysClock(pucBuf, Const_YYMMDDhhmm);
}
/*=========================================================================================\n
* @function_name: RTCCheck
* @function_file: Timeproc.c
* @����: �������ʱ�������Ƿ���ϸ�ʽ
*
*
* @����:
* @param:pucClk
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 RTCCheck(uint8* pucClk)
{
    if(DataCheck(7, pucClk, (S_DATACHK code *)&gCs_ClkChkTab) == Const_Data_OK)   //ʱ�����ݼ����ж�
    {
        return JudgeIsNum(pucClk, 7);                                       //ʱ������BCD���ж�
    }
    return Const_Data_Err;
}
/**=============================================================================================\n
 * @function_name: ClockBAK_RAM
 * @function_file: AP_timeproc.c
 * @����:����RAMʱ��
 *
 * @����: lwb  (2010-2-5)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-5)\n
 ================================================================================================*/
void ClockBAK_RAM(void)
{
    gs_DateTime.uiCRC = do_CRC((uint8*)(&gs_DateTime), sizeof(S_TIMEDATA) - 2);     //�ȶ���ʱ����crcУ��
    MemCpy((uint8*)(&gs_LastDateTime), (uint8*)(&gs_DateTime), sizeof(S_TIMEDATA)); //����Ϊ��һ������
}
/**=============================================================================================\n
 * @function_name: ClockBAK_E2
 * @function_file: AP_timeproc.c
 * @����:����ʱ������
 *
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
void ClockBAK_E2(void)
{
//    BE_WriteP(EEP_DATETIME,(uint8*)&gs_DateTime,sizeof(S_TIMEDATA));            //д��E2ʱ��
//#if (_SW_SE_Type > 0)
//    SE_WriteP(EEP_DATETIME,(uint8*)&gs_DateTime,sizeof(S_TIMEDATA));            //д����E2ʱ��
//#else
//    BE_WriteP(EEP_DATETIME+EEP_BAK_LEN, (uint8*)&gs_DateTime, sizeof(S_TIMEDATA));
//#endif
}
/**=============================================================================================\n
 * @function_name: ClockBAK_All
 * @function_file: AP_timeproc.c
 * @����:����ʱ�� RAM��E2
 *
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
void ClockBAK_All(void)
{//ע�����������������õ��Ⱥ��ϵ
    ClockBAK_RAM();                     //�ȱ���RAMʱ��
    SetExtRTC();                        //����Ӳʱ��
    //ClockBAK_E2();                      //�ڱ���E2ʱ��
}
/**=============================================================================================\n
 * @function_name: YearMonthDayCheck
 * @function_file: AP_timeproc.c
 * @����: ���������  ����Ĳ���ΪBCD��ʽ,����1��ȷ,0����
 *        ���������Ƿ�BCD���ж�
 *
 * @param:ucYear
 * @param:ucMonth
 * @param:ucDay
 *
 * @����: uint8
 * @����: lwb  (2010-2-4)\n
 *------------------------------------------------------------------------------------------------
 * @�޸���: lwb (2010-2-4)\n
 ================================================================================================*/
uint8 YearMonthDayCheck(uint8 ucYear, uint8 ucMonth, uint8 ucDay)
{
    uint8 ucMaxDay = MonthDays[ucMonth];

    ucYear = APIByteBCD2HEX(ucYear);
    ucMonth = APIByteBCD2HEX(ucMonth);
    ucDay = APIByteBCD2HEX(ucDay);

    if((ucMonth == 2) && ((ucYear & 0x03) == 0))
    {//����ͬʱ��2�·�
        ucMaxDay++;
    }
    if((ucDay == 0) || (ucDay > ucMaxDay))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*=========================================================================================\n
* @function_name: ValidTime
* @function_file: Timeproc.c
* @����: �ж��Ƿ��ǺϷ���ʱ������
*
*
* @����:
* @param:time
* @param:type  0: �������  1�����ʱ�� 2��������ں�ʱ�� 3: ������ں�ʱ��(���ݴ�����)
*
* @����:
* @return: uint8
* @����:   lwb (2012-03-01)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 ValidTime(uint8* time, uint8 type)
{
    uint8 offset;
    uint8 data1, day;
    uint8 uc_Cklen;
    offset=0;

    if(type==0)
    {
        uc_Cklen=3;
    }else if(type==1)
    {
        uc_Cklen=3;
    }else if(type==2)
    {
        uc_Cklen=6;
    }else
    {
        uc_Cklen=7;
    }

    if(JudgeIsNum(time,uc_Cklen)!=Const_Data_OK)
    {
        return Ret_Err;
    }

    if(type==1|| type == 2|| type==3)
    {
        // �� �� ʱ
        //data1 = APIByteBCD2HEX(time[0]);        // ��
        if(time[0] >= 0x60)
        {                                           //���ʱ���Ƿ���ȷ
            return Ret_Err;
        }

        //data1 = APIByteBCD2HEX(time[1]);        //��
        if(time[1] >= 0x60)
        {
            return Ret_Err;
        }

        //data1 = APIByteBCD2HEX(time[2]);        //ʱ
        if(time[2] >= 0x24)
        {
            return Ret_Err;
        }
    }


    if(type == 0 || type == 2 || type == 3)
    {
        if(type==3)
        {
            offset=4;
        }
        else if(type == 2)
        {
            offset=3;
        }else
        {
            offset=0;
        }
        //�� �� ��

        //data1 = APIByteBCD2HEX(time[1+offset]);        //����·��Ƿ���ȷ
        if(/*(time[1+offset] == 0x00) ||*/ (time[1+offset] > 0x12))
        {
            return Ret_Err;
        }

        data1 = MonthDays[time[1+offset]];             //���ȸ�������������Ƿ���ȷ
        day = APIByteBCD2HEX(time[0+offset]);          //��

        if((time[1+offset]== 2) && ((APIByteBCD2HEX(time[2+offset]) & 0x03) == 0))
        {                                           //����ͬʱ��2�·�
            data1++;
        }

        if(/*(day == 0) || */(day > data1))
        {
            return Ret_Err;
        }
    } 
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: SleepTimeProc
* @function_file: Timeproc.c
* @����: ������ʱ
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void SleepTimeProc(void)
{
//    GetExtRTC();
//    if(RTCCheck((uint8*)&gs_ClkTmp) != Const_Data_OK)                               //�ж�RTCʱ���Ƿ���ȷ
//    {
//        //����ʱ�Ӵ����־λ���ṩ�ϵ紦������
//        guc_ClockErr=CLOCKERR;    
//        if(RTCCheck((uint8*)&gs_DateTime) != Const_Data_OK)                         //����ȷ�Ļ����ж�RAMʱ���Ƿ���ȷ
//        {
//            BE_ReadP(EEP_DATETIME,(uint8*)&gs_DateTime, sizeof(S_TIMEDATA));        //��E2�л�ȡʱ������
//        }
//
//        if(RTCCheck((uint8*)&gs_DateTime) == Const_Data_OK)                         //�ж��µ�RAMʱ���Ƿ���ȷ,��ȷ�������ⲿʱ��
//        {
//            SetExtRTC();
//        }
//    }else                                                                           //��ȷ������RTCʱ�ӵ�RAMʱ��
//    {
//        MemCpy((uint8*)(&gs_DateTime), (uint8*)(&gs_ClkTmp), sizeof(S_TIMEDATA));
//    }
//
//    ClockBAK_RAM();                                                             //����ʱ��
}
