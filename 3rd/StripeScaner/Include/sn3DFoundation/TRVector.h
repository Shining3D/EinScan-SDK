// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef TRVECTOR_H
#define TRVECTOR_H

#include "sn3DFoundationLIB.h"
#include "TRational.h"

namespace sn3DFoundation
{

template <int VSIZE, int ISIZE>
class TRVector
{
public:
    // construction
    TRVector ();
    TRVector (const TRVector& rkV);

    // coordinate access
    operator const TRational<ISIZE>* () const;
    operator TRational<ISIZE>* ();
    TRational<ISIZE> operator[] (int i) const;
    TRational<ISIZE>& operator[] (int i);

    // assignment
    TRVector& operator= (const TRVector& rkV);

    // comparison
    bool operator== (const TRVector& rkV) const;
    bool operator!= (const TRVector& rkV) const;
    bool operator<  (const TRVector& rkV) const;
    bool operator<= (const TRVector& rkV) const;
    bool operator>  (const TRVector& rkV) const;
    bool operator>= (const TRVector& rkV) const;

    // arithmetic operations
    TRVector operator+ (const TRVector& rkV) const;
    TRVector operator- (const TRVector& rkV) const;
    TRVector operator* (const TRational<ISIZE>& rkR) const;
    TRVector operator/ (const TRational<ISIZE>& rkR) const;
    TRVector operator- () const;

    // arithmetic updates
    TRVector& operator+= (const TRVector& rkV);
    TRVector& operator-= (const TRVector& rkV);
    TRVector& operator*= (const TRational<ISIZE>& rkR);
    TRVector& operator/= (const TRational<ISIZE>& rkR);

    // vector operations
    TRational<ISIZE> SquaredLength () const;
    TRational<ISIZE> Dot (const TRVector& rkV) const;

protected:
    // support for comparisons
    int CompareArrays (const TRVector& rkV) const;

    TRational<ISIZE> m_akTuple[VSIZE];
};

template <int VSIZE, int ISIZE>
TRVector<VSIZE,ISIZE> operator* (const TRational<ISIZE>& rkR,
    const TRVector<VSIZE,ISIZE>& rkV);

#include "TRVector.inl"

}

#endif
