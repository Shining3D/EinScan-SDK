// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRTRIANGLE3SPHERE3_H
#define INTRTRIANGLE3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Triangle3.h"
#include "Sphere3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrTriangle3Sphere3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrTriangle3Sphere3 (const Triangle3<Real>& rkTriangle,
        const Sphere3<Real>& rkSphere);

    // Object access.
    const Triangle3<Real>& GetTriangle () const;
    const Sphere3<Real>& GetSphere () const;

    // Static test-intersection query.
    virtual bool Test ();

    // Dynamic find-intersection query.  If the query returns 'true', use
    // GetContactTime() to obtain the first time of contact.  If this time
    // is zero, the triangle is already intersecting the sphere and no
    // contact set is computed.  If this time is positive, obtain the
    // first point of contact using GetPoint().
    virtual bool Find (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    const Vector3<Real>& GetPoint () const;

private:
    using Intersector<Real,Vector3<Real> >::m_fContactTime;

    // Support for the dynamic query.
    bool FindTriangleSphereCoplanarIntersection (int iVertex,
        const Vector3<Real> akV[3], const Vector3<Real>& rkSideNorm,
        const Vector3<Real>& rkSide, Real fTMax,
        const Vector3<Real>& rkVelocity0, const Vector3<Real>& rkVelocity1);

    bool FindSphereVertexIntersection (const Vector3<Real>& rkVertex,
        Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // The objects to intersect.
    const Triangle3<Real>* m_pkTriangle;
    const Sphere3<Real>* m_pkSphere;

    // The point of contact for dynamic queries.
    Vector3<Real> m_kPoint;
};

typedef IntrTriangle3Sphere3<float> IntrTriangle3Sphere3f;
typedef IntrTriangle3Sphere3<double> IntrTriangle3Sphere3d;

}

#endif
