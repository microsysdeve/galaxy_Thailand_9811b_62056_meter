#define LCDMIDDLEEXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: Disp_Numb
* @function_file: Lcdmiddle.c
* @描述:
*
*
* @参数:
* @param:data1  需要显示的数据，十六进制传送
* @param:type  显示方式，具体参照显示驱动接口
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
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
        tmpdata = (uint8)(data1&0x0f);        //取最后一位
        tmptype = (uint8)(type&0x0f);
       data1 >>= 4;                            //数据处理
       type >>= 4;
        
        tmpdisph = NUMTABLE_1H[tmpdata];          //获取高位显示编码
        tmpdispl = NUMTABLE_1L[tmpdata];         //获取低位显示编码

        p = guc_LCDRAM + NumAddr[i*2];          //数字显示缓存
        q = guc_LCDRAM + NumAddr[i*2+1];        //数字显示缓存
        *p &= N_Resd1H;                             //保留不是数字位
        *q &= N_Resd1L;                          //保留不是数字位


        switch(tmptype)                         //根据参数二散转
        {
            case 0:
                *p |= tmpdisph;         //显示数据
                *q |= tmpdispl;         //显示数据
                break;
            case 1:
                *p |= LCD_CHAR1H_G;
                *q |= LCD_CHAR1L_G;      //显示"-"号
                break;
            case 2:                     //显示'L'
                *p |= LCD_CHAR1H_L;
                *q |= LCD_CHAR1L_L;
                break;
            case 3:                     //显示'r'
                *p |= LCD_CHAR1H_r;
                *q |= LCD_CHAR1L_r;
                break;
            case 4:                     //显示'n'
                *p |= LCD_CHAR1H_n;
                *q |= LCD_CHAR1L_n;
                break;
            case 5:                     //显示字母'o'
                *p |= LCD_CHAR1H_o;
                *q |= LCD_CHAR1L_o;
                break;
            case 6: //显示字母‘E’
                *p |= LCD_CHAR1H_E;
                *q |= LCD_CHAR1L_E;
                break;
            case 7: //显示字母‘C’
                *p |= LCD_CHAR1H_C;
                *q |= LCD_CHAR1L_C;
                break;
            case 0x0a:
                *p |= 0x00;             //消隐
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
* @描述:
*
*
* @参数:
* @param:低4位是符号  高12位是小数点
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Disp_UnitPoint(uint8 unitpoint)                        //
{
    uint16 tmpdata;
    uint8 i;
    uint8* p;

    // 单位符号的显示
    tmpdata = unitpoint & 0x0F;                                //低半字节用于符号显示定义
    if(tmpdata>=UnitTableLen)                                //第一排的符号
    {
        tmpdata=0;
    }
    tmpdata = UnitTable[tmpdata];                             // 由此查表取出需要显示的数据
    for(i=0; i<Len_UnitBit; i++)
    {
        p = ( guc_LCDRAM + ((UnitBitTable[i])>>3) );    // 找到显存地址
        if(tmpdata & 0x0001)
        {
            *p |= BIT8MAP[UnitBitTable[i] & 0x07];      //
        }else
        {
            *p &= ~BIT8MAP[UnitBitTable[i] & 0x07];     //
        }
        tmpdata >>= 1;
    }

    // 小数点的显示
    tmpdata = (unitpoint>>4);            //低半字节用于符号显示定义
    if(tmpdata>=PointLen)                     
    {
        tmpdata=0;
    }
    tmpdata = PointTable[tmpdata];                             // 由此查表取出需要显示的数据
    for(i=0; i<Len_PointBit; i++)
    {
        p = ( guc_LCDRAM + ((PointBitTable[i])>>3) );          // 找到显存地址
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
* @描述:
*
*
* @参数:
* @param:data1
* @返回:
* @作者:   lwb (2012-03-15)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Disp_State(uint32 data1)
{
    uint8 i,*p;

    for(i=0; i<St_Len; i++)
    {
        p = ( guc_LCDRAM + ((St_Table[i])>>3) );       // 找到显存地址
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




