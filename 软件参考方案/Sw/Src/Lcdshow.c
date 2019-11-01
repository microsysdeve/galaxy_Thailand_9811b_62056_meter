
#define AP_LCDSHOW_EXT
#define APLCDSHOW
#include "Include.h"

/*=========================================================================================\n
* @function_name: ShowMask
* @function_file: Lcdshow.c
* @描述: 显示保护，屏蔽其他不显示
* 
* @作者: lwb (2014/3/25)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void ShowMask(void)
{
    LCDM0=0x00;
    LCDM1&=0xfe;
    LCDM2&=0xfe;
    LCDM3&=0xfe;
    LCDM4&=0xfe;
//    LCDM5&=0xfe;
//    LCDM6&=0xfe;
//    LCDM7&=0xfe;
//    LCDM8&=0xfe; 
    LCDM9=0x00;
    LCDM10=0x00;

}

/*=========================================================================================\n
* @function_name: ShowSecondProc
* @function_file: Lcdshow.c
* @描述:一秒钟调用一次,分系统掉电N天以后、系统掉电N天之内、系统有电三种情况处理,它们之间的关系是互斥的
*       这里的状态切换中有一个问题,就是当在凌晨x时到y时之间如果按键的话,当按键退出时,会进入到轮显状态或
*       停显状态,但是最多过1min就会又进入关闭显示状态.
* @参数:
* @返回:
* @作者:   lwb (2012-03-23)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowSecondProc(void)
{

    //通讯保护
    if(gs_PtlCrt.uc_ComStep!=Com_HD)
    {
        if(gs_PtlCrt.uc_TimeOut > 0)
        {
            gs_PtlCrt.uc_TimeOut--;
            if(gs_PtlCrt.uc_TimeOut==0)
            {
                gs_PtlCrt.uc_ComStep=Com_HD;
                gs_PtlCrt.uc_CompLevel=0;
            }
        }
    }

    if(guc_ShowStCom > 0)
    {                                       //通讯标志显示延时
        guc_ShowStCom--;
//      if(guc_ShowStCom == 0)
//      {
//          CloseGJLed();
//      }
    }
//  else
//  {
//      if(gui_SystemState&flgStSys_Program)
//      {
//          FlashGJLed();
//      }
//      else
//      {
//          CloseGJLed();
//      }
//  }

    if(gs_DispStt.ucTmr != 0)
    {
        gs_DispStt.ucTmr--;
    }
    
    if(gs_DispStt.ucTmr > 0)
    {                                                   //判断各显示状态定时是否到,需要进行状态切换
        return;
    }

    gs_DispStt.ucTmr = 5;
    gs_DispStt.ucIndex++;
    
    if(gs_DispStt.ucIndex>=9)
    {
        gs_DispStt.ucIndex=0;
    }
}
const uint8 code lcdEnyshow[5]={0xbd,0x84,0xd9,0xcd,0xe4};
extern const uint8 code NUMTABLE[];
uint8 guc_lastShowIndex;
/*=========================================================================================\n
* @function_name: ShowRefresh
* @function_file: Lcdshow.c
* @描述: 显示刷新
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowRefresh(void)
{
     Word32 Data;
     int16 Eadd;
     uint32 ul_ShowData;
     uint32 ul_ShowType;

     if(guc_lastShowIndex!=gs_DispStt.ucIndex) //防止抖屏
     {
         ShowMask();
     }
     guc_lastShowIndex=gs_DispStt.ucIndex;
    if(guc_ShowStCom > 0)
    {
        ShowMask();
        ul_ShowType =0xaa1234aa;
    }
    else
    {
      switch(gs_DispStt.ucIndex)
      {
      default:                  //显示当前电量
      case 0x00:
      case 0x01:
      case 0x02:
      case 0x03:
      case 0x04:
        Data.lword = gs_EnergyA.lCP[gs_DispStt.ucIndex];
        Eadd = Eny_GetEp1(0, gs_DispStt.ucIndex);          //取得某个费率的电量增量
        Data.lword += Eadd;
        ul_ShowData=Hex2BCD(Data.lword);   //首先转化为BCD码;
        ul_ShowType=0;
        LCDM0=0x01;
        if(gs_DispStt.ucIndex!=0x00)
        {
          LCDM0|=NUMTABLE[gs_DispStt.ucIndex];
        }
        LCDM4|=0x01;      
        LCDM9|=0xF6;
        LCDM10=lcdEnyshow[gs_DispStt.ucIndex];
        break;
      case 0x05://需量
        LCDM0=0xE6;
        LCDM9|=0xd6;
        LCDM4|=0x01;  
        LCDM10=0x3d;
        ul_ShowType=0;
        Data.lword=0;
        DataProcRead2Slice(LSXLID,0,0,3,Data.byte);    // 读取当前需量最大值    
        ul_ShowData=Hex2BCD(Data.lword);               //首先转化为BCD码;
        break;
      case 0x06:                            //显示日期
        if(_SYS_IS_PWR_OFF)
        {
            SleepTimeProc();                //读取RTC时钟到RAM中
        }
        ul_ShowData=(((uint32)gs_DateTime.ucDay)<<24);  //日月年
        ul_ShowData|=((uint32)(gs_DateTime.ucMonth)<<16); 
        ul_ShowData|=0x2000+gs_DateTime.ucYear; 
        ul_ShowType=0x00000000;
        LCDM4|=0x01;
        LCDM9|=0xAB;
        LCDM10|=0x59;
        break;
      case 0x07:                            //显示时间
        if(_SYS_IS_PWR_OFF)
        {
            SleepTimeProc();                    //读取RTC时钟到RAM中
        }
        GetSysClock((uint8*)&ul_ShowData,Const_hhmmss);
        ul_ShowData<<=8;
        ul_ShowType=0x000000AA;
        LCDM4|=0x01;
        LCDM9|=0xAB;
        LCDM10|=0x04;
        break; 
      case 0x08:        //表号
         ul_ShowType=0;
         LCDM9|=0xea;
         LCDM10=0x3d;
         BE_ReadP(EEP_COMADD,Data.byte,4);
         ul_ShowData=Hex2BCD(Data.lword);               //首先转化为BCD码;
        break;
      }
    }
      LCDM5&=~0x01;
      LCDM6&=~0x01;
      LCDM7&=~0x01;
      LCDM8&=~0x01;
      switch(gs_FeeData.uc_FeeNo)
      {
            case 0: 
            default:
                LCDM5|=0x01;
                break;
            case 1: 
                LCDM6|=0x01;
                break;
             case 2: 
                LCDM7|=0x01;
                break;
             case 3: 
                LCDM8|=0x01;
                break;
      }
      Disp_Numb(ul_ShowData,ul_ShowType);
}


