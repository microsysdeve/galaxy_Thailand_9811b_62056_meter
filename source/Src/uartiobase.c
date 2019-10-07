#include "Include.h"
#include "uartiobase.h"
 

const GS_BaudRate code BaudRateTable_800K[_bpsend_] =
{
   {0xf2,   0x82},  //300
   {0xd9,   0x82},  //600
   {0xfc,   0x82},  //1200
   {0xeb,   0xA2},  //2400
   {0xf5,   0xA2},  //4800
   {0xFb,   0xA2},  //9600
};

const GS_BaudRate code BaudRateTable_3DO2M[_bpsend_] =
{
   {0xc7,   0x82},  //300
   {0xe4,   0x82},  //600
   {0xf2,   0x82},  //1200
   {0xd5,   0x22},  //2400
   {0xd5,   0xa2},  //4800
   {0xeb,   0xa2},  //9600
};

  char code *BaudRateTable[_PLL_END_] =
{
   (char code *)0,
   (char code *)&(BaudRateTable_800K[0]),
   (char code *)0,
   (char code *)0,
   (char code *)&(BaudRateTable_3DO2M[0]),
};
 

 char          cCalbitNum ( unsigned char ctemp)
  {
      char      i ,j;     
      for ( j =0,i = 0 ;i < 8 ;i++,ctemp>>=1)
        j +=(ctemp&1)?1:0;
    return j;
  }
  
char            c7bitParity_Set(unsigned char *cData , enum PARITYLIST cparty)
{
        unsigned char ctemp = (cCalbitNum (*cData))&1;                        
        (*cData) &=0x7f;
          
      switch (cparty)
      {
      case _Parity_Null_ :        
          return  SUCCESS;
          
      case _Parity_Even_ :
          if ( 0 == ctemp )                   
                  return SUCCESS;
            break;
            
      case  _Parity_Odd_ :
        if ( ctemp )                  
                return SUCCESS;
            break;
      }
        return  FAIL;
      
}


char           c7bitParity_Get(unsigned char cData , enum PARITYLIST cparty)
{
  
       unsigned char ctemp ;                        
        (cData) &=0x7f;
        ctemp = (cCalbitNum (cData))&1;                        
          
      switch (cparty)
      {
      case _Parity_Null_ :        
          return  SUCCESS;
          
      case _Parity_Even_ :          
          if (  ctemp )   
              (cData) |=0x80;           
            break;
            
      case  _Parity_Odd_ :
        if ( 0 == ctemp )            
              (cData) |=0x80;                           
            break;
      }
        return cData; 
      
}


 
