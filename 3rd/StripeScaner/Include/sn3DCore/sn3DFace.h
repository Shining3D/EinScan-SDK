#ifndef _sn3DFace_H
#define _sn3DFace_H

// ==========================================================================
// File name:	sn3DFace.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	类的定义
//					Face   :	"f"在模型中的面序号，  "vf"共点的下一个面, "ff"共边的下一个面
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
	// class sn3DFace 三角面定义
	class sn3DFace
	{
	public:
		sn3DFace();
		~sn3DFace();

		// 这两个是初始化函数，外部请勿调用
		void Initialize(int index, FaceFlag &flag, Vector3i &face,vector<sn3DVertex> *vertices);
		void SetNormal(Vector3f &norm);
		

		// 参数设置初始化
		void SetFace(int i0, int i1, int i2);
		void SetVFp(int i, sn3DFace &fp, int fi);
		void SetFFp(int i, sn3DFace &fp, int fi);
		

		// 数据访问
		int			&Index()	{ return m_index;};
		Vector3i	&F()		{ return *m_face;}
		Vector3f	&N()		{ return *m_normal;};
		FaceFlag	&Flag()		{ return *m_flag;};
		bool		HasNorm();

		// 方便访问
		bool		IsV()		{ return (*m_flag).Visisted==1;}		// 访问位
		void		SetV()		{ (*m_flag).Visisted = 1;}
		void		ClearV()	{ (*m_flag).Visisted = 0;}
    

		// 顶点访问
		Vector3f	&P(int j)	{ return V(j)->P();};
		sn3DVertex *V(int j)	{ return &((*m_vertArray)[(*m_face)[j]]);};			//  获取第j个顶点
		sn3DVertex *V1(int j)	{ return &((*m_vertArray)[(*m_face)[(j+1)%3]]);};	//  获取第j个顶点的后一个顶点
		sn3DVertex *V2(int j)	{ return &((*m_vertArray)[(*m_face)[(j+2)%3]]);};	//  获取第j个顶点的后两个顶点

		//拓扑访问
		sn3DFace* &FFp(int j)	{ return m_ffp[j];};			//	获取面面拓扑指针
		int		  &FFi(int j)	{ return m_ffi[j];};
		

		sn3DFace *&VFp(int j)	{ return m_vfp[j];};			//	获取点面拓扑指针
		int		  &VFi(int j)	{ return m_vfi[j];};
		//void	   SetVFp(int j, sn3DFace *f)	{ m_vfp[j] = f;};
		
		//sn3DFace& operator= (const sn3DFace& rh);
protected:
		int			m_index;
		// 这些指针指向sn3DTriMesh数据
		FaceFlag	*m_flag;
		Vector3i	*m_face;
		Vector3f	*m_normal;

		// 三个顶点
		vector<sn3DVertex>	*m_vertArray;
		
		// 共点关系，点与面的拓扑
		sn3DFace	*m_vfp[3];	//  在共点的情况下，指向下一个面。与VertexTopology配合使用，访问一个顶点周围的面。
		int			 m_vfi[3];
						
		// 共边关系，面与面的拓扑
		sn3DFace	*m_ffp[3];	//	在共边的情况下，保存当前面（边）
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