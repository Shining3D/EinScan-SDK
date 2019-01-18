// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTRECTANGLE3RECTANGLE3_H
#define DISTRECTANGLE3RECTANGLE3_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Rectangle3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistRectangle3Rectangle3
    : public Distance<Real,Vector3<Real> >
{
public:
    DistRectangle3Rectangle3 (const Rectangle3<Real>& rkRectangle0,
        const Rectangle3<Real>& rkRectangle1);

    // object access
    const Rectangle3<Real>& GetRectangle0 () const;
    const Rectangle3<Real>& GetRectangle1 () const;

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

    const Rectangle3<Real>* m_pkRectangle0;
    const Rectangle3<Real>* m_pkRectangle1;
};

typedef DistRectangle3Rectangle3<float> DistRectangle3Rectangle3f;
typedef DistRectangle3Rectangle3<double> DistRectangle3Rectangle3d;

}

#endif
