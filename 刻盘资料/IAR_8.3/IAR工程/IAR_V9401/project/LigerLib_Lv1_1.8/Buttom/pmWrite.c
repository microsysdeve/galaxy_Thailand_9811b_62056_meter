//--------------------------------------
//---- pm access functions
//--------------------------------------
#ifndef xdata
    #define xdata __xdata
#endif
void W_Buff(unsigned char dat_h, unsigned long dat_l)
{
    volatile unsigned char __xdata *p;
    
    p  = (volatile unsigned char xdata *)0x10e8;
    *p = (unsigned char)(dat_l);
    p  = (volatile unsigned char xdata *)0x10e9;
    *p = (unsigned char)(dat_l>>8);
    p  = (volatile unsigned char xdata *)0x10ea;
    *p = (unsigned char)(dat_l>>16);
    p  = (volatile unsigned char xdata *)0x10eb;
    *p = (unsigned char)(dat_l>>24);
    p  = (volatile unsigned char xdata *)0x10ec;
    *p = (unsigned char)(dat_h);
}



