// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTVECTOR2BOX2_H
#define DISTVECTOR2BOX2_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Box2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistVector2Box2
    : public Distance<Real,Vector2<Real> >
{
public:
    DistVector2Box2 (const Vector2<Real>& rkVector, const Box2<Real>& rkBox);

    // object access
    const Vector2<Real>& GetVector () const;
    const Box2<Real>& GetBox () const;

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
    const Box2<Real>* m_pkBox;
};

typedef DistVector2Box2<float> DistVector2Box2f;
typedef DistVector2Box2<double> DistVector2Box2d;

}

#endif
