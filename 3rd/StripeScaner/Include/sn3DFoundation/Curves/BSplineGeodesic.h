// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef BSPLINEGEODESIC_H
#define BSPLINEGEODESIC_H

#include "sn3DFoundationLIB.h"
#include "RiemannianGeodesic.h"
#include "BSplineRectangle.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM BSplineGeodesic : public RiemannianGeodesic<Real>
{
public:
    BSplineGeodesic (const BSplineRectangle<Real>& rkBSpline);
    virtual ~BSplineGeodesic ();

    virtual void ComputeMetric (const GVector<Real>& rkPoint);
    virtual void ComputeChristoffel1 (const GVector<Real>& rkPoint);

private:
    using RiemannianGeodesic<Real>::m_kMetric;
    using RiemannianGeodesic<Real>::m_akChristoffel1;

    const BSplineRectangle<Real>* m_pkBSpline;
};

typedef BSplineGeodesic<float> BSplineGeodesicf;
typedef BSplineGeodesic<double> BSplineGeodesicd;

}

#endif
