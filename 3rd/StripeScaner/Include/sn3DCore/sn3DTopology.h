#ifndef _sn3DTopology_H
#define _sn3DTopology_H

// ==========================================================================
// File name:	sn3DTopology.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	�����������˽���
//
// Histroy:		
//	- Created : 2010/01/24  
//
// ============================================================================

#include <vector>
#include <assert.h>
#include "sn3DTriMesh.h"
#include "sn3DVertex.h"
#include "sn3DFace.h"
#include "sn3DEdge.h"
//#include "sn3DSimplex.h"

using namespace std;
namespace sn3DCore
{
	class sn3DTopology    
	{    
	public:
		sn3DTopology();
		~sn3DTopology();
		sn3DTriMesh *GetMesh();
		void SetMesh(sn3DTriMesh *mesh);

		sn3DFace	&Face(int i)	{ return m_faces[i]; };
		sn3DVertex  &Vertex(int i)	{ return m_vertices[i]; };
		sn3DEdge	&Edge(int i)	{ return m_edges[i]; };

		sn3DFace	*F(int i)		{ return &(m_faces[i]); };
		sn3DVertex  *V(int i)		{ return &(m_vertices[i]); };
		sn3DEdge	*E(int i)		{ return &(m_edges[i]); };

		static void GetSurroundingFacesVF(sn3DFace * face,std::vector<sn3DFace *> & surround);//���õ������˻�ȡ��Ƭ����
		static bool IsBoundary(sn3DVertex * v);

		void IdentifyBoundary( );

		//void GetOneringEdge(sn3DVertex * v, std::vector<sn3DEdge*> & nei);
	protected:
		//build vTop and vfTop
		void VertexFace();
		//build ffTop
		void FaceFace();

		void DebugOutputVF();
		void DebugOutputFF();
	protected:
		vector<sn3DFace>	m_faces;
		vector<sn3DVertex>	m_vertices;
		vector<sn3DEdge>	m_edges;		// ָ�򶥵����
		sn3DTriMesh			*m_mesh;

		friend class sn3DFace;
		friend class sn3DVertex;
		friend class sn3DEdge;
	};// class sn3DTopology 
	
	void  VFAttach(sn3DFace &f,int z);
	void  VFDetach(sn3DFace & f, int z);
	void  VFDetach(sn3DFace & f, sn3DVertex & v);

	bool  IsInFace(sn3DFace * f, sn3DVertex * v);
	bool  IsInFace(sn3DFace * f, int v);

	int   ComplexSize(sn3DFace * f, int e);//����� e �ĸ��Ӷ�(��������)
	bool  FFCorrectness(sn3DFace * f, const int e);//��鹲�����˹�ϵ
	void  SwapEdge(sn3DFace * f, const int z);//ͨ���ı䶥��������ת��ĳ���

	sn3DFace * NeighborFaceByVF(sn3DFace * f,int z,int & z1);

}// namespace sn3DCore


#endif // _sn3DTopology_H