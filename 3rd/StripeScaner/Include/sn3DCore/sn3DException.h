// ==========================================================================
// File name:	sn3DException.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
// -
// Histroy:		
// ============================================================================

#ifndef _sn3DException_H
#define _sn3DException_H


#include <string>
#include <iostream>
#include "sn3Dglobaldef.h"

namespace sn3DCore 
{
	using namespace std;

	///////////////////////////////////////////////////////////////////////////
	// Base Class
	class  sn3DException 
	{
	public:
		sn3DException(const tstring msg) 
		{
			this->Msg = msg;
			#ifdef DEBUG
				cerr << msg.c_str();
			#endif
		}
		tstring GetMsg()				{ return Msg; }
		void Print()					{ cerr << Msg.c_str(); }
		virtual tstring GetTypeString()	{ return _T("sn3DException"); }
	protected:
		tstring Msg;
	};

	class  sn3DERangeCheck : public sn3DException 
	{
	public:
		sn3DERangeCheck(const tstring msg) : sn3DException(msg) {};
		virtual tstring getTypeString() {return _T("sn3DERangeCheck");}
	};

	class  sn3DEIOException : public sn3DException 
	{
	public:
		sn3DEIOException(const tstring msg) : sn3DException(msg) {};
		virtual tstring getTypeString()	{return _T("sn3DEIOException");}
	};

	class  sn3DEMath : public sn3DException 
	{
	public:
		sn3DEMath(const tstring msg) : sn3DException(msg) {};
		virtual tstring getTypeString() {return _T("sn3DEMath");}
	};

	class  sn3DEInvalidState : public sn3DException 
	{
	public:
		sn3DEInvalidState(const tstring msg) : sn3DException(msg) {};
		virtual tstring getTypeString() {return _T("sn3DEInvalidState");}
	};

	class  sn3DETypeMismatch : public sn3DException 
	{
	public:
		sn3DETypeMismatch(const tstring msg) : sn3DException(msg) {};
		virtual tstring getTypeString() {return _T("sn3DTypeMismatch");}
	};

	///////////////////////////////////////////////////////////////////////////

	/// printout warning message on debug console, pop-up window if non-visible.
	void error(tstring msg);

	/// printout error message on debug console, pop-up window if non-visible.
	void warning(tstring msg);

	/// printout message on debug console, pop-up window if non-visible.
	void message(tstring msg);

	void DisplaySN3DException(sn3DException *e);
	void DisplaySTLException(std::exception e);
	void DisplayGeneralException();


#define EXCEPTION_HANDLER_START \
	try {\

#define EXCEPTION_HANDLER_END \
	} catch (sn3DException &e) {\
	DisplaySN3DException(&e);\
	} catch (std::exception e) {\
	DisplaySTLException(e);\
	} catch (...) {\
	DisplayGeneralException();\
	}
}

#endif
