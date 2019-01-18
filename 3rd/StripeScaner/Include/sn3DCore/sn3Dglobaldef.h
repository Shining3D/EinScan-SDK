// ====================================================================================================================================================
// File name:	sn3Dglobaldef.h
//
// Copyright (C), 2009-2011, Shining 3D Tech. Co., Ltd.
//
// Description:	全局定义。包括类型、数学常量、宏运算、返回值代码等的定义。所有的自写代码都应该先包含此文件，并优先使用本文件中的定义。编码中如需使用本文件
//              中没有的定义，应当先申请加入到本文件中去，以方便今后的使用。
// 
// Histroy:		
// ======================================================================================================================================================

#ifndef __sn3Dglobaldef_H__
#define __sn3Dglobaldef_H__

// ======================================================================================================================================================
// 类型
typedef	unsigned char byte;
typedef short int16;            // 16 bit integer
typedef unsigned short uint16;  // 16 bit unsigned integer
typedef int int32;              // 32 bit integer
typedef unsigned int uint;      // 32 bit unsigned integer
typedef uint uint32;            // 32 bit unsigned integer
typedef long long int64;

//=====================================================================================================================================================
// UNICODE
#include <tchar.h>
#ifndef tstring
	#ifdef _UNICODE
		#define  tstring wstring
	#else
		#define  tstring string
	#endif
#endif
#ifdef _UNICODE
#define  tistringstream wistringstream
#define  tostringstream wostringstream
#define  tcout			wcout
#else
#define  tistringstream istringstream
#define  tostringstream ostringstream
#define  tcout			cout
#endif
// ======================================================================================================================================================
// 数学常量
const double ZERO_TOLERANCE = 1.0e-12;                  // 浮点零比较值，小于此值认为浮点数为0
const double DEGREES_TO_RADIANS = 0.01745329251994329576923690768489;       // 角度转弧度乘法因子
const double RADIANS_TO_DEGREES = 57.295779513082320876798154814105;     // 弧度转角度乘法因子

const float PI_FLOAT = 3.1415926535897932f;                     // 浮点型π
const double PI = 3.1415926535897932384626433832795;            // 双精度浮点型π
const double SN_2PI = 6.283185307179586476925286766559;         // 2*π
const double PI_OVER_2 = 1.5707963267948966192313216916398;     // π/2
const double PI_OVER_3 = 1.0471975511965977461542144610932;     // π/3
const double SN_2PI_OVER_3 = 2.0943951023931954923084289221863; // 2*π/3
const double PI_OVER_4 = 0.78539816339744830961566084581988;    // π/4
const double SN_3PI_OVER_4 = 2.3561944901923449288469825374596; // 3*π/4
const double PI_OVER_6 = 0.52359877559829887307710723054658;    // π/6
const double SIN_PI_OVER_12 = 0.2588190451025207623488990;      // sin(π/12)
const double COS_PI_OVER_12 = 0.9659258262890682867497433;      // cos(π/12)
const double SN_SQRT2 = 1.414213562373095048801689;         // 根号2
const double SN_SQRT3 = 1.732050807568877293527446;         // 根号3
const double SQRT3_OVER_2 = 0.8660254037844386467637230;    // (根号3)/2
const double SN_1_OVER_SQRT2 = 0.7071067811865475244008445; // 1/(根号2)

const double SN_LOG2 = 0.6931471805599453094172321;
const double SN_LOG10 = 2.302585092994045684017991;

const double DOUBLE_MAX = 1.7976931348623158e+308;      // 最大可表示的双精度浮点绝对值
const double DOUBLE_MIN = 2.22507385850720200e-308;     // 最小可表示的双精度浮点绝对值

const double EPSILON = 2.2204460492503131e-16;
const double SQRT_EPSILON = 1.490116119385000000e-8;

const double UNSET_VALUE = -1.23432101234321e+308;      // 为双精度浮点数初始化的值，若等于此值，表明该变量未被计算及赋值过
const float UNSET_FLOAT = -1.234321e+38f;               // 为浮点数初始化的值，若等于此值，表明该变量未被计算及赋值过


// ======================================================================================================================================================
// 宏运算
#define ArrayCount(a) (sizeof(a)/sizeof((a)[0]))

// ======================================================================================================================================================
// 返回值代码
#define ERR_SUCCESS             0x0     //成功的返回值
#define ERR_PARA_NULL_POINTER   0x101   //传入的参数不应该为空指针
#define ERR_PARA_NEGATIVE       0x102   //传入的参数不应该为负数
#define ERR_PARA_OVER_LIMIT     0x103   //传入的参数超载了合法的范围
#define ERR_PARA_LOGIC          0x104   //传入的参数有逻辑冲突
#define ERR_PARA_UNDEFINED      0x105   //一般的参数传入错误
#define ERR_MEM_NULL_POINTER    0x201   //试图对指针进行访问
#define ERR_MEM_LEAK            0x202   //没有足够的内存空间供使用
#define ERR_MEM_OVER_LIMIT      0x203   //内存的非法越界访问
#define ERR_MEM_UNDEFINED	    0x204   //一般的内存访问错误
#define ERR_CAL_DIV_BY_ZERO     0x301   //出现被0除错误
#define ERR_CAL_NO_ENDING       0x302   //算法可能陷入了死循环
#define ERR_CAL_OVER_LIMIT	    0x303   //算法的中间值超越合法范围
#define ERR_CAL_UNDEFINED	    0x304   //一般的算法错误
#define ERR_OPER_DATA_NOT_READY	0x401   //要操作的数据/对象没有准备充分
#define ERR_OPER_STEP_NOT_READY	0x402   //请先完成前面的操作
#define ERR_OPER_NO_LISENCE	    0x403   //此模块未购买，请升级加密卡
#define ERR_OPER_VERSION	    0x404   //子模块版本不匹配，请重新安装
#define ERR_OPER_UNDEFINED      0x405   //一般的操作错误
#define ERR_UNDEFINED           0x1001  //无法归类的错误

#endif