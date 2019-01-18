// ==========================================================================
// Copyright (C), 2017-2045, Shining 3D Tech. Co., Ltd.
//
// File name:	sn3DTurnTable.h
//
// Description:	 
//				 
//
// Functions:	
//				
// Histroy:		
//				2017/01/11 
//
// ============================================================================
#ifndef _SN3DTURNTABLE_H
#define _SN3DTURNTABLE_H

#ifdef SN3DTURNTABLE_EXPORTS
#define SN3D_TURNTABLE_API __declspec(dllexport)
#else
#define SN3D_TURNTABLE_API __declspec(dllimport)
#endif
#define  CLOCKWISE     0x01//clockwise direction of ratation
#define  ANTICLOCKWISE 0X02//counterclockwise direction of ratation
//freedom id
#define  X_ROTATE    0X00
#define  Y_ROTATE    0X01
#define  Z_ROTATE    0X02
#define  X_MOVE      0x03
#define  Y_MOVE      0x04
#define  Z_MOVE      0X05

#define  RELATIVE_ANGLE   1//relative angle
namespace sn3DTurnTable
{
	typedef unsigned char UCHAR;
	//=========================================================================
	// function£º	SetType set the turntable type
	// parm£º	idType  the device type of turntable
	// char *motortype = "COM9-115200-1100";
	// 0 success ,other failed.
	//==========================================================================
	int SN3D_TURNTABLE_API SetType(char *idType);
	//=========================================================================
	// function£º	OpenTurntable
	// 0 success ,other failed.
	//==========================================================================
	int SN3D_TURNTABLE_API OpenTurntable();

	//=========================================================================
	// function£º	initTurntable
	// 0 success ,other failed.
	//==========================================================================
	int SN3D_TURNTABLE_API initTurntable();

	
	//=========================================================================
	// function£º	CloseTurntable
	// 0 success ,other failed.
	//==========================================================================
	int SN3D_TURNTABLE_API CloseTurntable();

	

	//=========================================================================
	// function£º	Run2Coordinate:Run A Specific Angle
	// parm£º	degreefreedomID		[in]The degree of the freedom.degreefreedomID = X_ROTATE
	//          desangle            [in]The run angle
	//          state               [in]The run type state = RELATIVE_ANGLE
	//0 success, other failed.
	//==========================================================================
	int SN3D_TURNTABLE_API Run2Coordinate(UCHAR degreefreedomID, float desangle, bool state=RELATIVE_ANGLE);


	//=========================================================================
	// function£º	GetTurnTableState:Check the state of turntable
	//0 success, other failed.
	//==========================================================================
	bool SN3D_TURNTABLE_API GetTurnTableState();
}


#endif //_SN3DTURNTABLE_H
