// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY2ARC2_H
#define INTRRAY2ARC2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray2.h"
#include "Arc2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay2Arc2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrRay2Arc2 (const Ray2<Real>& rkRay, const Arc2<Real>& rkArc);

    // object access
    const Ray2<Real>& GetRay () const;
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
    const Ray2<Real>* m_pkRay;
    const Arc2<Real>* m_pkArc;

    // information about the intersection set
    int m_iQuantity;
    Vector2<Real> m_akPoint[2];
};

typedef IntrRay2Arc2<float> IntrRay2Arc2f;
typedef IntrRay2Arc2<double> IntrRay2Arc2d;

}

#endif
