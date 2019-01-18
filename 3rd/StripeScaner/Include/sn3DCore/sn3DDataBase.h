#ifndef _sn3DDataBase_H
#define _sn3DDataBase_H

///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2017-2045, Shining 3D Tech. Co., Ltd.
//
/// @file	sn3DDataBase.h
/// @brief	Data Base class\n
///			hve data id ,name,rt .
/// @author Will
/// @version 1.0
/// @date 2017-01-11
//////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "sn3Dglobaldef.h"
#include "Matrix4.h"
#include "Vector3.h"
using namespace sn3DFoundation;

namespace sn3DCore
{
	typedef enum
	{
		DT_DATA_BASE	=0,
		DT_POINT_SET,
		DT_MESH_DATA,
		DT_RANGE_DATA,
		DT_RANGE_IMAGE
	}DATA_TYPE;

	class sn3DDataBase
	{
	public:
		sn3DDataBase();
		virtual ~sn3DDataBase();

		// the model id
		inline int		GetID();
		inline void		SetID(int ID);

		// the mode type
		inline DATA_TYPE	GetType()const;
		inline bool		IsOfType( const DATA_TYPE dp);

		// RT
		Matrix4d&		GetTransformation();
		void			GetTransformationf(Matrix4f &mat);
		void			SetTransformation(const Matrix4d & mat);
		void			SetTransformation(double *rotate, double *trans);
		void			GetTransformation(double *rotate, double *trans);

		// 
		virtual void	Clear()				{};		// Alloc memory -  Reserved word
		virtual void	Squeeze()			{};		//  Reserved word
				
		bool			IsInMemory();
		virtual void	ClearMemory();				//  Reserved word
		virtual bool	SwapOutData();				//  Reserved word
		virtual bool	SwapInData();				//  Reserved word

		virtual	void	UpdateBox();				//  Reserved word
		virtual	void	UpdateFace();				//  Reserved word
		virtual	void    UpdateVertex();				//  Reserved word
		virtual	void    UpdateValidVN()		{m_validVN=0;};
		virtual	void    UpdateValidFN()		{m_validFN=0;};

		inline uint		GetValidVN();
		inline uint		GetValidFN();
		inline void		GetBoundBox(Vector3f &bmin, Vector3f &bmax);	//  Reserved word
		inline Vector3f	GetCenter();

		// //  Reserved word
		void			SetName(const TCHAR *szName);
		const TCHAR*	GetName();
		void			SetDirectory(const TCHAR *szDir);
		const TCHAR*	GetDirectory();;
		const TCHAR*	GetFullPath();

		// //  Reserved word
		virtual bool	LoadData(const TCHAR *szPath);
		virtual bool	SaveData(const TCHAR *szPath);
			
	public:
		static int	DataTypeRGE(const char *szPath, DATA_TYPE &tp);
	protected:
		int			m_index;		// 
		DATA_TYPE	m_dataType;		// 

		Matrix4d	m_matrix;

		Vector3f	m_boxMin;		// 
		Vector3f	m_boxMax;

		uint		m_validVN;
		uint		m_validFN;

		bool		m_isModified;
		bool		m_isInMemory;	// 
		
		// 
		std::tstring		m_strName;	// model name
		std::tstring		m_strDir;	// path Reserved word
		std::tstring		m_strExt;	// Reserved word
	};
	//////////////////////////////////////////////////////////////////////////////
	inline int sn3DDataBase::GetID()
	{
		return m_index;
	}
	inline void sn3DDataBase::SetID(int index)
	{
		m_index = index;
	}
	inline DATA_TYPE sn3DDataBase::GetType()const						
	{ 
		return m_dataType;	
	}
	inline bool	sn3DDataBase::IsOfType( const DATA_TYPE dp)		
	{ 
		return dp==m_dataType;
	}
	inline bool sn3DDataBase::IsInMemory()
	{
		return m_isInMemory;
	}
	inline uint sn3DDataBase::GetValidVN()
	{
		return m_validVN;
	}
	inline uint sn3DDataBase::GetValidFN()
	{
		return m_validFN;
	}
	inline void sn3DDataBase::GetBoundBox(Vector3f &bmin, Vector3f &bmax)
	{
		bmin = m_boxMin;
		bmax = m_boxMax;
	}
	inline Vector3f sn3DDataBase::GetCenter()
	{
		return Vector3f((m_boxMin+m_boxMax)/2);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	template<class Real>
	inline void RigidTransform( Vector3<Real> &out, Vector3<Real> &in, Matrix4<Real> &mat )
	{
		out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2] + mat[0][3];
		out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2] + mat[1][3];
		out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2] + mat[2][3];
	}
	template<class Real>
	inline void RotateTransform( Vector3<Real> &out, Vector3<Real> &in, Matrix4<Real> &mat )
	{
		out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2];
		out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2];
		out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2];
	}
	template<class Real>
	inline void RotateTransform( Vector3<Real> &out, Vector3<Real> &in, Real* rot )
	{
		out[0] = rot[0]*in[0] + rot[1]*in[1] + rot[2]*in[2];
		out[1] = rot[3]*in[0] + rot[4]*in[1] + rot[5]*in[2];
		out[2] = rot[6]*in[0] + rot[7]*in[1] + rot[8]*in[2];
	}
	template<class Real>
	inline void SetMatrix4d(Matrix4d &mat, Real *R, Real *T)
	{
		mat[0][0]=(double)R[0]; mat[0][1]=(double)R[1]; mat[0][2]=(double)R[2]; mat[0][3]=(double)T[0];
		mat[1][0]=(double)R[3]; mat[1][1]=(double)R[4]; mat[1][2]=(double)R[5]; mat[1][3]=(double)T[1];
		mat[2][0]=(double)R[6]; mat[2][1]=(double)R[7]; mat[2][2]=(double)R[8]; mat[2][3]=(double)T[2];
		mat[3][0]= 0.0;			mat[3][1]= 0.0;			mat[3][2]= 0.0;			mat[3][3]= 1.0;
	};
	template<class Real>
	inline void GetMatrix4d(Real *R, Real *T,Matrix4d &mat)
	{
		R[0]=(Real)mat[0][0]; R[1]=(Real)mat[0][1]; R[2]=(Real)mat[0][2]; T[0]=(Real)mat[0][3];
		R[3]=(Real)mat[1][0]; R[4]=(Real)mat[1][1]; R[5]=(Real)mat[1][2]; T[1]=(Real)mat[1][3];
		R[6]=(Real)mat[2][0]; R[7]=(Real)mat[2][1]; R[8]=(Real)mat[2][2]; T[2]=(Real)mat[2][3];
	}

	////   Rigid Vector Matrix4d double
	//template<class Real>
	//inline void RigidTransformd( Vector3d &out, Vector3d &in,Matrix4d &mat )
	//{
	//	out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2] + mat[0][3];
	//	out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2] + mat[1][3];
	//	out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2] + mat[2][3];
	//}
	////  Rigid Vector Matrix4d float
	//inline void RigidTransformf( Vector3f &out, Vector3f &in,Matrix4f &mat )
	//{
	//	out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2] + mat[0][3];
	//	out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2] + mat[1][3];
	//	out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2] + mat[2][3];
	//}
	////   Rotate Vector Matrix4d double
	//inline void RotateTransformd( Vector3d &out, Vector3d &in,Matrix4d &mat )
	//{
	//	out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2];
	//	out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2];
	//	out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2];
	//}
	//// Rotate Vector Matrix4d float
	//inline void RotateTransformf( Vector3f &out, Vector3f &in,Matrix4f &mat )
	//{
	//	out[0] = mat[0][0]*in[0] + mat[0][1]*in[1] + mat[0][2]*in[2];
	//	out[1] = mat[1][0]*in[0] + mat[1][1]*in[1] + mat[1][2]*in[2];
	//	out[2] = mat[2][0]*in[0] + mat[2][1]*in[1] + mat[2][2]*in[2];
	//}
	//inline void RotateTransformd(Vector3d& outVect, Vector3d& inVect, double* rot)
	//{
	//	outVect[0] = rot[0]*inVect[0] + rot[1]*inVect[1] + rot[2]*inVect[2];
	//	outVect[1] = rot[3]*inVect[0] + rot[4]*inVect[1] + rot[5]*inVect[2];
	//	outVect[2] = rot[6]*inVect[0] + rot[7]*inVect[1] + rot[8]*inVect[2];
	//}
	//// 
	//inline void RotateTransformf(Vector3f& outVect, Vector3f& inVect, float* rot)
	//{
	//	outVect[0] = rot[0]*inVect[0] + rot[1]*inVect[1] + rot[2]*inVect[2];
	//	outVect[1] = rot[3]*inVect[0] + rot[4]*inVect[1] + rot[5]*inVect[2];
	//	outVect[2] = rot[6]*inVect[0] + rot[7]*inVect[1] + rot[8]*inVect[2];
	//}

	// 旋转矩阵转置
	inline void TransposeRoatate(double *outR, double *inR)
	{
		outR[0]=inR[0]; outR[1]=inR[3]; outR[2]=inR[6];
		outR[3]=inR[1]; outR[4]=inR[4]; outR[5]=inR[7];
		outR[6]=inR[2]; outR[7]=inR[5]; outR[8]=inR[8];
	}
	// 对向量进行变换
	inline void TransformNorm(double *outX,double *R, double *inX )
	{
		outX[0] = R[0]*inX[0] + R[1]*inX[1] + R[2]*inX[2];
		outX[1] = R[3]*inX[0] + R[4]*inX[1] + R[5]*inX[2];
		outX[2] = R[6]*inX[0] + R[7]*inX[1] + R[8]*inX[2];
	}
	//inline void SetMatrix4d(Matrix4d &mat, double *R, double *T)
	//{
	//	mat[0][0]=R[0]; mat[0][1]=R[1]; mat[0][2]=R[2]; mat[0][3]=T[0];
	//	mat[1][0]=R[3]; mat[1][1]=R[4]; mat[1][2]=R[5]; mat[1][3]=T[1];
	//	mat[2][0]=R[6]; mat[2][1]=R[7]; mat[2][2]=R[8]; mat[2][3]=T[2];
	//	mat[3][0]= 0.0; mat[3][1]= 0.0; mat[3][2]= 0.0; mat[3][3]= 1.0;
	//};
	//inline void GetMatrix4d(double *R, double *T,Matrix4d &mat)
	//{
	//	R[0]=mat[0][0]; R[1]=mat[0][1]; R[2]=mat[0][2]; T[0]=mat[0][3];
	//	R[3]=mat[1][0]; R[4]=mat[1][1]; R[5]=mat[1][2]; T[1]=mat[1][3];
	//	R[6]=mat[2][0]; R[7]=mat[2][1]; R[8]=mat[2][2]; T[2]=mat[2][3];
	//}

	inline void InverseTransform(double *invRot, double *invTrans, double *rot, double *trans)
	{

		double tempTrans[3]= {-1.0*trans[0], -1.0*trans[1], -1.0*trans[2]};
		TransposeRoatate(invRot, rot);
		TransformNorm( invTrans,invRot, tempTrans);
	}
	inline void InverseMatrix4d(Matrix4d &invMat,Matrix4d &mat)
	{
		double invRot[9]={};	
		double invTrans[3]={};
		double rot[9]={};		
		double trans[3]={};
		GetMatrix4d(rot, trans,mat);
		InverseTransform(invRot, invTrans, rot, trans);
		SetMatrix4d(invMat, invRot, invTrans);
	};
	inline void InsertPointToBBox(Vector3f &p, Vector3f &minB, Vector3f &maxB )
	{
		if(p[0]<minB[0])		minB[0] = p[0];
		if(p[1]<minB[1])		minB[1] = p[1];
		if(p[2]<minB[2])		minB[2] = p[2];

		if(p[0]>maxB[0])		maxB[0] = p[0];
		if(p[1]>maxB[1])		maxB[1] = p[1];
		if(p[2]>maxB[2])		maxB[2] = p[2];
	};
}

#endif // _sn3DDataBase_H