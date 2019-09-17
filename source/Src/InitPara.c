#define INIT_EXT
#include"Include.h"


enum   ENUMDEF 
{
       _VolK_      =    0x5F6290b2,
      _Curr_L_K_     =    0x389d9999,
       _Curr_N_K_     =  0x389d9999,
         _PowerL_K_      =            0x84f431,
         _PowerN_K_       =           0x84f431,//803d04,
         _PluseConst_ =1200,
         _StandVol_= 230,
         _Ib_= 5,
         _HFCONST_L_ =0x17c6254,//0x1d5584a ,
         _HFCONST_N_ =0x17c6254,//0x1d5584a ,
         _HFCONST800K_ =0x2336761b ,
         _QDConst_L_= 0xfec164,
         _QDConst_N_= 0xfec164,
};

#define      _format4(n)      (n&0xff),((n>>8)&0xff),((n>>16)&0xff),((n>>24)&0xff)
#define      _format2(n)      (n&0xff),((n>>8)&0xff)


const uint8 code InitPara0[sizeof(S_JBPM)-2]=
{
    _format2(1200),//0xb0,0x04,     //表常数 1200
    _format2( _StandVol_*100),//0xd8,0x59,     //标称电压 240.00
    _format2( _Ib_ *1000) ,// 0x88,0x13,     //标称电流 5.000
    _format4(_HFCONST_L_),//0x4a,0x58,0xd5,0x01,//有功能量脉冲门限值
    _format4(_HFCONST800K_),//0x1B,0x76,0x36,0x23,//800K常数计量门限
    
    _format4(_QDConst_L_),//0x00,0x1B,0xB7,0x00,//有功能量潜动门限值
    _format4(_HFCONST_N_),//0x4a,0x58,0xd5,0x01,//I2常数门限
    0x00,0x00,0x00,0x00,//有功比差值
    0x00,0x00,0x00,0x00,//无功比差值
     _format4(0x03130463),//   0x00,0x00,0x00,0x00,//电压有效值比差
    0x00,0x00,0x00,0x00,//通道I1电流有效值比差  
    0x00,0x00,0x00,0x00,//通道I2电流有效值比差  
    0x00,0x00,0x00,0x00,//有功功率二次补偿值
    0x00,0x00,0x00,0x00,//无功功率二次补偿值
    0x00,               //通道I1角差校正值
    0x00,               //通道I2角差校正值
    _format4(_PowerL_K_),// 0x45,0x0c,0xa4,0x00,//功率1显示比例系数k
    _format4(_PowerN_K_),// 0x45,0x0c,0xa4,0x00,//功率2显示比例系数k
    _format4(_VolK_) ,//     0x85,0xA3,0xB3,0x65,//电压显示比例系数k
    _format4(_Curr_L_K_) ,//电流I1显示比例系数k
    _format4(_Curr_N_K_) ,//电流I2显示比例系数k 与I1倍数关系
    0x00,0x00,0x00,0x00,//通道I1_800K电流有效值比差0xC29AAE81
    0x00,0x00,0x00,0x00,//通道I2_800K电流有效值比差0xBE7E151F 0xBE85787B
    (((0) << 6)| ((2)<<3) | ((2)<<0)),// 0x0C,               //通道增益
    //CRC
};

 
const uint8 code InitPara1[]=
{
    0x11,0x11,0x11,0x11,0x11,0x11,  //通讯地址
    0x04,               //通信口速率 红外1200
    0x05,               //自动循环显示屏数
    0x05,               //轮显显示时间
    0x02,               //显示电能小数位数
    0x04,               //显示功率小数位数
    0x05,               //按键循环显示屏数
    0x1a,               //错误显示屏位置
    0x3c,               //有电下键显显示时间(自扩)
    0x1E,               //停电下键显显示时间(自扩)
    0x00,0x00,          //停电显示时间(自扩)
    0x05,               //上电全屏时间（自扩）
    0x05,               //上电开背光时间(自扩)
    0x14,               //红外触发背光时间(自扩)
    0x3C,               //按键触发背光时间(自扩)
    0x05,               //ESAM错误字显示时间（背光亮时间）(自扩)
    0x02,               //跳闸灯自检时间(自扩)
    0x50,//CF保存配置项（自扩）
    0x00,//抄表日补冻配置项（自扩）
    0x00,//冻结补冻配置项（自扩）
    0x00,0x00,//密码等级有效配置项（自扩）
    0x00,//时区和时段切换时间设置判断方式（自扩）
    0x02,//电量显示格式参数配置项（自扩）
    0x00,//时间显示格式参数配置项（自扩）
    0x00,//停电显示模式参数配置项（自扩）
    0x00,//继电器检测方式参数配置项（自扩）
    0x00,//电表清零次数（自扩）
    0x00,0x00,0x00,0x00,//电表清零电量阀值（自扩）
};

const uint8 code InitPara2[]=
{
    0x00,0x00,0x00,0x00,0x00,       //按显1  当前总电量
    0x00,0x01,0x01,0x02,0x00,       //电压
    0x00,0x01,0x02,0x02,0x00,       //电流
    0x01,0x00,0x80,0x02,0x00,       //零线电流
//    0x01,0x01,0x00,0x04,0x00,       //按显2  日期
//    0x02,0x01,0x00,0x04,0x00,       //按显3  时间
//    0x02,0x04,0x00,0x04,0x01,       //按显4  表号低8位
//    0x02,0x04,0x00,0x04,0x00,       //按显5  表号高4位
//    0x01,0x00,0x00,0x00,0x00,       //循显6  上月总电量
};

//const uint8 code InitPara3[]=
//{
//    0x00,0x00,0x00,0x00,0x00,       //总电量
//    0x00,0x00,0x01,0x01,0x00,       //最大需量
//    0x00,0x01,0x01,0x02,0x00,       //电压
//    0x00,0x01,0x02,0x02,0x00,       //电流   
//};
const uint8 code InitADK[]=
{
    0x11,0x11,0x11,0x11,0x11,0x11,  //通讯地址
    0x01,0x00,0x00,0x00,0x00,0x00,  //表号
        
    0x11,0x11,0x11,     //第0级密码
    0x11,0x11,0x11,     //第1级密码
    0x00,0x00,0x00,     //第2级密码
    0x00,0x00,0x00,     //第3级密码  无用
    0x00,0x00,0x00,     //第4级密码
        
    0,0,'V','0','3','2',    //额定电压
    0,0,0,'A','0','1',        //额定电流
    0,0,0,'A','0','6',      //最大电流
    0x00,0x16,0x00,         //脉冲常数
};

const uint8 code InitFwVer[]=
{
    //RDKWMNW60V1.0
 //RDKDDS155-9821YWG.1
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    '2','.','V','X','S','-','1', 
    '2','8','9','V','-','5',
    '5','1','S','D','D',
    //厂家软件版本号
};


const uint8 code InitHwVer[]=
{
    //V9811-M-YWGV1.0
   //DDS155-9821
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
    'X','S','-','1',
    '2','8','9','V','-','5',
    '5','1','S','D','D',   
       //厂家硬件版本号
};

typedef struct 
{
    const uint8 code* E2ParaTabAdrr;   //E2参数表格地址
    uint16 E2Adrr;          //E2地址
    uint8  uclen;           //数据长度
}GS_E2PARA;

const  GS_E2PARA code PageCRCAddr[]=
{
    {InitPara0,     EEP_JBTOTAL,    sizeof(InitPara0),  },
    {InitADK,       EEP_COMADD,     sizeof(InitADK)-21, },   
//    {InitPara2,     EEP_LXTABLE,    sizeof(InitPara2),  },
    //{InitPara3,     EEP_JXTABLE,    sizeof(InitPara3),  },
};

/*=========================================================================================\n
* @function_name: InitE2Data
* @function_file: InitPara.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-04)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void InitE2Data(void)
{
    Word16 CRC;
    ClRCRCWord(guc_InitWd);
    //校表参数单独判断,首先判读E2中的CRC是否正确，如果正确，则不需要初始化
    BE_ReadP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));
    if(Uint8_To_Uint16(XDATA_RAMZONE+sizeof(S_JBPM)-2) != do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2))
    {
        CLRWDT();               //喂狗
        FCpyTMem(XDATA_RAMZONE, InitPara0, sizeof(S_JBPM)-2);                   //拷贝Flash数据到RAM中
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //拷贝CRC到RAM中
        BE_WriteP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));                    //写入到E2中
    }
    
    for(uint8 i=1;i<sizeof(PageCRCAddr)/sizeof(GS_E2PARA);i++)
    {
        CLRWDT();                           //喂狗
        MemSet(XDATA_RAMZONE,0x00,64);
        FCpyTMem(XDATA_RAMZONE,PageCRCAddr[i].E2ParaTabAdrr,PageCRCAddr[i].uclen);//拷贝Flash数据到RAM中
        CRC.word=do_CRC(XDATA_RAMZONE,62);
        XDATA_RAMZONE[62]=CRC.byte[0];
        XDATA_RAMZONE[63]=CRC.byte[1];                          //拷贝CRC到RAM中
        BE_WriteP(PageCRCAddr[i].E2Adrr,XDATA_RAMZONE,64);      //写入到E2中
    }    
    
    SetCRCWord(guc_ClearWd);
    Data_ClearMeter();                                          //电表清零
    gui_RefreshEvent|=(flgEtPara_EnyBottom+flgEtPara_Config+flgEtPara_Show);
}
/*=========================================================================================\n
* @function_name: InitE2Data
* @function_file: InitPara.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-04)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void E2DataChk(void)
{
    Word16 CRC;
    
    //校表参数单独判断,首先判读E2中的CRC是否正确，如果正确，则不需要初始化
    BE_ReadP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));
    if(Uint8_To_Uint16(XDATA_RAMZONE+sizeof(S_JBPM)-2) != do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2))
    {
        CLRWDT();               //喂狗
        FCpyTMem(XDATA_RAMZONE, InitPara0, sizeof(S_JBPM)-2);                   //拷贝Flash数据到RAM中
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //拷贝CRC到RAM中
        BE_WriteP(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));                    //写入到E2中
//        for(uint8 i=1;i<sizeof(PageCRCAddr)/sizeof(GS_E2PARA);i++)
//        {
//            CLRWDT();                           //喂狗
//            MemSet(XDATA_RAMZONE,0x00,64);
//            FCpyTMem(XDATA_RAMZONE,PageCRCAddr[i].E2ParaTabAdrr,PageCRCAddr[i].uclen);//拷贝Flash数据到RAM中
//            CRC.word=do_CRC(XDATA_RAMZONE,62);
//            XDATA_RAMZONE[62]=CRC.byte[0];
//            XDATA_RAMZONE[63]=CRC.byte[1];                          //拷贝CRC到RAM中
//            BE_WriteP(PageCRCAddr[i].E2Adrr,XDATA_RAMZONE,64);      //写入到E2中
//        }
    }      
    CLRWDT();
//    gui_RefreshEvent|=(flgEtPara_Config+flgEtPara_Show);
}