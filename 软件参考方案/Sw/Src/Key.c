#define KEY_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: KeyInit
* @function_file: Key.c
* @描述: 按键初始化
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-20)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void KeyInit(void)
{
    KeyPortIn();                                        // 按键端口设置成输入模式
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
* @描述: 按键扫描
*
* @参数:
* @返回:
* @作者:   lwb (2012-02-27)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void KeyScan(void)
{
    if(KeyStUp())                                   //上翻键延时开启
    {
        if((gs_KeyCtr[UpKey].DlyCnt>=gs_KeyCtr[UpKey].KeyThd)&&
           gs_KeyCtr[UpKey].Status==KeyRls)
        {
//          OpenBeiGuang();
//          guc_DyBgLed = gs_DispCont.ucKeyBgTm;     // 设置背光延时时间
            guc_KeyEvent|=flgEtKey_Up;              // 置上翻键标记
            gs_KeyCtr[UpKey].Status=KeyDw;          //上翻键为按下状态
        }
        if( gs_KeyCtr[UpKey].Status !=KeyDWLong)
        {
            gs_KeyCtr[UpKey].DlyCnt++;              //延时计数器加1
        }
        if((gs_KeyCtr[UpKey].DlyCnt>=gs_KeyCtr[UpKey].LgKeyThd)&&
                 (gs_KeyCtr[UpKey].Status==KeyDw))
        {                                           //如果键状态为按下，并且延时计数大于2s为长按
            gs_KeyCtr[UpKey].Status=KeyDWLong;      //按键状态为长按
            //LongKeyProc();                          //长按键处理
        }
    }
    else
    {
        gs_KeyCtr[UpKey].DlyCnt=0;                  //延时计数清零
        gs_KeyCtr[UpKey].Status=KeyRls;             //按键为释放
    }

    if(KeyStPr())                                   //上翻键延时开启
    {
        if((gs_KeyCtr[PrKey].DlyCnt>=gs_KeyCtr[PrKey].KeyThd)&&
           gs_KeyCtr[PrKey].Status==KeyRls)
        {
            guc_KeyEvent|=flgEtKey_Pr;              // 置上翻键标记
            gs_KeyCtr[PrKey].Status=KeyDw;          //上翻键为按下状态
        }

        if( gs_KeyCtr[PrKey].Status !=KeyDw)
        {
            gs_KeyCtr[PrKey].DlyCnt++;              //延时计数器加1
        }
    }
    else
    {
        gs_KeyCtr[PrKey].DlyCnt=0;                  //延时计数清零
        gs_KeyCtr[PrKey].Status=KeyRls;             //按键为释放
    }
}

/*=========================================================================================\n
* @function_name: KeyProc
* @function_file: Key.c
* @描述: 按键处理函数
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void KeyProc(void)
{
    if(guc_KeyEvent & flgEtKey_Up)
    {
        ShowKeyProc();
        guc_KeyEvent &=~ flgEtKey_Up;               // 清除标志
    }else if(guc_KeyEvent & flgEtKey_Pr)                  // 编程状态考虑
    {                                               //
        if(gui_SystemState & flgStSys_Program)      // 首先判别是否处于编程状态
        {
//          guc_PrKeyNewDown=0;
            gui_SystemState &= ~flgStSys_Program;   // 已经处于编程状态，则清除标志
//          gui_DyPgmOut = 0x00;                     // 编程超时退出时间清零
//          gs_MeterState.ui_MeterState3.RunCode3Word.Program=false;
        }                                           //
        else                                        //
        {                                           //
            gui_SystemState |= flgStSys_Program;    // 设置编程状态标志
//          guc_PrKeyNewDown=0x55;
//          BE_ReadP(EEP_PROTIME,(uint8*)&gui_DyPgmOut,0x02);       // 编程超时退出时间设置
//          if(gui_DyPgmOut==0xffff)                                // 如果E2没有初始化的话，默认为240分钟
//          {
                gui_DyPgmOut=20;
//          }
//          gs_MeterState.ui_MeterState3.RunCode3Word.Program=true;
        }                                           //
        guc_KeyEvent &= ~flgEtKey_Pr;               //
//        BE_WriteP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);    //写入编程剩余时间
    }                                               //
    else                                            //
    {                                               //
        guc_KeyEvent =0x0;                          //  防止其他位设置起来，频繁进入该事件
    }                                               //
}

