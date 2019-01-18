#ifndef _SN3DCORE_DATASET_DATAPROCESS_SN3DGAUSSIANSMOOTHING_H_
#define _SN3DCORE_DATASET_DATAPROCESS_SN3DGAUSSIANSMOOTHING_H_

// ==========================================================================
// File name:	sn3DGuassianSmoothing.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
//			Smooth -- ¸ßË¹Æ½»¬	
//					
// Histroy:		
//     Create by HzY 6/24/2013 
//
// ============================================================================

#include "sn3DTriMesh.h"
#include "sn3DRangeData.h"
namespace sn3DCore
{

class sn3DGaussianSmoothing
{
public:
	sn3DGaussianSmoothing(void){}
	~sn3DGaussianSmoothing(void){}

	bool Smooth(sn3DRangeData *range, int template_width, double sigma);
	bool SmoothNormal(sn3DRangeData *range, int template_width, double sigma);
private:
	void GaussianKernel(int tmpsize, double sigma, double *kernel);
	float GetMedianNum(float *farray, int low, int high, int fliterlen);
	void MedianSmoothing(sn3DRangeData *range, int tmpwidth);
	void GaussianSmoothing(sn3DRangeData *range, int tmpwidth, double sigma);
	void NormalMedianSmoothing(sn3DRangeData *range, int tmpwidth);
	void NormalGaussianSmoothing(sn3DRangeData *range, int tmpwidth, double sigma);
};

} //end namespace sn3DCore
#endif //end _SN3DCORE_DATASET_DATAPROCESS_SN3DGAUSSIANSMOOTHING_H_