// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRLOZENGE3LOZENGE3_H
#define INTRLOZENGE3LOZENGE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Lozenge3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrLozenge3Lozenge3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrLozenge3Lozenge3 (const Lozenge3<Real>& rkLozenge0,
        const Lozenge3<Real>& rkLozenge1);

    // object access
    const Lozenge3<Real>& GetLozenge0 () const;
    const Lozenge3<Real>& GetLozenge1 () const;

    // static intersection query
    virtual bool Test ();

private:
    // the objects to intersect
    const Lozenge3<Real>* m_pkLozenge0;
    const Lozenge3<Real>* m_pkLozenge1;
};

typedef IntrLozenge3Lozenge3<float> IntrLozenge3Lozenge3f;
typedef IntrLozenge3Lozenge3<double> IntrLozenge3Lozenge3d;

}

#endif
