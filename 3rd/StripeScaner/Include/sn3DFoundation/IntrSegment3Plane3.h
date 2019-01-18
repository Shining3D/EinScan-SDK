// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSEGMENT3PLANE3_H
#define INTRSEGMENT3PLANE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Segment3.h"
#include "Plane3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSegment3Plane3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSegment3Plane3 (const Segment3<Real>& rkSegment,
        const Plane3<Real>& rkPlane);

    // object access
    const Segment3<Real>& GetSegment () const;
    const Plane3<Real>& GetPlane () const;

    // test-intersection query
    virtual bool Test ();

    // Find-intersection query.  The point of intersection is
    // P = origin + t*direction, with |t| <= e, where e is the segment
    // extent.
    virtual bool Find ();
    Real GetSegmentT () const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Segment3<Real>* m_pkSegment;
    const Plane3<Real>* m_pkPlane;

    // information about the intersection set
    Real m_fSegmentT;
};

typedef IntrSegment3Plane3<float> IntrSegment3Plane3f;
typedef IntrSegment3Plane3<double> IntrSegment3Plane3d;

}

#endif
