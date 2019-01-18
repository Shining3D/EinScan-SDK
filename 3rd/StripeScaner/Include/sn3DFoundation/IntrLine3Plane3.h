// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRLINE3PLANE3_H
#define INTRLINE3PLANE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Line3.h"
#include "Plane3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrLine3Plane3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrLine3Plane3 (const Line3<Real>& rkLine, const Plane3<Real>& rkPlane);

    // object access
    const Line3<Real>& GetLine () const;
    const Plane3<Real>& GetPlane () const;

    // test-intersection query
    virtual bool Test ();

    // Find-intersection query.  The point of intersection is
    // P = origin + t*direction.
    virtual bool Find ();
    Real GetLineT () const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_LINE;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Line3<Real>* m_pkLine;
    const Plane3<Real>* m_pkPlane;

    // information about the intersection set
    Real m_fLineT;
};

typedef IntrLine3Plane3<float> IntrLine3Plane3f;
typedef IntrLine3Plane3<double> IntrLine3Plane3d;

}

#endif
