// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef LINE3_H
#define LINE3_H

#include "sn3DFoundationLIB.h"
#include "Vector3.h"

namespace sn3DFoundation
{

template <class Real>
class Line3
{
public:
    // The line is represented as P+t*D where P is the line origin and D is
    // a unit-length direction vector.  The user must ensure that the
    // direction vector satisfies this condition.

    // construction
    Line3 ();  // uninitialized
    Line3 (const Vector3<Real>& rkOrigin, const Vector3<Real>& rkDirection);

    Vector3<Real> Origin, Direction;
};

#include "Line3.inl"

typedef Line3<float> Line3f;
typedef Line3<double> Line3d;

}

#endif
