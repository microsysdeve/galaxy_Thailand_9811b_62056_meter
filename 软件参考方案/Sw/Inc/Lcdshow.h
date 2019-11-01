
#ifndef _AP_LCDSHOW_H_
#define _AP_LCDSHOW_H_

#ifndef AP_LCDSHOW_EXT
#define AP_LCDSHOW_EXT extern
#endif

 
AP_LCDSHOW_EXT uint8 guc_ShowStCom;
 
enum
{
    Const_DispMode_LX=0,        //����
    Const_DispMode_JX,          //����
    Const_DispMode_TX,          //ͣ��
};
 
typedef struct s_DispStt
{
    uint8   ucTmr;          //��ʾ�Ķ�ʱʱ�䣬��ر���ʾʱ��
    uint8   ucIndex;        //��ǰ��ʾ��ı��е����,���������Ի��Ǽ��Ե�
}S_DISPSTT;

AP_LCDSHOW_EXT S_DISPSTT       gs_DispStt ;//״̬ת�����õ��Ľṹ
void ShowMask(void);
void ShowSecondProc(void);
void ShowRefresh(void);
#endif