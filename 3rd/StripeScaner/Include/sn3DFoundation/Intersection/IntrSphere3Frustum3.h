// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSPHERE3FRUSTUM3_H
#define INTRSPHERE3FRUSTUM3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Sphere3.h"
#include "Frustum3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSphere3Frustum3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSphere3Frustum3 (const Sphere3<Real>& rkSphere,
        const Frustum3<Real>& rkFrustum);

    // object access
    const Sphere3<Real>& GetSphere () const;
    const Frustum3<Real>& GetFrustum () const;

    // static intersection query
    virtual bool Test ();

private:
    // the objects to intersect
    const Sphere3<Real>* m_pkSphere;
    const Frustum3<Real>* m_pkFrustum;
};

typedef IntrSphere3Frustum3<float> IntrSphere3Frustum3f;
typedef IntrSphere3Frustum3<double> IntrSphere3Frustum3d;

}

#endif
