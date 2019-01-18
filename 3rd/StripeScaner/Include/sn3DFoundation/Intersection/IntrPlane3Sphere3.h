// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRPLANE3SPHERE3_H
#define INTRPLANE3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Plane3.h"
#include "Sphere3.h"
#include "Circle3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrPlane3Sphere3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrPlane3Sphere3 (const Plane3<Real>& rkPlane,
        const Sphere3<Real>& rkSphere);

    // object access
    const Plane3<Real>& GetPlane () const;
    const Sphere3<Real>& GetSphere () const;

    // Static intersection queries.
    virtual bool Test ();
    virtual bool Find ();

    // Culling support.  The view frustum is assumed to be on the positive
    // side of the plane.  The sphere is culled if it is on the negative
    // side of the plane.
    bool SphereIsCulled () const;

    // The intersection set.  The circle is valid only when Find() returns
    // 'true'.  If the intersection does not exist, the circle radius is
    // set to -1 as an additional indication that the circle is not valid.
    const Circle3<Real>& GetCircle () const;

protected:
    // The objects to intersect.
    const Plane3<Real>* m_pkPlane;
    const Sphere3<Real>* m_pkSphere;

    // The intersection set.
    Circle3<Real> m_kCircle;
};

typedef IntrPlane3Sphere3<float> IntrPlane3Sphere3f;
typedef IntrPlane3Sphere3<double> IntrPlane3Sphere3d;

}

#endif
