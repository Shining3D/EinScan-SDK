// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef RVECTOR2_H
#define RVECTOR2_H

#include "sn3DFoundationLIB.h"
#include "TRVector.h"

namespace sn3DFoundation
{

template <int ISIZE>
class RVector2 : public TRVector<2,ISIZE>
{
public:
    // construction
    RVector2 ();
    RVector2 (const RVector2& rkV);

#ifdef SN3D_USING_VC70
    RVector2 (const TRVector<2,ISIZE>& rkV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file, the compiler complains:
        //
        //   error C2244: 'sn3DFoundation::RVector2<>::__ctor' : unable to match function
        //       definition to an existing declaration
        //   definition
        //       'sn3DFoundation::RVector2<>::RVector2(const sn3DFoundation::TRVector<2,> &)'
        //   existing declarations
        //       'sn3DFoundation::RVector2<>::RVector2(const sn3DFoundation::TRational<> &,
        //                                  const sn3DFoundation::TRational<> &)'
        //       'sn3DFoundation::RVector2<>::RVector2(const sn3DFoundation::TRVector<2,> &)'
        //       'sn3DFoundation::RVector2<>::RVector2(const sn3DFoundation::RVector2<> &)'
        //       'sn3DFoundation::RVector2<>::RVector2(void)'
        // The "definition" is in the "existing declarations" list, so I do
        // not know what the compiler is complaining about.

        m_akTuple[0] = rkV[0];
        m_akTuple[1] = rkV[1];
    }
#else
    RVector2 (const TRVector<2,ISIZE>& rkV);
#endif

    RVector2 (const TRational<ISIZE>& rkX, const TRational<ISIZE>& rkY);

    // member access
    TRational<ISIZE> X () const;
    TRational<ISIZE>& X ();
    TRational<ISIZE> Y () const;
    TRational<ISIZE>& Y ();

    // assignment
    RVector2& operator= (const RVector2& rkV);

#ifdef SN3D_USING_VC70
    RVector2& operator= (const TRVector<2,ISIZE>& rkV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file, the compiler complains:
        //
        //   error C2244: 'sn3DFoundation::RVector2<>::operator`='' : unable to match
        //       function definition to an existing declaration
        //   definition
        //       'sn3DFoundation::RVector2<> &sn3DFoundation::RVector2<>::operator =(
        //            const sn3DFoundation::TRVector<2,> &)'
        //   existing declarations
        //       'sn3DFoundation::RVector2<> &sn3DFoundation::RVector2<>::operator =(
        //            const sn3DFoundation::TRVector<2,> &)'
        //       'sn3DFoundation::RVector2<> &sn3DFoundation::RVector2<>::operator =(
        //            const sn3DFoundation::RVector2<> &)'

        m_akTuple[0] = rkV[0];
        m_akTuple[1] = rkV[1];
        return *this;
    }
#else
    RVector2& operator= (const TRVector<2,ISIZE>& rkV);
#endif

    // returns Dot(this,V)
    TRational<ISIZE> Dot (const RVector2& rkV) const;

    // returns (y,-x)
    RVector2 Perp () const;

    // returns Cross((x,y,0),(V.x,V.y,0)) = x*V.y - y*V.x
    TRational<ISIZE> DotPerp (const RVector2& rkV) const;

protected:
    using TRVector<2,ISIZE>::m_akTuple;
};

#include "RVector2.inl"

}

#endif
