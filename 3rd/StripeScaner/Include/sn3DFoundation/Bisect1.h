// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef BISECT1_H
#define BISECT1_H

#include "sn3DFoundationLIB.h"
#include "System.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM Bisect1
{
public:
    typedef Real (*Function)(Real);

    Bisect1 (Function oF, int iMaxLevel, Real fTolerance);

    bool Bisect (Real fX0, Real fX1, Real& rfRoot);

private:
    // input data and functions
    Function m_oF;
    int m_iMaxLevel;
    Real m_fTolerance;
};

typedef Bisect1<float> Bisect1f;
typedef Bisect1<double> Bisect1d;

}

#endif
