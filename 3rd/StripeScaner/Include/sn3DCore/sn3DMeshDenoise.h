#ifndef _sn3DMeshDenoise_H
#define _sn3DMeshDenoise_H

///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
/// @file	sn3DMeshDenoise.h
/// @brief	·¨ÏòÂË²¨
///
/// @author 
/// @version 1.0
/// @date 2012-09-03
//////////////////////////////////////////////////////////////////////////////


#include "sn3DTriMesh.h"

namespace sn3DCore
{
	class sn3DMeshDenoise
	{
	public:
		sn3DMeshDenoise();
		~sn3DMeshDenoise();

		void FastEffectiveDenoise( sn3DTriMesh *mesh);
	protected:
		void VertexUpdate(sn3DTriMesh *mesh);
	public:
		int m_Iterations;
		int m_VIterations;
		float m_fSigma;
	};
}

#endif