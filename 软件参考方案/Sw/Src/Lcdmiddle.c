#define LCDMIDDLEEXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: Disp_Numb
* @function_file: Lcdmiddle.c
* @����:
*
*
* @����:
* @param:data1  ��Ҫ��ʾ�����ݣ�ʮ�����ƴ���
* @param:type  ��ʾ��ʽ�����������ʾ�����ӿ�
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Disp_Numb(uint32 data1, uint32 type)
{
    uint8 tmpdata;
    uint8 tmptype;
    uint8 tmpdisph;//tmpdispl;
    uint8x *p;
    uint8x *q;

    for(uint8 i=0; i<8; i++)
    {
        tmpdata = (uint8)(data1 & 0x0F);        //ȡ���һλ
        tmptype = (uint8)(type & 0x0F);
        data1 >>= 4;                            //���ݴ���
        type >>= 4;

        tmpdisph = NUMTABLE[tmpdata];         //��ȡ��ʾ����
 

        p = (uint8x *)(&LCDM0 + NumAddr[i]);              //������ʾ����
        *p &= N_x;                           //������������λ
 
        switch(tmptype)                         //���ݲ�����ɢת
        {
            case 0:
                *p |= tmpdisph;         //��ʾ����
                break;
           case 1:
               *p |= LCD_CHARL_r;
              // *q |= LCD_CHARL_G;      //��ʾ"R"��
                break;
            case 2:                     //��ʾ'E'
                *p |= LCD_CHARH_E;
                //*q |= LCD_CHARL_L;
               break;
            case 3:                     //��ʾ'A'
                *p |= LCD_CHARH_A;
               // *q |= LCD_CHARL_r;
               break;
            case 4:                     //��ʾ'n'
               *p |= LCD_CHARL_D;
                //*q |= LCD_CHARL_n;
                break;
//            case 5:                     //��ʾ��ĸ'o'
//                *p |= LCD_CHARH_o;
//                *q |= LCD_CHARL_o;
//                break;
//            case 6: //��ʾ��ĸ��E��
//                *p |= LCD_CHARH_E;
//                *q |= LCD_CHARL_E;
//                break;
//            case 7: //��ʾ��ĸ��C��
//                *p |= LCD_CHARH_C;
//                *q |= LCD_CHARL_C;
//                break;
            case 0x0a:
                *p |= 0x00;             //����
                *q |= 0x00;
                break;
            default:
                break;
        }
    }
}
/*=========================================================================================\n
* @function_name: Disp_String
* @function_file: Lcdmiddle.c
* @����:
*
*
* @����:
* @param:para1
* @param:para2
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
//void Disp_String(uint16 para)
//{
//    uint16 tmp;
//    uint32 data1;
//    uint8 i;
//    uint8* p;
//
//    tmp = para&0x00ff;                             // ȡ�����ĵ�8λ
//    if(tmp>Len_LCDChinaCode)
//    {
//        tmp=0;
//    }
//    data1 = LCD_ChinaCode[tmp];                     // �ɴ˲��ȡ����Ҫ��ʾ������
//    for(i=0; i<Len_ChineseTable; i++)
//    {//ChineseTable��ʹ���ǣ�ÿһ����ֵ�Ķ�Ӧһ��λ��λ�ö��壬��5λ������ʾ����ĵ�ַƫ������
//     //����λ��ʾ�ڶ�Ӧ��ַ�ֽڵĵڼ�λ
//        p = ( guc_LCDRAM + ((ChineseTable[i])>>3) );// �ҵ��Դ��ַ
//        if(data1 & 0x0001)                          //
//        {
//            *p |= BIT8MAP[ChineseTable[i] & 0x07];      //
//        }                                           //
//        else                                        //
//        {
//            *p &= ~BIT8MAP[ChineseTable[i] & 0x07];     //
//        }
//        data1 >>= 1;                                    //
//    }
//
//    tmp = (para&0xff00)>>8;                             // ȡ�����ĵ�8λ
//    //����������8��ʾ
//    data1 = Strnum[tmp];
//    for(i=0;i<Len_Strnum;i++)
//    {
//        p = ( guc_LCDRAM + ((BITStrnum[i])>>3) );           // �ҵ��Դ��ַ
//        if(data1 & 0x0001)
//        {
//            *p |= BIT8MAP[BITStrnum[i] & 0x07];             //
//        }else
//        {
//            *p &= ~BIT8MAP[BITStrnum[i] & 0x07];            //
//        }
//        data1 >>= 1;
//    }
//}

/*=========================================================================================\n
* @function_name: Disp_UnitPoint
* @function_file: Lcdmiddle.c
* @����:
*
*
* @����:
* @param:para
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
//void Disp_UnitPoint(uint16 para)                        //
//{
//    uint16 tmp;
//    uint16 data1;
//    uint8 i;
//    uint8* p;
//
//    // ��λ���ŵ���ʾ
//    tmp = para & 0x000F;                                //�Ͱ��ֽ����ڷ�����ʾ����
//    data1 = UnitTable[tmp];                             // �ɴ˲��ȡ����Ҫ��ʾ������
//    for(i=0; i<Len_UnitBit; i++)
//    {
//        p = ( guc_LCDRAM + ((UnitBitTable[i])>>3) );    // �ҵ��Դ��ַ
//        if(data1 & 0x0001)
//        {
//            *p |= BIT8MAP[UnitBitTable[i] & 0x07];      //
//        }else
//        {
//            *p &= ~BIT8MAP[UnitBitTable[i] & 0x07];     //
//        }
//        data1 >>= 1;
//    }
//
//    // С�������ʾ
//    data1 = para>>4;            //�Ͱ��ֽ����ڷ�����ʾ����
//    for(i=0; i<PointLen; i++)
//    {
//        p = ( guc_LCDRAM + ((PointTable[i])>>3) );          // �ҵ��Դ��ַ
//        if(data1 & 0x0001)
//        {
//            *p |= BIT8MAP[PointTable[i] & 0x07];//
//        }else
//        {
//            *p &= ~BIT8MAP[PointTable[i] & 0x07];//
//        }
//        data1 >>= 1;
//    }
//}

/*=========================================================================================\n
* @function_name: Disp_State
* @function_file: Lcdmiddle.c
* @����:
*
*
* @����:
* @param:data1
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
//void Disp_State(uint32 data1)
//{
//    uint8 i,*p;
//    for(i=0; i<St_Len; i++)
//    {
//        p = ( guc_LCDRAM + ((St_Table[i])>>3) );       // �ҵ��Դ��ַ
//        if(data1 & 0x0001)
//        {
//            *p |= BIT8MAP[St_Table[i] & 0x07];
//        }
//        else
//        {
//            *p &= ~BIT8MAP[St_Table[i] & 0x07];
//        }
//        data1 >>= 1;
//    }
//}




