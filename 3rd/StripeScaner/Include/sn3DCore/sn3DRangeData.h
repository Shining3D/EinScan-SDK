#ifndef _sn3DRangeData_H
#define _sn3DRangeData_H

///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2017-2045, Shining 3D Tech. Co., Ltd.
//
/// @file	sn3DRangeData.h
///		Point data with UV coordinates are said to be "ordered points".
///		For a given ordered point P1 with UV coordinates (u,v), a "cell" is
///		implicitly defined if other ordered points P2, P3 and P4 with
///	    UV coordinates (u+1,v), (u+1,v+1) and (u,v+1) exist.
///
///		If the point P1, P2, P3, P4 are traversed in counter-clockwise order
///		from a given view position, The side of the cell visible from that
///		position shall be called the "front".
///
/// @author Will
/// @version 1.0
/// @date 2017-01-11
///
//////////////////////////////////////////////////////////////////////////////


#include "sn3DPointSet.h"
#include "MatrixData.h"
#include "sn3DImageData.h"
#include <vector>
using namespace std;

namespace sn3DCore
{
	// mark point
	struct RefPointsData
	{
		RefPointsData():num(0){};			// Alloc memory
		inline void resize(int n);			// Free memory

		// membership
		int num;
		std::vector<Vector3d>	pos;
		std::vector<Vector3d>   norm;
		std::vector<int>		id;
		std::vector<double>     weight;
	};

	//                                        width,col
	// coordinate system:              |---------------------|   --
	//           / z                   |  ------> v,j,x      |   |
	//          /                      |  |                  |   |
	//        *------> x               |  | u,i,y            |   height,
	//        |                        |  V                  |   row
	//        | y                      |                     |   |
	//        v                        |_____________________|  _|_
	
	// Reserved word
	struct UVCoord
	{
		int u;	//   i,y [0,height] or [0, row]
		int v;  //  j,x  [0,width] or [0, col]
	};

	//=========================================================================
	// point cloud class
	class sn3DRangeData:public sn3DPointSet
	{
		typedef sn3DPointSet inherited;
	public:
		sn3DRangeData();
		virtual ~sn3DRangeData();

	public:
		// 
		bool SetData(uint w, uint h, int *mapImage, uint npt, float *x, float *y, float *z); // Reserved word
		bool SetData(uint w, uint h, int *mapImage, uint npt, double *x, double *y, double *z);// Reserved word
		
		bool SetCell(uint w, uint h, int *mapImage);	// Reserved word							//
		bool SetCell(uint w, uint h,UVCoord *arrayUV=NULL, char *arrayFlag=NULL);	//  Reserved word
		bool SetColor(sn3DImageData<byte> *rgbImage);								//  Reserved word
	
		uint GetWidth()								{ return m_width;};
		uint GetHeight()							{ return m_height;};

	
		void SetCellFlag(uint i, char valid)		{ m_aCellFlag[i]= valid;}  // Reserved word
		char CellFlag( uint i)						{ return m_aCellFlag[i];}; // Reserved word
		UVCoord &GetUV( uint i)						{ return m_aUVCoord[i];};  // Reserved word

		int *UVBuffer();          // Reserved word
		char *CellFlagBuffer();  // Reserved word
		//设置扫描仪方向
		void		SetCameraDir(double *dir);
		Vector3d&	GetCameraDir()					{ return m_cameraDir;}
		Matrix4d&	GetCameraMatrix()				{ return m_cameraRT;};
		void		SetCameraMatrix(double *rotate, double *trans);
		void		GetCameraMatrix(double *rotate, double *trans);
		double      Getmeadistance(){return m_meadistance;}      // Reserved word
		void        Setmeadistance(double meadistance)  {m_meadistance =meadistance; } 
	//	void        GetTexture(sn3DImageData<byte> Texture);

		inline bool IsHasTexture()					{return m_bTexture;}   //get texture iamge
		const sn3DImageData<byte>	*GetTexture()const;

		// 标志点信息的访问
		RefPointsData  &GetRefPoints()				{ return m_refPoints;}  //get mark point
	
	public:
		
		// 操作
				void ComputeVNormal();									// Compute the point' normal
				void ComputeCellNormal(MatrixData<int> &map,vector<Vector3f> &cellNormal);	// // Reserved word (0.0f, 0.0f, 0.0f)
        //updata the point data
		virtual	void UpdateValidFN();                                   //get the new face numbers.-- Reserved word
		// uptata the cloud data by set the some point as false 
		//then use the function to get the result data
		virtual void UpdateVertex();
		// updata the the face information
		virtual void UpdateFace();										
				void CreateIndexMap(MatrixData<int>	&map);     // Reserved word
				void CreateCellMaskMap(MatrixData<bool>	&map);  // Reserved word
	public:
		// 内存

		virtual void  Squeeze();                            // Reserved word
		virtual void  Clear();								// Reserved word

		
		virtual void ClearMemory();       // Reserved word
		virtual bool SwapOutData();	     // Reserved word
		virtual bool SwapInData();		// Reserved word

		// 模型读入写出
		virtual bool LoadData(const TCHAR* szPath);
		virtual bool SaveData(const TCHAR* szPath);

		bool SaveRefPoints();
		bool SaveTransformation();

		void  DownSample(uint factorh, uint factorx);
	public:
		void DebugPrintFlags();
		void DebugPrintCell();
		void DebugPrintAsc(std::string& fileName,bool bLocal=false);

	protected:
		uint		m_width;					// image width
		uint		m_height;					// image height
		Vector3d	m_cameraDir;
		Matrix4d	m_cameraRT;					// the camera RT Xc = m_cameraRT * Xw

		std::vector<UVCoord> m_aUVCoord;		// Reserved word
		std::vector<char>	 m_aCellFlag;		// Reserved word

		RefPointsData		m_refPoints;		// the mark point of the cloud data

		// 可选属性
		bool				m_bTexture;         //the texture information
		bool				m_hasTexCoord;		// 
		sn3DImageData<byte>	 m_texure;			// 
		std::vector<UVCoord> m_aTexCoord;		//
		double               m_meadistance;     //
		
	};

	//=========================================================================
	inline void RefPointsData::resize(int n)			// Alloc memory
	{
		num = n;
		pos.resize(n);
		id.resize(n);
		weight.resize(n);
	}
}

#endif // _sn3DRangeData_H
