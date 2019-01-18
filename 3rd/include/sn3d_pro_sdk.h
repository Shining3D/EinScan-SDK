
#ifndef SN3D_PRO_SDK_H
#define SN3D_PRO_SDK_H

#ifdef WIN32

#ifdef SN3DSCAN_EXPORTS
#define SN3D_SCAN_API  __declspec(dllexport) 
#else
#define SN3D_SCAN_API  __declspec(dllimport)
#endif

#define CALLBACK		__stdcall
#define CALL_METHOD		__stdcall  //__cdecl

#else	//linux

#define SN3D_SCAN_API	extern "C"
#define CALL_METHOD
#define CALLBACK
 
#endif



#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** const data define
 ***********************************************************************/
 
//initialise type define 
#define	SN3D_INIT_CALIBRATE							0x00000000	//calibrate initialise
#define	SN3D_INIT_RAPIDSCAN							0x00000001	//Rapid scan initialization 
#define	SN3D_INIT_HD_SCAN							0x00000002	//HD scan initialization 
#define	SN3D_INIT_FIX_SCAN							0x00000003	//Fix scan initialization 

#define SN3D_ALIGN_MODE_FEATURE						2		    //Alignment based on features
#define SN3D_ALIGN_MODE_MARK_POINT					1			//Alignment based on reference points
#define SN3D_ALIGN_MODE_GLOABL_MARK_POINT			3			//Alignment based on global reference points
#define SN3D_ALIGN_TURTABLE_CODE_POINT				4			//Alignment based on turntable  reference points

//scan event define 
#define	SN3D_VIDEO_IMAGE_DATA_READY					    6	//The notification of image data 
#define	SN3D_DISTANCE_INDECATE							7	//The Notification of scan work distance 1-10:normal, 0:too close;11:too far;12: track lost
#define	SN3D_SCANNER_RT_READY							8	//The Notification of scan transformation matrix 
#define	SN3D_CURRENT_MARKPOINT_DATA_READY				9	//The Notification of reference points data 
#define	SN3D_CURRENT_SCAN_POINT_CLOUD_READY				10	//The Notification of current scan data 
#define	SN3D_WHOLE_SCAN_POINT_CLOUD_READY				11	//The Notification of the whole point cloud data
#define	SN3D_WHOLE_MARKPOINT_DATA_READY					12	//The Notification of the whole of reference points data

#define	SN3D_CALIBRATION_STATE_DATA	                    13	//The notification of Calibration status
#define	SN3D_SCANNER_DOUBLECLICK	                    14	//The Notification of ‘Scan’ button is double-clicked
#define	SN3D_SCANNER_CLICK	                            15	//The Notification of ‘Scan’ button is single-clicked 
#define	SN3D_SCANNER_PLUS	                            16	//The Notification of  “+” button is clicked
#define	SN3D_SCANNER_SUB	                            17	//The Notification of  “-” button is clicked

#define	SN3D_SENSOR_PLUGGED	                            18	//
#define	SN3D_SENSOR_UNPLUGGED	                        19	//
#define	SN3D_START_REQUESTED	                        20	//
#define	SN3D_START_COMPLETED	                        21	//
#define	SN3D_PAUSE_REQUESTED	                        22	//
#define	SN3D_PAUSE_COMPLETED	                        23	//
#define	SN3D_FINISH_REQUESTED							24	//
#define	SN3D_FINISH_COMPLETED							25	//
#define	SN3D_ABANDON_REQUESTED	                        26	//
#define	SN3D_ABANDON_COMPLETED							27	//
#define	SN3D_MESH_DATA_READY							28	//The Notification  after mesh data process 


//mesh type define 
#define SN3D_MESH_WATERTIGHT							1	//mesh watertight
#define SN3D_MESH_UNWATERTIGHT							2	//mesh unwatertight
 
//mesh resolution 
#define	SN3D_MESH_HIGHT									0	//hight resolution
#define	SN3D_MESH_MIDDLE								1	//middle resolution
#define	SN3D_MESH_LOW									2	//low resolution


//return value define 
#define	SN3D_RET_NOERROR								0		//no error
#define	SN3D_RET_PARAM_ERROR							- 1		//param error
#define	SN3D_RET_ORDER_ERROR							- 2		//call order
#define	SN3D_RET_TIME_OUT_ERROR							- 3		//time out error
#define	SN3D_RET_NOT_SUPPORT_ERROR						- 4		//not support error
#define	SN3D_RET_NO_DEVICE_ERROR						 -6		//not connect device
#define	SN3D_RET_DEVICE_LICENSE_ERROR					 -7		//device license error
#define SN3D_RET_GPU_ERROR                               -8		//graphic card error
#define SN3D_RET_INNER_ERROR                             -9		//sdk inner card error
#define SN3D_RET_NOT_CALIBRATE_ERROR                     -10	//not calibrate error
#define SN3D_RET_LOST_CONFIG_FILE_ERROR                  -11	//not calibrate error
#define SN3D_RET_NO_DATA_ERROR                           -12	//no data error
#define SN3D_RET_LOST_CALIBRATE_FILE_ERROR               -13	//not calibrate error
#define SN3D_RET_NO_GLOBAL_MARK_POINT_PARAM_ERROR        -14	//no global mark point
//calibrate state
#define  SN3D_CALIBRATE_STATE_CAMERA					0		//
#define  SN3D_CALIBRATE_STATE_HD						1		//
#define  SN3D_CALIBRATE_STATE_WB						2		//
#define  SN3D_CALIBRATE_STATE_EXIT						3		//


#define  SN3D_CALIBRATE_INVALID							-1		//
#define  SN3D_CALIBRATE_SNAP_STATE_ON					0		//
#define  SN3D_CALIBRATE_SNAP_STATE_OFF					1		//

#define  SN3D_CALIBRATE_COMPUTING						0		//
#define  SN3D_CALIBRATE_COMPUTE_SUCCESS					1		//
#define  SN3D_CALIBRATE_COMPUTE_FAILED					2		//

#define SN3D_MAX_PATH								   256
/************************************************************************
 ** enum define 
 ***********************************************************************/
 
//initialize data
typedef struct tagSN3D_INIT_DATA
{

	char*             device_type;                  // The type of device to control different devices. Reserved word.
	wchar_t           config_path[SN3D_MAX_PATH];   // The path of configuration file. Reserved word.
	unsigned char     reserved[256];
}SN3D_INIT_DATA, *LPSN3D_INIT_DATA;

//video image
typedef struct tagSN3D_IMAGE_DATA
{
	int               width;  			//The width of image
	int               height;           //The height of image.
	int               channel;          //The channels of image 
	int               length;           //width*height；The length of image, the size is width*height*channel . 
	unsigned char*    data;             //The data of image  
}SN3D_IMAGE_DATA, *LPSN3D_IMAGE_DATA;

//video frame data 
typedef struct tagSN3D_VIDEO_FRAME
{
	int							id;				//The ID of cameras. 0 : Left camera , 1: Right camera , 2: Color camera.	
	int							fps;			//Frame rate. Reserved word		
	unsigned long long			stamp;			//The time stamp of image. Reserved word									
	SN3D_IMAGE_DATA				video_data;		//The data of image.
}SN3D_VIDEO_FRAME, *LPSN3D_VIDEO_FRAME;

typedef struct tagSN3D_SCAN_PARAM
{
	double		resolution;            //Space resolution. Value: 0.2-3.0 for HD scan;0.5-3.0 for Rapid Scan
	int		    flag_texture;          //Scan with color setting, 0 : scan without color ,1 : scan with color
	int		    align_mode;            //Alignment mode. Reference: Alignment mode macro definition
} SN3D_SCAN_PARAM, *LPSN3D_SCAN_PARAM;
//point data 
typedef struct tagSN3D_POINT_DATA
{
	int               id;						//The ID of data object, Reserved word.
	float              x;						//X coordinate value
	float              y;						//Y coordinate value
	float              z;						//Z coordinate value
} SN3D_POINT_DATA, *LPSN3D_POINT_DATA;
 

typedef struct tagSN3D_CLOUD_POINT
{  
    int 	          id;                   //The ID of data object, Reserved word
	int               vertex_count;			//The number of vertex .
	SN3D_POINT_DATA   *vertex_data;			//The data of vertex.
	int               norma_count;			//The number of vertex normal.
	SN3D_POINT_DATA   *norma_data;			//The data of vertex normal.
	int               vertex_color_count;	//The number of vertex color.
	SN3D_POINT_DATA    *vertex_color_data;	//The data of vertex color.
 
}SN3D_CLOUD_POINT, *LPSN3D_CLOUD_POINT;
  
// 
typedef struct tagSN3D_SCANNER_RT
{
	float		rotate[9];					// Rotation Matrix.
	float		trans[3];					// Translation Matrix.
} SN3D_SCANNER_RT, *LPSN3D_SCANNER_RT;
 

typedef struct tagSN3D_STATE_CALIBRATE
{
	int        current_calibrate;           //Reference:Calibration type macro definition: 0:Scanner calibration;1:HD calibration;2:White Balance;3:Calibration finished.
	int        distance_indicate;           //The work distance between scanner and calibration board, bigger value, further distance.
											//The ranges are different depends on calibration type.
											//Scanner calibration : ranges : 0 - 4. Each group must appear once for each value, for a total of 5
	int        current_group;               //HD calibration: ranges:0-11.Each value must appear once.
											//White balance : ranges : 0 - 11.Calibration is successful when value is 6.
											//- 1:Invalid data。

	int        snap_state;                  //Reference :The Constants of Calibration Capture Status.
											//-1:Invalid data, 0:Capturing, 1:Capture finished.
	int        compute_state;               //Reference :The Constants of Calibration Calculation Status.
											//-1:Invalid data;0:Calculating,1:Calculation success,2:Calculation failure.

}SN3D_STATE_CALIBRATE, *LPSN3D_STATE_CALIBRATE;
 

typedef struct tagSN3D_MESH_PROCESS_PARAM
{
	int			mesh_type;					//Reference:Mesh type macro definition
	int			mesh_resolution;			//Reference:Mesh resolution macro definition
	int         simplification_flag;		//simplification flag,0 diable,1 enable
	double		simplification_ratio;		//1-100
	int			smooth_flag;				//smooth flag ,0 diable,1 enable
	int			sharpen_flag;				//sharpen flag ,0 diable,1 enable
	int			mark_point_fill_hole_flag;  //mark point fill whole flag,0 diable,1 enable
	int			plaint_fill_hole_flag;		//mark point fill whole flag,0 diable,1 enable
	double		plaint_fill_hole_perimeter; //hole perimeter
} SN3D_MESH_PROCESS_PARAM, *LPSN3D_MESH_PROCESS_PARAM;


//
typedef struct tagSN3D_TRI_FACE
{
	int              vid[3];
}SN3D_TRI_FACE, *LPSN3D_TRI_FACE;


//
typedef struct tagSN3D_TRI_MESH
{
	int						id;
	int						vertex_count;
	SN3D_POINT_DATA			*vertex_data;
	SN3D_POINT_DATA			*norma_data;
	SN3D_POINT_DATA			*vertex_color_data;
	int						face_count;
	SN3D_TRI_FACE			*face_ids;
	SN3D_IMAGE_DATA         tex_data;
}SN3D_TRI_MESH, *LSN3D_TRI_MESH;

/************************************************************************
 ** callback define 
 ***********************************************************************/

 /** Callback Function of  Events
* @param[out]	handle				Device handle from sn3d_initialize
* @param[out]	event_type			Events Type. Reference : The Notification Events of Calibration.
* @param[out]	event_sub_type		Events subtype. Not used yet.
* @param[out]	data				The data structure pointer matched with event
* @param[out]	data_len			 The length of data.
* @param[out]	user_data			The parameter needs to be imported into sn3d_regist_callback.
*  @return void,  
*  NOTE: 1、callback function run in a workthread 2 you can only
*/
typedef void (CALLBACK *sn3d_callback)(void*  handle, int  event_type, int  event_sub_type, void* data, int data_len, void*  user_data);



/************************************************************************
** interface funtion define 
***********************************************************************/

/** The Open Device Handle
* @param[in]	type				Initialization type. Reference : The Definitions of Initialization Type
* @param[in]	init_data			Initialize device parameters. Reference : SN3D_INIT_DATA
* @param[out]	handle				Device handle.
*  @return							Reference : The Definitions of Return Values 
*  NOTE: 1 . Function: Initialize device handle.
         2 . Only One device handle can be used for one time.
         3. Before calling sn3d_initialize to initialize a device handle, you need to call sn3d_close to release current device handle.

*/
SN3D_SCAN_API int  CALL_METHOD  sn3d_Initialize(int  type, LPSN3D_INIT_DATA  init_data, void* & handle);

/** Close Device Handle
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:   1. Function: Release device handle.
           2. Only One device handle can be used for one time.
          3. Before calling sn3d_initialize to initialize a device handle, you need to release the current device handle first.

*/
SN3D_SCAN_API int   CALL_METHOD   sn3d_close(void* handle);


/** Capture Calibration Images
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE: Referance SDK Document 
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_start_calibrate(void* handle);

/** Skip the Current Calibration Phase
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:   1．It can only achieve the skip function among the camera calibration ,HD calibration and white balance.
           2．For example, if it is in the camera calibration phase, the user can call this function to enter the HD calibration directly, 
		     if it is in the HD calibration phase, the user can call this function to enter the white balance phase directly, 
		     if it is in the white balance phase, the user can call this function to enter the camera calibration phase directly.

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_skip_calibrate(void* handle);

/** Get the Camera Brightness Value Range
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	min					The minimum value of camera brightness , default is 0. Reserved word
* @param[out]	max					The maximum value of camera brightness.
*  @return							Reference : The Definitions of Return Values
*  NOTE:  
*/
SN3D_SCAN_API int   CALL_METHOD  sn3d_get_brightness_range(void* handle, int& min,int& max);

/** Set Camera Brightness
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	brightness			The level of brightness , Value ranges reference sn3d_get_brightness_range
*  @return							Reference : The Definitions of Return Values
*  NOTE:  
*/
SN3D_SCAN_API int   CALL_METHOD  sn3d_set_brightness(void* handle, int brightness);

/** Get Camera Brightness
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	brightness			The level of brightness , Value ranges reference sn3d_get_brightness_range
*  @return							Reference : The Definitions of Return Values
*  NOTE:  
*/
SN3D_SCAN_API int   CALL_METHOD  sn3d_get_brightness(void* handle, int& brightness);

/** Register Callback Function of   Events Notification
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	call_back			The system sends the events by calling this function
* @param[in]	user_data			Parameters of call_back. The system sends the parameters to user when the user status has been changed
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1. The system sends calibration events to registrant after calling this function.
          2 .For getting the time notification , the user must call this function before calling start_scan or start_calibrate.

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_regist_callback(void*  handle, sn3d_callback  call_back, void* user_data);

/** Set Scan Parameters
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	param				Scan configuration parameters.
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1. It is only valid in SN3D_INIT_RAPIDSCAN or SN3D_INIT_HD_SCAN is set by sn3d_initialize .
          2. It only can be called before calling sn3d_start_scan or after calling sn3d_abandon_scan.
          3. Calling this function to set scan parameters will clear scan data that are exist.

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_set_scan_param(void*  handle, LPSN3D_SCAN_PARAM param);

/** Get Scan Parameters
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	param				Scan configuration parameters
*  @return							Reference : The Definitions of Return Values
*  NOTE:   1 It is only valid in SN3D_INIT_RAPIDSCAN or SN3D_INIT_HD_SCAN is set by sn3d_initialize
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_get_scan_param(void*  handle, SN3D_SCAN_PARAM& param);

/** Start to Scan
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1. This function needs to be called after being registered.
          2. Send scan information that includes scan distance info, scan data etc. to users by calling this function while scanning. 
          3. The data from sn3d_get_current_scan_whole_point_cloud and sn3d_get_current_scan_point_cloud is only for 3D display. 

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_start_scan(void* handle);

/** Stop Scanning
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1. Get merged data from sn3d_get_current_scan_whole_point_cloud.
          2. Call sn3d_start_scan to continue to scan.
          3. Call sn3d_abandon_scan to delete scan data.
          4. Calling sn3d_set_scan_param is forbidden.
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_finish_scan(void*   handle);

/** Pause Scanning
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:    1. Call sn3d_start_scan to continue to scan.
		    2. Call sn3d_abandon_scan to cancel scan data.
		    3. Call sn3d_finish_scan to finish scan.
		    4. Calling sn3d_set_scan_param is forbidden.
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_pause_scan(void*   handle);

/** Delete Scan Data  
* @param[in]	handle				Device handle from sn3d_initialize
*  @return							Reference : The Definitions of Return Values
*  NOTE:   1. Clear all scan data.
           2. Call sn3d_set_scan_param to reset scan parameters.
           3. Call sn3d_start_scan to continue to scan.

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_abandon_scan(void*   handle);

/** Get Current Point Cloud Data
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	point_cloud			Point cloud data
*  @return							Reference : The Definitions of Return Values
*  NOTE:     1. Calling this function is valid before getting the return value from callback function and receiving the SN3D_CURRENT_SCAN_POINT_CLOUD_READY.
             2. This function needs to be called twice. The first time, keep point_cloud pointer member is NULL, the function will return the point number. 
			    Allocate the memory according to the point number from outside; when the pointer is not NULL , user needs to call this function again ,and it will return point cloud data. 
             3. The data is only for 3D display

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_get_current_scan_point_cloud(void*   handle, SN3D_CLOUD_POINT& point_cloud);

/** Get Merged Whole Point Cloud Data
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	point_cloud			Point cloud data
*  @return							Reference : The Definitions of Return Values
*  NOTE:    1. Calling this function is valid before getting the return value from callback function and receiving the SN3D_WHOLE_SCAN_POINT_CLOUD_READY
            2. This function needs to be called twice. The first time, keep point_cloud pointer member is NULL, the function will return the point number. 
               Allocate the memory according to the point number from outside; when the pointer is not NULL, user needs to call this function again, and it will return point cloud data.
            3. After calling sn3d_finish_scan, the data from this function is the final scan data, or the data is only for 3D display.



*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_get_current_scan_whole_point_cloud(void*   handle, SN3D_CLOUD_POINT& point_cloud);

/** Get Current Reference Points
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	point_cloud			Mark point cloud data
*  @return							Reference : The Definitions of Return Values
*  NOTE:    1. Calling this function is valid before getting the return value from callback function and receiving the SN3D_CURRENT_MARKPOINT_DATA_READY.
            2．This function needs to be called twice. The first time, keep point_cloud pointer member is NULL, the function will return the point number.
			 Allocate the memory according to the point number from outside; when the pointer is not NULL, user needs to call this function again, and it will return point cloud data.


*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_get_current_mark_point(void*   handle, SN3D_CLOUD_POINT& point_cloud);

/** Get ALL of Reference Points
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	point_cloud			Mark point cloud data
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1 Calling this function is valid before getting the return value from callback function and receiving SN3D_WHOLE_MARKPOINT_DATA_READY.
          2 This function needs to be called twice. The first time, keep point_cloud pointer member is NULL, the function will return the point number.
			 Allocate the memory according to the point number from outside; when the pointer is not NULL, user needs to call this function again, and it will return point cloud data.

*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_get_whole_mark_point(void*   handle, SN3D_CLOUD_POINT& point_cloud);

/** Delete Part of The Scan Data
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	point_cloud			The rest of data after editing
*  @return							Reference : The Definitions of Return Values
*  NOTE:  1. The data deleted by this function can't be undone. 
          2. This function only can be called in the pause scanning status(sn3d_pause_scan).
 


*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_update_cloud_point(void*   handle, SN3D_CLOUD_POINT& point_cloud);
 
/** Import Global Reference Point
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	mark_point			Global reference point, at least four points.
*  @return							Reference : The Definitions of Return Values
*  NOTE:
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_import_global_mark_point(void*  handle, const SN3D_CLOUD_POINT& mark_point);

/** mesh process
* @param[in]	handle				Device handle from sn3d_initialize
* @param[in]	param				Reference : The Definitions of SN3D_MESH_PROCESS_PARAM.
*  @return							Reference : The Definitions of Return Values
*  NOTE:
*/
SN3D_SCAN_API int	CALL_METHOD   sn3d_mesh_process(void*  handle, const SN3D_MESH_PROCESS_PARAM& param);

/** Get Mesh Data
* @param[in]	handle				Device handle from sn3d_initialize
* @param[out]	mesh_data			mesh trim  data
*  @return							Reference : The Definitions of Return Values
*  NOTE:    1. Calling this function is valid before getting the return value from callback function and receiving the SN3D_MESH_DATA_READY
2. This function needs to be called twice. The first time, keep mesh_data pointer member is NULL, the function will return the  number.
Allocate the memory according to the  number from outside; when the pointer is not NULL, user needs to call this function again, and it will return  data.

*/

SN3D_SCAN_API int	CALL_METHOD   sn3d_get_current_mesh_data(void*   handle, SN3D_TRI_MESH& mesh_data);

#ifdef __cplusplus
}
#endif

#endif // SN3D_PRO_SDK_H
