#ifndef _sn3DEdge_H
#define _sn3DEdge_H

// ==========================================================================
// File name:	sn3DEdge.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	类的定义
//					sn3DEdge:	
//
// Histroy:		
//	- Created : 2013/11/06 
//
// ============================================================================

#include "sn3DTriMesh.h"
#include "sn3DVertex.h"
#include "sn3DFace.h"
namespace sn3DCore
{
	class sn3DEdge
	{
	public:
		sn3DEdge():m_index(-1),m_flag(0)
		{
			m_vertex[0] = m_vertex[1] = NULL;
			m_face[0]   = m_face[1]   = NULL;
		};
		~sn3DEdge(){};

		int &	Index()				{ return m_index; };
		sn3DVertex &V(const int i)	{ return *m_vertex[i]; };
		sn3DFace   &F(const int i)	{ return *m_face[i]; }
	
	protected:
		int			m_index;
		int			m_flag;
		sn3DVertex  *m_vertex[2];
		sn3DFace	*m_face[2];
	};
}
#endif //_sn3DEdge_H