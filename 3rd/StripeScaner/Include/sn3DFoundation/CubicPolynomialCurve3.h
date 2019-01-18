// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CUBICPOLYNOMIALCURVE3_H
#define CUBICPOLYNOMIALCURVE3_H

#include "sn3DFoundationLIB.h"
#include "PolynomialCurve3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM CubicPolynomialCurve3
    : public PolynomialCurve3<Real>
{
public:
    // Construction and destruction.  CubicPolynomialCurve3 accepts
    // responsibility for deleting the input polynomials.
    CubicPolynomialCurve3 (Polynomial1<Real>* pkXPoly,
        Polynomial1<Real>* pkYPoly, Polynomial1<Real>* pkZPoly);

    virtual ~CubicPolynomialCurve3 ();

    // tessellation data
    int GetVertexQuantity () const;
    Vector3<Real>* Vertices ();

    // tessellation by recursive subdivision
    void Tessellate (int iLevel);

protected:
    using PolynomialCurve3<Real>::m_fTMin;
    using PolynomialCurve3<Real>::m_fTMax;

    // precomputation
    class SN3D_FOUNDATION_ITEM IntervalParameters
    {
    public:
        int m_iI0, m_iI1;
        Vector3<Real> m_akXuu[2];
    };

    // subdivide curve into two halves
    void Subdivide (int iLevel, Real fDSqr, Vector3<Real>* akX,
        IntervalParameters& rkIP);

    // tessellation data
    int m_iVertexQuantity;
    Vector3<Real>* m_akVertex;
};

typedef CubicPolynomialCurve3<float> CubicPolynomialCurve3f;
typedef CubicPolynomialCurve3<double> CubicPolynomialCurve3d;

}

#endif
