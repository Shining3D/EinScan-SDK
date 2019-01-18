#ifndef _sn3DRemoveCircle_H
#define _sn3DRemoveCircle_H

// ==========================================================================
// File name:	sn3DRemoveCircle.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.				
//			paper:	"Curvature Weighted smoothing of triangle meshes"
// Histroy:		
//	- Created : 2013/4/11  
//
// ============================================================================
#include "sn3DRangeData.h"
namespace sn3DCore
{
	class sn3DRemoveCircle
	{
	public:
		sn3DRemoveCircle(){};
		~sn3DRemoveCircle(){};
		bool RemoveCircle(sn3DRangeData *rge,MatrixData<int> &map, RefPointsData &refPts,float radius);
	protected:
		bool RemoveCircle(sn3DRangeData *rge,MatrixData<int> &map,double *ptxs, double *ptys, double *ptzs, int npt, double radius);
	private:
		bool isInRectangle( double minx, double maxx, double miny, double maxy, double minz, double maxz,double ptx, double pty,double ptz);
		bool isInCircle( double cx, double cy, double cz, double radius, double ptx, double pty, double ptz);
	};
}


#endif //_sn3DRemoveCircle_H