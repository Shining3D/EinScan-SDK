// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CIRCLE2_H
#define CIRCLE2_H

#include "sn3DFoundationLIB.h"
#include "Vector2.h"

namespace sn3DFoundation
{

template <class Real>
class Circle2
{
public:
    // construction
    Circle2 ();  // uninitialized
    Circle2 (const Vector2<Real>& rkCenter, Real fRadius);

    Vector2<Real> Center;
    Real Radius;
};

#include "Circle2.inl"

typedef Circle2<float> Circle2f;
typedef Circle2<double> Circle2d;

}

#endif
