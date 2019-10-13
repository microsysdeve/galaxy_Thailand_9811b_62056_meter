
#include "Include.h"
#include "PubSet.h"
#include "main_protect.h"

volatile unsigned char	cProtStatu  ;
/** *************************************************************************
 * protectMisc function.
 *
 * @brief	Misc register write protect mode setting.
 *
 * @param	protectCode
 *	@li @c		MSCPROT_OFF	remove the write protect.
 *	@li @c		other		write protect.
 ************************************************************************* */

void protectMisc_init(void)
{
  cProtStatu =0;
}

void protectMisc(unsigned char protectCode)
{
    switch ( protectCode)
    {
        case   MSCPROT_PROTECT_ON:
		if ( cProtStatu )
			cProtStatu-=1;                  
		if ( !cProtStatu )
		{		
                 INTERRUPT_ENABLE();
                }
		else
                {
                    debug_break(_debug_errno_turonntstate_instate_);
                  NOP_ASM();  //MSCPROT = protectCode; //return ;
                }			
        break;
          
    case MSCPROT_PROTECT_OFF :
      if ( 0 == cProtStatu )
      {
		NOP_ASM(); //MSCPROT = protectCode;
		cProtStatu++;
		if ( cProtStatu>2 )
                {
			NOP_ASM();
                        debug_break(  _debug_errno_turoffintstate_instate_);
                }
        }                 
	 INTERRUPT_DISABLE();
    
default :
    }
}
 