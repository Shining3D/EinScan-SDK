// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRSEGMENT3CYLINDER3_H
#define INTRSEGMENT3CYLINDER3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Segment3.h"
#include "Cylinder3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrSegment3Cylinder3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSegment3Cylinder3 (const Segment3<Real>& rkSegment,
        const Cylinder3<Real>& rkCylinder);

    // object access
    const Segment3<Real>& GetSegment () const;
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
    const Segment3<Real>* m_pkSegment;
    const Cylinder3<Real>* m_pkCylinder;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
};

typedef IntrSegment3Cylinder3<float> IntrSegment3Cylinder3f;
typedef IntrSegment3Cylinder3<double> IntrSegment3Cylinder3d;

}

#endif
