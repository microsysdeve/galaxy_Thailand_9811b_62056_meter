/*
 * lcd_1.h
 *
 *  Created on: 2015-6-5
 *      Author: Pangxiao
 */
#ifndef _ht1908001p00_hpp_
#define _ht1908001p00_hpp_


#define		_SP_				0xFF
#define		_BLINK_BIT_			1
#define		_DISP_DIGIT_		2


enum {
   _DISP_OVER_  =87,//(1+    10)*8 -1;
	_DISP_AT_JIAN_ = 16,//0,
	_DISP_AT_FENG_ = 17,//1,
	_DISP_JIETI_1_ = _DISP_OVER_ +62,//NULL
	_DISP_L_ = 56,//3,
	_DISP_N_ = 57,//4,
	_DISP_NEG_ = 48,//NULL
	_DISP_AT_GU_ = 49,//NULL
	_DISP_AT_PING_ = 11,//7,
	_DISP_SHANG_ = 50,//NULL
	_DISP_10_1_ = 51,//NULL
	
	_DISP_7_A_ = 63,//NULL,
	_DISP_7_F_ = 82,//NULL
	_DISP_7_E_ =  _DISP_OVER_ +1,//NULL
	_DISP_7_D_ = _DISP_OVER_ +2,//NULL
	_DISP_LO_1_ = _DISP_OVER_ +3,//NULL
	_DISP_PULSE_ = _DISP_OVER_ +4,//NULL
	_DISP_ST_1_ = _DISP_OVER_ +5,//NULL
	_DISP_ST_3_ = _DISP_OVER_ +6,//NULL
	_DISP_8_A_ = _DISP_OVER_ +7,//NULL
	_DISP_8_F_ = _DISP_OVER_ +8,//NULL
	_DISP_8_E_ = _DISP_OVER_ +9,//NULL
	_DISP_8_D_ = _DISP_OVER_ +10,//NULL
	_DISP_JIETI_2_ = _DISP_OVER_ +11,//NULL
	_DISP_DANGQIAN_ = _DISP_OVER_ +12,//NULL
	_DISP_ST_2_ = _DISP_OVER_ +13,//NULL
	_DISP_ST_4_ = _DISP_OVER_ +14,//NULL
	_DISP_8_B_ = _DISP_OVER_ +15,//NULL
	_DISP_8_G_ = _DISP_OVER_ +16,//NULL
	_DISP_8_C_ = _DISP_OVER_ +17,//NULL
	_DISP_NOP_1_ = _DISP_OVER_ +18,//NULL
	
	_DISP_9_F_ =80,// 32,
	_DISP_9_E_ =81,// 33,
	_DISP_PUB_ = _DISP_OVER_ +19,//NULL
	_DISP_7_B_ = _DISP_OVER_ +20,//NULL
	_DISP_7_G_ = _DISP_OVER_ +21,//NULL
	_DISP_7_C_ = _DISP_OVER_ +22,//NULL
	_DISP_NOP_2_ = _DISP_OVER_ +23,//NULL
	_DISP_LO_2_ = _DISP_OVER_ +24,//NULL
	_DISP_9_A_ = 73,//40,
	_DISP_9_G_ = 74,//41,
	_DISP_9_D_ = 75,//42,
	_DISP_6_A_ = 76,//43,
	_DISP_6_F_ = 77,//44,
	_DISP_6_E_ = 78,//45,
	_DISP_6_D_ = 79,//46,
	_DISP_BAT1_ =28,// 47,
	_DISP_9_B_ = 68,//48,
	_DISP_9_C_ = 69,//49,
	_DISP_JIETI_ = _DISP_OVER_ +25,//NULL
	_DISP_6_B_ = 70,//51,
	_DISP_6_G_ = 71,//52,
	_DISP_6_C_ = 72,//53,
	_DISP_NOP_3_ = _DISP_OVER_ +26,//NULL
	_DISP_PROG_ = _DISP_OVER_ +27,//NULL
	_DISP_ZUHE_ = _DISP_OVER_ +28,//NULL
	_DISP_YUE_ = _DISP_OVER_ +29,//NULL
	_DISP_TOUZHI_H_ = _DISP_OVER_ +30,//NULL
	_DISP_5_A_ = 64,//59,
	_DISP_5_F_ = 65,//60,
	_DISP_5_E_ = 66,//61,
	_DISP_5_D_ = 67,//62,
	_DISP_LOCK_ = _DISP_OVER_ +31,//NULL
	_DISP_ZHENG_ = _DISP_OVER_ +32,//NULL
	_DISP_YONG_ = _DISP_OVER_ +33,//NULL
	_DISP_DOT_4_2_ = 61,//66,
	_DISP_5_B_ = 58,//67,
	_DISP_5_G_ = 59,//68,
	_DISP_5_C_ = 60,//69,
	_DISP_DOT_4_ = 62,//70,
	_DISP_DUKA_ = _DISP_OVER_ +34,//NULL
	_DISP_FAN_ = _DISP_OVER_ +35,//NULL
	_DISP_LIANG_ = _DISP_OVER_ +36,//NULL
	_DISP_DIAN_ = _DISP_OVER_ +37,//NULL
	_DISP_4_A_ = 52,//75,
	_DISP_4_F_ = 53,//76,
	_DISP_4_E_ = 54,//77,
	_DISP_4_D_ = 55,//78,
	_DISP_ZHONG_ = _DISP_OVER_ +38,//NULL
	_DISP_XIANG_ = _DISP_OVER_ +39,//NULL
	_DISP_ZONG_ = _DISP_OVER_ +40,//NULL
	_DISP_JIA_ = _DISP_OVER_ +41,//NULL
	_DISP_4_B_ = 42,//83,
	_DISP_4_G_ = 43,//84,
	_DISP_4_C_ = 44,//85,
	_DISP_DOT_3_ =45,// 86,
	_DISP_CHENGGONG_ = _DISP_OVER_ +42,//NULL
	_DISP_JIAN_ = _DISP_OVER_ +43,//NULL
	_DISP_TM_SHI_ = _DISP_OVER_ +44,//NULL
	_DISP_HU_ = _DISP_OVER_ +45,//NULL
	_DISP_3_A_ =36,// 91,
	_DISP_3_F_ = 37,//92,
	_DISP_3_E_ = 38,//93,
	_DISP_3_D_ = 39,//94,
	_DISP_SHIBAI_ = _DISP_OVER_ +46,//NULL
	_DISP_FENG_ = _DISP_OVER_ +47,//NULL
	_DISP_TM_JIAN_ =  _DISP_OVER_ +48,//NULL
	_DISP_DOT_2_2_ = 33,//98,
	_DISP_3_B_ = 30,//99,
	_DISP_3_G_ = 31,//100,
	_DISP_3_C_ = 32,//101,
	_DISP_DOT_2_ =  34,//102,
	_DISP_GOUDIAN_ = _DISP_OVER_ +49,//NULL
	_DISP_PING_ = _DISP_OVER_ +50,//NULL
	_DISP_GU_ = _DISP_OVER_ +51,//NULL
	_DISP_DUAN_ = _DISP_OVER_ +52,//NULL
	_DISP_2_A_ = 24,//131,
	_DISP_2_F_ = 25,//132,
	_DISP_2_E_ = 26,//133,
	_DISP_2_D_ =27,// 134,
	_DISP_TIAOZHA_ = _DISP_OVER_ +53,//NULL
	_DISP_SHENGYU_ = _DISP_OVER_ +54,//NULL
	_DISP_CHANGSHU_ = _DISP_OVER_ +55,//NULL
	_DISP_JIN_E_ = _DISP_OVER_ +56,//NULL
	_DISP_2_B_ = 18,//123, 
	_DISP_2_G_ = 19,//124, 
	_DISP_2_C_ = 20,//125, 
	_DISP_DOT_1_ = 21,//126, 
	_DISP_TOUZHI_ = _DISP_OVER_ +57,//NULL 
	_DISP_HAO_ = _DISP_OVER_ +58,//NULL
	_DISP_BIAO_ = _DISP_OVER_ +59,//NULL
	_DISP_COS_ =10,// 114,
	_DISP_1_A_ = 12,//115,
	_DISP_1_F_ = 13,//116,
	_DISP_1_E_ = 14,//117,
	_DISP_1_D_ = 15,//118,
	_DISP_TUNJI_ = _DISP_OVER_ +60,//NULL
	_DISP_YUAN_ = _DISP_OVER_ +61,//NULL
	_DISP_A_ = 3,//105,
	_DISP_V_ = 9,//106,
	_DISP_1_B_ = 6,//107,
	_DISP_1_G_ = 7,//108,
	_DISP_1_C_ = 8,//109,
	_DISP_KW_ = 4,//110,
	_DISP_H_ = 5,//111,
        
         _DISP_DELTA_ALM_  = 22,//  三角形，中间感叹号
         _DISP_DELTA_OPEN_ = 23,//开合盖标志
          _DISP_TOTAL_ =40 , 
        _DISP_DELTA_EXPORT_ = 29,//
        _DISP_DELTA_IMPORT_ = 35,//
           _DISP_COMM_ = 41,//  通讯标志  
              _DISP_FOWARE_ = 46,//  ->正向箭头
              _DISP_REWARE_ = 47,//  ->返向箭头  
               _DISP_MD_ = 1,
               _DISP_tel_ = 0,  // 最右下角
               _DISP_TRX_ = _DISP_COMM_,//26, 
      //   _DISP_OVER_  =(1+    _LCDMEnd_)*8 -1;
	 _DISP_REVERSE_ = _DISP_REWARE_ ,
         
};
#define 		_DIS_VOLSET_  		0
#endif /* LCD_1_H_ */
