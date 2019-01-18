// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef SINGLECURVE3_H
#define SINGLECURVE3_H

#include "sn3DFoundationLIB.h"
#include "Curve3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM SingleCurve3 : public Curve3<Real>
{
public:
    // abstract base class
    SingleCurve3 (Real fTMin, Real fTMax);

    // length-from-time and time-from-length
    virtual Real GetLength (Real fT0, Real fT1) const;
    virtual Real GetTime (Real fLength, int iIterations = 32,
        Real fTolerance = (Real)1e-06) const;

protected:
    using Curve3<Real>::m_fTMin;
    using Curve3<Real>::m_fTMax;
    using Curve3<Real>::GetTotalLength;

    static Real GetSpeedWithData (Real fTime, void* pvData);
};

typedef SingleCurve3<float> SingleCurve3f;
typedef SingleCurve3<double> SingleCurve3d;

}

#endif
