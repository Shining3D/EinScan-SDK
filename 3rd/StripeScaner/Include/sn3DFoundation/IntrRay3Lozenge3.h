// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY3LOZENGE3_H
#define INTRRAY3LOZENGE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray3.h"
#include "Lozenge3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay3Lozenge3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrRay3Lozenge3 (const Ray3<Real>& rkRay,
        const Lozenge3<Real>& rkLozenge);

    // object access
    const Ray3<Real>& GetRay () const;
    const Lozenge3<Real>& GetLozenge () const;

    // static intersection query
    virtual bool Test ();

private:
    // the objects to intersect
    const Ray3<Real>* m_pkRay;
    const Lozenge3<Real>* m_pkLozenge;
};

typedef IntrRay3Lozenge3<float> IntrRay3Lozenge3f;
typedef IntrRay3Lozenge3<double> IntrRay3Lozenge3d;

}

#endif
