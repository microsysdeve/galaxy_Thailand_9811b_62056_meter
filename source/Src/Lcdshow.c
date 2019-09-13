#define LCDSHOWEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: ShowSysStart
* @function_file: Lcdshow.c
* @描述: 显示上电初始化
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowSysStart(void)
{
    ShowInitial();                  //显示参数初始化
#ifdef _DEL
    guc_DyBgLed = gs_DispCont.ucFullShowTm;         //上电背光时间跟全屏时间一样
    gul_ShowState= 0x00;
    gs_DispStt.uiIndex = 0;         //全屏显示
    gs_DispStt.ucMode = Const_DispMode_Full;
    gs_DispStt.ucTmr = gs_DispCont.ucFullShowTm;    //持续时间5s
#endif
}
/*=========================================================================================\n
* @function_name: ShowInitial
* @function_file: Lcdshow.c
* @描述: 显示初始化
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowInitial(void)
{
//    SysE2ReadData(EEP_MAX_LX_NUM,&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);   //读取显示项
//    gs_DispCont.ul_CRC=do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);       //计算显示项的crc
    gs_DispCont.ucLxCnt = 4;       //轮显屏数
    gs_DispCont.ucJxCnt = 4;        //键显屏数
    gs_DispCont.ucLxTm = 5;        //每屏显示时间
    gs_DispCont.ucJxTm = 5;         //键显时间
    gs_DispCont.ucJxPowOffTm = 5;    //停电键显时间
    gs_DispCont.ucFullShowTm = 5; //全屏显示时间
//    
//    gs_DispCont.ucPowUpBgTm = InitPara3[44]; //上电背光亮时间
//    gs_DispCont.ucIrBgTm = InitPara3[45];  //红外触发背光亮时间
//    gs_DispCont.ucKeyBgTm = InitPara3[46]; //按键触发背光亮时间
}
/*=========================================================================================\n
* @function_name: ShowKeyManage
* @function_file: Lcdshow.c
* @描述: 按键数据显示处理
* 
* 
* @参数: 
* @param:ucType  显示类别, Const_Disp_KeyUp-上翻, Const_Disp_KeyDn-下翻
* @返回: 
* @作者:   lwb (2012-05-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ShowKeyManage(void)
{
    //如果是停电下，就不需要显示错误字
    if(!_SYS_IS_PWR_OFF)                            //有电下进行错误字显示
    {
        gs_DispStt.ucTmr = gs_DispCont.ucJxTm;
    }else
    {
        gs_DispStt.ucTmr = gs_DispCont.ucJxPowOffTm;
    }
    
    if(gs_DispCont.ucJxCnt == 0)
    {                                       //键显表为0
        gs_DispCont.ucJxCnt = 1;
    }

    if(gs_DispStt.ucMode != Const_DispMode_JX)
    {                                       //由非键显状态进入键显状态
        gs_DispStt.ucMode = Const_DispMode_JX;
        gs_DispStt.uiIndex = 0;
    }
    else
    {                                                               //本来就在键显状态
        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucJxCnt)
        {
            gs_DispStt.uiIndex = 0;
        }
    }

    gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
    ShowRefresh();                                  //立即刷新
}
/*=========================================================================================\n
* @function_name: ShowSecondProc
* @function_file: Lcdshow.c
* @描述: 一秒钟调用一次,分系统掉电N天以后、系统掉电N天之内、系统有电三种情况处理,它们之间的
*       关系是互斥的这里的状态切换中有一个问题,就是当在凌晨x时到y时之间如果按键的话,当按键
*       退出时,会进入到轮显状态或停显状态,但是最多过1min就会又进入关闭显示状态.
* @参数:
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowSecondProc(void)
{

    gui_SystemEvent |= flgEtGlb_RefreshLcd;             //设置LCD刷新

    
//    guc_PrOutTm++;
//    if(guc_PrOutTm>=60)
//    {
//        guc_PrOutTm=0;
//        KeyPgm_DyOut();                                 //编程按键的退出
//        PwBs_DyOut();
//    }
    
    
    if(guc_ShowStCom>0)      //显示通信符号
    {
        guc_ShowStCom--;
        if(guc_ShowStCom==0)
        {
//          gul_ShowState &= ~flgShowSt_Phone;
        }
    }
    
    if(gs_DispStt.ucTmr != 0)
    {
        gs_DispStt.ucTmr--;
        if(gs_DispStt.ucTmr>0)                          //判断各显示状态定时是否到,需要进行状态切换
        {
            return; 
        }
    }

    switch(gs_DispStt.ucMode)
    {
    case Const_DispMode_LX:       //轮显
//        if(guc_PllSta == PLL_800K)
//        {
////            gs_DispStt.ucTmr = gs_DispCont.ucLxTm/2;
//        }
//        else
//        {
            gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
//        }

        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucLxCnt)
        {
            gs_DispStt.uiIndex = 0;                     //屏号复归到第一屏
        }
        break;
    case Const_DispMode_JX:       //键显  
        gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
        gs_DispStt.ucMode = Const_DispMode_LX;
        gs_DispStt.uiIndex = 0;
        break;
    case Const_DispMode_TX:        //停显
      break;
    case Const_DispMode_Full:      //全显
//      if(gs_DispStt.ucTmr != 0)
//        break;
//      AlarmLedLow();
    default:
                                                        //复位到轮显状态
        gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
        gs_DispStt.ucMode = Const_DispMode_LX;
        gs_DispStt.uiIndex = 0;
        break;
    }
    return;
}
 
/*=========================================================================================\n
* @function_name: ShowStateManage
* @function_file: Lcdshow.c
* @描述: 各类状态位的显示准备
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowStateManage(void)
{
//  static uint8 flg = 0;

    if(!_SYS_IS_PWR_OFF)
    {
//        if(((guc_CoverStatus&0x0f) == CoverOpen)&&(gul_ShowId != 0x03300E01)&&(gul_ShowId != 0x03300E02))//开表盖显示 表尾盖一屏不显示
//        {
//            gul_ShowState|=flgShowSt_Pane1;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Pane1;
//          
//        }
//        if(((guc_CoverWStatus&0x0f) == CoverOpen)&&(gul_ShowId != 0x03300D01)&&(gul_ShowId != 0x03300D02))//开表尾盖显示 表盖一屏不显示
//        {
//            gul_ShowState|=flgShowSt_Pane2;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Pane2;
//        }
    
//        if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir)  //功率反向显示
//        {
//            gul_ShowState|=flgShowSt_Lift;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Lift;
//        }

        if(gut_SysWarn.SysWarn.BatLow==true)   //电池报警
        {
            gul_ShowState|=flgShowSt_Bat;
        }else
        {
            gul_ShowState&=~flgShowSt_Bat;
        }
//        
//        if(guc_FactoryType == FactorMd)   //厂内符号
//        {
//            gul_ShowState|=flgShowSt_Switch;
//        }else
//        {
//          if(gui_SystemState & flgStSys_Program)   // 是否编程状态
//          {
//            if(flg)                   // 编程闪烁显示
//            {
//              flg = 0;
//              gul_ShowState|=flgShowSt_Switch;
//            }else
//            {
//              flg = 1;
//              gul_ShowState &= ~flgShowSt_Switch;
//            }
//          }else                                  
//          {
//            gul_ShowState &= ~flgShowSt_Switch;      
//          }
//        }
//        
//         if(ge_Channel == SETA)   //通道符号
//        {
////            gul_ShowState|=flgShowSt_L;
//            gul_ShowState&=~flgShowSt_N;
//        }else
//        {
//            gul_ShowState|=flgShowSt_N;
//            gul_ShowState&=~flgShowSt_L;
//        }
//        if(gs_MeterState.ui_MeterState7.RunCode7Word.IImbalance)   //电流不平衡符号
//        {
//          gul_ShowState|=flgShowSt_Scale;
//          AlarmLedHigh();  //报警灯亮
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Scale;
//          AlarmLedLow();
//        }
           
    }else
    {
        gul_ShowState=0;                    //停电下不显示状态
    }
}
/*=========================================================================================\n
* @function_name: ShowNumManage
* @function_file: Lcdshow.c
* @描述:
*
*
* @参数:
* @param:ulID  数据标识
* @返回:
* @作者:   zb (2015-12-2)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
/*
void ShowNumManage(uint32 ulID,uint8 ucSubNo)
{
    uint32  ulNum;
    uint32  ulMsk = 0;
    uint8   i,nobuf[6],dotbuf,j;
    Word32  timebuf,databuf;
    uint32  buf;
    
    CLRWDT();  
    switch(ulID)
    {
    case 0x00000000:                    //总电量
//      BE_ReadP(EEP_EDEC, (uint8*)&dotbuf,1);
      dotbuf = 2;
      switch(dotbuf)
      {
        case 0: //没有小数点
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/1000);
          ulNum&=~0xff800000;     //大于799999,从0开始
          j = 7;//消隐7位
          break;
        case 2: //2个小数点
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/10);
          ulNum&=~0x80000000;     //大于799999.99,从0开始
          j = 5;//消隐5位
          break;
        default://没有小数点
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/1000);
          ulNum&=~0xff800000;     //大于799999,从0开始
          j = 7;//消隐7位
      }
      for( i=0; i<j; i++)   //消隐处理
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }     
      break;
    case 0x02010100:       //电压
      ulNum = CalRMS(RMSU);
//      ulNum = Hex2BCD(ulNum/1000);
//      ulNum&=~0xff800000;     //大于799999.99,从0开始
      j = 6;//消隐6位
      for( i=0; i<j; i++)   //消隐处理
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x02020100:      //电流
      ulNum = CalRMS(RMSI1);
      j = 4;//消隐4位
//      ulNum = Hex2BCD(ulNum/1000);
//      ulNum&=~0xff800000;     //大于799999.99,从0开始
      for( i=0; i<j; i++)   //消隐处理
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x02800001:      //零线电流
//      databuf.lword = 0;
//      BE_ReadP(EEP_KBGETNO, (uint8*)databuf.byte,3);
//      BE_ReadP(EEP_FXQDETNO, (uint8*)databuf.byte,3);
      
      ulNum = CalRMS(RMSI2);
      j = 4;//消隐4位
      for( i=0; i<j; i++)   //消隐处理
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j== i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x03300E00:      //开尾盖次数
      databuf.lword = 0;
//      BE_ReadP(EEP_KBWGETNO, (uint8*)databuf.byte,3);

      ulNum = Hex2BCD(databuf.lword);
      for( i=0; i<7; i++)   //消隐处理
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(7 == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;      
    case 0x04000101:      //日期
      ulNum = 0;
      GetSysClock( timebuf.byte, Const_YYMMDD);
      for(i=0; i <3; i++)
      {
        buf = 0;
        buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
        ulNum |= buf;
      }
      ulMsk = 0xAA000000;
      break;
    case 0x04000102:      //时间
      ulNum = 0;
      GetSysClock( timebuf.byte, Const_hhmmss);
      for(i=3; i>0; i--)
      {
        buf = 0;
        buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
        ulNum |= buf;
      }
      ulMsk = 0xAA000000;
      break;
    case 0x04000402:      //表号
      SysE2ReadData(EEP_METERNO, (uint8*)nobuf,6);
//      BE_ReadP(EEP_METERNO +EEP_BAK_LEN, (uint8*)nobuf,6);//测试用
//      BE_ReadP(EEP_METERNO, (uint8*)nobuf,6);//测试用
      ulNum = 0;
//      if(ucSubNo)  //表号低8位
//      {
        for(i=4; i>0; i--)
        {
          ulNum = ulNum << 8;
          ulNum |= nobuf[i-1];
        }
//      }
//      else        //表号高4位
//      {
//        for(i=5; i>=4; i--)
//        {
//          ulNum = ulNum << 8;
//          ulNum |= nobuf[i];
//        }
//        for( i=0; i<4; i++)   //消隐处理
//        {
//          if((ulNum<<(i*4))&0xF0000000L)
//          {
//            ulMsk = ulMsk<<4;
//            break;
//          }
//          else
//          {
//            ulMsk|=0xA0000000L;
//            ulMsk = ulMsk>>4;
//          }
//        }
//        if(4 == i)
//        {
//          ulMsk = ulMsk<<4;
//        }        
//      }
      break; 
    case 0x03300D01:      //最近一次开表盖起始时间 日期
        ulNum = 0;
        DataProcRead2Slice(KBGJLID,0,3,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_YYMMDD);
        for(i=0; i <3; i++)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
        break;
     case 0x03300D02:      //最近一次开表盖起始时间  时间 
        ulNum = 0;
        DataProcRead2Slice(KBGJLID,0,0,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_hhmmss);
        for(i=3; i>0; i--)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;
    case 0x03300E01:      //最近一次开尾盖次数起始时间  日期
        ulNum = 0;
//        DataProcRead2Slice(KBWGJLID,0,3,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_YYMMDD);
        for(i=0; i <3; i++)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;
    case 0x03300E02:      //最近一次开尾盖次数起始时间  时间

        ulNum = 0;
//        DataProcRead2Slice(KBWGJLID,0,0,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_hhmmss);
        for(i=3; i>0; i--)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;      
    default:
      ulNum = 0x00000000;
      ulMsk = 0x72310000;
    }
    gs_LcdDisp.ulNum1 = ulNum;
    gs_LcdDisp.ulNum1Msk = ulMsk;
    CLRWDT();  
}
*/
/*=========================================================================================\n
* @function_name: SearchDispNO
* @function_file: Lcdshow.c
* @描述: 通过数据标识查找屏号
*
*
* @参数:
* @param:ulID
*
* @返回:
* @return: uint16
* @作者:   lwb (2012-03-19)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 SearchDispNO(Word32 ulID)
{
    if(ulID.byte[3]==0x00)                                  //电量类
    {
        for(uint8 i=0;i<guc_LenOfTabConvent;i++)
        {
            if(gCs_TabConvent[i].ulInID==ulID.lword)
            {
                return gCs_TabConvent[i].uiNumb;
            }
        }
    }else if(ulID.byte[3]==0x02)
    {
        for(uint8 i=0;i<guc_LenOfTabConvBL;i++)
        {
            if(gCs_TabConvBL[i].ulInID==ulID.lword)
            {
                return gCs_TabConvBL[i].uiNumb;
            }
        }
    }else if(ulID.byte[3]==0x03)
    {
        for(uint8 i=0;i<guc_LenOfTabAdd;i++)
        {
            if(gCs_TabAdd[i].ulInID==ulID.lword)
            {
                return gCs_TabAdd[i].uiNumb;
            }
        }

    }else if(ulID.byte[3]==0x04)
    {
        for(uint8 i=0;i<guc_LenOfTabConvCS;i++)
        {
            if(gCs_TabConvCS[i].ulInID==ulID.lword)
            {
                return gCs_TabConvCS[i].uiNumb;
            }
        }
    }
    return 0xff;    //无效屏
}

/*=========================================================================================\n
* @function_name: ShowDataProc
* @function_file: Lcdshow.c
* @描述: 显示数据的处理
*
* @参数:
*
* @返回:
* @return: 
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
/*
void ShowDataProc(void)
{
    uint16  uiAddr;                  //E2中各类显示相关表的地址
    Word32  wdInID;                 //数据标识
      
    uint8   ucDispNo;              //屏号
    uint8   ucDispSubNo;            //分2屏信息
//    uint8   dotbuf;

    CLRWDT();  
    uiAddr = gs_DispStt.uiIndex *5;                         //根据序号获取屏号地址

    if((gs_DispStt.ucMode==Const_DispMode_LX)||(gs_DispStt.ucMode==Const_DispMode_TX))
    {
        FCpyTMem(XDATA_RAMZONE, InitPara2 + uiAddr, 5);
        gul_ShowId=Uint8_To_Uint32(XDATA_RAMZONE);
//        uiAddr += EEP_LXTABLE;
//        BE_ReadP(uiAddr, XDATA_RAMZONE,5);   //从eeprom中获得数据标识
        
    }
    else if(gs_DispStt.ucMode==Const_DispMode_JX)
    {
      FCpyTMem(XDATA_RAMZONE, InitPara2 + uiAddr, 5);
      gul_ShowId=Uint8_To_Uint32(XDATA_RAMZONE);
//        uiAddr += EEP_JXTABLE;
//        BE_ReadP(uiAddr, XDATA_RAMZONE,5);   //从eeprom中获得数据标识

    }
    else if(gs_DispStt.ucMode==Const_DispMode_Full)
    {
        Disp_Full();
//        AlarmLedHigh();  //报警灯亮
        return;
    }
    else if(gs_DispStt.ucMode==Const_DispMode_AdvSysClr)
    {
              
    }    
    wdInID.lword = Uint8_To_Uint32(XDATA_RAMZONE);
    ucDispSubNo = XDATA_RAMZONE[4];
    
    ucDispNo = SearchDispNO(wdInID);   //从数据标识中获得屏号

    
    gs_LcdDisp.uiUnitPt1 = gCs_DispTab[ucDispNo].uiUnitPoint;   //得到显示单位和小数点
    gul_ShowState |= gCs_DispTab[ucDispNo].ulShowState;  //得到屏的状态
                                    
//    if((gul_ShowId==0x00000000)||(gul_ShowId==0x00000001)||(gul_ShowId==0x00000002))//电量小数点单独处理
//    {
//      BE_ReadP(EEP_EDEC, (uint8*)&dotbuf,1);
//      switch(dotbuf)
//      {
//        case 0: //没有小数点
//          break;
//        case 2: //2个小数点
//          gs_LcdDisp.uiUnitPt1 |= 0x30;
//          break;
//        default://没有小数点
//          break;
//      }
//    }
    
    CLRWDT();  
    
    ShowNumManage(wdInID.lword, ucDispSubNo);


}
*/
/*=========================================================================================\n
* @function_name: ShowRefreshTime
* @function_file: Lcdshow.c
* @描述: 停电情况下显示时间时的直接更新,这里不去数据处理得到时间是出于停电时功耗考虑
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void ShowRefreshTime(void)
{
    GetSysClock((uint8*)&gs_LcdDisp.ulNum1, Const_hhmmss);
    return;
}

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
    uint8 ucType = Const_NeedRefresh;

    
    ShowStateManage();
    
    ShowDataProc();
    if(gs_DispStt.ucMode==Const_DispMode_Full)
    {
      return;
    }
    if(ucType == Const_NeedRefresh)
    {
        Disp_State(gul_ShowState);
        Disp_Numb(gs_LcdDisp.ulNum1, gs_LcdDisp.ulNum1Msk);
        Disp_UnitPoint(gs_LcdDisp.uiUnitPt1);
//        guc_LCDRAM[7] = 0x9f;  //电量的小数点和符号
//        guc_LCDRAM[6] &= 0x0f;
//        guc_LCDRAM[6] |= 0x40;
//        guc_LCDRAM[5] &= 0x7f;
//        guc_LCDRAM[4] &= 0x7f;
//        guc_LCDRAM[3] &= 0x7f;
//        guc_LCDRAM[2] &= 0x7f;
//        guc_LCDRAM[1] &= 0x7f;
//        guc_LCDRAM[0] = 0x00;
        
        LCD_RAMUpdata();
        gul_ShowState = 0;   //状态清除
    }
}


extern const uint8 code NUMTABLE_1L[];
extern const uint8 code NUMTABLE_1H[];
extern const uint8 code NumAddr[12];
/*=========================================================================================\n
* @function_name: PowOffShowRefresh
* @function_file: Lcdshow.c
* @描述: 停电下显示刷新
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void PowOffShowRefresh(void)
{   
    
//    gs_LcdDisp.ulNum1 = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/10);
//    gs_LcdDisp.ulNum1&=~0x80000000;     //大于799999.99,从0开始
    
    gs_LcdDisp.ulNum1 = gul_Test;  //测试用
    gs_LcdDisp.ulNum1Msk =0xAA000000;
    
    Disp_Numb(gs_LcdDisp.ulNum1, gs_LcdDisp.ulNum1Msk);
    
//    guc_LCDRAM[7] = 0x9f;  //电量的小数点和符号
//    guc_LCDRAM[6] &= 0x0f;
//    guc_LCDRAM[6] |= 0x40;
//    guc_LCDRAM[5] &= 0x7f;
//    guc_LCDRAM[4] &= 0x7f;
//    guc_LCDRAM[3] &= 0x7f;
//    guc_LCDRAM[2] &= 0x7f;
//    guc_LCDRAM[1] &= 0x7f;
//    guc_LCDRAM[0] = 0x00;
        
    LCD_RAMUpdata();
}
/*=========================================================================================\n
* @function_name: SleepDispInit
* @function_file: Lcdshow.c
* @描述: 睡眠前初始化显示
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void SleepDispInit(void)
{
    gs_DispStt.uiIndex = 0;         //显示屏切换到第一屏
    guc_PowOffRuning=false;         //唤醒状态切换到睡眠
}

/*=========================================================================================\n
* @function_name: SleepDisp
* @function_file: Lcdshow.c
* @描述: 掉电显示
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 SleepDisp(void)
{

    if(gs_DispStt.ucTmr!=0)          //休眠显示
    {
        gs_DispStt.ucTmr--;
    }

    if(gs_DispStt.ucTmr>0)
    {
        //如果是时间那屏需要读取时间
        if(gul_ShowId == 0x04000102) 
        {
            SleepTimeProc();
            gs_DispStt.ucPwrOffRefresh|= Cosnt_RefreshTime;
            ShowRefresh();
        }
        return true;
    }

//  if(gs_DispStt.ulPwrOffTmr!=0)   //停显时间到
//  {
//      if(((gs_FunCfg.uc_PWOFFSHOWMDCfg&0x99)==0x09))  //停电常显
//      {
//          gs_DispStt.uiIndex = 0;                     //屏号复归到0
//          gs_DispStt.ucTmr = 1;                       //时间设置60s
//          gs_DispStt.ucMode = Const_DispMode_TX;
//          gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
//          ShowRefresh();
//          return false;
//      }
//  }


    if(gs_DispStt.ucTmr==0)
    {
        if(gs_DispStt.ucMode == Const_DispMode_LX)
        {
            SleepTimeProc();
            gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
            gs_DispStt.uiIndex++;
            gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
            if(gs_DispStt.uiIndex >= gs_DispCont.ucLxCnt)
            {
                gs_DispStt.uiIndex = 0;                     //屏号复归到0
                return false;
            }
        }else 
        {
            return false;
        }
        ShowRefresh();
    }
    return true;
}