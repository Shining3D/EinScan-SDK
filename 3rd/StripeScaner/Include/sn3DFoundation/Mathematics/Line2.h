// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef LINE2_H
#define LINE2_H

#include "sn3DFoundationLIB.h"
#include "Vector2.h"

namespace sn3DFoundation
{

template <class Real>
class Line2
{
public:
    // The line is represented as P+t*D where P is the line origin and D is
    // a unit-length direction vector.  The user must ensure that the
    // direction vector satisfies this condition.

    // construction
    Line2 ();  // uninitialized
    Line2 (const Vector2<Real>& rkOrigin, const Vector2<Real>& rkDirection);

    Vector2<Real> Origin, Direction;
};

#include "Line2.inl"

typedef Line2<float> Line2f;
typedef Line2<double> Line2d;

}

#endif
