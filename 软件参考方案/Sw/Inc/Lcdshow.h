
#ifndef _AP_LCDSHOW_H_
#define _AP_LCDSHOW_H_

#ifndef AP_LCDSHOW_EXT
#define AP_LCDSHOW_EXT extern
#endif

 
AP_LCDSHOW_EXT uint8 guc_ShowStCom;
 
enum
{
    Const_DispMode_LX=0,        //轮显
    Const_DispMode_JX,          //键显
    Const_DispMode_TX,          //停显
};
 
typedef struct s_DispStt
{
    uint8   ucTmr;          //显示的定时时间，或关闭显示时间
    uint8   ucIndex;        //当前显示查的表中的序号,不管是轮显或是键显等
}S_DISPSTT;

AP_LCDSHOW_EXT S_DISPSTT       gs_DispStt ;//状态转换中用到的结构
void ShowMask(void);
void ShowSecondProc(void);
void ShowRefresh(void);
#endif