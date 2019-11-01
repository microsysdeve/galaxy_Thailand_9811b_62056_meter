/*************************************************************************************

	文件类型：芯片信息头文件，不可修改
	文件作用：定义芯片底层信息以方便外部调用管理芯片资源
	修改权限：芯片维护级
	文件相关：可提供硬件资源配置调用，另提供了8位和16位的位定义
	
	创 建 人：GeminiKQ
	创建日期：2006.12.20
	修改记录：

**************************************************************************************/
#ifndef	_ChipDefine_H_
#define	_ChipDefine_H_
/* basic function define */

#ifndef xdata
 #define xdata __xdata 
#endif

/* another normal use */
#define		BIT0		0x01
#define		BIT1		0x02
#define		BIT2		0x04
#define		BIT3		0x08
#define		BIT4		0x10
#define		BIT5		0x20
#define		BIT6		0x40
#define		BIT7		0x80

#define		NONE	0
//=======================================================================
//======================     CrtlGA    ==================================
//=======================================================================
/* bit of CrtlGA */
#define		ADCGA0		BIT0
#define		ADCGA1		BIT1
#define		ADCGA2		BIT2
#define		REFGA0		BIT4
#define		REFGA1		BIT5
//=======================================================================
//======================     CrtlGB    ==================================
//=======================================================================
/* bit of CrtlGB */
#define		ADCGB0		BIT0
#define		ADCGB1		BIT1
#define		ADCGB2		BIT2
#define		REFGB0		BIT4
#define		REFGB1		BIT5
//=======================================================================
//======================     CrtlGU    ==================================
//=======================================================================
/* bit of CrtlGU */
#define		ADCGU		BIT0
#define		REFGU0		BIT4
#define		REFGU1		BIT5
//=======================================================================
//======================     CrtlGM    ==================================
//=======================================================================
/* bit of CrtlGM */
#define		ADCGM		BIT0
#define		REFGM0		BIT4
#define		REFGM1		BIT5
//=======================================================================
//======================     CrtlIAT    =================================
//=======================================================================
/* bit of CrtlIAT */
#define		ADIT1A0		BIT0
#define		ADIT1A1		BIT1
#define		ADIT2A0		BIT2
#define		ADIT2A1		BIT3
#define		ADQITA		BIT4
#define		REFBITA		BIT5
#define		REFGITA		BIT6
#define		ADRSTA		BIT7
//=======================================================================
//======================     CrtlIAD    =================================
//=======================================================================
/* bit of CrtlIAD */
#define		DITA0		BIT0
#define		DITA1		BIT1
#define		DITHERA0	BIT4
#define		DITHERA1	BIT5
//=======================================================================
//======================     CrtlIBT    =================================
//=======================================================================
/* bit of CrtlIBT */
#define		ADIT1B0		BIT0
#define		ADIT1B1		BIT1
#define		ADIT2B0		BIT2
#define		ADIT2B1		BIT3
#define		ADQITB		BIT4
#define		REFBITB		BIT5
#define		REFGITB		BIT6
#define		ADRSTB		BIT7
//=======================================================================
//======================     CrtlIBD    =================================
//=======================================================================
/* bit of CrtlIBD */
#define		DITB0		BIT0
#define		DITB1		BIT1
#define		DITHERB0	BIT4
#define		DITHERB1	BIT5
#define		CURRSEL0	BIT6
#define		CURRSEL1	BIT7
//=======================================================================
//======================     CrtlIUT    =================================
//=======================================================================
/* bit of CrtlIUT */
#define		ADIT1U0		BIT0
#define		ADIT1U1		BIT1
#define		ADIT2U0		BIT2
#define		ADIT2U1		BIT3
#define		ADQITU		BIT4
#define		REFBITU		BIT5
#define		REFGITU		BIT6
#define		ADRSTU		BIT7
//=======================================================================
//======================     CrtlIMT    =================================
//=======================================================================
/* bit of CrtlIMT */
#define		ADIT1M0		BIT0
#define		ADIT1M1		BIT1
#define		ADIT2M0		BIT2
#define		ADIT2M1		BIT3
#define		ADQITM		BIT4
#define		REFBITM		BIT5
#define		REFGITM		BIT6
#define		ADRSTM		BIT7
//=======================================================================
//======================     CrtlBGP    =================================
//=======================================================================
/* bit of CrtlBGP */
#define		BGPSTART	BIT0
#define		BGPCHOP		BIT1
#define		RTRIM0		BIT4
#define		RTRIM1		BIT5
#define		RTRIM2		BIT6
#define		CURRLP		BIT7
#define		ADPOWER		(CURRLP+RTRIM2+RTRIM1)
//=======================================================================
//======================     CrtlPow    =================================
//=======================================================================
/* bit of CrtlPow */
#define		MAES0		BIT0
#define		MAES1		BIT1
#define		TEMSENPDN	BIT4
#define		BATSENPDN	BIT5
#define		BATSENPDN2	BIT6
#define		PRPDN		BIT7
#define     TEMSEN  	(TEMSENPDN+MAES0)
#define     BATSEN  	(BATSENPDN+MAES1)
#define     BATSEN2 	(BATSENPDN2+MAES1)
#define     OTHER   	(MAES1+MAES0)

//=======================================================================
//======================     CrtlADC    =================================
//=======================================================================
/* bit of CrtlADC */
#define		ADCAPDN		BIT0
#define		ADCBPDN		BIT1
#define		ADCUPDN		BIT2
#define		ADCMPDN		BIT3
#define		ADCLKEXT	BIT6
#define		CLKOSEL		BIT7
//=======================================================================
//======================     CrtlCry    =================================
//=======================================================================
/* bit of CrtlCry */
#define		XTRIM0		BIT0
#define		XTRIM1		BIT1
#define		XTRIM2		BIT2
#define		XEASY_N		BIT3
#define		REST0		BIT4
#define		REST1		BIT5
#define		REST2		BIT6
#define		P3V		    BIT7
//=======================================================================
//======================     CrtlLDO    =================================
//=======================================================================
/* bit of CrtlLDO */
#define		LDOVSEL0	BIT0
#define		LDOVSEL1	BIT1
#define		LDOLPN		BIT2
#define		LDOMOD		BIT3
#define		P3V5		BIT4
#define		DGEN		BIT7
//=======================================================================
//======================     CrtlCLK    =================================
//=======================================================================
/* bit of CrtlCLK */
#define		MCUCLKSEL0	BIT0
#define		MCUCLKSEL1	BIT1
#define		ADCLKSEL0	BIT2
#define		ADCLKSEL1	BIT3
#define		PLLSEL		BIT4
#define		BGPPDN  	BIT5
#define		PLLPDN  	BIT6
#define		BGPPDNB		BIT7

#define		PLL8		(PLLPDN+BGPPDN)
#define		PLL16		(PLLPDN+BGPPDN+MCUCLKSEL0+ADCLKSEL0)
#define		PLL32		(PLLPDN+BGPPDN+MCUCLKSEL1+ADCLKSEL1)
#define		PLL64		(PLLPDN+BGPPDN+MCUCLKSEL0+MCUCLKSEL1+ADCLKSEL0+ADCLKSEL1)
//=======================================================================
//======================     CrtlPLL    =================================
//=======================================================================
/* bit of CrtlPLL */
#define		PLLIB0		BIT0
#define		PLLIB1		BIT1
#define		XTALINV		BIT2
#define		MCUINV		BIT3
#define		PLLLF		BIT4


#endif
