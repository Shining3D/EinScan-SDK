// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSEGMENT2ARC2_H
#define INTRSEGMENT2ARC2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Segment2.h"
#include "Arc2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSegment2Arc2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrSegment2Arc2 (const Segment2<Real>& rkSegment,
        const Arc2<Real>& rkCircle);

    // object access
    const Segment2<Real>& GetSegment () const;
    const Arc2<Real>& GetArc () const;

    // static intersection query
    virtual bool Find ();

    // the intersection set
    int GetQuantity () const;
    const Vector2<Real>& GetPoint (int i) const;

private:
    using Intersector<Real,Vector2<Real> >::IT_EMPTY;
    using Intersector<Real,Vector2<Real> >::IT_POINT;
    using Intersector<Real,Vector2<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Segment2<Real>* m_pkSegment;
    const Arc2<Real>* m_pkArc;

    // information about the intersection set
    int m_iQuantity;
    Vector2<Real> m_akPoint[2];
};

typedef IntrSegment2Arc2<float> IntrSegment2Arc2f;
typedef IntrSegment2Arc2<double> IntrSegment2Arc2d;

}

#endif
