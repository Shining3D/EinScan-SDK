// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSEGMENT3CAPSULE3_H
#define INTRSEGMENT3CAPSULE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Segment3.h"
#include "Capsule3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSegment3Capsule3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSegment3Capsule3 (const Segment3<Real>& rkSegment,
        const Capsule3<Real>& rkCapsule);

    // object access
    const Segment3<Real>& GetSegment () const;
    const Capsule3<Real>& GetCapsule () const;

    // static intersection queries
    virtual bool Test ();
    virtual bool Find ();

    // the intersection set
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;
    Real GetParameter (int i) const;  // segment parameters for points

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Segment3<Real>* m_pkSegment;
    const Capsule3<Real>* m_pkCapsule;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
    Real m_afParameter[2];
};

typedef IntrSegment3Capsule3<float> IntrSegment3Capsule3f;
typedef IntrSegment3Capsule3<double> IntrSegment3Capsule3d;

}

#endif
