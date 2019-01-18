// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTEGRATE1_H
#define INTEGRATE1_H

#include "sn3DFoundationLIB.h"
#include "System.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM Integrate1
{
public:
    // last parameter is for user-defined data
    typedef Real (*Function)(Real,void*);

    static Real RombergIntegral (int iOrder, Real fA, Real fB, Function oF,
        void* pvUserData = 0);

    static Real GaussianQuadrature (Real fA, Real fB, Function oF,
        void* pvUserData = 0);

    static Real TrapezoidRule (int iNumSamples, Real fA, Real fB,
        Function oF, void* pvUserData = 0);
};

typedef Integrate1<float> Integrate1f;
typedef Integrate1<double> Integrate1d;

}

#endif
