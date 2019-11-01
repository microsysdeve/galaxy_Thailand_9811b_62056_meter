#define UART2_EXT
#include "Include.h"
//变量声明
uint8   guc_DyUart2Over;        //模拟串口超时保护
/*=========================================================================================\n
* @function_name: Init_Uart2
* @function_file: Uart2.c
* @描述: uart2的初始化
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Init_Uart2(uint8 ucBode,uint8 uctype)
{    

//  if(uctype==0x00)                            //62056-21
    {
        if(ucBode>=6)
        {
            ucBode=0;                           //默认2400
        }
    }
//  else                                        //645 规约
//  {
//      if(ucBode>=6)
//      {
//          ucBode=3;                           //默认2400
//      }
//  }

    TMOD2 = 0x20;                               // 8-bit counter with auto-reload
    TCON2 =BaudRateTable[ucBode].Type;          //时钟选择CLK  clear SMOD  SET  T1M,TR1
    TL21=TH21=BaudRateTable[ucBode].THValue;    //波特率设置
        
//    if(uctype==0x00)                            //62056-21
    {
        SCON2 = 0x50;                           //数据位8位,7位数据位+1校验位
    }
//    else
//    {
//        SCON2=0xD0;                             //数据位9位,8位数据位+1校验位
//    }
    P2OD|= BIT5; 
    P2OE &= ~BIT5;                      //UART2发送口输出允许
    P2IE &= ~BIT5;                      //UART2发送口输入禁止
    P2OE |= BIT4;                       //UART2接收口输出禁止
    P2IE |= BIT4;                       //UART2接收口输入允许
    P24FS=2;                            //P2.4配置成RXD
    P25FS=2;                            //P2.5配置成GPIO,只有在发送的时候切换成TXD

    EIE|=(BIT0);                        //使能uart2中断
    //近红外，不调制输出
    Txd2FS=0x01;
    ExInt2IE&=~BIT0;                    //关闭发送中断
    SCON2&=~(BIT0+BIT1);
    ExInt2IFG&=~(BIT0+BIT1);
    ExInt2IE|=BIT1;                    //开启接收中断
}

/*=========================================================================================\n
* @function_name: Uart2_Dy10ms
* @function_file: Uart2.c
* @描述: 模拟串口的超时保护
*       为防止锁死，定时保护，当没有任何数据发送和接收的时候，初始化
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart2_Dy10ms(void)
{
    guc_DyUart2Over--;
    if(0x00== guc_DyUart2Over)
    {
        if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
           ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
        {
            Init_Uart2(0,0);        //初始化红外
        }
        else
        {
            Init_Uart2(3, 0);        //初始化红外
        }
        ComBom_Init(ComIndex_Uart2);    //将uart6 端口对应的 COM初始化
    }
}
/*=========================================================================================\n
* @function_name: Uart2_Receive
* @function_file: Uart2.c
* @描述: UART4接收,在中断中调用该函数
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart2_Receive(void)
{

//    uint8 temp,temp1;
    guc_DyUart2Over = Const_DyUart2Over;//端口超时保护

    //处于空闲状态或已经处于uart接收状态
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //设置数据包接收超时时间

    if((gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle)
       ||(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv))        //当前是空闲的状态的话，判断是否是帧头68
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //判断 com中的buf是否溢出
        {                                                           //防止缓存溢出
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = (SBUF2&0x7F);//数据存入缓冲区，指针加加
        }
    }
}
/*=========================================================================================\n
* @function_name: Uart2_Transmit
* @function_file: Uart2.c
* @描述: UART2发送,中断中调用
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Uart2_Transmit(void)
{
    guc_DyUart2Over = Const_DyUart2Over;//端口超时保护

    if(gs_ComGroup[ComIndex_Uart2].ucPort   == Port_Uart2)
    {   //处于空闲状态或已经处于uart接收状态
        if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart2].ucPos >= gs_ComGroup[ComIndex_Uart2].ucLen)
            {   //发送完毕,初始化通讯控制状态
                //发送完，配置回去
                ComBom_Init(ComIndex_Uart2);//将uart2 端口对应的 COM初始化
                if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
                   ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
                {
                    DelayXms(60);
                    Init_Uart2(0,0);        //初始化红外
                }
                else
                {
                    DelayXms(8);
                    Init_Uart2(3, 0);        //初始化红外
                }
            }else
            {
                Uart2_SendEn();//控制端口设置为发送模式（三线制通讯使用）  //还有未发送数据则写入外设发送缓存
//              if(guc_PrtlTpye==Prtl_645)
//              {
//                  if(gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt<4)
//                  {
//                      SCON2|=(BIT3);
//                      SBUF2=0xfe;
//                      gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt++;
//                  }
//                  else
//                  {
//                      //这里可以做奇偶校验运算
//                      ACC = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos]; //计算校验位
//                      if(P==0)                                        //校验位
//                      {
//                          SCON2&=(~BIT3);
//                      }
//                      else
//                      {
//                          SCON2|=(BIT3);
//                      }
//
//                      SBUF2 = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++];
//                  }
//              }
//              else
                {
                    //这里可以做奇偶校验运算
                    ACC = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos]; //计算校验位
                    SBUF2 = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++]| ((uint8)P)<<7;; 
                }
            }
        }else
        {   //如果在发送中断标记中，进入但是状态不正确，则初始化
            ComBom_Init(ComIndex_Uart2);//将uart2 端口对应的 COM初始化
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart2(0,0);        //初始化红外
            }
            else
            {
                Init_Uart2(3, 0);        //初始化红外
            }
            Uart2_RevEn();
        }
    }
}
