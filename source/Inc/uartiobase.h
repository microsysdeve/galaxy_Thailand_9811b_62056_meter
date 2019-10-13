#ifndef _uartiobase_hpp_
#define _uartiobase_hpp_
 
enum PARITYLIST
{
  _Parity_Null_ =0,
  _Parity_Even_,
  _Parity_Odd_,
  _Parity_End_,
};
  typedef struct 
{
    uint8   THValue;
    uint8   Type;              //T1M和SMOD的取值
}GS_BaudRate;

#define                 _Parity_Set(SCONx)              { SCONx |=(BIT3);}
#define                 _Parity_Res(SCONx)              { SCONx&=(~BIT3);}

#define    _BitYX(SReg,SendData)   {ACC=SendData ; if(P==0) { SReg&=(~BIT3); }  else{SReg|=(BIT3);}}
#define       _EvenMod( cData , SCONx)    { ACC = cData;if( 0 == P) SCONx&=(~BIT3);else SCONx|=(BIT3);}
#define       _OddMod( cData , SCONx)    { ACC = cData;if (P)   SCONx&=(~BIT3);else SCONx|=(BIT3);}
#define       _SendOper( cData,SBUFx)   {SBUFx = cData;}
   
extern const GS_BaudRate code BaudRateTable_800K[_bpsend_] ;

extern const GS_BaudRate code BaudRateTable_3DO2M[_bpsend_] ;

 char          cCalbitNum ( unsigned char ctemp);
  
char            c7bitParity_Set(unsigned char *cData , enum PARITYLIST cparty);

char           c7bitParity_Get(unsigned char cData , enum PARITYLIST cparty);


#define _UartInit(bpsno,TMODx,TCONx,TLx,THx,SCONx) {GS_BaudRate code *BaudRateTable=(PLL_800K==guc_PllSta)?(GS_BaudRate code *)BaudRateTable_800K:(GS_BaudRate code *)BaudRateTable_3DO2M; if(bpsno>=_bpsend_) bpsno=_bps2400_; TMODx = 0x20;TCONx= BaudRateTable[bpsno].Type; TLx=THx= BaudRateTable[bpsno].THValue;SCONx=0xD0;}   


#endif
