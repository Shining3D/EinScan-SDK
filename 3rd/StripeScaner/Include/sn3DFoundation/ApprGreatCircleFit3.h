// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef APPRGREATCIRCLEFIT3_H
#define APPRGREATCIRCLEFIT3_H

#include "sn3DFoundationLIB.h"
#include "Vector3.h"

namespace sn3DFoundation
{

// Least-squares fit of a great circle to unit-length vectors (x,y,z) by
// using distance measurements orthogonal (and measured along great circles)
// to the proposed great circle.  The inputs akPoint[] are unit length.  The
// returned value is unit length, call it N.  The fitted great circle is
// defined by Dot(N,X) = 0, where X is a unit-length vector on the great
// circle.
template <class Real> SN3D_FOUNDATION_ITEM
Vector3<Real> GreatCircleFit3 (int iQuantity, const Vector3<Real>* akVector);

// In addition to the least-squares fit of a great circle, the input vectors
// are projected onto that circle.  The sector of smallest angle (possibly
// obtuse) that contains the points is computed.  The endpoints of the arc
// of the sector are returned.  The returned endpoints A0 and A1 are
// perpendicular to the returned normal N.  Moreover, when you view the
// arc by looking at the plane of the great circle with a view direction
// of -N, the arc is traversed counterclockwise starting at A0 and ending
// at A1.
template <class Real>
class SN3D_FOUNDATION_ITEM GreatArcFit3
{
public:
    GreatArcFit3 (int iQuantity, const Vector3<Real>* akVector,
        Vector3<Real>& rkNormal, Vector3<Real>& rkArcEnd0,
        Vector3<Real>& rkArcEnd1);

private:
    class Item
    {
    public:
        Real U, V, Angle;

        bool operator< (const Item& rkItem) const
        {
            return Angle < rkItem.Angle;
        }
    };
};

}

#endif
