#ifndef _sn3DSpaceBox_H
#define _sn3DSpaceBox_H
// ==========================================================================
// File name:	sn3DSpaceBox.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	���ȿռ�ṹ
//	���ӣ�
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
		// SpaceBoxEntry��ʾ�ռ��ʷֵ�һ����Ԫ��
		class SpaceBoxEntry 
		{
		public:
			SpaceBoxEntry():m_size(0),m_beginIndex(0){}

			int m_size;			//�÷�������������Ԫ������          
			int m_beginIndex;	//���ݳ�����ʼ��ַ
		};

	public:

		sn3DSpaceBox(void);
		~sn3DSpaceBox(void);

	public:

		//��ʼ���ռ��ʷֽṹ
		void Initialize(sn3DPointSet* m,int scale);
		void Initialize(Vector3f * pointData,int num,int scale);
		void Initialize(Vector3f * pointData, unsigned char* deleteFlag, int num,int scale);

		Vector3f GetMinPoint();							//��ȡ��С��
		Vector3f GetMaxPoint();							//��ȡ����
		int GetSpaceLength();							//��ȡ�ռ䳤��

		// ����ֵΪ��Ԫ��ĸ�����indexArryΪ�������
		int GetEntry(float x, float y, float z, int *& indexArry);
		int GetEntrySize(int x,int y,int z);			//��ȡ��Ԫ���С
		int GetEntryItem(int x,int y,int z,int index);	//��ȡ��Ԫ�����(index����)
		
		void Clear();									//Clear���ڴ��������

	protected:
		int EntryIndex(int i, int j, int k);
		int CoordX(float x);
		int CoordY(float y);
		int CoordZ(float z);
		bool InSpace(float x, float y, float z);
	protected:

		std::vector<SpaceBoxEntry>	m_spaceBox;			//�ռ䵥Ԫ��
		std::vector<int>			m_dataPool;			//����
		std::vector<int>			m_entryMap;			//��Ԫ��ӳ��

		int			m_divisionNum;						//�ռ��ʷֵ�����
		Vector3f	m_maxCorner;						//�ռ�ṹ������(��x,y,z����)
		Vector3f	m_minCorner;						//�ռ�ṹ����С��(��x,y,z����)
		Vector3f	m_delta;							//Ϊ���ܶ�Ԥ�ȼ����m_divisionNum/(m_maxCorner-m_minCorner)
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