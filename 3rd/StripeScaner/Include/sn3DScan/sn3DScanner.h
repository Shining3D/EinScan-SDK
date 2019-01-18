// ==========================================================================
// Copyright (C), 2017-2025, Shining 3D Tech. Co., Ltd.
//
// File name:	sn3DScanner.h
//
// Description: 3D Scanner API Definition
//
// Functions:	3D Scanner Interface 
//
/// @author Will
/// @version 1.0
/// @date 2017-01-11
///			
// ============================================================================
#ifndef _Einscan_Scanner_H
#define _Einscan_Scanner_H

#ifdef SN3DSCAN_EXPORTS
#define SN3D_SCAN_API __declspec(dllexport)
#else
#define SN3D_SCAN_API __declspec(dllimport)
#endif

#include <vector>
#include <tchar.h>
#include <string>

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

 
typedef void(*CAMERA_DISPLAY_CALLBACK_FUNCTION)(const void* const& pOwner, const int& cameraID,
	const unsigned char* const& pImage, const int& width, const int& height, const int& channel);
//namespace 
namespace sn3DCore { template<class T> class sn3DImageData; class sn3DRangeData; }
namespace sn3DTargetAlign { class RefPoints; }

namespace sn3DScan
{

	typedef enum
	{
		BINOCULARS,
		BINOCULAR,
		BINO_MONO,
		MULTI_MONO
	}SCANTYPE;

	///////////////////////////////////////////////////////////////////////////////
	typedef void* HSCAN;
	
	/** \brief Initialize device handle
	*  \param[in]      scantype             Initialization type  = BINOCULARS
	*  \param[in]      szIniPath            The path of configuration file
	*  \param[out]     hScan                Device handle
	*  \param[in]      unitSize             Reserved word
	*  \return         0 success ,other failed

	*/

	int SN3D_SCAN_API sn3d_Initialize_Scan_Session(int scantype, const TCHAR* szIniPath, void*& hScan, int unitSize = 1);


	/** \brief  Closing the scan session
	*  \param[in]      hScant               Device handle
	*  @return         0 success ,other failed
	*/

	int SN3D_SCAN_API sn3d_Destroy_Scan_Session(HSCAN& hScan);

	/** \brief the free Scan
	*  \param[in]      hScan           Device handle
	*  \param[in]      datas           all the scan data
	*  \param[out]     data            the scan data
	*  \return         0 success ,other failed

	*/

	int  SN3D_SCAN_API sn3d_free_Scan(HSCAN hScan, std::vector<sn3DCore::sn3DRangeData*> datas, sn3DCore::sn3DRangeData*& data);

	/** \brief the code scan of turntable
	*  \param[in]      hScan                    device handle
	*  \param[out]     data                     the scan data
	*  \param[in]      isfirst_model            the start position of the turntable(a group turntable scan)
	*  \return         0 success ,other failed

	*/
	int  SN3D_SCAN_API sn3d_turntable_code_Scan(HSCAN hScan, sn3DCore::sn3DRangeData*& data, bool isfirst_model);

	/** \brief the mark scan of turntable
	*  \param[in]      hScan                    device handle
	*  \param[out]     datas                    the from the state (true ==isfirst_model) to the end of the group.
	*  \param[out]     data                     the scan data
	*  \param[in]      isfirst_model            the start position of the turntable(a group turntable scan)
	*  \return         0 success ,other failed

	*/
	int  SN3D_SCAN_API sn3d_turntable_mark_Scan(HSCAN hScan, sn3DCore::sn3DRangeData*& data, std::vector<sn3DCore::sn3DRangeData*> datas, bool isfirst_model);

	/** \brief set camera brightness
	*  \param[in]      hScan                    device handle
	*  \param[in]      brightness               The level of brightness , Ranges: 0-12
	*  \return         0 success ,other failed

	*/
	int  SN3D_SCAN_API sn3d_set_brightness(HSCAN hScan, const int brightness);

	/** \brief set camera brightness
	*  \param[in]       hScan                    device handle
	*  \param[out]      brightness               The maximum value of camera brightness(12)
	*  \return         0 success ,other failed

	*/
	int  SN3D_SCAN_API sn3d_get_brightness_max_range(void* hScan, int& max);

	/** \brief // Reserved function
	*  \return         0 success ,other failed

	*/
	int  SN3D_SCAN_API sn3d_set_turntable_align_type(HSCAN hScan, const int align_type);

	/** \brief register callback function of display video image
	*  \param[in]       hScan                    device handle
	*  \param[in]       fun                      The system sends the video status events to cameras by calling this function
	*  \param[in]       pOwner                   Parameters of call_back. The system sends the parameters to user when the user status has been changed. Reserved word
	*  \return         0 success ,other failed

	*/
	int SN3D_SCAN_API sn3d_Regist_Fix_Scan_Camera_Callback(HSCAN hScan, CAMERA_DISPLAY_CALLBACK_FUNCTION fun, void* pOwner);

	/** \brief register callback function of display video image
	*  \param[in]       hScan                    device handle
	*  \param[out]      global_mark              global mark point,at least four points
	*  \return         0 success ,other failed

	*/
	int SN3D_SCAN_API sn3d_import_global_mark_point(HSCAN hScan, sn3DTargetAlign::RefPoints global_mark);

	
	/** \brief Set Texture Scan Parameters
	*  \param[in]       hScan                    device handle
	*  \param[out]      bEnable                  1  use texture scan  0  use non-texture scan
	*  \return         0 success ,other failed

	*/
	int SN3D_SCAN_API sn3d_enable_textrue(HSCAN hScan, int bEnable);

	///////////////////////////////////////////////////////////////////////////////  
}


#endif //_Einscan_Scanner_H
