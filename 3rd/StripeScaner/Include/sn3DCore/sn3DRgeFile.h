#ifndef _sn3DRgeFile_H
#define _sn3DRgeFile_H

// ==========================================================================
// File name:	sn3DRgeFile.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	RGE文件格式的读取和存储。读取支持RGE_v2.0,RGE_v3.0，存储只支持RGE_v3.0
//
// Histroy:		
//	- Created : 2015/07/08  
//
// ============================================================================

#include <vector>

#include "sn3DPointSet.h"
#include "sn3DRangeData.h"

namespace sn3DCore
{
	//===========================================================================
	// 函数：	sn3DDataTypeRGE 
	// 参数：	szName	[in]输入文件名
	//			type	[out]输出该文件保存的数据类型
	// 返回值： 0 成功，其他 失败
	// 功能：判断RGE文件保存的数据类型
	//===========================================================================
	int sn3DDataTypeRGE(const TCHAR *szName,DATA_TYPE &type);

	//===========================================================================
	// 函数：	sn3DReadRGE
	// 参数：	szName	[in]文件名
	//			dataObj	[out]数据
	// 返回值： 0 成功，其他 失败
	// 功能：读取RGE文件。已知数据类型，外部创建数据对象
	//===========================================================================
	int sn3DReadRGE(const TCHAR* szName, sn3DDataBase *dataObj);
	
	//===========================================================================
	// 函数：	sn3DReadRGE
	// 参数：	szName	[in]文件名
	//			dataObj	[out]数据
	// 返回值： NULL 失败，其他 成功
	// 功能：读取RGE文件。函数内部创建数据对象
	//===========================================================================
	sn3DPointSet *sn3DReadRGE(const TCHAR* szName);

	//===========================================================================
	// 函数：	sn3DSaveRGE
	// 参数：	szName	[in]文件名
	//			dataObj	[out]数据
	// 返回值： 0 成功，其他 失败
	// 功能：数据保存为RGE文件格式。
	//===========================================================================
	int sn3DSaveRGE(const TCHAR* szName, sn3DDataBase *dataObj);

	int sn3DSaveRange_v2(const TCHAR* szName, sn3DRangeData *range);
	
	// 只更新文件里面标志点的信息。标志点只能比文件里少
	int sn3DSaveRefPointRGE(const TCHAR* szName,sn3DRangeData *range);
	// 更新RGE文件中的变换矩阵信息
	int sn3DSaveTransformationRGE(const TCHAR* szName,sn3DRangeData *range);
	//===========================================================================
	// 函数：	sn3DSavePLY
	// 参数：	szName	[in]文件名
	//			dataObj	[out]数据
	// 返回值： 0 成功，其他 失败
	// 功能：数据保存为PLY文件格式。
	//===========================================================================
	int sn3DSavePLY(const TCHAR* szName, sn3DDataBase *dataObj);
}

#endif // _sn3DRgeFile.h