
struct PMReadBuff//40位数据
{
	unsigned char return_data_h;		// 高8 位
	unsigned long return_data_l;		// 低32 位
};

void R_Buff(struct PMReadBuff  *pPMReadBuff)
{
    volatile unsigned char __xdata *p;
    unsigned char d0, d1, d2, d3, d4;
    
    p  = (volatile unsigned char __xdata *)0x10ec;
    d4 = *p;
    p  = (volatile unsigned char __xdata *)0x10eb;
    d3 = *p;
    p  = (volatile unsigned char __xdata *)0x10ea;
    d2 = *p;
    p  = (volatile unsigned char __xdata *)0x10e9;
    d1 = *p;
    p  = (volatile unsigned char __xdata *)0x10e8;
    d0 = *p;

    pPMReadBuff->return_data_l = ((unsigned long)d3<<24)|((unsigned long)d2<<16)|((unsigned long)d1<<8)|d0;
    pPMReadBuff->return_data_h = d4;
}
