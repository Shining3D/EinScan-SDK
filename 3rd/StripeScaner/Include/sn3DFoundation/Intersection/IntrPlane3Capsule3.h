// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRPLANE3CAPSULE3_H
#define INTRPLANE3CAPSULE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Plane3.h"
#include "Capsule3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrPlane3Capsule3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrPlane3Capsule3 (const Plane3<Real>& rkPlane,
        const Capsule3<Real>& rkCapsule);

    // object access
    const Plane3<Real>& GetPlane () const;
    const Capsule3<Real>& GetCapsule () const;

    // static intersection query
    virtual bool Test ();

    // Culling support.  The view frustum is assumed to be on the positive
    // side of the plane.  The capsule is culled if it is on the negative
    // side of the plane.
    bool CapsuleIsCulled () const;

protected:
    // the objects to intersect
    const Plane3<Real>* m_pkPlane;
    const Capsule3<Real>* m_pkCapsule;
};

typedef IntrPlane3Capsule3<float> IntrPlane3Capsule3f;
typedef IntrPlane3Capsule3<double> IntrPlane3Capsule3d;

}

#endif
