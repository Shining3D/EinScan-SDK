#ifndef _sn3DVertex_H
#define _sn3DVertex_H

// ==========================================================================
// File name:	sn3DVertex.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	类的定义
//					Vertex :	"v"在模型中的顶点序号，"vf"该点的第一个邻面

//
// Histroy:		
//	- Created : 2013/11/06 
//
// ============================================================================

#include "sn3DTriMesh.h"
namespace sn3DCore
{
	class sn3DFace;

	class sn3DVertex
	{
	public:
		sn3DVertex():m_index(-1),m_flag(NULL),m_position(NULL),m_normal(NULL),
			m_vfp(NULL),m_vfi(-1){};
		~sn3DVertex(){};

		// 初始化
		void Initialize(int index, VertexFlag &flag, Vector3f &pos);
		void SetNormal(Vector3f &norm);

		void SetVFp(sn3DFace &face, int i);
		void SetVFp(sn3DFace *f,    int i);


		// 方便访问
		bool		IsV()	{ return (*m_flag).Visisted==1; }			// 访问位
		void		SetV()	{ (*m_flag).Visisted = 1;}
		void		ClearV(){ (*m_flag).Visisted = 0;}
		bool		IsB()   { return (*m_flag).Boundary==1; }			// 边界位
		void		SetB()	{ (*m_flag).Boundary = 1; }                    
		void		ClearB(){ (*m_flag).Boundary = 0; }    

		// 数据访问
		int			Index()	{ return m_index;};
		VertexFlag	&Flag()	{ return *m_flag;};
		Vector3f	&P()	{ return *m_position;};
		Vector3f	&N()	{ return *m_normal;};
		bool		HasNorm();

		// 拓扑访问
		sn3DFace	*&VFp()	{ return m_vfp;};
		int			&VFi()	{ return m_vfi;};

	protected:
		int m_index;			// 用来指示该点在sn3DTriMesh中的序号

		// 顶点的数据,指针指向sn3DTriMesh数据。
		VertexFlag *m_flag;
		Vector3f   *m_position;
		Vector3f   *m_normal;		// 可能会空

		// 顶点拓扑结构，用来访问连接该点的面
		sn3DFace *m_vfp;			// 该顶点的一个面,作为共点面链表的首面  
		int		  m_vfi;

	};
	//============================================================================
	// 初始化
	inline void sn3DVertex::Initialize(int index, VertexFlag &flag, Vector3f &pos)
	{
		m_index = index;
		m_flag = &flag;
		m_position= &pos;
	};
	inline void sn3DVertex::SetNormal(Vector3f &norm)
	{
		m_normal = &norm;
	};
	inline void sn3DVertex::SetVFp(sn3DFace &face, int i)
	{
		m_vfp = &face;
		m_vfi = i;
	}
	inline void sn3DVertex::SetVFp(sn3DFace *f,    int i)
	{
		m_vfp = f;
		m_vfi = i;
	}
	inline bool sn3DVertex::HasNorm()
	{
		if(m_normal)
			return true;
		else
			return false;
	}
}


#endif //_sn3DVertex_H