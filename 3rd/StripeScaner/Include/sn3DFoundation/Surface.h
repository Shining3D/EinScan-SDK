// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef SURFACE_H
#define SURFACE_H

#include "sn3DFoundationLIB.h"
#include "System.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM Surface
{
public:
    virtual ~Surface ();

protected:
    // abstract base class
    Surface ();
};

typedef Surface<float> Surfacef;
typedef Surface<double> Surfaced;

}

#endif
