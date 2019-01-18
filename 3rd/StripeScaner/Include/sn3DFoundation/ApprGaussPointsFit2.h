// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef APPRGAUSSPOINTSFIT2_H
#define APPRGAUSSPOINTSFIT2_H

#include "sn3DFoundationLIB.h"
#include "Box2.h"

namespace sn3DFoundation
{

// Fit points with a Gaussian distribution.  The center is the mean of the
// points, the axes are the eigenvectors of the covariance matrix, and the
// extents are the eigenvalues of the covariance matrix and are returned in
// increasing order.  The quantites are stored in a Box2<Real> just to have a
// single container.
template <class Real> SN3D_FOUNDATION_ITEM
Box2<Real> GaussPointsFit2 (int iQuantity, const Vector2<Real>* akPoint);

}

#endif
