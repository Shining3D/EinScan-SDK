#ifndef _sn3DTriMesh_H
#define _sn3DTriMesh_H

// ==========================================================================
// File name:	sn3DTriMesh.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
//				默认分配：sn3DPointSet::m_aVertics		sn3DTriMesh:m_aFaces		数据
//						 sn3DPointSet::m_aVFlag	sn3DTriMesh:m_aFFlag    标志位
//
// Histroy:		
//	- Created : 2010/01/24  
//
// ============================================================================

#include "sn3DPointSet.h"
#include "sn3DImageData.h"

namespace sn3DCore
{
	union FaceFlag
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
	extern const FaceFlag FACE_FLAG_INIT;


	class sn3DTopology;
	class sn3DTriMesh:public sn3DPointSet
	{
		typedef sn3DPointSet inherited;
	public:
		sn3DTriMesh();
		virtual ~sn3DTriMesh();
		
	public:
		

		// 设置面数，并分配了内存
		void		SetFN(uint n);
		void		SetFN(uint fn, uint *faces);
		inline uint	GetFN()					{ return m_uFN;}
		virtual uint ValidFN();

		// 加入面，该函数效率低。返回面id，通过id修改其他面相关组件。
		uint		AddFace(Vector3i &f);
		uint		AddFace(uint i0, uint i1, uint i2);

		// 访问面
		inline Vector3i&	Face(uint i)		{ return m_aFaces[i];}
		Vector3i*	Faces();

		//设置顶点纹理数，分配内存
		// isFaceTex是面纹理还是顶点纹理，texCoordNumber纹理坐标的个数
		// 如果isFaceTex=false，则不需要指定texCoordNumber
		void				SetTexture(sn3DImageData<byte> *imageData,bool isFaceTex,uint texCoordNumber);
	
		inline bool			HasTexture()			{return m_hasTexture;}			// 是否有纹理
		inline bool			IsFaceTexture()			{return m_isFaceTex;}			// 是顶点纹理还是面纹理
		inline uint			GetTexNum()				{return m_uTexCoordNum;}

		inline sn3DImageData<byte> *GetTexture()	{return &m_texImage;}			// 访问纹理对象 add by hu 2011-8-29
		inline Vector2f&	TexCoord(uint i)		{return m_aTexCoord[i];}		// 访问每一个纹理坐标
		inline Vector3i&	IndexCoord(uint i)		{return m_aTexCoordIndex[i];}		// 访问每一个纹理坐标
		inline Vector3i&	FaceTexIndex(uint i)	{return m_aFTexIndex[i];}		// 访问每一个面纹理坐标序号
		void	ClearTexture();
	

		// 通过引用方式，访问可释放面组件
		inline Vector3f&	FNormal(uint i)	{ return m_aFNormal[i];}
		inline ColorRGB&	FColor(uint i)	{ return m_aFColor[i];}
		inline uint&		FIdentity(uint i){ return m_aFIdentity[i];}
		inline FaceFlag&	FFlag(uint i)	{ return m_aFFlag[i];}
		
		
		// 通过指针方式，访问可释放属性
		Vector3f*	FNormal();
		ColorRGB*   FColor();
		uint*		FIdentity();

		// 通过Buffer方式访问
		int*	FacesBuffer();
		float*	FNormalBuffer();
		float*  FColorBuffer();
	
		// 标志位访问
		void	InitFFlags();

		
		/// 通过顶点标志位(m_aVFlag)更新面标志位(m_aFFlag)。通常在编辑时，删除顶点使用
		virtual	void	UpdateFace();							//  m_aVFlag => m_aFFlag
		virtual	void    UpdateVertex();							// 当面变化了，需要跟新顶点
		virtual	void    UpdateValidFN();

		// 可释放组件
		inline bool	IsEnableFNormal()		{ return (m_uFFieldFlag&FACE_FIELD_NORMAL)	!=0;}
		inline bool	IsEnableFColor()		{ return (m_uFFieldFlag&FACE_FIELD_COLOR)		!=0;}
		inline bool	IsEnableFIdentity()		{ return (m_uFFieldFlag&FACE_FIELD_IDENTITY)	!=0;}

		// 可释放组件的分配和释放
		void	EnableFNormal();
		void	DisableFNormal();

		void	EnableFColor();
		void	DisableFColor();

		void	EnableFIdentity();
		void	DisableFIdentity();
// 		void    SetTexCoord(float u,float v);  //临时
// 		void    SetIndexTexCoord(int index0,int index1,int index2);  //临时
// 		void    SetTexCoordh(int h,int w);    //临时
// 		void    GetTexCoord(int &h,int &w);  //临时
		int     GetTexCoord();
		void	SetTexture(sn3DImageData<byte> *imageData); //临时
		void    clearTexCoord();
		int     GetTexCoordSize();
		int     GetIndexTexSize();
		void	EnableIndexColor(int texcoordsize);
		void    UnEnableIndexColor();

		// 建立拓扑关系
		sn3DTopology *GetTop();					// 通过拓扑访问网格
		void CreateTopology();
		void DestoryTopology();

		// 操作 压缩内存
		void  Compact();
		void  Clear();			// 清除几何数据

		bool DebugSaveSTL(std::tstring& fileName);
	protected:
		void UpdateFField();

	public:
		enum
		{
			FACE_FIELD_NULL					= 0x0,
			FACE_FIELD_NORMAL				= 0x1,
			FACE_FIELD_COLOR				= 0x2,
			FACE_FIELD_IDENTITY				= 0x4,
		};
	protected:
		uint					m_uFN;					// 顶点个数
		uint				    m_uFFieldFlag;

		// 必选组件
		std::vector<Vector3i>		m_aFaces;	// 指向顶点序号
		std::vector<FaceFlag>		m_aFFlag;

		// 可选组件
		std::vector<Vector3f>		m_aFNormal;
		std::vector<ColorRGB>		m_aFColor;
		std::vector<uint>			m_aFIdentity;

		//纹理 add by hu 
		bool						m_hasTexture;			// 该模型是否有纹理
		sn3DImageData<byte>         m_texImage; 
		bool						m_isFaceTex;			// 如果m_isFaceTex为false表示顶点纹理；m_aTexIndex为空，并且m_uVTexCoordNum等于m_uVN
		uint						m_uTexCoordNum;			// 顶点纹理坐标数与顶点数未必相等

		
		std::vector<Vector3i>		m_aFTexIndex;			// 面纹理坐标。m_hasTexIndex为false，改项为空。
		std::vector<Vector2f>		m_aTexCoord;			// 纹理数据
		std::vector<Vector3i>		m_aTexCoordIndex;			// 纹理数据
		int                         m_TexCoored;

		sn3DTopology				*m_pTopology;     // 应该指明是否只是作为参考数据而无需进行内存管理 [2011-5-31 18:35 ChenKun]
		friend class sn3DTopology;
		friend class sn3DVertex;
		friend class sn3DFace;
	};
}

#endif // _sn3DTriMesh_H