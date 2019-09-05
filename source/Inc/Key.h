#ifndef __KEY_H__
    #define __KEY_H__


#ifndef KEY_EXT
    #define KEY_EXT extern
#else 
    #define KEY_SELF
#endif

#define KeyNums     2
enum
{
  UpKey=0,
  PrKey,
};
enum
{
    TmOff=0,
    TmOn,
};

enum 
{
    KeyRls=0,
    KeyDw,
    KeyDWLong,
};

typedef struct
{
    uint8  Status;       //����״̬�����£��ͷ�
    uint8  TmStu;        //��ʱ��״̬
    uint16 DlyCnt;       //��ʱ����
    uint16 KeyThd;       //��������ֵ
    uint16 LgKeyThd;     //����������ֵ
}KEYCTR;

KEY_EXT KEYCTR  idata gs_KeyCtr[KeyNums];

KEY_EXT uint8       guc_DyBgLed;        // ������ʱ���ƼĴ���
//KEY_EXT uint8       guc_DyLed;          // LED�ƿ���
KEY_EXT uint16      gui_DyPgmOut;
KEY_EXT uint16      gui_DyProDmOut;
//KEY_EXT uint8       guc_PrOutTm;        //��̱������˳�ʱ��
//KEY_EXT uint8   guc_PowOffKeyTmCnt;

KEY_EXT uint8   guc_PrKeyNewDown;       // ��̼��Ƿ��°���
KEY_EXT uint8   guc_CoverStatus;        // ���״̬
//KEY_EXT uint8   guc_PoweroffCoverJl;    // �е����Ƿ񿪱��
KEY_EXT uint8   guc_CoverKeyDwCnt;
KEY_EXT uint8   guc_CoverKeyUpCnt;





#define Const_DyBLed   20

void KeyScan(void);
void LongKeyProc(void);
void KeyProc(void);
void Key_Init(void);
void CoverScanSleep(void);
//void CoverKeyScan(void);
void KeyDispSleepDown(void);
void KeyPgm_DyOut(void);


#endif
