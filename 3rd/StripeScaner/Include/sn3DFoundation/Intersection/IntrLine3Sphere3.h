// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRLINE3SPHERE3_H
#define INTRLINE3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Line3.h"
#include "Sphere3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrLine3Sphere3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrLine3Sphere3 (const Line3<Real>& rkLine,
        const Sphere3<Real>& rkSphere);

    // object access
    const Line3<Real>& GetLine () const;
    const Sphere3<Real>& GetSphere () const;

    // test-intersection query
    virtual bool Test ();

    // find-intersection query
    virtual bool Find ();
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;
    Real GetLineT (int i) const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Line3<Real>* m_pkLine;
    const Sphere3<Real>* m_pkSphere;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
    Real m_afLineT[2];
};

typedef IntrLine3Sphere3<float> IntrLine3Sphere3f;
typedef IntrLine3Sphere3<double> IntrLine3Sphere3d;

}

#endif
