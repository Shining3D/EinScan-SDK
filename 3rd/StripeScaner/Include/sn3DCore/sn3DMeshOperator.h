#ifndef _sn3DMeshOperator_H
#define _sn3DMeshOperator_H


#include "sn3DTriMesh.h"
#include "sn3DRangeData.h"

namespace sn3DCore
{
	//�������ɵ�ǰ�������ݵ��桢���㷨������
	void ComputeNormal(sn3DTriMesh &data);

	//��RangeDataת��ΪMeshData
	bool ConvertRange2Mesh(sn3DRangeData &in_RangeData,sn3DTriMesh &out_MeshData);
}

#endif