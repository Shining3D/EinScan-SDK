// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSEGMENT3SPHERE3_H
#define INTRSEGMENT3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Segment3.h"
#include "Sphere3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSegment3Sphere3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSegment3Sphere3 (const Segment3<Real>& rkSegment,
        const Sphere3<Real>& rkSphere);

    // object access
    const Segment3<Real>& GetSegment () const;
    const Sphere3<Real>& GetSphere () const;

    // test-intersection query
    virtual bool Test ();

    // find-intersection query
    virtual bool Find ();
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;
    Real GetSegmentT (int i) const;

    // dynamic test-intersection query
    virtual bool Test (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // Dynamic find-intersection query.  The first point of contact is
    // accessed by GetPoint(0).  The first time of contact is accessed by
    // GetContactTime().
    virtual bool Find (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    Real ZeroThreshold;  // default = Math<Real>::ZERO_TOLERANCE

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::IT_OTHER;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;
    using Intersector<Real,Vector3<Real> >::m_fContactTime;

    // the objects to intersect
    const Segment3<Real>* m_pkSegment;
    const Sphere3<Real>* m_pkSphere;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
    Real m_afSegmentT[2];
};

typedef IntrSegment3Sphere3<float> IntrSegment3Sphere3f;
typedef IntrSegment3Sphere3<double> IntrSegment3Sphere3d;

}

#endif
