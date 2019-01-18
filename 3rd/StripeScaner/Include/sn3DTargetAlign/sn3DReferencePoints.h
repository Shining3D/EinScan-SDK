// File: sn3DReferencePoints.h

#ifndef _sn3DReferencePoints_H
#define _sn3DReferencePoints_H

#ifdef SN3DTARGETALIGN_EXPORTS
#define SN3D_TARGET_ALIGN_API __declspec(dllexport)
#else
#define SN3D_TARGET_ALIGN_API __declspec(dllimport)
#endif

#include "stdlib.h"
#include "Vector"
using namespace std; 
namespace sn3DTargetAlign
{
	// mark point align class
	class RefPoints 
	{
	public:
		RefPoints():nPoint(0),xPoints(NULL),yPoints(NULL),zPoints(NULL),IDList(NULL),weights(NULL){InitTransform();}
//		~RefPoints()					{ Free();}
		~RefPoints(){};
		inline void Alloc(int n);		// Alloc memory £¬ point ºÍIDList
		inline void Free();				// Free memory
	protected:
		inline void InitTransform();	// initialization RT
	public:
		int nPoint;				// mark point bunber
		std::vector<double>  xVPoints;
		std::vector<double>  yVPoints;
		std::vector<double>  zVPoints;
		std::vector<int>     IDVLists;
		std::vector<double>  Vweights;
		double *xPoints;
		double *yPoints;
		double *zPoints;

		int *IDList;			// mark point id 
		double *weights;        // remark parm
		
		double trans[3];		// translation matrix
		double rotate[9];		// rotation matrix
	};

	inline void RefPoints::Alloc(int n)
	{
		Free();
		if(n<=0)return ;
		nPoint = n;
		xPoints = new double[nPoint];
		yPoints = new double[nPoint];
		zPoints = new double[nPoint];
		IDList  = new int[nPoint];
		weights = new double[nPoint];
		InitTransform();
	}
	inline void RefPoints::Free()
	{
		nPoint = 0;
		if( xPoints )
		{
			delete[] xPoints; xPoints= NULL;
			delete[] yPoints; yPoints= NULL;
			delete[] zPoints; zPoints= NULL;
			delete[] IDList;  IDList= NULL;
			delete[] weights; weights=NULL;
		}
	}
	inline void RefPoints::InitTransform()
	{
		for (int i=0;i<3; i++)
		{
			trans[i]=0.0;
			for (int j=0;j<3; j++)
				rotate[i*3+j]=(i==j);
		}
	}

}

#endif //_sn3DReferencePoints_H
