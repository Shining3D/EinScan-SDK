// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef APPRLINEFIT3_H
#define APPRLINEFIT3_H

#include "sn3DFoundationLIB.h"
#include "Line3.h"

namespace sn3DFoundation
{

// Least-squares fit of a line to (x,y,z) data by using distance measurements
// orthogonal to the proposed line.
template <class Real> SN3D_FOUNDATION_ITEM
Line3<Real> OrthogonalLineFit3 (int iQuantity, const Vector3<Real>* akPoint);

}

#endif
