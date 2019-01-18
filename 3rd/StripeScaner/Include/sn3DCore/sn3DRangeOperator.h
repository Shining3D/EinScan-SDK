#ifndef _sn3DRangeOperator_H
#define _sn3DRangeOperator_H
#pragma once

#include "sn3DPointSet.h"
#include "MatrixData.h"
#include "sn3DRangeData.h"
namespace sn3DCore
{
	//===========================================================================
	// 函数：	RemoveSmallPatch
	// 
	// 参数：	rge		[in/out] 深度图模型，当连通区域的的面数过少时，则置cellflag为flase
	//			removeSize	[in] 连区域最小面个数
	//			maps		[in] 获取：range.CreateIndexMap(maps);
	//
	// 功能：去除小的连通区域。	
	//===========================================================================
	bool RemoveSmallPatch(sn3DRangeData& range, MatrixData<int> &maps,int removeSize);

	//===========================================================================
	// 函数：	CameraRemove
	// 
	// 参数：	range		[in/out] 深度图模型，当相机视角与法向夹角超出阈值，则置cellflag为flase
	//			cellNorma	[in] 深度图模型cell法向。 获取range.ComputeCellNormal(cellNormal)
	//			dirx		[in] 相机原点X
	//			dirx		[in] 相机原点Y
	//			dirx		[in] 相机原点Z
	//			maxViewAngle[in] 相机视角与法向夹角阈值，用（度°）
	// 功能：去除相机不稳定数据，去除与视线夹角过大的点。	
	//===========================================================================
	void CameraRemove(sn3DRangeData& range, vector<Vector3f> &cellNormal,float dirx,float diry, float dirz, float maxViewAngle);

	void CameraRemove(sn3DRangeData& range,float dirx,float diry, float dirz, float maxViewAngle);
	
	void DistanceRemove(sn3DRangeData& range, MatrixData<int> &maps, float maxLength);
	bool PointDistance(sn3DRangeData& range,  MatrixData<int> &maps,int sampleCount, float &meanDis);

	// 扫描数据删除边缘数据
	void BoundaryRemove(sn3DRangeData& range,MatrixData<int> &maps, int boundaryWidth);

	// 该函数不建议使用，目前没测试
	void DepthRemove(sn3DRangeData& range,  MatrixData<int> &maps,float depth);
	//
	void RemoveDepth(sn3DRangeData& range,  MatrixData<int> &maps,float depth);
}

#endif // _sn3DRangeOperator_H
