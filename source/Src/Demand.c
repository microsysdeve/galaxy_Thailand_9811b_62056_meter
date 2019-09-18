#define DEMANDEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: InitDemand
* @function_file: Demand.c
* @����: ��ʼ��������һЩ����,POR ��ʱ�����
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Demand_Init(void)
{
    guc_Dmd250msCnt=0;                  //250ms��������
    guc_DeamandTimer = 0;               //�������Ӵ������
    gul_Power=0;                                                            
    gl_DemandValue=0x00;                //���µ縺�ɼ�������
    gl_XPm  = 0;                        //��ʼ�������м���
    guc_DmdCnt = 0;                     // �����������ڵļ�����
    ResetMinuteDemand(0);               //�Ѽ���һ�������õ���һЩ����ȫ������
}
/*=========================================================================================\n
* @function_name: Demand_1s
* @function_file: Demand.c
* @����: �Ƿ���������������,1�����������е���
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Demand_1s(void)                                                    
{
    guc_DeamandTimer ++;						                    
    if (guc_DeamandTimer >= 60)					                    
    {                                                               
        guc_DeamandTimer = 0;					                    
        gui_SystemEvent |= flgEtGlb_DemadProc;      //�����������־���Ƿ��������ȡ�����������ںͻ���ʱ��
    }                                                                   
}  
/*=========================================================================================\n
* @function_name: Demand_250ms
* @function_file: Demand.c
* @����: 250ms�жϳ����е���,����ʱ���ۼ�
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Demand_250ms(void)
{
    __disable_interrupt();              //���ж�
    gs_DemanCalcData.uiTotalTime ++;    //��ʱ������
    __enable_interrupt();               //���ж�
}
/*=========================================================================================\n
* @function_name: Demand_EnergyPulse
* @function_file: Demand.c
* @����: ���������ۼӣ��ڳ�������жϳ�����
* 
* 
* @����: 
* @param:type  
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
#ifdef _DEL
void Demand_EnergyPulse(void)
{
    gs_DemanCalcData.uiEnergy ++;  			//��Ӧ����������ӣ���λ���ڳ�����֮һkwh
    //�����Ӧʱ�� ���� ���μ�����ܼ�ʱ
    gs_DemanCalcData.uiEnergyTime = gs_DemanCalcData.uiTotalTime;
}
#endif
/*=========================================================================================\n
* @function_name: ResetMinuteDemand
* @function_file: Demand.c
* @����: ��ʼ��������ֵ,��ʼ����ʱ��,ÿ������������ϵ�ʱ��
* 
* 
* @����: 
* @param:type : 0-ȫ����0��1-����ʣ��ʱ��
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ResetMinuteDemand(uint8 type)
{
    if (type == 0)  								//ȫ����0
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

        //�������3����δ����������壬����ʱ�䰴3�������㣬�������
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
* @����: ����Ľ�����ں�������,������������Ч��ʱ��ִ�����³���
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void CalcMinuteDemand(void)
{
    uint16 uiEnergy;								
    uint16 uiEnergyTime;							

    __disable_interrupt();								//���ݱ���
    uiEnergy = gs_DemanCalcData.uiEnergy;		    //��ʱ���������ں����ļ���
    uiEnergyTime = gs_DemanCalcData.uiEnergyTime;   
    __enable_interrupt();								
    ResetMinuteDemand(1);  								//60����ۼ���������
    //����һ��ƽ������	
    if(uiEnergyTime==0)
    {
      uiEnergyTime=1;
    }
    gs_DemanCalcData.ulPower = (uint32)(uiEnergy *(uint32)144000)/ uiEnergyTime; //����Ҫע�����,16λ�������,����Ҫ��UL
    gs_DemanCalcData.ulPower *= 100;
    gs_DemanCalcData.ulPower /= gs_JbPm.ui_MeterC;
    
    gul_Power=gs_DemanCalcData.ulPower;
}
/*=========================================================================================\n
* @function_name: StartDemand
* @function_file: Demand.c
* @����: ��ʼ���������RAM����,��ʼ�������� �������¿�ʼ����������ʱ��
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void StartDemand(void)
//{
//    gl_XPm  = 0;                                        //��ʼ�������м���
//    guc_DmdCnt = 0;                                     // �����������ڵļ�����
//    guc_DeamandTimer = 0;                               //��ȡ�ڲ�ÿ����
//    ResetMinuteDemand(1);                               //60����ۼ���������
//}
/*=========================================================================================\n
* @function_name: Demand_Proc
* @function_file: Demand.c
* @����: ��������(60s����һ��)���õ�1���ӵ�һ�����ʣ����������õ�,����˵���������ñ�Ǻ���ȥ����
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Demand_Proc(void)
{
//  if (guc_DemandDelay > 0)        					    //�ϵ�����������ʱδ��
//  {
//      guc_DemandDelay --;								    //�ϵ�����������ʱʱ�䴦��
//      if (guc_DemandDelay == 0)
//      {
//          StartDemand();								    //��ʼ�����һЩRAM�Ĵ���
//      }
//  }
//  else
    {	                                                    
        CalcMinuteDemand();         						//�����ƽ�����ʣ��������塢��ʱ���õ�һ���ӵĹ���
        gl_XPm    += gs_DemanCalcData.ulPower;	            //��
        Demand_Calc();          								//��������
    }
}
/*=========================================================================================\n
* @function_name: Demand_Calc
* @function_file: Demand.c
* @����: ��������,ÿ���ӵ���һ�Σ�������ײ��ƽ�����ʺ����
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Demand_Calc(void)
{
    uint8 ucPeriod;			        // ��������
    int32 tmpLong; 	                // BCD��
    uint8 ucData[DemandLen];

    ////////////////////////////////////////////////////////////////////////////
    //���������ǰ��׼�������������ںͻ���ʱ��Ⱦ����˱���
    //BE_ReadP(EEP_XLZQ,(uint8*)&ucPeriod,1);         // ��E2�л�ȡ��������
    //ucPeriod=APIByteBCD2HEX(ucPeriod);
    ucPeriod = 15;
    if (ucPeriod > MAX_D_PERIOD)	                // ����������ڳ��ȱ��������Ϊ 30 ����
    {//ucPeriod����0�������Ŀǰ���ܳ���,������ʾ�رյ�ʱ��,E2�����ݺܿ��ܶ���0,�����ֵ������������
    	ucPeriod = MAX_D_PERIOD;						// ������Χ����30���Ӵ���
    }

   	// �������ڵ��˺󣬼������ǰ�����ڵ�����ֵ
    guc_DmdCnt++;							        // �������ڵ���ʱ����
    if (guc_DmdCnt >= ucPeriod)            	        // �ﵽ��������
    {
        tmpLong = gl_XPm;                            
        if (tmpLong < 0)    					    // ��ȡ��ֵ
        {										     
            tmpLong = -tmpLong;					    // ȡ����	
        }										     
        gl_DemandValue = tmpLong / guc_DmdCnt;
        gl_XPm = 0;                                 // ������Ϻ�����
        guc_DmdCnt = 0;    					        // �����������¼������������������㣬��ǰ�������Ҫ
        //DataProcRead2Slice(LSXLID,0,0,3,ucData);    // ��ȡ��ǰ�������ֵ 
        BE_ReadP(EEP_MAXDEMAND , ucData, 3);
        if (gl_DemandValue< 10)					    // ���˼�Сֵ
        { 
            gl_DemandValue= 0;					    // ����
        } 

        tmpLong = Uint8_To_Uint24(ucData);	       // ��ȡ�洢��E2�е��������
        if (gl_DemandValue  > tmpLong)		     
        {										 
            tmpLong = gl_DemandValue;		     
            Uint24_To_Uint8(tmpLong, ucData);      // ������������� ucData ��ȥ
            //MemCpy(ucData+3,(uint8*)&gs_DateTime.ucMinute,5);     
            //DataProcWriteRound2(R2_NO_MOVE,LSXLID,ucData);  // д������������ݼ�ʱ��
            BE_WriteP(EEP_MAXDEMAND , ucData, 3);
        }										 
    }
}
/*=========================================================================================\n
* @function_name: DemandClrCur
* @function_file: Demand.c
* @����: ���㵱������ֵ
* 
* @����: 
* @����: 
* @����:   Lwb (2011-10-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void DemandClrCur(void)
//{
////  uint8 ucData[DemandLen];
////  MemSet(ucData, 0, DemandLen);
////  Uint16_To_Uint8(do_CRC(ucData, DemandLen - 2), ucData + DemandLen - 2);
////  BE_WriteP(EEP_MAXDEMAND,ucData,10);                                          // д�������������    
//    guc_DeamandTimer = 0;                                                        
//    gul_Power=0;                                                                 
//    ResetMinuteDemand(0);                                                       //��RAM����
//
//}
                                                                               
