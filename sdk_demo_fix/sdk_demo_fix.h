#ifndef SDK_DEMO_FIX_H
#define SDK_DEMO_FIX_H

#include <QtWidgets/QMainWindow>
#include "ui_sdk_demo_fix.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <QRadioButton>
#include <qdialog.h>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "msg_define.h"
#include <qstackedwidget.h>

#include "sn3d_pro_sdk.h"
#include"sn3DScanner.h"
#include"sn3DTurnTable.h"
#include "sn3DRangeData.h"
#include "sn3DReferencePoints.h"

class sdk_demo_fix : public QDialog
{
	Q_OBJECT

public:
	sdk_demo_fix(QWidget *parent = 0);
	~sdk_demo_fix();

	enum
	{
		ui_state_ui_init,
		ui_state_open_scanner_ok,
		ui_state_scanner_closed,
		ui_state_scanning,
		ui_state_scanning_paused,
		ui_state_scanning_finished,
		ui_state_scanning_canceled,
	};

	void scan_callback(void*  handle, int  event_type, int  event_sub_type, void* data, int data_len);
signals:
	void sig_handle_msg(msg_data_t msg_data);
protected:
	//scan message 
	int handle_update_video(msg_data_t msg_data);					 
	int handle_update_scanner_rt(msg_data_t msg_data);				 
	int handle_update_current_cloud_point(msg_data_t msg_data);		 
	int handle_update_whole_cloud_point(msg_data_t msg_data);		 
	int handle_update_current_mark_cloud_point(msg_data_t msg_data);
	int handle_update_whole_mark_cloud_point(msg_data_t msg_data);
	int handle_calibrate_msg(msg_data_t msg_data);

	//scanner device message
	int handle_scanner_double_click_msg(msg_data_t msg_data);
	int handle_scanner_click_msg(msg_data_t msg_data);
	int handle_scanner_plus_sub_msg(msg_data_t msg_data);

	//
	int change_ui_state(int state);
	void post_msg_data_update(int type, int param);
 
protected slots:
    void handle_msg(msg_data_t msg_data);

    void on_open_scanner();
	void on_close_scanner();

	//calibrate
	void on_start_calibrate();
	void on_skip_calibrate();
	void resolution_value_change(const QString &);
 
	//scan param config
	void on_get_scan_param();
	void on_set_scan_param();

	void on_brightness_list_change(int index);

	void on_free_mode_toggle(bool tog);
	void on_Turntable_mode_toggle(bool tog);
	void on_texture_toggle(bool tog);

	void on_global_mark_point_toggled(bool toggle);
	void on_code_point_toggled(bool toggle);
	void on_mark_toggled(bool toggle);
	void on_feature_toggled(bool toggle);
	void on_global_mark_point_checked(bool toggle);

	//scan 
	void on_start_scan();
	void on_clear_scan();

	void on_delete_point();
	void on_save_whole_data();

protected:
	void	show_error(int err_code, bool only_show_err=true);
	 
	void	show_data();
	void	set_calibrate_state(int calibrate_type, int distance_index = -1, int group = -1);
	int		update_brightness();
	int		update_scan_param();
	void	clear_show_data();

	static  void fix_scan_calback(const void* const& pOwner, const int& cameraID,
		const unsigned char* const& pImage, const int& width, const int& height, const int& channel);

	int turntable_scan();
	bool turntban_ref_scan_control(void* hScanSession_, int times_);


	bool Algin_Code_Points(sn3DTargetAlign::RefPoints& code_rfPts_);
	bool turntban_code_scan_control(void* hScanSession_,int times_);
	bool free_scan();

	bool load_global_mark();

	void	on_scan_mode_change();

	void edit_Example();
private:
	Ui::sdk_demo_fixClass ui;
	QBoxLayout* init_camera_video();
	QWidget*  init_scanner();
 
	QWidget*  init_calibrate();
	QWidget*  init_scan();
	QWidget*  init_calibrate_distance();
	void reset_calibrate_distance();

	//for pro calibrate 
	void		on_pro_open_scanner();
	void		on_pro_close_scanner();

	//for pro scan 
	void		on_fix_open_scanner();
	void		on_fix_close_scanner();

	//camera video data
	QLabel* left_camera_video;
	QLabel* right_camera_video;
	QLabel* colour_camera_video;


	//open close scanner
	QGroupBox*   scanner_group;
	QPushButton* open_scanner;
	QPushButton* close_scanner;
	QLabel*      scaner_prompt;
	QComboBox*   init_type_list;
	QComboBox*   device_type_list;
	//calibrate
	QGroupBox*    calibrate_group;
	QLabel*       calibrate_type;
	QLabel*       calibrate_state;
	QLabel*       calibrate_prompt;
	QPushButton*  start_calibrate;
	QPushButton*  skip_calibrate;
	int           current_calibrate_type;
	int           current_camera_group;
 
	//calibrate distance 
	QLabel*       camera_distance[5];
	QLabel*       hd_distance[12];
	QLabel*       wb_distance[12];
	QStackedWidget* calibrate_state_manager;
 

	//scan group
	QGroupBox*    scan_group;
	QComboBox*    brightness_list;
	QPushButton*  get_scan_param;
	QPushButton*  set_scan_param;
 
	//turtable 
	QLineEdit*    turntable_times_value;
	QLabel*       turntable_times_label;

	QCheckBox*    texture;
 
	//scan mode 
	QRadioButton* fix_scan_mode_free;
	QRadioButton* fix_scan_mode_turntable;
	QGroupBox*    fix_scan_mode_group;

	//align mode group 
	QRadioButton* align_mode_code_point;
	QRadioButton* align_mode_markpoint;
	QRadioButton* align_mode_feature;
	QRadioButton* align_mode_global_mark_point;       //use for turtable scan 
	QCheckBox*	  align_mode_global_mark_point_check; //use for free scan 
	QGroupBox*    align_group;

	QLabel*       scan_point_count;
	QPushButton*  start_scan;
	QPushButton*  clear_scan;
	QPushButton*  save_whole_data;
 	QPushButton*  delete_point;
	QLineEdit*    point_index0_start;
	QLineEdit*    point_index0_end;
	QLineEdit*    point_index1_start;
	QLineEdit*    point_index1_end;
	QLineEdit*    point_index2_start;
	QLineEdit*    point_index2_end;

	//scan data
	int           cur_point_count;
	int           whole_point_count;
	int           marker_point_count;
	int           whole_marker_point_count;

	//hand scan handle,only use for calibrate
	void*			handle;
	

	//fix scan handle
	void*			hScanSession;

	int             current_scan_type;  //
	int             current_device_type;
	int             current_align_type;
	int             current_turntable_scan; // 0 free scan; 1 turtable scan 
	int             current_texture;
	//

	vector<sn3DCore::sn3DRangeData*> m_rangeDatas;
//	sn3DTargetAlign::RefPoints       m_code_all;
	vector<sn3DTargetAlign::RefPoints> m_code_alls;  


	int turntable_times;
};

#endif // SDK_DEMO_PRO_H
