// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRBOX2BOX2_H
#define INTRBOX2BOX2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Box2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrBox2Box2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrBox2Box2 (const Box2<Real>& rkBox0, const Box2<Real>& rkBox1);

    // object access
    const Box2<Real>& GetBox0 () const;
    const Box2<Real>& GetBox1 () const;

    // static test-intersection query
    virtual bool Test ();

private:
    // the objects to intersect
    const Box2<Real>* m_pkBox0;
    const Box2<Real>* m_pkBox1;
};

typedef IntrBox2Box2<float> IntrBox2Box2f;
typedef IntrBox2Box2<double> IntrBox2Box2d;

}

#endif
