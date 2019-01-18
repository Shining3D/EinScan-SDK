#ifndef _sn3DSpaceBox_H
#define _sn3DSpaceBox_H
// ==========================================================================
// File name:	sn3DSpaceBox.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	均匀空间结构
//	例子：
//		
//
// Histroy:		
//	- Created : 2009/09/05  fanran 
//	- Modified: 2013/12/04  wuzq
//
// ============================================================================
#include "Vector3.h"
#include "sn3DPointSet.h"

#include <vector>
using namespace sn3DFoundation;

namespace sn3DCore
{
	class sn3DSpaceBox
	{
		// SpaceBoxEntry表示空间剖分的一个单元格
		class SpaceBoxEntry 
		{
		public:
			SpaceBoxEntry():m_size(0),m_beginIndex(0){}

			int m_size;			//该方格中所包含的元素数量          
			int m_beginIndex;	//数据池中起始地址
		};

	public:

		sn3DSpaceBox(void);
		~sn3DSpaceBox(void);

	public:

		//初始化空间剖分结构
		void Initialize(sn3DPointSet* m,int scale);
		void Initialize(Vector3f * pointData,int num,int scale);
		void Initialize(Vector3f * pointData, unsigned char* deleteFlag, int num,int scale);

		Vector3f GetMinPoint();							//获取最小点
		Vector3f GetMaxPoint();							//获取最大点
		int GetSpaceLength();							//获取空间长度

		// 返回值为单元点的个数，indexArry为点的索引
		int GetEntry(float x, float y, float z, int *& indexArry);
		int GetEntrySize(int x,int y,int z);			//获取单元格大小
		int GetEntryItem(int x,int y,int z,int index);	//获取单元格对象(index索引)
		
		void Clear();									//Clear是内存清除函数

	protected:
		int EntryIndex(int i, int j, int k);
		int CoordX(float x);
		int CoordY(float y);
		int CoordZ(float z);
		bool InSpace(float x, float y, float z);
	protected:

		std::vector<SpaceBoxEntry>	m_spaceBox;			//空间单元格
		std::vector<int>			m_dataPool;			//数据
		std::vector<int>			m_entryMap;			//单元格映射

		int			m_divisionNum;						//空间剖分的粒度
		Vector3f	m_maxCorner;						//空间结构的最大点(按x,y,z排序)
		Vector3f	m_minCorner;						//空间结构的最小点(按x,y,z排序)
		Vector3f	m_delta;							//为性能而预先计算的m_divisionNum/(m_maxCorner-m_minCorner)
	};
	inline int sn3DSpaceBox::EntryIndex(int i, int j, int k)	
	{ 
		return i*m_divisionNum*m_divisionNum+j*m_divisionNum+k;
	}
	inline int sn3DSpaceBox::CoordX(float x)					
	{
		int coord = (int)((x-m_minCorner.X())* m_delta.X());
		return coord;
	};
	inline int sn3DSpaceBox::CoordY(float y)	
	{
		int coord = (int)((y-m_minCorner.Y())* m_delta.Y());
		return coord;
	};
	inline int sn3DSpaceBox::CoordZ(float z)					
	{
		int coord = (int)((z-m_minCorner.Z())* m_delta.Z());
		return coord;
	};
	inline bool sn3DSpaceBox::InSpace(float x, float y, float z)
	{
		if(x<m_minCorner[0] || x>m_maxCorner[0])
			return false;
		if(y<m_minCorner[1] || y>m_maxCorner[1])
			return false;
		if(z<m_minCorner[2] || z>m_maxCorner[2] )
			return false;
		return true;
	}
	
}
#endif