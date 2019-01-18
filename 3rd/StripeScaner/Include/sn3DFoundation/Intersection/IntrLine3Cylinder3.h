// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRLINE3CYLINDER3_H
#define INTRLINE3CYLINDER3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Line3.h"
#include "Cylinder3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrLine3Cylinder3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrLine3Cylinder3 (const Line3<Real>& rkLine,
        const Cylinder3<Real>& rkCylinder);

    // object access
    const Line3<Real>& GetLine () const;
    const Cylinder3<Real>& GetCylinder () const;

    // static intersection query
    virtual bool Find ();

    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;

    // the objects to intersect
    const Line3<Real>* m_pkLine;
    const Cylinder3<Real>* m_pkCylinder;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];

// internal use (shared by IntrRay3Cylinder3 and IntrSegment3Cylinder3)
public:
    static int Find (const Vector3<Real>& rkOrigin,
        const Vector3<Real>& rkDir, const Cylinder3<Real>& rkCylinder,
        Real afT[2]);
};

typedef IntrLine3Cylinder3<float> IntrLine3Cylinder3f;
typedef IntrLine3Cylinder3<double> IntrLine3Cylinder3d;

}

#endif
