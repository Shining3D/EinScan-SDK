// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTVECTOR3BOX3_H
#define DISTVECTOR3BOX3_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Box3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistVector3Box3
    : public Distance<Real,Vector3<Real> >
{
public:
    DistVector3Box3 (const Vector3<Real>& rkVector,
        const Box3<Real>& rkBox);

    // object access
    const Vector3<Real>& GetVector () const;
    const Box3<Real>& GetBox () const;

    // static distance queries
    virtual Real Get ();
    virtual Real GetSquared ();

    // function calculations for dynamic distance queries
    virtual Real Get (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);
    virtual Real GetSquared (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

private:
    using Distance<Real,Vector3<Real> >::m_kClosestPoint0;
    using Distance<Real,Vector3<Real> >::m_kClosestPoint1;

    const Vector3<Real>* m_pkVector;
    const Box3<Real>* m_pkBox;
};

typedef DistVector3Box3<float> DistVector3Box3f;
typedef DistVector3Box3<double> DistVector3Box3d;

}

#endif
