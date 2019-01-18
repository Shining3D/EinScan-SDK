#ifndef _sn3DVertex_H
#define _sn3DVertex_H

// ==========================================================================
// File name:	sn3DVertex.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	��Ķ���
//					Vertex :	"v"��ģ���еĶ�����ţ�"vf"�õ�ĵ�һ������

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

		// ��ʼ��
		void Initialize(int index, VertexFlag &flag, Vector3f &pos);
		void SetNormal(Vector3f &norm);

		void SetVFp(sn3DFace &face, int i);
		void SetVFp(sn3DFace *f,    int i);


		// �������
		bool		IsV()	{ return (*m_flag).Visisted==1; }			// ����λ
		void		SetV()	{ (*m_flag).Visisted = 1;}
		void		ClearV(){ (*m_flag).Visisted = 0;}
		bool		IsB()   { return (*m_flag).Boundary==1; }			// �߽�λ
		void		SetB()	{ (*m_flag).Boundary = 1; }                    
		void		ClearB(){ (*m_flag).Boundary = 0; }    

		// ���ݷ���
		int			Index()	{ return m_index;};
		VertexFlag	&Flag()	{ return *m_flag;};
		Vector3f	&P()	{ return *m_position;};
		Vector3f	&N()	{ return *m_normal;};
		bool		HasNorm();

		// ���˷���
		sn3DFace	*&VFp()	{ return m_vfp;};
		int			&VFi()	{ return m_vfi;};

	protected:
		int m_index;			// ����ָʾ�õ���sn3DTriMesh�е����

		// ���������,ָ��ָ��sn3DTriMesh���ݡ�
		VertexFlag *m_flag;
		Vector3f   *m_position;
		Vector3f   *m_normal;		// ���ܻ��

		// �������˽ṹ�������������Ӹõ����
		sn3DFace *m_vfp;			// �ö����һ����,��Ϊ���������������  
		int		  m_vfi;

	};
	//============================================================================
	// ��ʼ��
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