#ifndef _E2ADDRTAB_H_
#define _E2ADDRTAB_H_


/***********************************E2地址排布定义**************************************/
//以下宏定义数据都为对于的数据在E2中的存储地址,实际数据长度可以从相邻两项的地址差得到,
//或可以查看本表E2排布定义的详细设计文档
/****************************************************************************************/
#define EEP_BAK_LEN     0x0280

//下面是第0页地址
#define EEP_COMADD      0x0000  //通讯地址,6Bytes
#define EEP_METERNO     0x0006  //表号 ,6Bytes
#define EEP_ASSETNO     0x000C  //资产管理编码（ASCII码）
#define EEP_STANDUN     0x002C  //额定电压（ASCII码）
#define EEP_STANDIN     0x0032  //额定电流/基本电流（ASCII码）
#define EEP_MAXIN       0x0038  //最大电流（ASCII码）
                                
//下面是第1页地址                                
#define EEP_YGACCURACY  0x0040  //有功准确度等级（ASCII码）
#define EEP_DBWZXX      0x0044  //电表位置信息
#define EEP_METERMODEL  0x004F  //电表型号（ASCII码）
#define EEP_PDATE       0x0059  //生产日期（ASCII码）
#define EEP_PROTOCOLNO  0x0063  //协议版本号（ASCII码）
#define EEP_KHBH        0x0073  //客户编号（6byte）
#define EEP_YGCALC      0x0079  //有功组合方式特征字
#define EEP_IARBDM      0x007A  //调制型红外光口通信速率特征字
#define EEP_UARTBDM     0x007B  //通信口1通信速率特征字
#define EEP_PROTIME     0x007C  //编程有效时间(自扩)

//下面是第2页地址                                
#define EEP_JBMCKD      0x0080  //校表脉冲宽度(ms) 
#define EEP_METERRUNST1 0x0082  //电表运行状态字1
#define EEP_METERRUNST2 0x0084  //电表运行状态字2
#define EEP_METERRUNST3 0x0086  //电表运行状态字3
#define EEP_METERRUNST4 0x0088  //电表运行状态字4
#define EEP_METERRUNST5 0x008A  //电表运行状态字5
#define EEP_METERRUNST6 0x008C  //电表运行状态字6
#define EEP_METERRUNST7 0x008E  //电表运行状态字7
#define EEP_BSTIME      0x0090  //闭锁时间(自扩)
#define EEP_BSCOUNT     0x0092  //闭锁次数(自扩)
#define EEP_RELAYDLY    0x0093  //跳闸延时时间
#define EEP_RELAYGATE   0x0095  //跳闸电流阀值
//保留1字节
#define EEP_DSFREEZ     0x0099  //定时冻结数据模式字
#define EEP_YDFREEZ     0x009A  //瞬时冻结数据模式字
#define EEP_SSFREEZ     0x009B  //约定冻结数据模式字
#define EEP_ZDFREEZ     0x009C  //整点冻结数据模式字
#define EEP_RFREEZ      0x009D  //日冻结数据模式字
#define EEP_CJBH        0x009E  //厂家编号(ASCII码 32字节) 

//下面是第3页地址

#define EEP_645PASSWD1  0x00C0  //第一级密码
#define EEP_645PASSWD2  0x00C3  //第二级密码
#define EEP_645PASSWD3  0x00C6  //第三级密码
#define EEP_645PASSWD4  0x00C9  //第四级密码
#define EEP_645PASSWD5  0x00CC  //第五级密码
#define EEP_645PASSWD6  0x00CF  //第六级密码
#define EEP_645PASSWD7  0x00D2  //第七级密码
#define EEP_645PASSWD8  0x00D5  //第八级密码
#define EEP_645PASSWD9  0x00D8  //第九级密码
#define EEP_CBR1        0x00DB  //每月第一结算日
#define EEP_CBR2        0x00DD  //每月第二结算日
#define EEP_CBR3        0x00DF  //每月第三结算日
#define EEP_MAX_LX_NUM  0x00E1  //自动循环显示屏数
#define EEP_LXTM        0x00E2  //每屏显示时间
#define EEP_EDEC        0x00E3  //显示电能小数位数
#define EEP_PDEC        0x00E4  //显示功率(最大需量显示位数)
#define EEP_MAX_JX_NUM  0x00E5  //按键循环显示屏数
#define EEP_SHOWERRPOS  0x00E6  //ERR错误字显示位置
#define EEP_POWUPJXTM   0x00E7  //有电下键显显示时间(自扩)
#define EEP_POWDWJXTM   0x00E8  //停电下键显显示时间(自扩)
#define EEP_POWOFFXSTM  0x00E9  //停电显示时间(自扩)
#define EEP_FULLSHOWTM  0x00EB  //全屏显示时间(自扩)
#define EEP_POWUPBGTM   0x00EC  //上电背光亮时间(自扩)
#define EEP_IRBGTM      0x00ED  //红外触发背光亮时间(自扩)
#define EEP_KEYBGTM     0x00EE  //按键触发背光亮时间(自扩)
#define EEP_ESAMERRBGTM 0x00EF  //ESAM错误背光亮时间(自扩)
#define EEP_LEDSFCKTM   0x00F0  //LED自检时间(自扩)
#define EEP_ZDFREEZTM   0x00F1  //整点冻结起始时间
#define EEP_ZDTMJG      0x00F6  //整点冻结时间间隔
#define EEP_DSFRZ       0x00F7  //定时冻结时间
#define EEP_RFREEZTM    0x00FB  //日冻结时间
#define EEP_DBYXTZZ     0x00FD  //电表运行特征字1

//下面是第4页地址
//RTC 参数
#define EEP_RTCTEMPOFFSET 0x0100    //RTC温度常温偏移
#define EEP_RTCFRQOFFSET  0x0101    //RTC晶体常温偏移
#define EEP_RTCDDTEMP     0x0105    //RTC顶点温度
#define EEP_RTCBVAL       0x0106    //RTC的B值
#define EEP_BATCAL        0x011A    //电池校正值
#define EEP_BATCRC        0x011C    //电池校正CRC 
 
//下面是第5页地址 
//校表参数 
#define EEP_JBTOTAL     0x0140  //校表参数首地址
#define EEP_JBBCS       0x0140  //表常数
#define EEP_JBBCDY      0x0142  //标称电压
#define EEP_JBBCDL      0x0144  //标称电流

//下面是第6页地址 
//实时时钟备份
#define EEP_DATETIME    0x0180  //当前时钟备份(自扩)
#define EEP_AUTOCAL     0x0190  //自动校表比对数据

//下面是第7页地址
#define EEP_SQCNT           0x01C0  //年时区数
#define EEP_RSDCNT          0x01C1  //日时段表数
#define EEP_FSDCNT          0x01C2  //费率时段数(每日切换数)
#define EEP_FEECNT          0x01C3  //费率数
#define EEP_SZX             0x01C4  //周休日状态字
#define EEP_ZXSD            0x01C5  //周休日时段表
#define EEP_SFRZTIME        0x01C6  //身份认证时效
#define EEP_JRCNT           0x01C8  //公共假日数(不带年/带年)
#define EEP_SQQHTM          0x01CA  //两套时区表切换时间
#define EEP_RSDQHTM         0x01CF  //两套日时段表切换时间
#define EEP_PDIRTIME        0x01D4  //功率反向事件判定延时时间
#define EEP_PDIRGATE        0x01D5  //功率反向事件有功功率触发下限
                                    //0x01D8保留  
#define EEP_CFSAVECFG       0x01D9  //CF保存配置项（自扩）
#define EEP_CBRCFG          0x01DA  //抄表日补冻配置项（自扩）
#define EEP_DJCFG           0x01DB  //冻结补冻配置项（自扩）
#define EEP_PWLCFG          0x01DC  //密码等级有效配置项（自扩）
#define EEP_SQSDCFG         0x01DE  //时区和时段切换时间设置判别配置项（自扩）
#define EEP_ENSHOWCFG       0x01DF  //电量显示格式配置项（自扩）
#define EEP_TMSHOWCFG       0x01E0  //时间显示格式配置项（自扩）
#define EEP_PWOFFSHOWMDCFG  0x01E1  //停电显示模式配置项（自扩）
#define EEP_JDQCKCFG        0x01E2  //继电器检测方式配置项（自扩）
#define EEP_METERCLRCNT     0x01E3  //电表清零次数（自扩）
#define EEP_METERCLFENGVAL  0x01E4  //电表清零电量阀值（自扩）
#define EEP_PRODUCE         0x01E8  //生产模式状态(自扩)
#define EEP_PRODUCETM       0x01E9  //生产模式退出时间(自扩
#define EEP_MYZTS           0x01EB  //密钥总条数
#define EEP_SWBAKNUM        0x01EC  //软件备案号
#define EEP_MYZTZ           0x01F4  //密钥状态字
#define EEP_OCGATE          0x01F8  //过流事件电流触发下限
#define EEP_OCTIME          0x01FA  //过流事件判定延时时间
#define EEP_SWHPTDLY        0x01FB  //预跳闸（超拉闸）控制电流门限保护延时时间
#define EEP_IRAUTHTM        0x01FD  //红外认证时效
//#define EEP_ZDSBMSZ         0x01F8  //主动上报模式字

//下面是第8页地址
//新增负荷记录
#define EEP_ZDSBMSZ         0x0200  //主动上报模式字
#define EEP_RPTCLRTM        0x0208  //主动上报状态字自动复位延时时间
#define EEP_FHJLMSZ         0x0209  //负荷记录模式字
#define EEP_FHJL1JG         0x020a  //第1类负荷记录间隔时间
#define EEP_FHJL2JG         0x020c  //第2类负荷记录间隔时间
#define EEP_FHJL3JG         0x020e  //第3类负荷记录间隔时间
#define EEP_FHJL4JG         0x0210  //第4类负荷记录间隔时间
#define EEP_FHJLTIME        0x0212  //负荷记录起始时间
#define EEP_FHJLFLAG        0x0216  //负荷记录起始标志

//下面是第9页地址
//以下是当前电量部分
#define EEP_EPS             0x0240  //当前有功电量数据

//下面10~19页是上面的备份地址

//下面是第20~28页地址
#define EEP_1SQ         0x0500  //第一套时区表首地址
#define EEP_1RSDS       (EEP_1SQ+E2_PROTECT_LEN)  //第一套日时段表首地址

#define EEP_1RSDS1      EEP_1RSDS
#define EEP_1RSDS2      (EEP_1RSDS1+E2_PROTECT_LEN)
#define EEP_1RSDS3      (EEP_1RSDS2+E2_PROTECT_LEN)
#define EEP_1RSDS4      (EEP_1RSDS3+E2_PROTECT_LEN)
#define EEP_1RSDS5      (EEP_1RSDS4+E2_PROTECT_LEN)
#define EEP_1RSDS6      (EEP_1RSDS5+E2_PROTECT_LEN)
#define EEP_1RSDS7      (EEP_1RSDS6+E2_PROTECT_LEN)
#define EEP_1RSDS8      (EEP_1RSDS7+E2_PROTECT_LEN)


//下面是第29~37页地址
#define EEP_2SQ         0x0740  //第二套时区表首地址
#define EEP_2RSDS       (EEP_2SQ+E2_PROTECT_LEN)  //第二套日时段表首地址

#define EEP_2RSDS1      EEP_2RSDS
#define EEP_2RSDS2      (EEP_2RSDS1+E2_PROTECT_LEN)
#define EEP_2RSDS3      (EEP_2RSDS2+E2_PROTECT_LEN)
#define EEP_2RSDS4      (EEP_2RSDS3+E2_PROTECT_LEN)
#define EEP_2RSDS5      (EEP_2RSDS4+E2_PROTECT_LEN)
#define EEP_2RSDS6      (EEP_2RSDS5+E2_PROTECT_LEN)
#define EEP_2RSDS7      (EEP_2RSDS6+E2_PROTECT_LEN)
#define EEP_2RSDS8      (EEP_2RSDS7+E2_PROTECT_LEN)

#define TPLEN           (42)  //费率参数长度

//下面是第38页地址
#define EEP_CJRJBB      0x0980  //厂家软件版本号(ASCII码)

//下面是第38页地址
#define EEP_CJYJBB      0x09A0  //厂家硬件版本号(ASCII码)

//下面是第39页地址                                
//下面是轮显表,键显表等
#define EEP_LXTABLE     0x09C0  //轮显表

//下面是第47页地址  
#define EEP_JXTABLE     0x0BC0  //键显表
                                
//下面是第55页地址                                  
#define EEP_JRS         0x0DC0  //公共假日日期表首地址

//下面是第59页地址 
#define EEP_POWDWENERGY     0x0EC0      //掉电保存电量增量
#define EEP_POWDWCURFEE     0x0ED6      //掉电时费率
#define EEP_POWDWCURTIME    0x0ED7      //掉电时时间
#define EEP_POWDWCFCNT      0x0EDD      //掉电时CF数
#define EEP_POWDWCFENERGY   0x0EE7      //掉电时CF对应能量数
#define EEP_PRGLEFTTM       0x0EF1      //编程剩余时间(计时使用)(自扩)
#define EEP_PRODUCELEFTTM   0x0EF3      //厂内时间（计时使用）(自扩)
#define EEP_PW2BSTM         0x0EF5      //2级密码闭锁时间
#define EEP_PW4BSTM         0x0EF7      //4级密码闭锁时间
#define EEP_POWERDWTM       0x0EF9      //停电时间
#define EEP_STRELAY         0x0EFD      //拉合闸状态（自扩）
//#define EEP_ESAMKEYST       0x0EFF      //Esam密钥状态





//月度组合有功有功累计用电量
#define EEP_SYZHLYDL_PT     0x0F00
#define EEP_SYZHLYDLADDR    0x0F01
#define EEP_RPTDATA         0x0F09    //主动上报数据

//下面是第61页空闲
#define EEP_DDLXZ     0x0F40        //大电流修正值

//下面是第62页地址
//历史电量
#define EEP_EPHIS_PT    0x0F80      //历史有功电量存储指针
#define EEP_EPHIS       0x0F81      //历史有功电量在E2的起始地址




//下面是第74页地址
//瞬时冻结
#define EEP_SSDJHIS_PT  0x1280      //瞬时冻结指针存储指针
#define EEP_SSDJHISNO   0x1281      //瞬时冻结总次数
#define EEP_SSDJLHIS    0x1284      //瞬时冻结指针数据在E2中的起始地址

//下面是第77页地址
//约定冻结
//时区
#define EEP_SQDJHIS_PT  0x1340      //时区表切换冻结指针存储指针
#define EEP_SQDJHISNO   0x1341      //时区表切换冻结总次数
#define EEP_SQDJLHIS    0x1344      //时区表切换冻结指针数据在E2中的起始地址

//下面是第79页地址
//时段
#define EEP_RSDJHIS_PT  0x13C0      //日时段表切换冻结指针存储指针
#define EEP_RSDJHISNO   0x13C1      //日时段表切换冻结总次数
#define EEP_RSDJLHIS    0x13C4      //日时段表切换冻结指针数据在E2中的起始地址

//下面是第81页地址
//日冻结
#define EEP_RDJHIS_PT   0x1440      //日冻结指针存储指针
#define EEP_RDJHISNO    0x1441      //日冻结冻结总次数
#define EEP_RDJLHIS     0x1444      //日冻结指针数据在E2中的起始地址

//下面是第129页地址
//整点冻结
#define EEP_ZDDJHIS_PT  0x2040      //整点冻结指针存储指针
#define EEP_ZDDJHISNO   0x2041      //整点冻结总次数
#define EEP_ZDDJLHIS    0x2044      //整点冻结指针数据在E2中的起始地址

//下面是第181页地址
//定时冻结
#define EEP_DSDJHIS_PT  0x2D40      //定时冻结指针存储指针
#define EEP_DSDJHISNO   0x2D41      //定时冻结总次数
#define EEP_DSDJLHIS    0x2D44      //定时冻结指针数据在E2中的起始地址


//下面是第227页地址
//电表清零记录
#define EEP_DBQLETNO    0x38C0      //电表清零总次数
#define EEP_DBQLET_PT   0x38C3      //电表清零记录指针
#define EEP_DBQLET      0x38C4      //电表清零记录在E2中的起始地址

//下面是第230页地址
//事件清零记录
#define EEP_SJQLETNO    0x3980      //事件清零总次数
#define EEP_SJQLET_PT   0x3983      //事件清零记录指针
#define EEP_SJQLET      0x3984      //事件清零记录在E2中的起始地址

//下面是第233页地址
//校时记录
#define EEP_JSETNO      0x3A40      //校时总次数
#define EEP_JSET_PT     0x3A43      //校时记录指针
#define EEP_JSET        0x3A44      //校时记录在E2中的起始地址

//下面是第236页地址
//编程记录
#define EEP_BCETNO      0x3B00      //编程总次数
#define EEP_BCET_PT     0x3B03      //编程记录指针
#define EEP_BCET        0x3B04      //编程记录在E2中的起始地址

//下面是第244页地址
//掉电记录
#define EEP_DDETNO      0x3D00      //掉电总次数
#define EEP_DDET_PT     0x3D03      //掉电记录指针
#define EEP_DDET        0x3D04      //掉电记录在E2中的起始地址

//下面是第246页地址
//开表盖记录
#define EEP_KBGETNO     0x3D80      //开表盖总次数
#define EEP_KBGET_PT    0x3D83      //开表盖记录指针
#define EEP_KBGET       0x3D84      //开表盖记录在E2中的起始地址


//下面是第251页地址
//电源异常事件记录
#define EEP_DYYCNO      0x3EC0      //电源异常事件总次数
#define EEP_DYYC_PT     0x3EC3      //电源异常事件记录指针
#define EEP_DYYC        0x3EC4      //电源异常事件记录在E2中的起始地址


//下面是第255页地址
//时段表编程记录
#ifdef SQSDPRLOG
#define EEP_RSDXGNO     0x3FC0      //日时段更改记录次数            3个字节
#define EEP_RSDXGJL_PT  0x3FC3      //日时段更改记录指针地址        1个字节
#define EEP_RSDXGJL     0x3FC4      //日时段更改记录最近10次首地址  530个字节


//下面是第264页地址
//时区表编程记录
#define EEP_SQXGNO      0x4200      //时区表更改记录次数            3个字节
#define EEP_SQXGJL_PT   0x4203      //时区表更改记录指针地址        1个字节
#define EEP_SQXGJL      0x4204      //时区表更改记录最近10次首地址  530个字节
#endif

////下面是第339页地址
////周休日编程记录
//#ifdef ZXRPRLOG
//#define EEP_ZXRXGNO     0x54C0      //周休日更改记录次数            3个字节
//#define EEP_ZXRXGJL_PT  0x54C3      //周休日更改记录指针地址        1个字节
//#define EEP_ZXRXGJL     0x54C4      //周休日更改记录最近10次首地址  11*10=110个字节
//#endif

//下面是第273页地址
//有功组合字编程记录
#ifdef YGZHZPRLOG
#define EEP_YGZHETNO    0x4440      //有功组合方式字更改记录次数            3个字节有
#define EEP_YGZHET_PT   0x4443      //有功组合方式字更改记录指针地址        1个字节
#define EEP_YGZHET      0x4444      //有功组合方式字更改记录最近10次首地址  11*10=110个字节
#endif

//下面是第275页地址
//结算日编程记录
#ifdef JSRPRLOG
#define EEP_JSRETNO     0x44C0      //结算日更改记录次数            3个字节
#define EEP_JSRET_PT    0x44C3      //结算日更改记录指针地址        1个字节
#define EEP_JSRET       0x44C4      //结算日更改记录最近10次首地址  16*10=160个字节
#endif

//下面是第278页地址
//结算时间记录
#define EEP_JSTIME_PT   0x4580      //结算时间记录指针
#define EEP_JSTIME      0x4581      //结算时间记录起始地址



//下面是第279页地址
//拉闸记录
#define EEP_LZETNO      0x45C0      //拉闸总次数
#define EEP_LZET_PT     0x45C3      //拉闸记录指针
#define EEP_LZET        0x45C4      //拉闸记录在E2中的起始地址


//下面是第282页地址
//合闸记录
#define EEP_HZETNO      0x4680      //合闸总次数
#define EEP_HZET_PT     0x4683      //合闸记录指针
#define EEP_HZET        0x4684      //合闸记录在E2中的起始地址


//下面是第285页地址
//密钥跟新记录
#define EEP_MYGXNO      0x4740      //密钥跟新总次数
#define EEP_MYGX_PT     0x4743      //密钥跟新记录指针
#define EEP_MYGXET      0x4744      //密钥跟新记录在E2中的起始地址


//下面是第288页地址
//负荷开关误动作记录
#define EEP_FHKGNO      0x4800      //负荷开关误动作总次数
#define EEP_FHKG_PT     0x4803      //负荷开关误动作记录指针
#define EEP_FHKGET      0x4804      //负荷开关误动作记录在E2中的起始地址

//下面是第293页地址
//总负荷记录
#define EEP_OCETNO     0x4940      //过流次数
#define EEP_OCETTM     0x4943      //过流累计时间
#define EEP_OCET_PT    0x4946      //过流指针
#define EEP_OCET       0x4947      //过流事件最近1次记录首地址

//下面是第293页地址
//总负荷记录
#define EEP_ZFHETNO     0xFF00//0x4940      //总负荷次数
#define EEP_ZFHET_PT    0xFF00//0x4943      //总负荷指针
#define EEP_ZFHET       0xFF00//0x4945      //总负荷最近1次记录首地址


//下面是第300页地址
//第1类负荷记录
#define EEP_FHET1NO     0x4B00      //第1类负荷次数
#define EEP_FHET1_PT    0x4B03      //第1类负荷指针
#define EEP_FHET1       0x4B05      //第1类负荷最近1次记录首地址


//下面是第346页地址
//第2类负荷记录
#define EEP_FHET2NO     0x5680      //第2类负荷次数
#define EEP_FHET2_PT    0x5683      //第2类负荷指针
#define EEP_FHET2       0x5685      //第2类负荷最近1次记录首地址


//下面是第383页地址
//第3类负荷记录
#define EEP_FHET3NO    0x5FC0      //第3类负荷次数
#define EEP_FHET3_PT   0x5FC3      //第3类负荷指针
#define EEP_FHET3      0x5FC4      //第3类负荷最近1次记录首地址


//下面是第415页地址
//第4类负荷记录
#define EEP_FHET4NO    0x67C0      //第4类负荷次数
#define EEP_FHET4_PT   0x67C3      //第4类负荷指针
#define EEP_FHET4      0x67C5      //第4类负荷最近1次记录首地址


//下面是第474页地址
//密钥密文36字节*32条
#define EEP_MYGX_CMD   0x7680      //密钥密文首地址，36*32=1152字节


//下面是第492页地址
#define EEP_TEST_TIME  0x7B00      //上电时间，7字节+2字节CRC


#endif

