#ifndef _sn3DRandomBox_H
#define _sn3DRandomBox_H
// ==========================================================================
// File name:	sn3DRandomBox.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	功能：确定采样间距
//
// Histroy:		
//	- Created : 2012/09/05  
//
// ============================================================================

#include "sn3DOctree.h"

namespace sn3DCore
{
	class sn3DRandomBox
	{
	public:
		sn3DRandomBox();
		~sn3DRandomBox();
		void SetTree(sn3DOctree *tree){ m_tree =tree; };

		// averageCount(m0) 100 / 30老版本,  sampleCount(s0) 100
		float DetermineWidth(int averageCount=100, int sampleCount=100);
	protected:
		void  UniqueRandom(std::vector<int> &data, int count, int maxValue);
		int	  AverageYield( float radius );

	protected:
		sn3DOctree*			m_tree;
		int					m_count;

		std::vector<int>	m_samplePnt;
		int					m_sampleCount;

	};

}

#endif // _sn3DRandomBox_H