#ifndef _sn3DFace_H
#define _sn3DFace_H

// ==========================================================================
// File name:	sn3DFace.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	��Ķ���
//					Face   :	"f"��ģ���е�����ţ�  "vf"�������һ����, "ff"���ߵ���һ����
//
// Histroy:		
//	- Created : 2012/09/05  
//
// ============================================================================

#include "sn3DTriMesh.h"
#include "sn3DVertex.h"
#include <vector>
using namespace std;

namespace sn3DCore
{
	// class sn3DFace �����涨��
	class sn3DFace
	{
	public:
		sn3DFace();
		~sn3DFace();

		// �������ǳ�ʼ���������ⲿ�������
		void Initialize(int index, FaceFlag &flag, Vector3i &face,vector<sn3DVertex> *vertices);
		void SetNormal(Vector3f &norm);
		

		// �������ó�ʼ��
		void SetFace(int i0, int i1, int i2);
		void SetVFp(int i, sn3DFace &fp, int fi);
		void SetFFp(int i, sn3DFace &fp, int fi);
		

		// ���ݷ���
		int			&Index()	{ return m_index;};
		Vector3i	&F()		{ return *m_face;}
		Vector3f	&N()		{ return *m_normal;};
		FaceFlag	&Flag()		{ return *m_flag;};
		bool		HasNorm();

		// �������
		bool		IsV()		{ return (*m_flag).Visisted==1;}		// ����λ
		void		SetV()		{ (*m_flag).Visisted = 1;}
		void		ClearV()	{ (*m_flag).Visisted = 0;}
    

		// �������
		Vector3f	&P(int j)	{ return V(j)->P();};
		sn3DVertex *V(int j)	{ return &((*m_vertArray)[(*m_face)[j]]);};			//  ��ȡ��j������
		sn3DVertex *V1(int j)	{ return &((*m_vertArray)[(*m_face)[(j+1)%3]]);};	//  ��ȡ��j������ĺ�һ������
		sn3DVertex *V2(int j)	{ return &((*m_vertArray)[(*m_face)[(j+2)%3]]);};	//  ��ȡ��j������ĺ���������

		//���˷���
		sn3DFace* &FFp(int j)	{ return m_ffp[j];};			//	��ȡ��������ָ��
		int		  &FFi(int j)	{ return m_ffi[j];};
		

		sn3DFace *&VFp(int j)	{ return m_vfp[j];};			//	��ȡ��������ָ��
		int		  &VFi(int j)	{ return m_vfi[j];};
		//void	   SetVFp(int j, sn3DFace *f)	{ m_vfp[j] = f;};
		
		//sn3DFace& operator= (const sn3DFace& rh);
protected:
		int			m_index;
		// ��Щָ��ָ��sn3DTriMesh����
		FaceFlag	*m_flag;
		Vector3i	*m_face;
		Vector3f	*m_normal;

		// ��������
		vector<sn3DVertex>	*m_vertArray;
		
		// �����ϵ�������������
		sn3DFace	*m_vfp[3];	//  �ڹ��������£�ָ����һ���档��VertexTopology���ʹ�ã�����һ��������Χ���档
		int			 m_vfi[3];
						
		// ���߹�ϵ�������������
		sn3DFace	*m_ffp[3];	//	�ڹ��ߵ�����£����浱ǰ�棨�ߣ�
		int			 m_ffi[3];

		friend class sn3DTopology;			
	};
	inline bool sn3DFace::HasNorm()
	{
		if(m_normal)
			return true;
		else
			return false;
	}
}


#endif //_sn3DFace_H