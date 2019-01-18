///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
/// @file	sn3DCore.h
/// @brief	数据结构基础库\n
///			包含：类型重定义、算法进度回调函数、异常、字符串处理辅助函数、
///         图像数据，几何数据（点云、网格、深度图）等功能
/// @author wuzq
/// @version 1.0
/// @date 2010-01-24
//////////////////////////////////////////////////////////////////////////////


#ifndef _sn3DCore_H
#define _sn3DCore_H

// System
#include "sn3Dglobaldef.h"
#include "sn3DCallback.h"
#include "sn3DException.h"
#include "sn3DStringHelper.h"

// Image
#include "sn3DImageArray.h"
#include "sn3DImageData.h"

// Mesh
#include "sn3DDataBase.h"
#include "sn3DPointSet.h"
#include "sn3DTriMesh.h"
#include "sn3DVertex.h"
#include "sn3DEdge.h"
#include "sn3DFace.h"
#include "sn3DSimplex.h"
#include "sn3DTopology.h"
#include "sn3DOctree.h"

// Range
#include "sn3DRangeData.h"
#include "sn3DRangeOperator.h"
#include "sn3DRgeFile.h"
#include "sn3DSmoothing.h"
#include "sn3DRemoveCircle.h"
#include "sn3DGaussSmooth.h"


#endif


