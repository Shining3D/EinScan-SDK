// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY2SEGMENT2_H
#define INTRRAY2SEGMENT2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray2.h"
#include "Segment2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay2Segment2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrRay2Segment2 (const Ray2<Real>& rkRay,
        const Segment2<Real>& rkSegment);

    // object access
    const Ray2<Real>& GetRay () const;
    const Segment2<Real>& GetSegment () const;

    // static intersection query
    virtual bool Test ();
    virtual bool Find ();

    // The intersection set.  If the ray and segment do not intersect,
    // GetQuantity() returns 0.  If the ray and segment intersect in a single
    // point, GetQuantity() returns 1, in which case GetPoint() returns the
    // point of intersection and Intersector::GetIntersectionType() returns
    // IT_POINT.  If the ray and segment are collinear and intersect in a
    // segment, GetQuantity() returns INT_MAX and
    // Intersector::GetIntersectionType() returns IT_SEGMENT.
    int GetQuantity () const;
    const Vector2<Real>& GetPoint () const;

private:
    using Intersector<Real,Vector2<Real> >::IT_EMPTY;
    using Intersector<Real,Vector2<Real> >::IT_POINT;
    using Intersector<Real,Vector2<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector2<Real> >::m_iIntersectionType;

    // Determine the relationship between the lines that contain the ray and
    // the segment.
    int Classify (Real* afS, Vector2<Real>* pkDiff, Vector2<Real>* pkDiffN);

    // the objects to intersect
    const Ray2<Real>* m_pkRay;
    const Segment2<Real>* m_pkSegment;

    // information about the intersection set
    int m_iQuantity;
    Vector2<Real> m_kPoint;
};

typedef IntrRay2Segment2<float> IntrRay2Segment2f;
typedef IntrRay2Segment2<double> IntrRay2Segment2d;

}

#endif
