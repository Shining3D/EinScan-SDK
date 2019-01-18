// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef WM4ETMANIFOLDMESH_H
#define WM4ETMANIFOLDMESH_H

#include "sn3DFoundationLIB.h"
#include "EdgeKey.h"
#include "TriangleKey.h"

namespace sn3DFoundation
{

class SN3D_FOUNDATION_ITEM ETManifoldMesh
{
public:
    // edge data types
    class Edge;
    typedef Edge* EPtr;
    typedef const Edge* ECPtr;
    typedef EPtr (*ECreator)(int,int);
    typedef std::map<EdgeKey,Edge*> EMap;
    typedef EMap::iterator EMapIterator;
    typedef EMap::const_iterator EMapCIterator;

    // triangle data types
    class Triangle;
    typedef Triangle* TPtr;
    typedef const Triangle* TCPtr;
    typedef TPtr (*TCreator)(int,int,int);
    typedef std::map<TriangleKey,Triangle*> TMap;
    typedef TMap::iterator TMapIterator;
    typedef TMap::const_iterator TMapCIterator;

    // edge object
    class SN3D_FOUNDATION_ITEM Edge
    {
    public:
        Edge (int iV0, int iV1);
        virtual ~Edge ();

        int V[2];
        TPtr T[2];
    };

    // triangle object
    class SN3D_FOUNDATION_ITEM Triangle
    {
    public:
        Triangle (int iV0, int iV1, int iV2);
        virtual ~Triangle ();

        // vertices, listed in counterclockwise order (V[0],V[1],V[2])
        int V[3];

        // adjacent edges
        // E[0] points to edge (V[0],V[1])
        // E[1] points to edge (V[1],V[2])
        // E[2] points to edge (V[2],V[0])
        EPtr E[3];

        // adjacent triangles
        //   T[0] points to triangle sharing edge E[0]
        //   T[1] points to triangle sharing edge E[1]
        //   T[2] points to triangle sharing edge E[2]
        TPtr T[3];
    };


    // construction and destruction
    ETManifoldMesh (ECreator oECreator = 0, TCreator oTCreator = 0);
    virtual ~ETManifoldMesh ();

    // member access
    const EMap& GetEdges () const;
    const TMap& GetTriangles () const;

    // mesh manipulation
    TPtr InsertTriangle (int iV0, int iV1, int iV2);
    bool RemoveTriangle (int iV0, int iV1, int iV2);

    // manifold mesh is closed if each edge is shared twice
    bool IsClosed () const;

    void Print (const char* acFilename);

protected:
    // edges
    static EPtr CreateEdge (int iV0, int iV1);
    ECreator m_oECreator;
    EMap m_kEMap;

    // triangles
    static TPtr CreateTriangle (int iV0, int iV1, int iV2);
    TCreator m_oTCreator;
    TMap m_kTMap;
};

#include "ETManifoldMesh.inl"

}

#endif