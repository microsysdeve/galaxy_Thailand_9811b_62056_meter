#ifndef _E2ADDRTAB_H_
#define _E2ADDRTAB_H_
/***********************************E2地址排布定义**************************************/
//以下宏定义数据都为对于的数据在E2中的存储地址,实际数据长度可以从相邻两项的地址差得到,
//或可以查看本表E2排布定义的详细设计文档
/****************************************************************************************/
#define EEP_BAK_LEN         0x00C0

//下面是第0~1页地址 
//校表参数 
#define EEP_JBTOTAL         0x0000  //校表参数首地址
#define EEP_JBBCS           0x0000  //表常数
#define EEP_JBBCDY          0x0002  //标称电压
#define EEP_JBBCDL          0x0004  //标称电流

//下面是第1.5页地址
//以下是当前电量部分
#define EEP_EPS             0x0060  //当前有功电量数据

//下面是第2页地址
//#define EEP_COMADD          0x0080  //通讯地址,6Bytes
#define EEP_UARTBDM         0x0086  //通信口1通信速率特征字
#define EEP_MAX_LX_NUM      0x0087  //自动循环显示屏数
#define EEP_LXTM            0x0088  //每屏显示时间
#define EEP_EDEC            0x0089  //显示电能小数位数
#define EEP_PDEC            0x008A  //显示功率(最大需量显示位数)
#define EEP_MAX_JX_NUM      0x008B  //按键循环显示屏数
#define EEP_SHOWERRPOS      0x008C  //ERR错误字显示位置
#define EEP_POWUPJXTM       0x008D  //有电下键显显示时间(自扩)
#define EEP_POWDWJXTM       0x008E  //停电下键显显示时间(自扩)
#define EEP_POWOFFXSTM      0x008F  //停电显示时间(自扩)
#define EEP_FULLSHOWTM      0x0091  //全屏显示时间(自扩)
#define EEP_POWUPBGTM       0x0092  //上电背光亮时间(自扩)
#define EEP_IRBGTM          0x0093  //红外触发背光亮时间(自扩)
#define EEP_KEYBGTM         0x0094  //按键触发背光亮时间(自扩)
#define EEP_ESAMERRBGTM     0x0095  //ESAM错误背光亮时间(自扩)
#define EEP_LEDSFCKTM       0x0096  //LED自检时间(自扩)
#define EEP_CFSAVECFG       0x0097  //CF保存配置项（自扩）
#define EEP_CBRCFG          0x0098  //抄表日补冻配置项（自扩）
#define EEP_DJCFG           0x0099  //冻结补冻配置项（自扩）
#define EEP_PWLCFG          0x009A  //密码等级有效配置项（自扩）
#define EEP_SQSDCFG         0x009C  //时区和时段切换时间设置判别配置项（自扩）
#define EEP_ENSHOWCFG       0x009D  //电量显示格式配置项（自扩）
#define EEP_TMSHOWCFG       0x009E  //时间显示格式配置项（自扩）
#define EEP_PWOFFSHOWMDCFG  0x009F  //停电显示模式配置项（自扩）
#define EEP_JDQCKCFG        0x00A0  //继电器检测方式配置项（自扩）
#define EEP_METERCLRCNT     0x00A1  //电表清零次数（自扩）
#define EEP_METERCLFENGVAL  0x00A2  //电表清零电量阀值（自扩）
//下面3~5页是上面的备份地址

//下面是第6页地址
//显示参数
#define EEP_LXTABLE         0x0180    //循显表    32字节 
#define EEP_JXTABLE         0x0180    //键显表    相同处理

//下面是第7页地址 
#define EEP_MAXDEMAND       0x01C0    //
#define EEP_AUTOCAL         0x01CC    //自动校表比对数据

#define EEP_DATETIME        0x01E0
//下面是第7.5页地址 
#define EEP_POWDWENERGY     0x01E0      //掉电保存电量增量
//#define EEP_POWDWCURFEE     0x0ED6      //掉电时费率
//#define EEP_POWDWCURTIME    0x0ED7      //掉电时时间
//#define EEP_POWDWCFCNT      0x0EDD      //掉电时CF数
//#define EEP_POWDWCFENERGY   0x0EE7      //掉电时CF对应能量数
//#define EEP_PRGLEFTTM       0x0EF1      //编程剩余时间(计时使用)(自扩)
//#define EEP_PRODUCELEFTTM   0x0EF3      //厂内时间（计时使用）(自扩)
//#define EEP_PW2BSTM         0x0EF5      //2级密码闭锁时间
//#define EEP_PW4BSTM         0x0EF7      //4级密码闭锁时间
//#define EEP_POWERDWTM       0x0EF9      //停电时间
//#define EEP_ESAMKEYST       0x0C2E      //Esam密钥状态



     /*                          

//下面是第3页地址
enum  {
 EEP_COMADD =    _Dftset_start_	,//((unsigned short)&FlashInfo.SafeInfo.TRx_Num),  // 0x0080  //通讯地址,6Bytes
  EEP_CBR1  =  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[0][0]),  //     //结算日        0x01
     EEP_CBR2  =  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[1][0]),  //      //结算日        0x02
     EEP_CBR3=  ((unsigned short)&FlashInfo.SafeInfo.FrozeDT[2][0])  //     //结算日        0x03
    }；
    
    */
#define EEP_METERNO     0x0086  //表号 ,6Bytes
#define EEP_645PASSWD1  0x008C  //第0级密码
#define EEP_645PASSWD2  0x008F  //第1级密码
#define EEP_645PASSWD3  0x0092  //第2级密码
#define EEP_645PASSWD4  0x0095  //第3级密码
#define EEP_645PASSWD5  0x0098  //第4级密码


//下面是第6页地址 
//实时时钟备份
//#define EEP_DATETIME    0x0180  //当前时钟备份(自扩)
//#define EEP_AUTOCAL     0x0190  //自动校表比对数据




//下面是第59页地址 
//#define EEP_POWDWENERGY     0x0EC0      //掉电保存电量增量
//#define EEP_POWDWCURFEE     0x0ED6      //掉电时费率
//#define EEP_POWDWCURTIME    0x0ED7      //掉电时时间
//#define EEP_POWDWCFCNT      0x0EDD      //掉电时CF数
//#define EEP_POWDWCFENERGY   0x0EE7      //掉电时CF对应能量数
//#define EEP_PRGLEFTTM       0x0EF1      //编程剩余时间(计时使用)(自扩)
//#define EEP_PRODUCELEFTTM   0x0EF3      //厂内时间（计时使用）(自扩)
//#define EEP_PW2BSTM         0x0EF5      //2级密码闭锁时间
//#define EEP_PW4BSTM         0x0EF7      //4级密码闭锁时间
//#define EEP_POWERDWTM       0x0EF9      //停电时间




#endif

