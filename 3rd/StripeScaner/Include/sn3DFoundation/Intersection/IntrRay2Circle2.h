// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY2CIRCLE2_H
#define INTRRAY2CIRCLE2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray2.h"
#include "Circle2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay2Circle2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrRay2Circle2 (const Ray2<Real>& rkRay, const Circle2<Real>& rkCircle);

    // object access
    const Ray2<Real>& GetRay () const;
    const Circle2<Real>& GetCircle () const;

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
    const Circle2<Real>* m_pkCircle;

    // information about the intersection set
    int m_iQuantity;
    Vector2<Real> m_akPoint[2];
};

typedef IntrRay2Circle2<float> IntrRay2Circle2f;
typedef IntrRay2Circle2<double> IntrRay2Circle2d;

}

#endif
