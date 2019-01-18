// ==========================================================================
// File name:	sn3DCallback.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
// -
// Histroy:		
// ============================================================================

#ifndef _sn3DCallback_H
#define _sn3DCallback_H

#include <string>
#include "sn3Dglobaldef.h"

namespace sn3DCore 
{
	class sn3DGenericCallback
	{
	public:
		//=====================================================================
		// Function  : Reset()
		// Decription: Resets the progress status
		//				The progress (percentage) is set to 0, and the title/infos are cleared.
		//=====================================================================
		virtual void Reset()									=0;

		//=====================================================================
		// Function  : Update()
		// Decription: Notifies the algorithm progress
		//				The notification is sent by the ongoing algorithm (on the library side).
		//				This virtual method shouldn't be called too often, as the real process
		//				behind it is unspecified and may be time consuming. Typically it shouldn't
		//				be called more than once per percent.
		// Param     : percent the current progress, between 0 and 100%
		//=====================================================================
		virtual void Update(float percent)=0;

		//=====================================================================
		// Function  : SetMethodTitle()
		// Decription: Notifies the algorithm title
		//				The notification is sent by the ongoing algorithm (on the library side).
		// Param     : methodTitle the algorithm title
		//=====================================================================
		virtual void SetMethodTitle(const TCHAR* methodTitle)=0;

		//=====================================================================
		// Function  : SetInfomation()
		// Decription: Notifies some information about the ongoing process
		//				The notification is sent by the ongoing algorithm (on the library side).
		// Param     : infoStr some textual information about the ongoing process
		//=====================================================================
		virtual void SetInfomation(const TCHAR* infoStr)=0;

		//=====================================================================
		// Function  : Start()
		// Decription: Notifies the fact that every information has been sent and that the process begins
		//				Once start() is called, the progress bar and other informations could be displayed (for example).
		//=====================================================================
		virtual void Start()=0;

		//=====================================================================
		// Function  : Stop()
		// Decription: Notifies the fact that the process has ended
		//				Once end() is called, the progress bar and other informations could be hidden (for example).
		//=====================================================================
		virtual void Stop()=0;

		//=====================================================================
		// Function  : IsCancelRequested()
		// Decription: Checks if the process should be cancelled()
		//				This method is called by some process from time to time to know if it
		//				should halt before its normal ending. This is a way for the client application
		//				to cancel an ongoing process (but it won't work with all algorithms).
		//				Process results may be incomplete/void. The cancel requirement mechanism must
		//				be implemented (typically a simple "cancel()" method that will be called by the
		//				client application).
		//=====================================================================
		virtual bool IsCancelRequested()=0;
	};

	class sn3DDebugCallback:public sn3DGenericCallback
	{
	public:
		sn3DDebugCallback();

		void Start();
		void Stop();
		void Reset();
		void Update(float percent);;

		void SetMethodTitle(const TCHAR* methodTitle);;
		void SetInfomation(const TCHAR* infoStr);;
		bool IsCancelRequested();

		void SetCancel();
	protected:
		volatile bool	m_bCancal;
		std::tstring	m_title;
	};


}

#endif
