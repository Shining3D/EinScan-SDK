// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTLINE2RAY2_H
#define DISTLINE2RAY2_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Line2.h"
#include "Ray2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistLine2Ray2 : public Distance<Real,Vector2<Real> >
{
public:
    DistLine2Ray2 (const Line2<Real>& rkLine, const Ray2<Real>& rkRay);

    // object access
    const Line2<Real>& GetLine () const;
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

    const Line2<Real>* m_pkLine;
    const Ray2<Real>* m_pkRay;
};

typedef DistLine2Ray2<float> DistLine2Ray2f;
typedef DistLine2Ray2<double> DistLine2Ray2d;

}

#endif
