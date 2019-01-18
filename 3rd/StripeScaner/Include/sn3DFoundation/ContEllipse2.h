// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CONTELLIPSE2_H
#define CONTELLIPSE2_H

#include "sn3DFoundationLIB.h"
#include "Ellipse2.h"
#include "Line2.h"

namespace sn3DFoundation
{

// The input points are fit with a Gaussian distribution.  The center C of the
// ellipsoid is chosen to be the mean of the distribution.  The axes of the
// ellipsoid are chosen to be the eigenvectors of the covariance matrix M.
// The shape of the ellipsoid is determined by the absolute values of the
// eigenvalues.
//
// WARNING.  The construction is ill-conditioned if the points are (nearly)
// collinear.  In this case M has a (nearly) zero eigenvalue, so inverting M
// is problematic.
template <class Real> SN3D_FOUNDATION_ITEM
Ellipse2<Real> ContEllipse (int iQuantity, const Vector2<Real>* akPoint);

// Project an ellipse onto a line.  The projection interval is [min,max]
// and corresponds to the line segment P+t*D, where min <= t <= max.
template <class Real> SN3D_FOUNDATION_ITEM
void ProjectEllipse (const Ellipse2<Real>& rkEllipse,
    const Line2<Real>& rkLine, Real& rfMin, Real& rfMax);

// Construct a bounding ellipse for the two input ellipses.
template <class Real> SN3D_FOUNDATION_ITEM
const Ellipse2<Real> MergeEllipses (const Ellipse2<Real>& rkEllipse0,
    const Ellipse2<Real>& rkEllipse1);

}

#endif
