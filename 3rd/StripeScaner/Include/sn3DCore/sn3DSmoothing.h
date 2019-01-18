#ifndef _sn3DSmoothing_H
#define _sn3DSmoothing_H

// ==========================================================================
// File name:	sn3DSmoothing.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	��=di*(cos(bi-ai/2)/cos(ai/2))
//				dn = 1/2n* Sum(wi*��i)         ... wi= d0/di
//					
//					
//					
//			paper:	"Curvature Weighted smoothing of triangle meshes"
// Histroy:		
//	- Created : 2012/12/12  wuzq
//
// ============================================================================

#include "sn3DTriMesh.h"
#include "sn3DRangeData.h"
namespace sn3DCore
{
	class sn3DSmoothing
	{
	public:
		sn3DSmoothing(){};
		~sn3DSmoothing(){};

		// �ڵ��øú���ʱ���뱣֤range->VFlag(i).Deleted����Ч�ġ���������Ч�ض��㣬���Ǻ���ЧCell���ڽӵġ�
		// ������ǰ����m_range->UpdateFace();�� m_range->UpdateVertex();
		bool Smooth( sn3DRangeData *range, int iter, int k, int r);// k=0, r=6
	protected:
		bool UpdateNormal(Vector3f &newNorm,int p, int num, int *nb,vector<Vector3f> &arrayNormal,sn3DPointSet *set,int k, int r);
		bool UpdatePosition(int p, int num, int *nb,vector<Vector3f> &arrayNormal,sn3DPointSet *set,int k, int r);

		// ����ֵ  wo������ͬ��Ȩ��		wa����������Ȩ��
		// ���Ʋ���k �����Ƹ���ͬ��		r �����Ƹ�������
		bool Anisotropic(float &wo, float *wa, int num, float *dota,float *dis,int k=0, int r=6);

		float Deviation(float dota, float dotb, float dis);
	private:
		void RangeNeighbor( sn3DRangeData *range, MatrixData<int> &map,vector<int> &aNeibor,vector<char>&aVCount);
		void RangeBuildNormal( sn3DRangeData *range, MatrixData<int> &map,vector<Vector3f> &aVNormal);
		void RangeBuildVertexNormal( sn3DRangeData* range, MatrixData<int>& map, vector<Vector3f>& aVNormal );
	};

}


#endif //_sn3DSmoothing_H