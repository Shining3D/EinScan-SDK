// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef SPHERE3_H
#define SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Vector3.h"

namespace sn3DFoundation
{

template <class Real>
class Sphere3
{
public:
    // The sphere is represented as |X-C| = R where C is the center and R is
    // the radius.

    Sphere3 ();  // uninitialized
    Sphere3 (const Vector3<Real>& rkCenter, Real fRadius);
    Sphere3 (const Sphere3& rkSphere);

    // assignment
    Sphere3& operator= (const Sphere3& rkSphere);

    Vector3<Real> Center;
    Real Radius;
};

#include "Sphere3.inl"

typedef Sphere3<float> Sphere3f;
typedef Sphere3<double> Sphere3d;

}

#endif
