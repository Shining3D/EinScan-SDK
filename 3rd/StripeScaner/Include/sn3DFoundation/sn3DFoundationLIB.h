// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef SN3DFOUNDATIONLIB_H
#define SN3DFOUNDATIONLIB_H

// For the DLL library.
#ifdef SN3D_FOUNDATION_DLL_EXPORT
#define SN3D_FOUNDATION_ITEM __declspec(dllexport)

// For a client of the DLL library.
#else
#ifdef SN3D_FOUNDATION_DLL_IMPORT
#define SN3D_FOUNDATION_ITEM __declspec(dllimport)

// For the static library.
#else
#define SN3D_FOUNDATION_ITEM

#endif
#endif
#endif
