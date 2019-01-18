// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY3PLANE3_H
#define INTRRAY3PLANE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray3.h"
#include "Plane3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay3Plane3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrRay3Plane3 (const Ray3<Real>& rkRay, const Plane3<Real>& rkPlane);

    // object access
    const Ray3<Real>& GetRay () const;
    const Plane3<Real>& GetPlane () const;

    // test-intersection query
    virtual bool Test ();

    // Find-intersection query.  The point of intersection is
    // P = origin + t*direction, with t >= 0.
    virtual bool Find ();
    Real GetRayT () const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Ray3<Real>* m_pkRay;
    const Plane3<Real>* m_pkPlane;

    // information about the intersection set
    Real m_fRayT;
};

typedef IntrRay3Plane3<float> IntrRay3Plane3f;
typedef IntrRay3Plane3<double> IntrRay3Plane3d;

}

#endif
