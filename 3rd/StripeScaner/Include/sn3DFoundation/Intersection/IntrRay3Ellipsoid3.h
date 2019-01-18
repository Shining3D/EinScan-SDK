// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY3ELLIPSOID3_H
#define INTRRAY3ELLIPSOID3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray3.h"
#include "Ellipsoid3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay3Ellipsoid3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrRay3Ellipsoid3 (const Ray3<Real>& rkRay,
        const Ellipsoid3<Real>& rkEllipsoid);

    // object access
    const Ray3<Real>& GetRay () const;
    const Ellipsoid3<Real>& GetEllipsoid () const;

    // static intersection queries
    virtual bool Test ();
    virtual bool Find ();

    // the intersection set
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Ray3<Real>* m_pkRay;
    const Ellipsoid3<Real>* m_pkEllipsoid;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
};

typedef IntrRay3Ellipsoid3<float> IntrRay3Ellipsoid3f;
typedef IntrRay3Ellipsoid3<double> IntrRay3Ellipsoid3d;

}

#endif
