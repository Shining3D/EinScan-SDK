// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTVECTOR2QUADRATIC2_H
#define DISTVECTOR2QUADRATIC2_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Quadratic2.h"
#include "Polynomial1.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistVector2Quadratic2
    : public Distance<Real,Vector2<Real> >
{
public:
    DistVector2Quadratic2 (const Vector2<Real>& rkVector,
        const Quadratic2<Real>& rkQuadratic);

    // object access
    const Vector2<Real>& GetVector () const;
    const Quadratic2<Real>& GetQuadratic () const;

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

    static void ComputePoly (Real afA[2], Real afB[2], Real afD[2],
        Real fC, Polynomial1<Real>& rkPoly);

    const Vector2<Real>* m_pkVector;
    const Quadratic2<Real>* m_pkQuadratic;
};

typedef DistVector2Quadratic2<float> DistVector2Quadratic2f;
typedef DistVector2Quadratic2<double> DistVector2Quadratic2d;

}

#endif
