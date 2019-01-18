// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTVECTOR2RAY2_H
#define DISTVECTOR2RAY2_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Ray2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistVector2Ray2
    : public Distance<Real,Vector2<Real> >
{
public:
    DistVector2Ray2 (const Vector2<Real>& rkVector,
        const Ray2<Real>& rkRay);

    // object access
    const Vector2<Real>& GetVector () const;
    const Ray2<Real>& GetRay () const;

    // static distance queries
    virtual Real Get ();
    virtual Real GetSquared ();

    // function calculations for dynamic distance queries
    virtual Real Get (Real fT, const Vector2<Real>& rkVelocity0,
        const Vector2<Real>& rkVelocity1);
    virtual Real GetSquared (Real fT, const Vector2<Real>& rkVelocity0,
        const Vector2<Real>& rkVelocity1);

private:
    using Distance<Real,Vector2<Real> >::m_kClosestPoint0;
    using Distance<Real,Vector2<Real> >::m_kClosestPoint1;

    const Vector2<Real>* m_pkVector;
    const Ray2<Real>* m_pkRay;
};

typedef DistVector2Ray2<float> DistVector2Ray2f;
typedef DistVector2Ray2<double> DistVector2Ray2d;

}

#endif
