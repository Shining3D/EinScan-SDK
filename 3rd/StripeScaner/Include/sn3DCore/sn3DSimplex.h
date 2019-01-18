#ifndef _sn3DSimplex_H
#define _sn3DSimplex_H

// ==========================================================================
// File name:	sn3DSimplex.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	类的定义
//					Pos			:	由点、边、面组成的访问基本元素
//					VFIterator	:	顶点单圈邻面，无序访问
//					VVNeighbor	:	顶点单圈邻点，顺序访问
//
// Histroy:		
//	- Created : 2012/09/05  
//
// ============================================================================

#include "sn3DTopology.h"
#include "sn3DTriMesh.h"
#include "sn3DVertex.h"
#include "sn3DFace.h"
namespace sn3DCore
{
	class sn3DPos
	{
	public:
		sn3DPos();
		sn3DPos(sn3DFace * const fp, int const zp, sn3DVertex * const vp);
		sn3DPos(sn3DFace * const fp, int const zp);
		sn3DPos(sn3DFace * const fp, sn3DVertex * const vp);

		sn3DVertex * & V() { return m_v;};
		sn3DFace   * & F() { return m_f;};
		int			 & I() { return m_z;};

		bool operator == ( sn3DPos const & p ) const;
		bool operator != ( sn3DPos const & p ) const;
		bool operator <= ( sn3DPos const & p) const;//首先比较面指针，然后比较边索引，最后比较顶点指针

		sn3DPos & operator = ( const sn3DPos & h );
		void SetNull();
		bool IsNull() const ;

		void Set(sn3DFace  * const fp, int const zp,  sn3DVertex  * const vp);
		void Set(sn3DFace  * const pFace, sn3DVertex  * const pVertex);

		void NextF();				//移动到共边 z的下个面
		void NextE();				//移动到共点 v的下一边
		void NextB();				//移动到下一个边界,要保证当前已在边界位置

		void FlipE();				//点、面不变，边翻转
		void FlipF();				//点、边不变，面翻转
		void FlipV();				//边、面不变，点翻转

		sn3DVertex		 *VFlip();
		const sn3DVertex *VFlip()const;
		sn3DFace		 *FFlip() ;
		const sn3DFace	 *FFlip()  const;

		bool IsBorder();
		bool IsManifold();			//检查是否为流形

		int NumberOfIncidentVertices();//返回当前顶点的度,边
		int NumberOfIncidentFaces();//返回当前顶点的度,面
		bool Coerent() const;		//方向一致性检查
		void CheckIncidentFaces(int & count, bool & on_border);

	public:
		int			m_z;			//边索引
		sn3DFace	*m_f;			//面指针
		sn3DVertex	*m_v;			//顶点指针
	};
	//============================================================================
	class sn3DVFIterator
	{
	public:

		sn3DFace   *&F()  { return m_f;}
		int			&I()  { return m_z;}
		bool		End() { return m_f==0;}

		sn3DFace *operator++()
		{
			sn3DFace * t = m_f;
			m_f = t->VFp(m_z);
			m_z = t->VFi(m_z);
			return m_f;
		}	
	public:

		sn3DVFIterator(){}
		sn3DVFIterator(sn3DFace * f,  const int & z)	{ m_f=f; m_z=z; }
		sn3DVFIterator(sn3DVertex * v)					{ m_f=v->VFp(); m_z=v->VFi(); }
	public:

		int			m_z;
		sn3DFace *	m_f;
		
	};
	//============================================================================
	class sn3DVVNeighbor
	{
	public:
		sn3DVVNeighbor();
		sn3DVVNeighbor(sn3DVertex *v);

		int GetCount();
		int GetIndex(int  id); // 查找邻居的索引
		int GetNeighborID(int index); // 从0开始的索引
		int GetPrevID(int index);
		int GetNextID(int index);
		sn3DVertex * GetNeighborVertex(int index);

	public:
		sn3DPos m_pos;
	};
}


#endif //_sn3DSimplex_H