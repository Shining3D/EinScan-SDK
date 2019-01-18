// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRBOX3FRUSTUM3_H
#define INTRBOX3FRUSTUM3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Box3.h"
#include "Frustum3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrBox3Frustum3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrBox3Frustum3 (const Box3<Real>& rkBox,
        const Frustum3<Real>& rkFrustum);

    // object access
    const Box3<Real>& GetBox () const;
    const Frustum3<Real>& GetFrustum () const;

    // test-intersection query
    virtual bool Test ();

private:
    // the objects to intersect
    const Box3<Real>* m_pkBox;
    const Frustum3<Real>* m_pkFrustum;
};

typedef IntrBox3Frustum3<float> IntrBox3Frustum3f;
typedef IntrBox3Frustum3<double> IntrBox3Frustum3d;

}

#endif
