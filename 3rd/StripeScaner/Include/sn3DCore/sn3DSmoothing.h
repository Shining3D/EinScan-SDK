#ifndef _sn3DSmoothing_H
#define _sn3DSmoothing_H

// ==========================================================================
// File name:	sn3DSmoothing.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	Δ=di*(cos(bi-ai/2)/cos(ai/2))
//				dn = 1/2n* Sum(wi*Δi)         ... wi= d0/di
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

		// 在调用该函数时，请保证range->VFlag(i).Deleted是有效的。即所有有效地顶点，都是和有效Cell相邻接的。
		// 可以提前调用m_range->UpdateFace();和 m_range->UpdateVertex();
		bool Smooth( sn3DRangeData *range, int iter, int k, int r);// k=0, r=6
	protected:
		bool UpdateNormal(Vector3f &newNorm,int p, int num, int *nb,vector<Vector3f> &arrayNormal,sn3DPointSet *set,int k, int r);
		bool UpdatePosition(int p, int num, int *nb,vector<Vector3f> &arrayNormal,sn3DPointSet *set,int k, int r);

		// 返回值  wo：各向同性权重		wa：各向异性权重
		// 控制参数k ：控制各向同性		r ：控制各向异性
		bool Anisotropic(float &wo, float *wa, int num, float *dota,float *dis,int k=0, int r=6);

		float Deviation(float dota, float dotb, float dis);
	private:
		void RangeNeighbor( sn3DRangeData *range, MatrixData<int> &map,vector<int> &aNeibor,vector<char>&aVCount);
		void RangeBuildNormal( sn3DRangeData *range, MatrixData<int> &map,vector<Vector3f> &aVNormal);
		void RangeBuildVertexNormal( sn3DRangeData* range, MatrixData<int>& map, vector<Vector3f>& aVNormal );
	};

}


#endif //_sn3DSmoothing_H