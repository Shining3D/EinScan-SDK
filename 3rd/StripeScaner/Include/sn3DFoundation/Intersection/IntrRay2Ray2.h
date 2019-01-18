// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY2RAY2_H
#define INTRRAY2RAY2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay2Ray2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrRay2Ray2 (const Ray2<Real>& rkRay0, const Ray2<Real>& rkRay1);

    // object access
    const Ray2<Real>& GetRay0 () const;
    const Ray2<Real>& GetRay1 () const;

    // static intersection query
    virtual bool Test ();
    virtual bool Find ();

    // The intersection set.  If the rays do not intersect, GetQuantity()
    // returns 0.  If the rays intersect in a single point, GetQuantity()
    // returns 1, in which case GetPoint() returns the point of intersection
    // and Intersector::GetIntersectionType() returns IT_POINT.  If the rayd
    // are collinear, GetQuantity() returns INT_MAX and
    // Intersector::GetIntersectionType() returns IT_RAY.
    int GetQuantity () const;
    const Vector2<Real>& GetPoint () const;

private:
    using Intersector<Real,Vector2<Real> >::IT_EMPTY;
    using Intersector<Real,Vector2<Real> >::IT_POINT;
    using Intersector<Real,Vector2<Real> >::IT_RAY;
    using Intersector<Real,Vector2<Real> >::m_iIntersectionType;

    // Determine the relationship between the lines that contain the rays.
    int Classify (Real* afS, Vector2<Real>* pkDiff, Vector2<Real>* pkDiffN);

    // the objects to intersect
    const Ray2<Real>* m_pkRay0;
    const Ray2<Real>* m_pkRay1;

    // information about the intersection set
    int m_iQuantity;
    Vector2<Real> m_kPoint;
};

typedef IntrRay2Ray2<float> IntrRay2Ray2f;
typedef IntrRay2Ray2<double> IntrRay2Ray22d;

}

#endif
