#define DEMANDEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: InitDemand
* @function_file: Demand.c
* @描述: 初始化需量的一些变量,POR 的时候调用
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Demand_Init(void)
{
    guc_Dmd250msCnt=0;                  //250ms计数清零
    guc_DeamandTimer = 0;               //需量分钟处理计数
    gul_Power=0;                                                            
    gl_DemandValue=0x00;                //上下电负荷监控能清掉
    gl_XPm  = 0;                        //初始化计算中间量
    guc_DmdCnt = 0;                     // 需量计算周期的计数器
    ResetMinuteDemand(0);               //把计算一分钟中用到的一些变量全部清零
}
/*=========================================================================================\n
* @function_name: Demand_1s
* @function_file: Demand.c
* @描述: 是否计算需量标记设置,1秒钟主程序中调用
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Demand_1s(void)                                                    
{
    guc_DeamandTimer ++;						                    
    if (guc_DeamandTimer >= 60)					                    
    {                                                               
        guc_DeamandTimer = 0;					                    
        gui_SystemEvent |= flgEtGlb_DemadProc;      //置需量处理标志，是否产生数据取决于需量周期和滑差时间
    }                                                                   
}  
/*=========================================================================================\n
* @function_name: Demand_250ms
* @function_file: Demand.c
* @描述: 250ms中断程序中调用,需量时间累加
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Demand_250ms(void)
{
    __disable_interrupt();              //关中断
    gs_DemanCalcData.uiTotalTime ++;    //总时间增加
    __enable_interrupt();               //开中断
}
/*=========================================================================================\n
* @function_name: Demand_EnergyPulse
* @function_file: Demand.c
* @描述: 脉冲能量累加，在出脉冲的中断程序中
* 
* 
* @参数: 
* @param:type  
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#ifdef _DEL
void Demand_EnergyPulse(void)
{
    gs_DemanCalcData.uiEnergy ++;  			//对应项的能量增加，单位等于常数分之一kwh
    //脉冲对应时间 等于 本次计算的总计时
    gs_DemanCalcData.uiEnergyTime = gs_DemanCalcData.uiTotalTime;
}
#endif
/*=========================================================================================\n
* @function_name: ResetMinuteDemand
* @function_file: Demand.c
* @描述: 初始化分需量值,初始化的时候,每次需量计算完毕的时候
* 
* 
* @参数: 
* @param:type : 0-全部清0，1-保留剩余时间
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ResetMinuteDemand(uint8 type)
{
    if (type == 0)  								//全部清0
    {
        MemSet((uint8*)&gs_DemanCalcData, 0, sizeof(gs_DemanCalcData));
        guc_DmdFrscnt=0;
    }
    else
    {
        __disable_interrupt();
        gs_DemanCalcData.uiTotalTime -= gs_DemanCalcData.uiEnergyTime;
        gs_DemanCalcData.uiEnergy = 0;
        gs_DemanCalcData.uiEnergyTime = 0;
        __enable_interrupt();

        //如果超过3分钟未获得能量脉冲，则总时间按3分钟起算，以免溢出
        if (gs_DemanCalcData.uiTotalTime > 1800)
        {
            gs_DemanCalcData.uiTotalTime = 1800;
        }
        gs_DemanCalcData.ulPower = 0;
    }
}
/*=========================================================================================\n
* @function_name: CalcMinuteDemand
* @function_file: Demand.c
* @描述: 计算的结果用于后续计算,需量计算标记有效的时候执行如下程序
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void CalcMinuteDemand(void)
{
    uint16 uiEnergy;								
    uint16 uiEnergyTime;							

    __disable_interrupt();								//数据保护
    uiEnergy = gs_DemanCalcData.uiEnergy;		    //临时变量，用于后续的计算
    uiEnergyTime = gs_DemanCalcData.uiEnergyTime;   
    __enable_interrupt();								
    ResetMinuteDemand(1);  								//60秒的累加数据清零
    //计算一次平均功率	
    if(uiEnergyTime==0)
    {
      uiEnergyTime=1;
    }
    gs_DemanCalcData.ulPower = (uint32)(uiEnergy *(uint32)144000)/ uiEnergyTime; //这里要注意的是,16位计算溢出,常数要加UL
    gs_DemanCalcData.ulPower *= 100;
    gs_DemanCalcData.ulPower /= gs_JbPm.ui_MeterC;
    
    gul_Power=gs_DemanCalcData.ulPower;
}
/*=========================================================================================\n
* @function_name: StartDemand
* @function_file: Demand.c
* @描述: 初始化需量相关RAM变量,开始计算需量 或者重新开始计算需量的时候
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void StartDemand(void)
//{
//    gl_XPm  = 0;                                        //初始化计算中间量
//    guc_DmdCnt = 0;                                     // 需量计算周期的计数器
//    guc_DeamandTimer = 0;                               //获取第层每分种
//    ResetMinuteDemand(1);                               //60秒的累加数据清零
//}
/*=========================================================================================\n
* @function_name: Demand_Proc
* @function_file: Demand.c
* @描述: 需量处理(60s处理一次)，得到1分钟的一个功率，根据能量得到,调用说明：在设置标记后再去计算
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Demand_Proc(void)
{
//  if (guc_DemandDelay > 0)        					    //上电需量计算延时未到
//  {
//      guc_DemandDelay --;								    //上电需量计算延时时间处理
//      if (guc_DemandDelay == 0)
//      {
//          StartDemand();								    //开始计算的一些RAM的处理
//      }
//  }
//  else
    {	                                                    
        CalcMinuteDemand();         						//计算各平均功率，根据脉冲、定时器得到一分钟的功率
        gl_XPm    += gs_DemanCalcData.ulPower;	            //加
        Demand_Calc();          								//需量计算
    }
}
/*=========================================================================================\n
* @function_name: Demand_Calc
* @function_file: Demand.c
* @描述: 需量计算,每分钟调用一次，计算出底层的平均功率后调用
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Demand_Calc(void)
{
    uint8 ucPeriod;			        // 需量周期
    int32 tmpLong; 	                // BCD码
    uint8 ucData[DemandLen];

    ////////////////////////////////////////////////////////////////////////////
    //需量计算的前期准备，对需量周期和滑差时间等均做了保护
    //BE_ReadP(EEP_XLZQ,(uint8*)&ucPeriod,1);         // 从E2中获取需量周期
    //ucPeriod=APIByteBCD2HEX(ucPeriod);
    ucPeriod = 15;
    if (ucPeriod > MAX_D_PERIOD)	                // 最大需量周期长度保护，最大为 30 分钟
    {//ucPeriod出现0的情况在目前可能出现,就是显示关闭的时候,E2读数据很可能都是0,而这个值被用作除数了
    	ucPeriod = MAX_D_PERIOD;						// 超出范围，用30分钟代替
    }

   	// 需量周期到了后，计算出当前周期内的需量值
    guc_DmdCnt++;							        // 需量周期的临时变量
    if (guc_DmdCnt >= ucPeriod)            	        // 达到需量周期
    {
        tmpLong = gl_XPm;                            
        if (tmpLong < 0)    					    // 总取正值
        {										     
            tmpLong = -tmpLong;					    // 取反码	
        }										     
        gl_DemandValue = tmpLong / guc_DmdCnt;
        gl_XPm = 0;                                 // 计算完毕后，清零
        guc_DmdCnt = 0;    					        // 需量周期重新计数，必须放在最后清零，因前面计算需要
        //DataProcRead2Slice(LSXLID,0,0,3,ucData);    // 读取当前需量最大值 
        BE_ReadP(EEP_MAXDEMAND , ucData, 3);
        if (gl_DemandValue< 10)					    // 过滤极小值
        { 
            gl_DemandValue= 0;					    // 清零
        } 

        tmpLong = Uint8_To_Uint24(ucData);	       // 读取存储在E2中的最大需量
        if (gl_DemandValue  > tmpLong)		     
        {										 
            tmpLong = gl_DemandValue;		     
            Uint24_To_Uint8(tmpLong, ucData);      // 把最大需量存入 ucData 中去
            //MemCpy(ucData+3,(uint8*)&gs_DateTime.ucMinute,5);     
            //DataProcWriteRound2(R2_NO_MOVE,LSXLID,ucData);  // 写入最大需量数据及时间
            BE_WriteP(EEP_MAXDEMAND , ucData, 3);
        }										 
    }
}
/*=========================================================================================\n
* @function_name: DemandClrCur
* @function_file: Demand.c
* @描述: 清零当月需量值
* 
* @参数: 
* @返回: 
* @作者:   Lwb (2011-10-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void DemandClrCur(void)
//{
////  uint8 ucData[DemandLen];
////  MemSet(ucData, 0, DemandLen);
////  Uint16_To_Uint8(do_CRC(ucData, DemandLen - 2), ucData + DemandLen - 2);
////  BE_WriteP(EEP_MAXDEMAND,ucData,10);                                          // 写入最大需量数据    
//    guc_DeamandTimer = 0;                                                        
//    gul_Power=0;                                                                 
//    ResetMinuteDemand(0);                                                       //清RAM需量
//
//}
                                                                               
