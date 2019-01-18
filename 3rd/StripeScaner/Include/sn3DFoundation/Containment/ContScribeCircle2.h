// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CONTSCRIBECIRCLE2_H
#define CONTSCRIBECIRCLE2_H

#include "sn3DFoundationLIB.h"
#include "Circle2.h"
#include "LinearSystem.h"

namespace sn3DFoundation
{

// All functions return 'true' if circle has been constructed, 'false'
// otherwise (input points are linearly dependent).

// circle containing three 2D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Circumscribe (const Vector2<Real>& rkV0, const Vector2<Real>& rkV1,
    const Vector2<Real>& rkV2, Circle2<Real>& rkCircle);

// circle inscribing triangle of three 2D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Inscribe (const Vector2<Real>& rkV0, const Vector2<Real>& rkV1,
    const Vector2<Real>& rkV2, Circle2<Real>& rkCircle);

}

#endif
