#ifndef _sn3DPointSet_H
#define _sn3DPointSet_H

// ==========================================================================
// File name:	sn3DPointSet.h
//
// Copyright (C), 2017-2045, Shining 3D Tech. Co., Ltd.
//
// Description:	base data class。
//				cloud points and mark points
//
/// @author Will
/// @version 1.0
/// @date 2017-01-11
// ============================================================================

#include <vector>

#include "sn3DDataBase.h"
#include "ColorRGB.h"
#include "Vector2.h"

namespace sn3DCore
{
	union VertexFlag
	{
		struct
		{
			unsigned Deleted:	1;
			unsigned Selected:	1;
			unsigned Visisted:	1;
			unsigned Modified:	1;
			unsigned Boundary:	1;
		};
		uint flags;
	} ;
	enum
	{
		VERTEX_FIELD_NULL		= 0x00,
		VERTEX_FIELD_NORMAL		= 0x01,
		VERTEX_FIELD_COLOR		= 0x02,
		VERTEX_FIELD_IDENTITY	= 0x04
	};
	extern const VertexFlag VERTEX_FLAG_INIT;

	class sn3DPointSet : public sn3DDataBase
	{
		typedef sn3DDataBase inherited;
	public:
		sn3DPointSet(uint vertexField=VERTEX_FIELD_NULL);
		virtual ~sn3DPointSet();

		// set the cloud number and Alloc memory
		void			SetVN(uint n);
		void			SetVN(uint n, Vector3f *pts);
		void			SetVN(uint n, float *data);
		inline uint		GetVN()	{ return m_uVN;}
		

		//// Reserved word
		uint			AddVertex(Vector3f &pt);

		// use the function to get the cloud point and normal
		inline Vector3f&	operator[](uint i)	{ return m_aVertics[i];}
		inline Vector3f&	Vertex(uint i)		{ return m_aVertics[i];}
		inline Vector3f&	VNormal(uint i)		{ return m_aVNormal[i];}
		inline ColorRGB&	VColor(uint i)		{ return m_aVColor[i];}
		inline uint&		VIdentity(uint i)	{ return m_aVIdentity[i];}
		inline VertexFlag&	VFlag(uint i)		{ return m_aVFlag[i];}

		// //// Reserved word。
		void DeleteFlags(unsigned char *& deleteArray);

		// use the function to get the cloud point and normal
		Vector3f*	Vertics();
		Vector3f*	VNormal();
		ColorRGB*	VColor();
		uint*		VIdentity();

		//// Reserved word
		float*		VerticsBuffer();
		float*		VNormalBuffer();
		float*		VColorBuffer();
//		float*		TexColorBuffer();

		//// Reserved word
		void	InitVFlags();
			
		// //// Reserved word
		inline bool	IsEnableVNormal()		{ return (m_uVFieldFlag&VERTEX_FIELD_NORMAL)	!=0;}
		inline bool	IsEnableVColor()		{ return (m_uVFieldFlag&VERTEX_FIELD_COLOR)	!=0;}
		inline bool	IsEnableVIdentity()		{ return (m_uVFieldFlag&VERTEX_FIELD_IDENTITY)	!=0;}


		void	EnableVNormal();   //use the cloud normal
		void	DisableVNormal();  //unuse the cloud normal

		void	EnableVColor();  // Reserved word
		void	DisableVColor();  // Reserved word

		void	EnableVIdentity(); // Reserved word
		void	DisableVIdentity(); // Reserved word

		// Reserved word
		void    DisableOptionVField();	
	public: // Reserved word
		virtual	void	UpdateBox();		// 
		virtual	void    UpdateValidVN();	// 
		// 
		virtual void  Squeeze();
		// 
		virtual void  Clear();	

		// 
		virtual void ClearMemory();
		virtual bool SwapOutData();	
		virtual bool SwapInData();		

		// 
		virtual bool LoadData(const TCHAR* szPath);
		virtual bool SaveData(const TCHAR* szPath);
		
				bool TestSaveASC(const TCHAR* szPath);
	protected:
		void UpdateVField();
		void SqueezeV();
		
	protected:		
		uint				m_uVN;							// cloud number
		uint				m_uVFieldFlag;					// Reserved word
		
		// 必选组件
		std::vector<Vector3f>		m_aVertics;				// Reserved word
		std::vector<VertexFlag>		m_aVFlag;				// Reserved word
		
		// 可选组件
		std::vector<Vector3f>		m_aVNormal;				// normal
		std::vector<ColorRGB>		m_aVColor;				// colour
//		std::vector<ColorRGB>		m_aTexColor;		    // 
		std::vector<uint>			m_aVIdentity;			// cloud flag
	};
}

#endif // _sn3DPointSet_H