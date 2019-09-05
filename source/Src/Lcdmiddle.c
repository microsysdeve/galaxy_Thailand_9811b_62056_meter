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
     uint8 i;
    uint8 tmpdata;
    uint8 tmptype;
    uint8 tmpdisph,tmpdispl;
    uint8 *p;
    uint8 *q;

    for(i=0; i<6; i++)
    {
        tmpdata = (uint8)(data1&0x0f);        //ȡ���һλ
        tmptype = (uint8)(type&0x0f);
       data1 >>= 4;                            //���ݴ���
       type >>= 4;
        
        tmpdisph = NUMTABLE_1H[tmpdata];          //��ȡ��λ��ʾ����
        tmpdispl = NUMTABLE_1L[tmpdata];         //��ȡ��λ��ʾ����

        p = guc_LCDRAM + NumAddr[i*2];          //������ʾ����
        q = guc_LCDRAM + NumAddr[i*2+1];        //������ʾ����
        *p &= N_Resd1H;                             //������������λ
        *q &= N_Resd1L;                          //������������λ


        switch(tmptype)                         //���ݲ�����ɢת
        {
            case 0:
                *p |= tmpdisph;         //��ʾ����
                *q |= tmpdispl;         //��ʾ����
                break;
            case 1:
                *p |= LCD_CHAR1H_G;
                *q |= LCD_CHAR1L_G;      //��ʾ"-"��
                break;
            case 2:                     //��ʾ'L'
                *p |= LCD_CHAR1H_L;
                *q |= LCD_CHAR1L_L;
                break;
            case 3:                     //��ʾ'r'
                *p |= LCD_CHAR1H_r;
                *q |= LCD_CHAR1L_r;
                break;
            case 4:                     //��ʾ'n'
                *p |= LCD_CHAR1H_n;
                *q |= LCD_CHAR1L_n;
                break;
            case 5:                     //��ʾ��ĸ'o'
                *p |= LCD_CHAR1H_o;
                *q |= LCD_CHAR1L_o;
                break;
            case 6: //��ʾ��ĸ��E��
                *p |= LCD_CHAR1H_E;
                *q |= LCD_CHAR1L_E;
                break;
            case 7: //��ʾ��ĸ��C��
                *p |= LCD_CHAR1H_C;
                *q |= LCD_CHAR1L_C;
                break;
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
* @function_name: Disp_UnitPoint
* @function_file: Lcdmiddle.c
* @����:
*
*
* @����:
* @param:��4λ�Ƿ���  ��12λ��С����
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Disp_UnitPoint(uint8 unitpoint)                        //
{
    uint16 tmpdata;
    uint8 i;
    uint8* p;

    // ��λ���ŵ���ʾ
    tmpdata = unitpoint & 0x0F;                                //�Ͱ��ֽ����ڷ�����ʾ����
    if(tmpdata>=UnitTableLen)                                //��һ�ŵķ���
    {
        tmpdata=0;
    }
    tmpdata = UnitTable[tmpdata];                             // �ɴ˲��ȡ����Ҫ��ʾ������
    for(i=0; i<Len_UnitBit; i++)
    {
        p = ( guc_LCDRAM + ((UnitBitTable[i])>>3) );    // �ҵ��Դ��ַ
        if(tmpdata & 0x0001)
        {
            *p |= BIT8MAP[UnitBitTable[i] & 0x07];      //
        }else
        {
            *p &= ~BIT8MAP[UnitBitTable[i] & 0x07];     //
        }
        tmpdata >>= 1;
    }

    // С�������ʾ
    tmpdata = (unitpoint>>4);            //�Ͱ��ֽ����ڷ�����ʾ����
    if(tmpdata>=PointLen)                     
    {
        tmpdata=0;
    }
    tmpdata = PointTable[tmpdata];                             // �ɴ˲��ȡ����Ҫ��ʾ������
    for(i=0; i<Len_PointBit; i++)
    {
        p = ( guc_LCDRAM + ((PointBitTable[i])>>3) );          // �ҵ��Դ��ַ
        if(tmpdata & 0x0001)
        {
            *p |= BIT8MAP[PointBitTable[i] & 0x07];//
        }else
        {
            *p &= ~BIT8MAP[PointBitTable[i] & 0x07];//
        }
        tmpdata >>= 1;
    }
}

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
void Disp_State(uint32 data1)
{
    uint8 i,*p;

    for(i=0; i<St_Len; i++)
    {
        p = ( guc_LCDRAM + ((St_Table[i])>>3) );       // �ҵ��Դ��ַ
        if(data1 & 0x0001)
        {
            *p |= BIT8MAP[St_Table[i] & 0x07];
        }
        else
        {
            *p &= ~BIT8MAP[St_Table[i] & 0x07];
        }
        data1 >>= 1;
    }
}




