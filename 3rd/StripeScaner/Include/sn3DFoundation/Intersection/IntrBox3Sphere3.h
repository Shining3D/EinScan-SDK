// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRBOX3SPHERE3_H
#define INTRBOX3SPHERE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Box3.h"
#include "Sphere3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrBox3Sphere3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrBox3Sphere3 (const Box3<Real>& rkBox,
        const Sphere3<Real>& rkSphere);

    // object access
    const Box3<Real>& GetBox () const;
    const Sphere3<Real>& GetSphere () const;

    // test-intersection query
    virtual bool Test ();

    // find-intersection query
    virtual bool Find (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // intersection set for dynamic find-intersection query
    const Vector3<Real>& GetContactPoint () const;

private:
    using Intersector<Real,Vector3<Real> >::IT_EMPTY;
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_OTHER;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;
    using Intersector<Real,Vector3<Real> >::m_fContactTime;

    // supporting functions for dynamic Find function
    static Real GetVertexIntersection (Real fDx, Real fDy, Real fDz,
        Real fVx, Real fVy, Real fVz, Real fRSqr);

    static Real GetEdgeIntersection (Real fDx, Real fDz, Real fVx, Real fVz,
        Real fVSqr, Real fRSqr);

    int FindFaceRegionIntersection (Real fEx, Real fEy, Real fEz,
        Real fCx, Real fCy, Real fCz, Real fVx, Real fVy, Real fVz,
        Real& rfIx, Real& rfIy, Real& rfIz, bool bAboveFace);

    int FindJustEdgeIntersection (Real fCy, Real fEx, Real fEy,
        Real fEz, Real fDx, Real fDz, Real fVx, Real fVy, Real fVz,
        Real& rfIx, Real& rfIy, Real& rfIz);

    int FindEdgeRegionIntersection (Real fEx, Real fEy, Real fEz,
        Real fCx, Real fCy, Real fCz, Real fVx, Real fVy, Real fVz,
        Real& rfIx, Real& rfIy, Real& rfIz, bool bAboveEdge);

    int FindVertexRegionIntersection (Real fEx, Real fEy, Real fEz,
        Real fCx, Real fCy, Real fCz, Real fVx, Real fVy, Real fVz,
        Real& rfIx, Real& rfIy, Real& rfIz);

    // the objects to intersect
    const Box3<Real>* m_pkBox;
    const Sphere3<Real>* m_pkSphere;

    // point of intersection
    Vector3<Real> m_kContactPoint;
};

typedef IntrBox3Sphere3<float> IntrBox3Sphere3f;
typedef IntrBox3Sphere3<double> IntrBox3Sphere3d;

}

#endif
