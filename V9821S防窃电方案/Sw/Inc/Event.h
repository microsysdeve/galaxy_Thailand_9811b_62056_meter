 
#ifndef _AP_EVENT_H_
#define _AP_EVENT_H_

#ifndef AP_EVENT_EXT
#define AP_EVENT_EXT extern
#endif


/*******************************************************************************
**ö�ٶ������������
*******************************************************************************/
typedef enum 
{
    E_HourFreeze = 0,                           //Сʱ����
    E_DayFreeze,                                //�춳��
    E_MonthFreeze,                              //�¶���
    E_DSFreeze,                                 //��ʱ����
    E_SQFreeze,                                 //ʱ�����л�����
    E_SDFreeze,                                 //��ʱ�α��л�����
}e_TypeOfFrez;

AP_EVENT_EXT e_TypeOfFrez ge_TypeOfFrezP;       //��Ҫˢ�¶������������
AP_EVENT_EXT e_TypeOfFrez ge_TypeOfFrez;        //���������

/*******************************************************************************
**����ʱ��ṹ��
*******************************************************************************/
typedef struct s_FrzTime
{
  uint8         HourFrzTime;                    //Сʱ����ʱ��
  uint8         DayFrzTime[2];                  //�ն���ʱ��
  uint8         MonthFrzTime[3];                //�¶���ʱ��
  S_TIMEDATA    DSFrzTime;                      //��ʱ����ʱ��
  S_TIMEDATA    SQFrzTime;                      //ʱ�����л�����ʱ��
  S_TIMEDATA    SDFrzTime;                      //��ʱ�α��л�����ʱ��
} S_FRZTIME;
AP_EVENT_EXT S_FRZTIME gs_FrzTime;              //����ʱ��


/*******************************************************************************
**���¼�������
*******************************************************************************/
enum 
{
    ClrType_Power = 1,              //�����µ��¼
    ClrType_BC,                     //���̼�¼
    ClrType_JS,                     //��Уʱ��¼
    ClrType_BG,                     //���Ǽ�¼
    ClrType_POWERR,                 //���Դ���ϼ�¼
#ifdef SQSDPRLOG
    ClrType_RSDBC,                              //����ʱ�α�̼�¼
    ClrType_SQBC,                               //��ʱ����̼�¼
#endif

#ifdef ZXRPRLOG
    ClrType_ZXRBC,                              //�������ձ�̼�¼
#endif

#ifdef YGZHZPRLOG
    ClrType_YGZHBC,                             //���й���Ϸ�ʽ��̼�¼
#endif

#ifdef JSRPRLOG
    ClrType_JSRBC,                              //������ձ�̼�¼
#endif
    ClrType_All,                                //�����м�¼
};

/*******************************************************************************
**���¼��ṹ��
*******************************************************************************/
typedef struct s_ClearEvent
{
  uint32    ID;                                 //���ݱ�ʶ
  uint8     type;                               //��ĳ����¼
} S_CLEAREVENT;

                                                //���¼�����
extern const   S_CLEAREVENT code gs_ClearEvent[];
extern const   uint8 code CntgClrE;           //����
AP_EVENT_EXT uint8 guc_ClearType;               //���¼�������

AP_EVENT_EXT uint32 gui_LHZCoder[2];

/*******************************************************************************
**��������
*******************************************************************************/
uint8 SaveProgramLog(S_FRAMEINFO *s_FrmInfo);
void PowerUpProc(void);
void PowerDnProc(void);
void PowerJL(uint8 type);
void Com_JSJL(uint32 code, S_TIMEDATA* time);
void Com_ClearMeterJL(void);
void Com_ClearEventJL(uint8 type);
void Data_ClearEvent(void);

void CoverOpenLog(void);
void CoverCloseLog(void);

void HurryFrez(void);
void SQFrez(void);
void RSDFrez(void);
void DSFrez(void);
void ZDFrez(void);
void DayFrez(void);
uint8 ZDFreStartTm(void);


#endif

