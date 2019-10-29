#ifndef _main_protect_hpp_
#define _main_protect_hpp_

#define MSCPROT_PROTECT_ON	( 0x00 )	///< Set the write protect.
#define MSCPROT_PROTECT_OFF     ( 0x96 )	///< Remove the write protect.
void protectMisc(unsigned char protectCode) ;
void protectMisc_init(void);


#define _Interrupt_AppDisable()           protectMisc( MSCPROT_PROTECT_OFF )
#define _Interrupt_AppEnable()           protectMisc( MSCPROT_PROTECT_ON )

#define  _Interrupt_Disable_Total()         { IE =0;protectMisc_init();}
#endif
