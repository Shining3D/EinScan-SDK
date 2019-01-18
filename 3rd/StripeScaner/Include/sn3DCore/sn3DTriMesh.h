#ifndef _sn3DTriMesh_H
#define _sn3DTriMesh_H

// ==========================================================================
// File name:	sn3DTriMesh.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
//				Ĭ�Ϸ��䣺sn3DPointSet::m_aVertics		sn3DTriMesh:m_aFaces		����
//						 sn3DPointSet::m_aVFlag	sn3DTriMesh:m_aFFlag    ��־λ
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
		

		// �������������������ڴ�
		void		SetFN(uint n);
		void		SetFN(uint fn, uint *faces);
		inline uint	GetFN()					{ return m_uFN;}
		virtual uint ValidFN();

		// �����棬�ú���Ч�ʵ͡�������id��ͨ��id�޸���������������
		uint		AddFace(Vector3i &f);
		uint		AddFace(uint i0, uint i1, uint i2);

		// ������
		inline Vector3i&	Face(uint i)		{ return m_aFaces[i];}
		Vector3i*	Faces();

		//���ö����������������ڴ�
		// isFaceTex���������Ƕ�������texCoordNumber��������ĸ���
		// ���isFaceTex=false������Ҫָ��texCoordNumber
		void				SetTexture(sn3DImageData<byte> *imageData,bool isFaceTex,uint texCoordNumber);
	
		inline bool			HasTexture()			{return m_hasTexture;}			// �Ƿ�������
		inline bool			IsFaceTexture()			{return m_isFaceTex;}			// �Ƕ���������������
		inline uint			GetTexNum()				{return m_uTexCoordNum;}

		inline sn3DImageData<byte> *GetTexture()	{return &m_texImage;}			// ����������� add by hu 2011-8-29
		inline Vector2f&	TexCoord(uint i)		{return m_aTexCoord[i];}		// ����ÿһ����������
		inline Vector3i&	IndexCoord(uint i)		{return m_aTexCoordIndex[i];}		// ����ÿһ����������
		inline Vector3i&	FaceTexIndex(uint i)	{return m_aFTexIndex[i];}		// ����ÿһ���������������
		void	ClearTexture();
	

		// ͨ�����÷�ʽ�����ʿ��ͷ������
		inline Vector3f&	FNormal(uint i)	{ return m_aFNormal[i];}
		inline ColorRGB&	FColor(uint i)	{ return m_aFColor[i];}
		inline uint&		FIdentity(uint i){ return m_aFIdentity[i];}
		inline FaceFlag&	FFlag(uint i)	{ return m_aFFlag[i];}
		
		
		// ͨ��ָ�뷽ʽ�����ʿ��ͷ�����
		Vector3f*	FNormal();
		ColorRGB*   FColor();
		uint*		FIdentity();

		// ͨ��Buffer��ʽ����
		int*	FacesBuffer();
		float*	FNormalBuffer();
		float*  FColorBuffer();
	
		// ��־λ����
		void	InitFFlags();

		
		/// ͨ�������־λ(m_aVFlag)�������־λ(m_aFFlag)��ͨ���ڱ༭ʱ��ɾ������ʹ��
		virtual	void	UpdateFace();							//  m_aVFlag => m_aFFlag
		virtual	void    UpdateVertex();							// ����仯�ˣ���Ҫ���¶���
		virtual	void    UpdateValidFN();

		// ���ͷ����
		inline bool	IsEnableFNormal()		{ return (m_uFFieldFlag&FACE_FIELD_NORMAL)	!=0;}
		inline bool	IsEnableFColor()		{ return (m_uFFieldFlag&FACE_FIELD_COLOR)		!=0;}
		inline bool	IsEnableFIdentity()		{ return (m_uFFieldFlag&FACE_FIELD_IDENTITY)	!=0;}

		// ���ͷ�����ķ�����ͷ�
		void	EnableFNormal();
		void	DisableFNormal();

		void	EnableFColor();
		void	DisableFColor();

		void	EnableFIdentity();
		void	DisableFIdentity();
// 		void    SetTexCoord(float u,float v);  //��ʱ
// 		void    SetIndexTexCoord(int index0,int index1,int index2);  //��ʱ
// 		void    SetTexCoordh(int h,int w);    //��ʱ
// 		void    GetTexCoord(int &h,int &w);  //��ʱ
		int     GetTexCoord();
		void	SetTexture(sn3DImageData<byte> *imageData); //��ʱ
		void    clearTexCoord();
		int     GetTexCoordSize();
		int     GetIndexTexSize();
		void	EnableIndexColor(int texcoordsize);
		void    UnEnableIndexColor();

		// �������˹�ϵ
		sn3DTopology *GetTop();					// ͨ�����˷�������
		void CreateTopology();
		void DestoryTopology();

		// ���� ѹ���ڴ�
		void  Compact();
		void  Clear();			// �����������

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
		uint					m_uFN;					// �������
		uint				    m_uFFieldFlag;

		// ��ѡ���
		std::vector<Vector3i>		m_aFaces;	// ָ�򶥵����
		std::vector<FaceFlag>		m_aFFlag;

		// ��ѡ���
		std::vector<Vector3f>		m_aFNormal;
		std::vector<ColorRGB>		m_aFColor;
		std::vector<uint>			m_aFIdentity;

		//���� add by hu 
		bool						m_hasTexture;			// ��ģ���Ƿ�������
		sn3DImageData<byte>         m_texImage; 
		bool						m_isFaceTex;			// ���m_isFaceTexΪfalse��ʾ��������m_aTexIndexΪ�գ�����m_uVTexCoordNum����m_uVN
		uint						m_uTexCoordNum;			// ���������������붥����δ�����

		
		std::vector<Vector3i>		m_aFTexIndex;			// ���������ꡣm_hasTexIndexΪfalse������Ϊ�ա�
		std::vector<Vector2f>		m_aTexCoord;			// ��������
		std::vector<Vector3i>		m_aTexCoordIndex;			// ��������
		int                         m_TexCoored;

		sn3DTopology				*m_pTopology;     // Ӧ��ָ���Ƿ�ֻ����Ϊ�ο����ݶ���������ڴ���� [2011-5-31 18:35 ChenKun]
		friend class sn3DTopology;
		friend class sn3DVertex;
		friend class sn3DFace;
	};
}

#endif // _sn3DTriMesh_H