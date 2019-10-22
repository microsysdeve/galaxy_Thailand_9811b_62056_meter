#include "Include.h"
#include "streamio.h"
#include "uartiobase.h"
//变量声明
#define Uart2_CtrIoIdle()  {} 
enum   ENUMZBCONTROL
{
    _zb_exist =0,  //0, 带有38kHz 载波；1,不带有载波。 
    _zb_noexti,
};

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
void Init_Uart2(uint8 ucBode)
{    
  unsigned char j;
  unsigned long i;
  char  stemp[10];
  
_UartInit(ucBode,TMOD2,TCON2,TL21,TH21,SCON2); 
 
    P2OE &= ~BIT5;                      //Uart4发送口输出允许
    P2IE &= ~BIT5;                      //Uart4发送口输入禁止
    P2OE |= BIT4;                       //Uart4接收口输出禁止
    P2IE |= BIT4;                       //Uart4接收口输入允许
    P24FS=2;                            //P2.0配置成RXD
    P25FS=2;                            //P2.1配置成TXD
    
    Txd2FS = _zb_noexti;
    ExInt2IE|=BIT0;
    ExInt2IE|=BIT1;
    EIE|=BIT0;
    //====================
   /*
    SCON2&=(~BIT4);
     gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //设置数据包接收超时时间
gs_ComGroup[ComIndex_Uart2].ucLen =0;
    gs_ComGroup[ComIndex_Uart2].ucStt  = ComStt_Idle;
      
 
                while (1)
                {
                  for ( j =0;j<128;j++)
                  {
                   SLPWDT();               //800k喂狗
                   SCON2 &=~BIT1;         
                  //_EvenMod(j,SCON4)  ;
                   //_SendOper(j,SBUF4);
                   SCON2|=(BIT3);
                   SBUF2 =   c7bitParity_Get(j,  _Parity_Even_);
       for ( i =0 ;i < 1000;i++)
       {
            if (SCON2 & BIT1)
            goto a2;
          asm("nop"); asm("nop"); asm("nop");
        }       
                  a2:
                }
                
                }
                  
a1:    
                SCON2|=(BIT4);
                SCON2&=~BIT0;
                j =0;
                EA=1;
                while (1)
                {
                     SLPWDT();
                     continue;
                        if (  SCON2 & BIT0)
                       {
                              stemp[j++] = SBUF2;
                              if ( j>=sizeof(stemp))
                                  j =0;
                             SCON2&=~BIT0;
                       }
                        
                }
   */
    
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
  #ifndef _ComUSE645_
    guc_DyUart2Over--;
    if(0x00== guc_DyUart2Over)
    {
        Init_Uart2(guc_485Bode);                   // 初始化模拟串口
        ComBom_Init(ComIndex_Uart2);    //将uart6 端口对应的 COM初始化
    }

    if(guc_BodeDely>0)                  //波特率切换
    {
        guc_BodeDely--;
        if(guc_BodeDely==0)
        {
            gui_RefreshEvent|=flgEtPara_Bode;
        }
    }
    #endif
}

void Uart2_Receiveio( unsigned char cData )
{
//    uint8 temp,temp1;
    guc_DyUart2Over = Const_DyUart2Over;//端口超时保护
    //这里可以做奇偶校验判断

    //处于空闲状态或已经处于uart接收状态
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //设置数据包接收超时时间

    if((gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle) 
      ||(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv))            //这个判断是防止发送的时候有接收中断进入的可能
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //判断 com中的buf是否溢出
        {
            //防止缓存溢出
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = cData ;//数据存入缓冲区，指针加加
        }
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

  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_IR_Chanel_]);
    uint8 temp,temp1;
    //guc_DyUart2Over = Const_DyUart2Over;//端口超时保护
    //这里可以做奇偶校验判断
 
#ifdef _ComUSE645_
    ACC=SBUF2;                          //ACC 奇校验
    temp=P;
    temp1=(SCON2>>2)&BIT0;              //偶校验

    if(temp!=temp1)                     //奇偶校验位不正确
    {
        return;
    }
    stream_rece_fun_645( usartcomp,SBUF2);
    if (usartcomp->bEventRec645) {
				//do {
			//		unitp->INTE.reg = unitp->INTE.reg & 0xff80;//_DISABLE_USART0_RECE_INT_);
			//	} while (unitp->INTE.reg & 0x7f);
			} else {
			//	if (flag & 0x4) {
			//		// iReRece =0x66;
			//		flag &= 0xb;
			//		goto a1;
			//	}

			}
#else
     unsigned char ctemp = SBUF2;
     if ( SUCCESS == c7bitParity_Set(&ctemp ,_Parity_Even_))
        Uart2_Receiveio(ctemp);      
      return ;
  stream_rece_fun ( usartcomp,SBUF2);
#endif
  
    return ;
#ifdef DEL
    //处于空闲状态或已经处于uart接收状态
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //设置数据包接收超时时间


    if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle)        //当前是空闲的状态的话，判断是否是帧头68
    {

        if(SBUF2==COMHEAD)               //接受到起始字节
        {
            gs_ComGroup[ComIndex_Uart2].ucStt = ComStt_Recv;
        }
    }
 
    //处于空闲状态或已经处于uart接收状态
    if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv)            //这个判断是防止发送的时候有接收中断进入的可能
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //判断 com中的buf是否溢出
        {                                                           //防止缓存溢出
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = SBUF2;//数据存入缓冲区，指针加加

            if(gs_ComGroup[ComIndex_Uart2].ucLen>COMINITLEN)
            {
                if(gs_ComGroup[ComIndex_Uart2].ucBuf[7]!=COMHEAD)           //如果第7个不是68返回错误
                {
                    gs_ComGroup[ComIndex_Uart2].ucStt=ComStt_Idle;
                }else if(gs_ComGroup[ComIndex_Uart2].ucLen>=(gs_ComGroup[ComIndex_Uart2].ucBuf[9]+COMINITLEN+2))   //长度符合要求
                {
                    if(SBUF2==COMTAIL)
                    {
                        guc_ComSendDy=3;                                        //延时30ms发送
                        gs_ComGroup[ComIndex_Uart2].ucStt=ComStt_WaitProc;
                        gui_SystemEvent |= flgEtGlb_NeedPrtclChk;               // 设置标志
                        gs_ComGroup[ComIndex_Uart2].ucRecvTmr=0;
                        //关闭接收
                    }
                }
            }
        }
    }
#endif
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
  unsigned char ctemp;
 
  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_IR_Chanel_]);
 #ifdef  _ComUSE645_
  if (usartcomp->cStatu < _end_sendcom) 
  {
	ctemp  = stream_send_fun_645(usartcomp);
        _BitYX(SCON2,ctemp) ;   
        SBUF2 = ctemp;
	resetWdt();
        if ((0 == --(usartcomp->cHead)) && ( _workNormal_ == WorkState_ReCheck(_cIolist )))
          usartcomp->cStatu++;
	} else {
			do {
				usartcomp->cSilence = 1;
		} while (1 != usartcomp->cSilence);
	}

	return;
#else
  
  

  // guc_DyUart4Over = Const_DyUart4Over;//端口超时保护

    if(gs_ComGroup[ComIndex_Uart2].ucPort   == Port_Uart2)
    {   //处于空闲状态或已经处于uart接收状态
        if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart2].ucPos >= gs_ComGroup[ComIndex_Uart2].ucLen)
            {   //发送完毕,初始化通讯控制状态
            #ifdef RS485_TWOLINE
                Uart2_CtrIoIdle();
            #else
                Uart2_RevEn();
            #endif
                ComBom_Init(ComIndex_Uart2);//将uart4 端口对应的 COM初始化
            }else
            {
//          //这里可以做奇偶校验运算
              SCON2|=(BIT3);
              SBUF2 =  c7bitParity_Get(gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++],_Parity_Even_);                   
               
            #ifdef RS485_TWOLINE
                Uart2_CtrIoIdle();
            #else
                Uart2_SendEn();//控制端口设置为发送模式（三线制通讯使用）  //还有未发送数据则写入外设发送缓存
            #endif

            }
        }else
        {   //如果在发送中断标记中，进入但是状态不正确，则初始化
            ComBom_Init(ComIndex_Uart2);//将uart4 端口对应的 COM初始化
        #ifdef RS485_TWOLINE
        //    Uart2_CtrIoIdle();
        #else
            Uart2_RevEn();
        #endif
        }
    }
#endif
    
}

