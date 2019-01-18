// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTRAY3TRIANGLE3_H
#define DISTRAY3TRIANGLE3_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Ray3.h"
#include "Triangle3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistRay3Triangle3
    : public Distance<Real,Vector3<Real> >
{
public:
    DistRay3Triangle3 (const Ray3<Real>& rkRay,
        const Triangle3<Real>& rkTriangle);

    // object access
    const Ray3<Real>& GetRay () const;
    const Triangle3<Real>& GetTriangle () const;

    // static distance queries
    virtual Real Get ();
    virtual Real GetSquared ();

    // function calculations for dynamic distance queries
    virtual Real Get (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);
    virtual Real GetSquared (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // Information about the closest points.
    Real GetRayParameter () const;
    Real GetTriangleBary (int i) const;

private:
    using Distance<Real,Vector3<Real> >::m_kClosestPoint0;
    using Distance<Real,Vector3<Real> >::m_kClosestPoint1;

    const Ray3<Real>* m_pkRay;
    const Triangle3<Real>* m_pkTriangle;

    // Information about the closest points.
    Real m_fRayParameter;  // closest0 = ray.origin+param*ray.direction
    Real m_afTriangleBary[3];  // closest1 = sum_{i=0}^2 bary[i]*tri.vertex[i]
};

typedef DistRay3Triangle3<float> DistRay3Triangle3f;
typedef DistRay3Triangle3<double> DistRay3Triangle3d;

}

#endif
