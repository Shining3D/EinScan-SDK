#ifndef _sn3DRangeOperator_H
#define _sn3DRangeOperator_H
#pragma once

#include "sn3DPointSet.h"
#include "MatrixData.h"
#include "sn3DRangeData.h"
namespace sn3DCore
{
	//===========================================================================
	// ������	RemoveSmallPatch
	// 
	// ������	rge		[in/out] ���ͼģ�ͣ�����ͨ����ĵ���������ʱ������cellflagΪflase
	//			removeSize	[in] ��������С�����
	//			maps		[in] ��ȡ��range.CreateIndexMap(maps);
	//
	// ���ܣ�ȥ��С����ͨ����	
	//===========================================================================
	bool RemoveSmallPatch(sn3DRangeData& range, MatrixData<int> &maps,int removeSize);

	//===========================================================================
	// ������	CameraRemove
	// 
	// ������	range		[in/out] ���ͼģ�ͣ�������ӽ��뷨��нǳ�����ֵ������cellflagΪflase
	//			cellNorma	[in] ���ͼģ��cell���� ��ȡrange.ComputeCellNormal(cellNormal)
	//			dirx		[in] ���ԭ��X
	//			dirx		[in] ���ԭ��Y
	//			dirx		[in] ���ԭ��Z
	//			maxViewAngle[in] ����ӽ��뷨��н���ֵ���ã��ȡ㣩
	// ���ܣ�ȥ��������ȶ����ݣ�ȥ�������߼нǹ���ĵ㡣	
	//===========================================================================
	void CameraRemove(sn3DRangeData& range, vector<Vector3f> &cellNormal,float dirx,float diry, float dirz, float maxViewAngle);

	void CameraRemove(sn3DRangeData& range,float dirx,float diry, float dirz, float maxViewAngle);
	
	void DistanceRemove(sn3DRangeData& range, MatrixData<int> &maps, float maxLength);
	bool PointDistance(sn3DRangeData& range,  MatrixData<int> &maps,int sampleCount, float &meanDis);

	// ɨ������ɾ����Ե����
	void BoundaryRemove(sn3DRangeData& range,MatrixData<int> &maps, int boundaryWidth);

	// �ú���������ʹ�ã�Ŀǰû����
	void DepthRemove(sn3DRangeData& range,  MatrixData<int> &maps,float depth);
	//
	void RemoveDepth(sn3DRangeData& range,  MatrixData<int> &maps,float depth);
}

#endif // _sn3DRangeOperator_H
