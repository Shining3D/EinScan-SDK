#ifndef _sn3DMeshOperator_H
#define _sn3DMeshOperator_H


#include "sn3DTriMesh.h"
#include "sn3DRangeData.h"

namespace sn3DCore
{
	//计算生成当前几何数据的面、顶点法向量。
	void ComputeNormal(sn3DTriMesh &data);

	//把RangeData转化为MeshData
	bool ConvertRange2Mesh(sn3DRangeData &in_RangeData,sn3DTriMesh &out_MeshData);
}

#endif