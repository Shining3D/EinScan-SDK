// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef CUBICPOLYNOMIALCURVE2_H
#define CUBICPOLYNOMIALCURVE2_H

#include "sn3DFoundationLIB.h"
#include "PolynomialCurve2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM CubicPolynomialCurve2
    : public PolynomialCurve2<Real>
{
public:
    // Construction and destruction.  CubicPolynomialCurve2 accepts
    // responsibility for deleting the input polynomials.
    CubicPolynomialCurve2 (Polynomial1<Real>* pkXPoly,
        Polynomial1<Real>* pkYPoly);
    virtual ~CubicPolynomialCurve2 ();

    // tessellation data
    int GetVertexQuantity () const;
    Vector2<Real>* Vertices ();

    // tessellation by recursive subdivision
    void Tessellate (int iLevel);

protected:
    using PolynomialCurve2<Real>::m_fTMin;
    using PolynomialCurve2<Real>::m_fTMax;

    // precomputation
    class SN3D_FOUNDATION_ITEM IntervalParameters
    {
    public:
        int m_iI0, m_iI1;
        Vector2<Real> m_akXuu[2];
    };

    // subdivide curve into two halves
    void Subdivide (int iLevel, Real fDSqr, Vector2<Real>* akX,
        IntervalParameters& rkIP);

    // tessellation data
    int m_iVertexQuantity;
    Vector2<Real>* m_akVertex;
};

typedef CubicPolynomialCurve2<float> CubicPolynomialCurve2f;
typedef CubicPolynomialCurve2<double> CubicPolynomialCurve2d;

}

#endif
