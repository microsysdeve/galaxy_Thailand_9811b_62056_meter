#ifndef _E2ADDRTAB_H_
#define _E2ADDRTAB_H_


/***********************************E2地址排布定义**************************************/
//以下宏定义数据都为对于的数据在E2中的存储地址,实际数据长度可以从相邻两项的地址差得到,
//或可以查看本表E2排布定义的详细设计文档
/****************************************************************************************/
#define EEP_BAK_LEN       0x0180

//第0页
#define EEP_COMADD        0x0000  //表号
#define EEP_XLZQ          0x0007  //需量周期
#define EEP_FHQXZQ        0x0008  //负荷曲线周期
#define EEP_MANUDATE      0x0009  //生产日期
#define EEP_JBDATE        0x000c  //校表日期
#define EEP_FEEMDATE      0x000f  //费率修改日期
#define EEP_RDPASSWORD    0x0014  //密码1
#define EEP_WRPASSWORD    0x001c  //密码2
#define EEP_CBR1          0x0024  //第1抄表日
#define EEP_CBR2          0x0026  //第2抄表日
#define EEP_CBR3          0x0028  //第3抄表日
#define EEP_BATTERYSTAT   0x002a  //电池状态

//第1页
#define EEP_WORK_FEE_TIME 0x0040  //工作日费率时间
#define EEP_SAT_FEE_TIME  0x0050  //星期六费率时间
#define EEP_SUN_FEE_TIME  0x0060  //星期日费率时间

//第2页
#define EEP_WORK_FEE      0x0080  //工作日费率
#define EEP_SAT_FEE       0x0088  //星期六费率
#define EEP_SUN_FEE       0x0090  //星期日费率

//第3页
#define EEP_JBTOTAL       0x00C0  //校表参数首地址
#define EEP_JBBCS         0x00C0  //表常数
#define EEP_JBBCDY        0x00C2  //标称电压
#define EEP_JBBCDL        0x00C4  //标称电流


//第4页
#define EEP_EPS             0x0100  //当前电量数据


//第12页
#define EEP_EPHIS_PT        0x0300  //历史电量指针
#define EEP_EPHIS           0x0301  //历史有功电量在E2的起始地址


//第16页
#define EEP_XULIANGHIS_PT   0x0400  //历史需量指针
#define EEP_XULIANGHIS      0x0401  //历史需量首地址

//第18页
#define EEP_XGEVENT_PT      0x0480  //开线盖记录指针
#define EEP_XGEVENT         0x0481
//第20页
#define EEP_BGEVENT_PT      0x0500  //开表盖记录指针
#define EEP_BGEVENT         0x0501

//掉电记录 第22页
#define EEP_DDETNO          0x0580      //掉电总次数
#define EEP_DDET_PT         0x0582      //掉电记录指针
#define EEP_DDET            0x0583      //掉电记录在E2中的起始地址


#define EEP_POWDWENERGY     0x0640




#endif

