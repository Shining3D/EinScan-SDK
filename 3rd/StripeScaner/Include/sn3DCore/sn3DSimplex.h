#ifndef _sn3DSimplex_H
#define _sn3DSimplex_H

// ==========================================================================
// File name:	sn3DSimplex.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	��Ķ���
//					Pos			:	�ɵ㡢�ߡ�����ɵķ��ʻ���Ԫ��
//					VFIterator	:	���㵥Ȧ���棬�������
//					VVNeighbor	:	���㵥Ȧ�ڵ㣬˳�����
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
		bool operator <= ( sn3DPos const & p) const;//���ȱȽ���ָ�룬Ȼ��Ƚϱ����������Ƚ϶���ָ��

		sn3DPos & operator = ( const sn3DPos & h );
		void SetNull();
		bool IsNull() const ;

		void Set(sn3DFace  * const fp, int const zp,  sn3DVertex  * const vp);
		void Set(sn3DFace  * const pFace, sn3DVertex  * const pVertex);

		void NextF();				//�ƶ������� z���¸���
		void NextE();				//�ƶ������� v����һ��
		void NextB();				//�ƶ�����һ���߽�,Ҫ��֤��ǰ���ڱ߽�λ��

		void FlipE();				//�㡢�治�䣬�߷�ת
		void FlipF();				//�㡢�߲��䣬�淭ת
		void FlipV();				//�ߡ��治�䣬�㷭ת

		sn3DVertex		 *VFlip();
		const sn3DVertex *VFlip()const;
		sn3DFace		 *FFlip() ;
		const sn3DFace	 *FFlip()  const;

		bool IsBorder();
		bool IsManifold();			//����Ƿ�Ϊ����

		int NumberOfIncidentVertices();//���ص�ǰ����Ķ�,��
		int NumberOfIncidentFaces();//���ص�ǰ����Ķ�,��
		bool Coerent() const;		//����һ���Լ��
		void CheckIncidentFaces(int & count, bool & on_border);

	public:
		int			m_z;			//������
		sn3DFace	*m_f;			//��ָ��
		sn3DVertex	*m_v;			//����ָ��
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
		int GetIndex(int  id); // �����ھӵ�����
		int GetNeighborID(int index); // ��0��ʼ������
		int GetPrevID(int index);
		int GetNextID(int index);
		sn3DVertex * GetNeighborVertex(int index);

	public:
		sn3DPos m_pos;
	};
}


#endif //_sn3DSimplex_H