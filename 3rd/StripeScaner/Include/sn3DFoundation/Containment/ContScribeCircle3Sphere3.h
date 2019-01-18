// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CONTSCRIBECIRCLE3SPHERE3_H
#define CONTSCRIBECIRCLE3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Circle3.h"
#include "Sphere3.h"

namespace sn3DFoundation
{

// All functions return 'true' if circle/sphere has been constructed,
// 'false' otherwise (input points are linearly dependent).

// circle containing three 3D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Circumscribe (const Vector3<Real>& rkV0, const Vector3<Real>& rkV1,
    const Vector3<Real>& rkV2, Circle3<Real>& rkCircle);

// sphere containing four 3D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Circumscribe (const Vector3<Real>& rkV0, const Vector3<Real>& rkV1,
    const Vector3<Real>& rkV2, const Vector3<Real>& rkV3,
    Sphere3<Real>& rkSphere);

// circle inscribing triangle of three 3D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Inscribe (const Vector3<Real>& rkV0, const Vector3<Real>& rkV1,
    const Vector3<Real>& rkV2, Circle3<Real>& rkCircle);

// sphere inscribing tetrahedron of four 3D points
template <class Real> SN3D_FOUNDATION_ITEM
bool Inscribe (const Vector3<Real>& rkV0, const Vector3<Real>& rkV1,
    const Vector3<Real>& rkV2, const Vector3<Real>& rkV3,
    Sphere3<Real>& rkSphere);

}

#endif
