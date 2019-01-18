#include "sdk_demo_fix.h"
#include <qgroupbox.h>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <qcombobox.h>
#include <QFileDialog>
#include "DataCenter.h"
#include <qDebug>
#include <qvalidator.h>
#include <QToolTip>


//use for fix scan only 
sdk_demo_fix* g_sdk_demo=NULL;

void CALLBACK scan_demo_callback(void*  handle, int  event_type, int  event_sub_type, void* data, int data_len, void*  user_data)
{
	if (user_data == 0)
		return;

	sdk_demo_fix* sdk_demo = (sdk_demo_fix*)user_data;
	sdk_demo->scan_callback(handle, event_type, event_sub_type, data, data_len);
}

void sdk_demo_fix::fix_scan_calback(const void* const& pOwner, const int& cameraID,
	const unsigned char* const& pImage, const int& width, const int& height, const int& channel)
{
	
	if (NULL == pImage || g_sdk_demo==NULL)
	{
		return;
	}
 
	if ((0 == cameraID || 1 == cameraID) && NULL != pImage)
	{

		SN3D_VIDEO_FRAME video_frm = { 0 };
		 
		video_frm.id = cameraID;
		video_frm.fps = 15;
		video_frm.video_data.channel = channel;
		video_frm.video_data.width = width;
		video_frm.video_data.height = height;
		video_frm.video_data.data =(unsigned char*) pImage;
		video_frm.video_data.length = width*height*channel;
		g_sdk_demo->scan_callback((void*)pOwner, SN3D_VIDEO_IMAGE_DATA_READY,0, &video_frm, sizeof(SN3D_VIDEO_FRAME));
	 
	}
 
}
void sdk_demo_fix::post_msg_data_update(int type, int param)
{
	msg_data_t msg_data;
	msg_data.hint = 0;
	msg_data.msg_type = type;
	msg_data.map_data["param"] = param;
	emit sig_handle_msg(msg_data);
}
void sdk_demo_fix::scan_callback(void*  handle, int  event_type, int  event_sub_type, void* data, int data_len)
{
	switch (event_type)
	{
	case SN3D_VIDEO_IMAGE_DATA_READY:
	{
										 
										SN3D_VIDEO_FRAME* video_frm = (SN3D_VIDEO_FRAME*)data;
										msg_data_t msg_data;
										msg_data.hint = video_frm->id;
										msg_data.map_data["width"] = video_frm->video_data.width;
										msg_data.map_data["height"] = video_frm->video_data.height;
										msg_data.msg_type = SN3D_VIDEO_IMAGE_DATA_READY;
										if (video_frm->id == 0 || video_frm->id == 1)
										{
											QImage img((unsigned char*)(video_frm->video_data.data), video_frm->video_data.width, video_frm->video_data.height, QImage::Format_Grayscale8);
											msg_data.map_data["image"] = img.copy();
											emit sig_handle_msg(msg_data);
										}
										else if (video_frm->id == 2)
										{
											int width_step = video_frm->video_data.width * 3;
											unsigned char* imageColor = new unsigned char[width_step*video_frm->video_data.height];
										
											unsigned char* img_data = (unsigned char*)video_frm->video_data.data;
											memcpy(imageColor, img_data, width_step*video_frm->video_data.height);
											QVariant varData;
											varData.setValue<unsigned char*>(imageColor);
											msg_data.map_data["image"] = varData;
										 
											emit sig_handle_msg(msg_data);

										}
										
										break;
	}
	case  SN3D_SCANNER_RT_READY:
	{

								   SN3D_SCANNER_RT* rt = (SN3D_SCANNER_RT*)data;

								   demo_data_center::Instance()->update_scanner_rt(*rt);
								   post_msg_data_update(SN3D_SCANNER_RT_READY, 0);
								   break;
	}

	case  SN3D_CURRENT_MARKPOINT_DATA_READY:
	{
													 SN3D_CLOUD_POINT point = { 0 };
													 int ret = sn3d_get_current_mark_point(handle, point);
													 if (ret != SN3D_RET_NOERROR)
													 {
														 qDebug() << " fail ret" << ret;
														 return;
													 }

													 if (!demo_data_center::Instance()->allocate_point_memory(point))
													 {
														 qDebug() << " fail allocate_point_memory";
														 return;
													 }
													 ret = sn3d_get_current_mark_point(handle, point);
													 if (ret != SN3D_RET_NOERROR)
													 {
														 qDebug() << " fail ret" << ret;
														 demo_data_center::Instance()->free_point_memory(point);
														 return;
													 }
													 demo_data_center::Instance()->update_current_mark_point(point);
													 post_msg_data_update(SN3D_CURRENT_MARKPOINT_DATA_READY, point.vertex_count);
													 break;
	}
	case SN3D_WHOLE_MARKPOINT_DATA_READY:
	{
												  SN3D_CLOUD_POINT point = { 0 };
												  int ret = sn3d_get_whole_mark_point(handle, point);
												  if (ret != SN3D_RET_NOERROR)
												  {
													  qDebug() << " fail ret" << ret;
													  return;
												  }

												  if (!demo_data_center::Instance()->allocate_point_memory(point))
												  {
													  qDebug() << " fail allocate_point_memory";
													  return;
												  }
												  ret = sn3d_get_whole_mark_point(handle, point);
												  if (ret != SN3D_RET_NOERROR)
												  {
													  qDebug() << " fail ret" << ret;
													  demo_data_center::Instance()->free_point_memory(point);
													  return;
												  }
												  demo_data_center::Instance()->update_whole_mark_point(point);
												  post_msg_data_update(SN3D_WHOLE_MARKPOINT_DATA_READY, point.vertex_count);
												  break;
	}
	case  SN3D_CURRENT_SCAN_POINT_CLOUD_READY:
	{
													   SN3D_CLOUD_POINT point = { 0 };
													   int ret = sn3d_get_current_scan_point_cloud(handle, point);
													   if (ret != SN3D_RET_NOERROR)
													   {
														   qDebug() << " fail ret" << ret;
														   return;
													   }

													   if (!demo_data_center::Instance()->allocate_point_memory(point))
													   {
														   qDebug() << " fail allocate_point_memory";
														   return;
													   }
													   ret = sn3d_get_current_scan_point_cloud(handle, point);
													   if (ret != SN3D_RET_NOERROR)
													   {
														   qDebug() << " fail ret" << ret;
														   demo_data_center::Instance()->free_point_memory(point);
														   return;
													   }
													   demo_data_center::Instance()->update_current_cloud_point(point);
													   post_msg_data_update(SN3D_CURRENT_SCAN_POINT_CLOUD_READY, point.vertex_count);

													   break;
	}

	case  SN3D_WHOLE_SCAN_POINT_CLOUD_READY:
	{
													 SN3D_CLOUD_POINT point = { 0 };
													 int ret = sn3d_get_current_scan_whole_point_cloud(handle, point);
													 if (ret != SN3D_RET_NOERROR)
													 {
														 qDebug() << " fail ret" << ret;
														 return;
													 }

													 if (!demo_data_center::Instance()->allocate_point_memory(point))
													 {
														 qDebug() << " fail allocate_point_memory";
														 return;
													 }
													 ret = sn3d_get_current_scan_whole_point_cloud(handle, point);
													 if (ret != SN3D_RET_NOERROR)
													 {
														 qDebug() << " fail ret" << ret;
														 demo_data_center::Instance()->free_point_memory(point);
														 return;
													 }
													 demo_data_center::Instance()->update_whole_cloud_point(point);
													 post_msg_data_update(SN3D_WHOLE_SCAN_POINT_CLOUD_READY, point.vertex_count);
													 break;
	}
	case SN3D_DISTANCE_INDECATE:
	case SN3D_SCANNER_DOUBLECLICK:
	case SN3D_SCANNER_CLICK:
	case SN3D_SCANNER_PLUS:
	case SN3D_SCANNER_SUB:
	{
										int * event_data = (int *)data;
										post_msg_data_update(event_type, *event_data);
										break;
	}
	case SN3D_CALIBRATION_STATE_DATA:
	{

										SN3D_STATE_CALIBRATE*  calibrate_data = (SN3D_STATE_CALIBRATE*)data;
										
										msg_data_t msg_data;
										msg_data.hint = 0;
										msg_data.msg_type = SN3D_CALIBRATION_STATE_DATA;
										msg_data.map_data["current_calibrate"] = calibrate_data->current_calibrate;
										msg_data.map_data["distance"] = calibrate_data->distance_indicate;
										msg_data.map_data["group"] = calibrate_data->current_group;
										msg_data.map_data["snap_state"] = calibrate_data->snap_state;
										msg_data.map_data["compute_state"] = calibrate_data->compute_state;
										emit sig_handle_msg(msg_data);
										break;
	}


	default:

		break;
	}
}
sdk_demo_fix::sdk_demo_fix(QWidget *parent)
: QDialog(parent, Qt::WindowCloseButtonHint |Qt::WindowMinimizeButtonHint)
{
	turntable_times = 8;
	g_sdk_demo = this;
	handle = 0;
	hScanSession = 0;

	cur_point_count = 0;
	whole_point_count = 0;
	marker_point_count = 0;
	whole_marker_point_count = 0;

	current_calibrate_type = SN3D_CALIBRATE_INVALID;
	current_camera_group = SN3D_CALIBRATE_INVALID;

	qRegisterMetaType<msg_data_t>();
	qRegisterMetaType<unsigned char*>();

	QGridLayout* main_layout = new QGridLayout();

	main_layout->addLayout(init_camera_video(), 0, 0, 1, 4);
	main_layout->addWidget(init_scanner(), 1, 0);
	main_layout->addWidget(init_calibrate(), 1, 1);
	main_layout->addWidget(init_scan(), 1, 2);

	this->setLayout(main_layout);



	QObject::connect(open_scanner, SIGNAL(clicked()), SLOT(on_open_scanner()));
	QObject::connect(close_scanner, SIGNAL(clicked()), SLOT(on_close_scanner()));
	QObject::connect(start_calibrate, SIGNAL(clicked()), SLOT(on_start_calibrate()));
	QObject::connect(skip_calibrate, SIGNAL(clicked()), SLOT(on_skip_calibrate()));



	QObject::connect(get_scan_param, SIGNAL(clicked()), SLOT(on_get_scan_param()));
	QObject::connect(set_scan_param, SIGNAL(clicked()), SLOT(on_set_scan_param()));

	QObject::connect(start_scan, SIGNAL(clicked()), SLOT(on_start_scan()));
	QObject::connect(clear_scan, SIGNAL(clicked()), SLOT(on_clear_scan()));
	QObject::connect(save_whole_data, SIGNAL(clicked()), SLOT(on_save_whole_data()));
	 

	QObject::connect(delete_point, SIGNAL(clicked()), SLOT(on_delete_point()));


	QObject::connect(brightness_list, SIGNAL(currentIndexChanged(int)), SLOT(on_brightness_list_change(int)));


	QObject::connect(this, SIGNAL(sig_handle_msg(msg_data_t)), SLOT(handle_msg(msg_data_t)));
	QObject::connect(align_mode_global_mark_point, SIGNAL(toggled(bool)), SLOT(on_global_mark_point_toggled(bool)));
	QObject::connect(align_mode_code_point, SIGNAL(toggled(bool)), SLOT(on_code_point_toggled(bool)));
	QObject::connect(align_mode_markpoint, SIGNAL(toggled(bool)), SLOT(on_mark_toggled(bool)));
	QObject::connect(align_mode_feature, SIGNAL(toggled(bool)), SLOT(on_feature_toggled(bool)));
	QObject::connect(align_mode_global_mark_point_check, SIGNAL(toggled(bool)), SLOT(on_global_mark_point_checked(bool)));

	change_ui_state(ui_state_ui_init);

	setFixedHeight(800);
}

void sdk_demo_fix::on_code_point_toggled(bool toggle)
{
	if (!toggle)
		return;
	current_align_type = SN3D_ALIGN_TURTABLE_CODE_POINT;
	std::cout << "on_code_point_toggled === ===current_align_type=  " << current_align_type << std::endl;
}
void sdk_demo_fix::on_mark_toggled(bool toggle)
{
	if (!toggle)
		return;
	current_align_type = SN3D_ALIGN_MODE_MARK_POINT;
	std::cout << "on_mark_toggled === ===current_align_type=  " << current_align_type << std::endl;
}
void sdk_demo_fix::on_feature_toggled(bool toggle)
{
	if (!toggle)
		return;
	current_align_type = SN3D_ALIGN_MODE_FEATURE;

	std::cout << "on_feature_toggled === ===current_align_type=  " << current_align_type << std::endl;
}
void  sdk_demo_fix::on_global_mark_point_checked(bool toggle)
{
	if (!toggle)
	{
		current_align_type = 0;
		return;
	}

	on_global_mark_point_toggled(true);
}
void sdk_demo_fix::on_global_mark_point_toggled(bool toggle)
{
	if (!toggle)
		return;
	current_align_type = SN3D_ALIGN_MODE_GLOABL_MARK_POINT;
	std::cout << "on_global_mark_point_toggled === ===current_align_type=  " << current_align_type << std::endl;
	QString filename_ = QFileDialog::getOpenFileName(this, tr("import global mark point file"), "", tr("(*.p3)"));
	if (!filename_.isNull()){

		QFile file(filename_);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(nullptr, tr("failed"), tr("Open file failed"));
			return;
		}

		QByteArray data = file.readLine();

		data = file.readLine();
		data = file.readLine();
		data = file.readLine();

		std::vector<SN3D_POINT_DATA> points;
		int index = 0;
		while (data.length() > 0)
		{
			SN3D_POINT_DATA pt = { 0 };

			sscanf(data.data_ptr()->data(), "%d %f %f %f", &index, &pt.x, &pt.y, &pt.z);
			points.push_back(pt);

			qDebug() << "index=" << index << " x=" << pt.x << "y=" << pt.y << "z=" << pt.z;

			data = file.readLine();
		}

		SN3D_CLOUD_POINT  mark_point = { 0 };

		qDebug() << "index=" << index << " size=" << points.size();
		if (points.size() > 0)
		{
			mark_point.vertex_count = points.size();
			mark_point.vertex_data = &points[0];
		}

		load_global_mark();
	/*	int ret = sn3d_import_global_mark_point(handle, mark_point);

		show_error(ret);*/

	}
	else
	{
		QMessageBox::warning(NULL, tr("Warning"), tr("Global align mode must import globa markpoint data"));
	}
}
QBoxLayout* sdk_demo_fix::init_camera_video()
{
	//camera video data
	left_camera_video = new QLabel();
	right_camera_video = new QLabel();
	colour_camera_video = new QLabel();
	left_camera_video->setFixedSize(QSize(360, 270));
	right_camera_video->setFixedSize(QSize(360, 270));
	colour_camera_video->setFixedSize(QSize(360, 270));
	left_camera_video->setStyleSheet("QLabel{background-color:rgb(0,0,0);}");
	right_camera_video->setStyleSheet("QLabel{background-color:rgb(0,0,0);}");
	colour_camera_video->setStyleSheet("QLabel{background-color:rgb(0,0,0);}");

	QHBoxLayout* h_layout = new QHBoxLayout();
	h_layout->addWidget(left_camera_video);
	h_layout->addWidget(right_camera_video);
	h_layout->addWidget(colour_camera_video);

	return h_layout;
}

QWidget* sdk_demo_fix::init_scanner()
{
	QStringList device_items;
	device_type_list = new QComboBox();
	device_items << tr("EinScan-Pro") << tr("EinScan-S");
	device_type_list->addItems(device_items);
	device_type_list->setItemData(0, DEVICE_TYPE_PRO);
	device_type_list->setItemData(1, DEVICE_TYPE_S);
	device_type_list->setCurrentIndex(0);


	init_type_list = new QComboBox();

	QStringList items;
	items << tr("Calibrate") << tr("Fix Scan");
	init_type_list->addItems(items);
	init_type_list->setItemData(0, SN3D_INIT_CALIBRATE);
	init_type_list->setItemData(1, SN3D_INIT_FIX_SCAN);
	init_type_list->setCurrentIndex(0);

	//open close scanner
	open_scanner = new QPushButton();
	open_scanner->setText(tr("OpenScanner"));
	close_scanner = new QPushButton();
	close_scanner->setText(tr("CloseScanner"));
	scaner_prompt = new QLabel();
	QVBoxLayout* v_layout = new QVBoxLayout();

	
	v_layout->addWidget(device_type_list);
	v_layout->addWidget(init_type_list);
	v_layout->addWidget(open_scanner);
	v_layout->addWidget(close_scanner);
	v_layout->addWidget(scaner_prompt);

	scanner_group = new QGroupBox();
	scanner_group->setTitle(tr("Scanner"));
	scanner_group->setLayout(v_layout);
	return scanner_group;
}

QWidget* sdk_demo_fix::init_calibrate()
{
	//calibrate

	start_calibrate = new QPushButton();
	start_calibrate->setText(tr("Snap"));


	skip_calibrate = new QPushButton();
	skip_calibrate->setText(tr("SkipCalibrate"));

	QVBoxLayout* v_layout = new QVBoxLayout();
	v_layout->addWidget(start_calibrate);
	v_layout->addWidget(skip_calibrate);

	calibrate_prompt = new QLabel();

	calibrate_type = new QLabel();
	calibrate_state = new QLabel();

	calibrate_type->setFixedHeight(40);
	calibrate_state->setFixedHeight(40);
	calibrate_prompt->setFixedHeight(40);

	v_layout->addWidget(calibrate_type);
	v_layout->addWidget(calibrate_state);
	v_layout->addWidget(calibrate_prompt);

	v_layout->addWidget(init_calibrate_distance());


	calibrate_group = new QGroupBox();
	calibrate_group->setTitle(tr("Calibrate"));
	calibrate_group->setLayout(v_layout);
	return calibrate_group;

}

QWidget* sdk_demo_fix::init_scan()
{
	//scan 
	QLabel* brightness = new QLabel();
	brightness->setText(tr("AdjustBrightness"));
	brightness_list = new QComboBox();
	for (int i = 0; i <= 16; i++)
	{
		brightness_list->addItem(QString("%1").arg(i), i);
	}

	QHBoxLayout* brightness_layout = new QHBoxLayout();
	brightness_layout->addWidget(brightness);
	brightness_layout->addWidget(brightness_list);

	QGroupBox* scan_param_group = new QGroupBox();
	scan_param_group->setTitle(tr("ScanParam"));

	//
	get_scan_param = new QPushButton();
	get_scan_param->setText(tr("GetScanParam"));
	set_scan_param = new QPushButton();
	set_scan_param->setText(tr("SetScanParam"));

   //
	texture = new QCheckBox();
	texture->setText(tr("Texture"));
	current_texture = 0;
	texture->setChecked(false);

	//
	fix_scan_mode_free = new QRadioButton();
	fix_scan_mode_free->setText(tr("Free"));
	fix_scan_mode_turntable = new QRadioButton();
	fix_scan_mode_turntable->setText(tr("Turntable"));
	fix_scan_mode_free->setChecked(true);
	current_turntable_scan = 0;
	current_align_type = 0;
	connect(fix_scan_mode_free, SIGNAL(toggled(bool)), this, SLOT(on_free_mode_toggle(bool)));
	connect(fix_scan_mode_turntable, SIGNAL(toggled(bool)), this, SLOT(on_Turntable_mode_toggle(bool)));
	connect(texture, SIGNAL(toggled(bool)), this, SLOT(on_texture_toggle(bool)));

	turntable_times_label = new QLabel();
	turntable_times_label->setText(tr("Turntable Times ( 2-180 )"));
	turntable_times_value = new QLineEdit();

	QDoubleValidator* resolution_validate = new QDoubleValidator(turntable_times_value);
	resolution_validate->setBottom(2);
	resolution_validate->setTop(80);
	turntable_times_value->setValidator(resolution_validate);
	QObject::connect(turntable_times_value, SIGNAL(textChanged(const QString &)), SLOT(resolution_value_change(const QString &)));

	fix_scan_mode_group = new QGroupBox();
	fix_scan_mode_group->setFixedHeight(80);
	fix_scan_mode_group->setTitle(tr("ScanMode"));
	QHBoxLayout* h_scan_mode_layout = new QHBoxLayout();
	h_scan_mode_layout->addWidget(fix_scan_mode_free);
	h_scan_mode_layout->addWidget(fix_scan_mode_turntable);

	QHBoxLayout* h_Turntable_layout = new QHBoxLayout();
	h_Turntable_layout->addWidget(turntable_times_label);
	h_Turntable_layout->addWidget(turntable_times_value);

	QVBoxLayout* v_scan_mode_layout = new QVBoxLayout();
	v_scan_mode_layout->addLayout(h_scan_mode_layout);
	v_scan_mode_layout->addLayout(h_Turntable_layout);
	
	fix_scan_mode_group->setLayout(v_scan_mode_layout);

	//
	align_mode_code_point = new QRadioButton();
	align_mode_code_point->setText(tr("CodePoint"));
	align_mode_markpoint = new QRadioButton();
	align_mode_markpoint->setText(tr("MarkPoint"));

	align_mode_feature = new QRadioButton();
	align_mode_feature->setText(tr("Feature"));

	align_mode_global_mark_point = new QRadioButton();
	align_mode_global_mark_point->setText(tr("GlobalMarkPoint"));

	align_mode_global_mark_point_check = new QCheckBox();
	align_mode_global_mark_point_check->setText(tr("GlobalMarkPoint"));

	
	align_mode_feature->setChecked(true);

	align_group = new QGroupBox();
	align_group->setFixedHeight(50);
	align_group->setTitle(tr("AlignMode"));

	QHBoxLayout* h_layout = new QHBoxLayout();
	h_layout->addWidget(align_mode_feature);
	h_layout->addWidget(align_mode_code_point);
	h_layout->addWidget(align_mode_markpoint);
	h_layout->addWidget(align_mode_global_mark_point);
	h_layout->addWidget(align_mode_global_mark_point_check);
 
 
	align_group->setLayout(h_layout);

	QGridLayout* scan_paran_layout = new QGridLayout();
	scan_paran_layout->setSpacing(2);

	scan_paran_layout->addWidget(get_scan_param, 3, 0);
	scan_paran_layout->addWidget(set_scan_param, 3, 1);

 
	scan_paran_layout->addWidget(texture, 0, 0, 1, 2);
	scan_paran_layout->addWidget(fix_scan_mode_group,1,0,1,2);
	scan_paran_layout->addWidget(align_group, 2, 0, 1, 2);
	
	scan_param_group->setLayout(scan_paran_layout);
	scan_param_group->setFixedHeight(240);


	start_scan = new QPushButton();
	start_scan->setText(tr("StartScan"));
	 
	clear_scan = new QPushButton();
	clear_scan->setText(tr("ClearScan"));
 
	save_whole_data = new QPushButton();
	save_whole_data->setText(tr("Save")); 

	delete_point = new QPushButton();
	delete_point->setText(tr("DeletePoint"));

	point_index0_start = new QLineEdit();
	point_index0_end = new QLineEdit();
	point_index1_start = new QLineEdit();
	point_index1_end = new QLineEdit();
	point_index2_start = new QLineEdit();
	point_index2_end = new QLineEdit();

	QIntValidator* start0_validate = new QIntValidator(point_index0_start);
	start0_validate->setBottom(0);
	point_index0_start->setValidator(start0_validate);

	QIntValidator* end0_validate = new QIntValidator(point_index0_end);
	end0_validate->setBottom(0);
	point_index0_end->setValidator(start0_validate);

	QIntValidator* start1_validate = new QIntValidator(point_index1_start);
	start1_validate->setBottom(0);
	point_index1_start->setValidator(start0_validate);

	QIntValidator* end1_validate = new QIntValidator(point_index1_end);
	end1_validate->setBottom(0);
	point_index1_end->setValidator(end1_validate);

	QIntValidator* start2_validate = new QIntValidator(point_index2_start);
	start2_validate->setBottom(0);
	point_index2_start->setValidator(start2_validate);

	QIntValidator* end2_validate = new QIntValidator(point_index2_end);
	end2_validate->setBottom(0);
	point_index2_end->setValidator(end2_validate);


	QGridLayout* point_index_data = new QGridLayout();

	QLabel* index0 = new QLabel();
	index0->setText("IndexGroup:");
	point_index_data->addWidget(index0, 0, 0);
	point_index_data->addWidget(point_index0_start, 0, 1);
	QLabel*index0_span = new QLabel();
	index0_span->setText("--");
	point_index_data->addWidget(index0_span, 0, 2);
	point_index_data->addWidget(point_index0_end, 0, 3);

	//
	QLabel* index1 = new QLabel();
	index1->setText("IndexGroup:");
	point_index_data->addWidget(index1, 1, 0);
	point_index_data->addWidget(point_index1_start, 1, 1);
	QLabel*index1_span = new QLabel();
	index1_span->setText("--");
	point_index_data->addWidget(index0_span, 1, 2);
	point_index_data->addWidget(point_index1_end, 1, 3);

	QLabel* index2 = new QLabel();
	index2->setText("IndexGroup:");
	point_index_data->addWidget(index2, 2, 0);
	point_index_data->addWidget(point_index2_start, 2, 1);
	QLabel*index2_span = new QLabel();
	index2_span->setText("--");
	point_index_data->addWidget(index2_span, 2, 2);
	point_index_data->addWidget(point_index2_end, 2, 3);

	point_index_data->addWidget(delete_point, 3, 0, 1, 4);


	QGroupBox* delete_point_group = new QGroupBox();
	delete_point_group->setTitle(tr("Deleted Point"));
	delete_point_group->setLayout(point_index_data);
	delete_point_group->setFixedHeight(140);


	QVBoxLayout* v_layout = new QVBoxLayout();

	v_layout->setSpacing(2);
	v_layout->addLayout(brightness_layout);
	v_layout->addWidget(scan_param_group);

	QHBoxLayout* start_save = new QHBoxLayout;
	start_save->addWidget(start_scan);
	start_save->addWidget(save_whole_data);
	start_save->addWidget(clear_scan);

	v_layout->addLayout(start_save);
	 
	v_layout->addWidget(delete_point_group);


	scan_point_count = new QLabel();
	scan_point_count->setFixedHeight(60);

	v_layout->addWidget(scan_point_count);

	scan_group = new QGroupBox();
	scan_group->setTitle(tr("Scan"));
	scan_group->setLayout(v_layout);

	scan_group->setFixedWidth(480);
	return scan_group;

}

sdk_demo_fix::~sdk_demo_fix()
{

}

int sdk_demo_fix::handle_update_video(msg_data_t msg_data)
{

	int imgW_ = msg_data.map_data["width"].toInt();
	int imgH_ = msg_data.map_data["height"].toInt();

	QImage  picture;
	unsigned char* img_data = NULL;
	if (msg_data.hint == 2)//color camera
	{
		QImage testStep(imgW_, imgH_, QImage::Format_RGB888);

		int width_step = testStep.bytesPerLine();
		 
		img_data=msg_data.map_data["image"].value<unsigned char*>();
	
		unsigned char u = 0;
		for (int i = 0; i < imgW_; i++)
		{
			for (int j = 0; j < imgH_; j++)
			{
                u = (unsigned char)img_data[j*width_step + i * 3 + 2];
				img_data[j*width_step + i * 3 + 2] = (unsigned char)img_data[j*width_step + i * 3 + 0];
				img_data[j*width_step + i * 3 + 0] = u;
			}
		}
		picture = QImage(img_data, imgW_, imgH_, QImage::Format_RGB888);
	

		 
	}
	else// left right camera
	{
		picture = msg_data.map_data["image"].value<QImage>();
	}
	
	QLabel* video_wnd = left_camera_video;
	if (msg_data.hint == 1)//right cam
	{
		video_wnd = right_camera_video;
	}
	else if (msg_data.hint == 2)
	{
		video_wnd = colour_camera_video;
	}
	int nWidth = video_wnd->width();
	int nHeight = video_wnd->height();
	QPixmap pixmap = QPixmap::fromImage(picture);
	pixmap = pixmap.scaled(QSize(nWidth, nHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QMatrix left_matrix_;
	left_matrix_.rotate(180);

	pixmap = pixmap.transformed(left_matrix_, Qt::SmoothTransformation);

	video_wnd->setPixmap(pixmap);

	if (img_data != NULL)
		delete[] img_data;
	img_data = NULL;

	return 0;
}
int sdk_demo_fix::change_ui_state(int state)
{
	switch (state)
	{
	case ui_state_ui_init:
	{
			calibrate_group->setEnabled(false);
			scan_group->setEnabled(false);
			close_scanner->setEnabled(false);
			open_scanner->setEnabled(true);
	}
		break;
	case ui_state_open_scanner_ok:
	{
			if (current_scan_type == SN3D_INIT_CALIBRATE)
			{

				calibrate_group->setEnabled(true);
				scan_group->setEnabled(false);
				close_scanner->setEnabled(true);
				open_scanner->setEnabled(false);
				start_calibrate->setEnabled(true);
				skip_calibrate->setEnabled(true);
			}
			else if (current_scan_type == SN3D_INIT_FIX_SCAN )
			{
				calibrate_group->setEnabled(false);
				
				close_scanner->setEnabled(true);
				open_scanner->setEnabled(false);

				scan_group->setEnabled(true);
				//
				start_scan->setEnabled(true);
				clear_scan->setEnabled(false);
				save_whole_data->setEnabled(false);

				//scan param
				set_scan_param->setEnabled(true);
				get_scan_param->setEnabled(true);
				
				//
				texture->setEnabled(true);
				//scan mode
				fix_scan_mode_group->setEnabled(true);
				fix_scan_mode_free->setChecked(true);
				
				//align mode 
				align_group->setEnabled(true);
			 
			    //
				turntable_times_value->setEnabled(false);
				turntable_times_label->setEnabled(false);
				//delete point
				delete_point->setEnabled(false);
				point_index0_start->setEnabled(false);
				point_index0_end->setEnabled(false);
				point_index1_start->setEnabled(false);
				point_index1_end->setEnabled(false);
				point_index2_start->setEnabled(false);
				point_index2_end->setEnabled(false);

				on_scan_mode_change();
			}

	}
		break;
	case ui_state_scanner_closed:
	{

		calibrate_group->setEnabled(false);
		scan_group->setEnabled(false);
		close_scanner->setEnabled(false);
		open_scanner->setEnabled(true);
	}
		break;
	case ui_state_scanning:
	{

			texture->setEnabled(false);
			fix_scan_mode_group->setEnabled(false);
			align_group->setEnabled(false);

			clear_scan->setEnabled(true);
			save_whole_data->setEnabled(true);
			delete_point->setEnabled(true);
			point_index0_start->setEnabled(true);
			point_index0_end->setEnabled(true);
			point_index1_start->setEnabled(true);
			point_index1_end->setEnabled(true);
			point_index2_start->setEnabled(true);
			point_index2_end->setEnabled(true);

			break;
	}
	 
	case ui_state_scanning_canceled:
	{
		 
		 
			save_whole_data->setEnabled(false);
			clear_scan->setEnabled(false);
			 
			delete_point->setEnabled(false);
			point_index0_start->setEnabled(false);
			point_index0_end->setEnabled(false);
			point_index1_start->setEnabled(false);
			point_index1_end->setEnabled(false);
			point_index2_start->setEnabled(false);
			point_index2_end->setEnabled(false);

			clear_show_data();
			break;
	}


	}
	return 0;
}

void sdk_demo_fix::on_pro_open_scanner()
{

	current_scan_type = init_type_list->currentData().toInt();

	SN3D_INIT_DATA init_data = { 0 };
	init_data.device_type = 0;
	int ret = 0;
	if (handle != 0)
	{
		ret = sn3d_close(handle);
		handle = 0;
		show_error(ret);
	}
	qDebug() << "init_type=" << current_scan_type;
	ret = sn3d_Initialize(current_scan_type, &init_data, handle);

	if (ret == SN3D_RET_NOERROR)
	{
		change_ui_state(ui_state_open_scanner_ok);
		//
		sn3d_regist_callback(handle, scan_demo_callback, this);
		if (current_scan_type != SN3D_INIT_CALIBRATE)
		{
			int min_brigthness = 0;
			int max_brigthness = 12;

			if (SN3D_RET_NOERROR == sn3d_get_brightness_range(handle, min_brigthness, max_brigthness))
			{
				brightness_list->clear();
				for (int i = min_brigthness; i <= max_brigthness; i++)
				{
					brightness_list->addItem(QString("%1").arg(i), i);
				}
			}

			update_brightness();
			update_scan_param();
		}
	}
	show_error(ret, false);
}
void sdk_demo_fix::on_fix_open_scanner()
{
	hScanSession = NULL;
	int ret = -1;
	TCHAR* scan_path_ = _T("res\\einscan-pro");

	sn3DScan::sn3d_Initialize_Scan_Session(sn3DScan::BINO_MONO, scan_path_, hScanSession);

	if (hScanSession)
	{
		printf("open cam is ok   === \n");
		current_texture = 0;//use non-texture
		sn3DScan::sn3d_enable_textrue(hScanSession, current_texture);
		//current_texture = 1;//use texture
		//sn3DScan::sn3d_enable_textrue(hScanSession, current_texture);
		sn3DScan::sn3d_Regist_Fix_Scan_Camera_Callback(hScanSession, fix_scan_calback,this);
		int turntable_type_ = 1;
		if (0 < turntable_type_){
			int set_ = -1;
			{
				char *motortype = "COM9-115200-1100";
				int set_ = sn3DTurnTable::SetType(motortype);
			}

			set_ = sn3DTurnTable::OpenTurntable();
			printf("set_   === %d\n", set_);
			set_ = sn3DTurnTable::initTurntable();
			printf("set_   === %d\n", set_);
		}

		ret = 0;
	}
	change_ui_state(ui_state_open_scanner_ok);
}

void sdk_demo_fix::on_open_scanner()
{
	current_scan_type = init_type_list->currentData().toInt();
	current_device_type = device_type_list->currentData().toInt();
 
	if (current_device_type == DEVICE_TYPE_PRO && current_scan_type == SN3D_INIT_CALIBRATE)
	{
		on_pro_open_scanner();
	}
	else
	{
		on_fix_open_scanner();
		//QMessageBox::warning(NULL, tr("Warning"), tr("Not support"));
	}
	
}

void sdk_demo_fix::on_pro_close_scanner()
{
	int ret = 0;
	if (handle != 0)
	{
		ret = sn3d_close(handle);
		handle = 0;
		show_error(ret, false);
	}
	change_ui_state(ui_state_scanner_closed);
	reset_calibrate_distance();
}
void sdk_demo_fix::on_fix_close_scanner()
{
	if (hScanSession){
		sn3DScan::sn3d_Regist_Fix_Scan_Camera_Callback(hScanSession, NULL,this);
		sn3DScan::sn3d_Destroy_Scan_Session(hScanSession);
	}
	hScanSession = NULL;
	change_ui_state(ui_state_scanner_closed);
}
void sdk_demo_fix::on_close_scanner()
{
	if (current_device_type == DEVICE_TYPE_PRO &&  current_scan_type == SN3D_INIT_CALIBRATE)
	{
		on_pro_close_scanner();
	}
	else
	{
		on_clear_scan();
		on_fix_close_scanner();
	}
}
void sdk_demo_fix::on_start_calibrate()
{
	int ret = 0;
	if (handle != 0)
	{
		ret = sn3d_start_calibrate(handle);
		show_error(ret);
		reset_calibrate_distance();
		if (ret == SN3D_RET_NOERROR)
		{
			start_calibrate->setEnabled(false);
		}
	}
}

void sdk_demo_fix::on_skip_calibrate()
{
	int ret = 0;
	if (handle != 0)
	{
		ret = sn3d_skip_calibrate(handle);
		show_error(ret);
		if (ret == SN3D_RET_NOERROR)
		{
			start_calibrate->setEnabled(true);
		}
		reset_calibrate_distance();
	}
}

void sdk_demo_fix::resolution_value_change(const QString& text)
{
	QString msg = tr("Suggest value range 2-180");
	double minValue = 2;
	if (current_scan_type == SN3D_INIT_HD_SCAN)
	{
		msg = tr("Suggest value range 2-180");
		minValue = 2;
	}
	bool ok = false;
	

	double value = text.toInt(&ok);
	 
	if (!ok || value < minValue || value>180)
	{
		QPoint  left_top = turntable_times_value->pos();
		left_top.setY(left_top.y() + 5);
		left_top = turntable_times_value->parentWidget()->mapToGlobal(left_top);

		QRect rt;
		rt.setTopLeft(left_top);
		rt.setHeight(30);
		rt.setWidth(100);

		QToolTip::showText(left_top, msg, turntable_times_value, rt, 1000);
		
	}
	else
	{
		turntable_times = text.toInt(&ok);
		printf("turntable_times   =  %d\n", turntable_times);
		printf("turntable_times   =  %d\n", turntable_times);
		printf("turntable_times   =  %d\n", turntable_times);
		printf("turntable_times   =  %d\n", turntable_times);
	}

}
void sdk_demo_fix::on_get_scan_param()
{
	if (handle)
	{
		int ret = update_scan_param();
		show_error(ret);
	}
}
void sdk_demo_fix::on_set_scan_param()
{
	if (handle)
	{
		SN3D_SCAN_PARAM param = { 0 };
		param.resolution = turntable_times_value->text().toDouble();
		param.flag_texture = texture->isChecked() ? 1 : 0;
	
		if (current_scan_type == SN3D_INIT_HD_SCAN)
		{
			param.align_mode = SN3D_ALIGN_MODE_MARK_POINT;
			param.flag_texture = 0;
		}
		else
		{
			param.align_mode = align_mode_markpoint->isChecked() ? SN3D_ALIGN_MODE_MARK_POINT : SN3D_ALIGN_MODE_FEATURE;
		}

		int ret = 0;// sn3d_set_scan_param(handle, &param);

		qDebug() << "ret=" << ret << "resolution=" << param.resolution << "flag_texture=" << param.flag_texture << "align_mode=" << param.align_mode;

		show_error(ret);
		clear_show_data();
	}
}
void sdk_demo_fix::on_clear_scan()
{
	 //
	int size_vn_ = m_rangeDatas.size();
	for (int i = 0; i < size_vn_; i++)
	{
		delete m_rangeDatas[i];
		m_rangeDatas[i] = NULL;	 
	}

	m_rangeDatas.clear();
}
void sdk_demo_fix::on_start_scan()
{
		int ret = 0; 
		if (0==current_turntable_scan)
			free_scan();
		else
			turntable_scan();
		if (ret == SN3D_RET_NOERROR)
		{
			change_ui_state(ui_state_scanning);
		}
		else
		{
			show_error(ret);
		}
 
} 

void sdk_demo_fix::on_save_whole_data()
{
	QString filename_ = QFileDialog::getSaveFileName(this, tr("save file"), "", tr("(*.asc)"));
	if (!filename_.isNull()){
		demo_data_center::Instance()->save_whole_point(filename_.toLocal8Bit().data());
	}
}
void sdk_demo_fix::on_texture_toggle(bool tog)
{
	current_texture = tog ? 1 : 0;
}
void sdk_demo_fix::on_free_mode_toggle(bool tog)
{
	turntable_times_value->setEnabled(!tog);
	turntable_times_label->setEnabled(!tog);
	
	current_turntable_scan = 0;


	current_align_type = 0;
	on_scan_mode_change();
}
void sdk_demo_fix::on_Turntable_mode_toggle(bool tog)
{
	turntable_times_value->setEnabled(tog);
	turntable_times_label->setEnabled(tog);
	current_align_type = 0;

	align_mode_feature->setEnabled(false);

	if (align_mode_code_point->isChecked())
	{
		current_align_type = SN3D_ALIGN_TURTABLE_CODE_POINT;
	}
	else if (align_mode_markpoint->isChecked())
	{
		current_align_type = SN3D_ALIGN_MODE_MARK_POINT;
	}
	else if (align_mode_feature->isChecked())
	{
		current_align_type = SN3D_ALIGN_MODE_FEATURE;
	}
	else if (align_mode_global_mark_point->isChecked())
	{
		current_align_type = SN3D_ALIGN_MODE_GLOABL_MARK_POINT;
	}
 

	current_turntable_scan = 1;
	on_scan_mode_change();
	std::cout << "on_Turntable_mode_toggle === ===current_align_type=  " << current_align_type << std::endl;
}
void sdk_demo_fix::on_delete_point()
{
	if (handle)
	{
		int start0 = point_index0_start->text().toInt();
		int end0 = point_index0_end->text().toInt();

		int start1 = point_index1_start->text().toInt();
		int end1 = point_index1_end->text().toInt();

		int start2 = point_index2_start->text().toInt();
		int end2 = point_index2_end->text().toInt();

		SN3D_CLOUD_POINT remain_point = { 0 };
		int remain_count = demo_data_center::Instance()->delete_point(start0, end0, start1, end1, start2, end2, remain_point);


		int ret = sn3d_update_cloud_point(handle, remain_point);
		show_error(ret);
		whole_point_count = remain_point.vertex_count;
		show_data();
	}
}

void sdk_demo_fix::on_brightness_list_change(int index)
{
//	if (handle)
	{
		int value = brightness_list->itemData(index).toInt();
		int value_ = 0;
		sn3DScan::sn3d_get_brightness_max_range(hScanSession, value_);
		sn3DScan::sn3d_set_brightness(hScanSession, value);

		//int ret = 0; 
		//show_error(ret);
	}
}
void sdk_demo_fix::handle_msg(msg_data_t msg_data)
{
	switch (msg_data.msg_type)
	{
	case SN3D_VIDEO_IMAGE_DATA_READY:
		handle_update_video(msg_data);
		break;
	case SN3D_SCANNER_RT_READY:
		handle_update_scanner_rt(msg_data);
		break;
	case SN3D_CURRENT_MARKPOINT_DATA_READY:
		handle_update_current_mark_cloud_point(msg_data);
		break;
	case SN3D_WHOLE_MARKPOINT_DATA_READY:
		handle_update_whole_mark_cloud_point(msg_data);
		break;
	case SN3D_CURRENT_SCAN_POINT_CLOUD_READY:
		handle_update_current_cloud_point(msg_data);
		break;
	case SN3D_WHOLE_SCAN_POINT_CLOUD_READY:
		handle_update_whole_cloud_point(msg_data);
		break;
	case SN3D_CALIBRATION_STATE_DATA:
		handle_calibrate_msg(msg_data);
		break;
	case SN3D_SCANNER_DOUBLECLICK:
		handle_scanner_double_click_msg(msg_data);
		break;
	case SN3D_SCANNER_CLICK:
		handle_scanner_click_msg(msg_data);
		break;
	case SN3D_SCANNER_PLUS:
	case SN3D_SCANNER_SUB:
		handle_scanner_plus_sub_msg(msg_data);
		break;

	default:
		break;
	}
}
int sdk_demo_fix::handle_update_scanner_rt(msg_data_t msg_data)
{
	SN3D_SCANNER_RT rt = { 0 };
	demo_data_center::Instance()->get_scanner_rt(rt);

	/*qDebug() << "rot=" << rt.rotate[0] << " " << rt.rotate[1] << " " << rt.rotate[2]
		<< " " << rt.rotate[3] << " " << rt.rotate[4] << " " << rt.rotate[5]
		<< " " << rt.rotate[6] << " " << rt.rotate[7] << " " << rt.rotate[9]
		<< "trans= " << rt.trans[0] << " " << rt.trans[1] << " " << rt.trans[2];*/

	return 0;
}
int sdk_demo_fix::handle_update_current_cloud_point(msg_data_t msg_data)
{
	cur_point_count = msg_data.map_data["param"].toInt();
	show_data();
	return 0;
}
int sdk_demo_fix::handle_update_whole_cloud_point(msg_data_t msg_data)
{
	whole_point_count = msg_data.map_data["param"].toInt();
	show_data();
	return 0;
}
int sdk_demo_fix::handle_update_current_mark_cloud_point(msg_data_t msg_data)
{
	marker_point_count = msg_data.map_data["param"].toInt();
	show_data();
	return 0;
}
int sdk_demo_fix::handle_update_whole_mark_cloud_point(msg_data_t msg_data)
{
	whole_marker_point_count = msg_data.map_data["param"].toInt();
	show_data();
	return 0;
}

int sdk_demo_fix::handle_scanner_double_click_msg(msg_data_t msg_data)
{
	qDebug() << "scanner double click ";
	return 0;
}
int sdk_demo_fix::handle_scanner_click_msg(msg_data_t msg_data)
{
 

	return 0;
}
int sdk_demo_fix::handle_scanner_plus_sub_msg(msg_data_t msg_data)
{
	int current_index = brightness_list->currentIndex();
	if (msg_data.msg_type == SN3D_SCANNER_PLUS)
	{
		current_index++;
	}
	else
	{
		current_index--;
	}
	if (current_index <= 0) current_index = 0;
	if (current_index >= brightness_list->count())
		current_index = brightness_list->count() - 1;

	brightness_list->setCurrentIndex(current_index);

	return 0;
}
int sdk_demo_fix::handle_calibrate_msg(msg_data_t msg_data)
{
	int current_calibrate = msg_data.map_data["current_calibrate"].toInt();
	int distance = msg_data.map_data["distance"].toInt();
	int group = msg_data.map_data["group"].toInt();
	int snap_state = msg_data.map_data["snap_state"].toInt();
	int compute_state = msg_data.map_data["compute_state"].toInt();


	QString str_compute_state = tr(" ");
 
	QString cur_calibrate_type = tr("Current: Camera Calibrate");
	if (current_calibrate == SN3D_CALIBRATE_STATE_HD)
	{
		cur_calibrate_type = tr("Current: HD Calibrate");
	}
	else if (current_calibrate == SN3D_CALIBRATE_STATE_WB)
	{
		cur_calibrate_type = tr("Current: WB Calibrate");
	}
	else if (current_calibrate == SN3D_CALIBRATE_STATE_EXIT)
	{
		cur_calibrate_type = tr("Current: Calibrate Finished ");
		start_calibrate->setEnabled(false);
		skip_calibrate->setEnabled(false);
		str_compute_state = tr("Please Close The Device");
	}

	QString str_snap_sate = tr(" ");
	if (snap_state == SN3D_CALIBRATE_SNAP_STATE_ON)
	{
		str_snap_sate = tr("Snap On");
		start_calibrate->setEnabled(false);
		
	}
	else if (snap_state == SN3D_CALIBRATE_SNAP_STATE_OFF)
	{
		str_snap_sate = tr("Snap Off");
		start_calibrate->setEnabled(true);
	}

	if (compute_state == SN3D_CALIBRATE_COMPUTING)
	{
		str_compute_state = tr("Computing ");
		skip_calibrate->setEnabled(false);
		start_calibrate->setEnabled(false);
	}
	else if (compute_state == SN3D_CALIBRATE_COMPUTE_SUCCESS)
	{
		str_compute_state = tr("Compute sucesse ");
		skip_calibrate->setEnabled(true);
		start_calibrate->setEnabled(true);
	}
	else if (compute_state == SN3D_CALIBRATE_COMPUTE_FAILED)
	{
		str_compute_state = tr("Compute failed ");
		skip_calibrate->setEnabled(true);
		start_calibrate->setEnabled(true);
	}

	if (current_calibrate == SN3D_CALIBRATE_STATE_CAMERA && group != SN3D_CALIBRATE_INVALID )
	{
		cur_calibrate_type += QString(" %1/5").arg(group);
	}
	 
	calibrate_state->setText(str_snap_sate);
	calibrate_type->setText(cur_calibrate_type);
	calibrate_prompt->setText(str_compute_state);

	set_calibrate_state(current_calibrate, distance, group);

	if (current_calibrate != current_calibrate_type)
	{
		current_calibrate_type = current_calibrate;
		reset_calibrate_distance();
	}
	if (group != SN3D_CALIBRATE_INVALID && group != current_camera_group)
	{
		current_camera_group = group;
		QApplication::processEvents();
		_sleep(1000);
		reset_calibrate_distance();
	}
	return 0;
}
void sdk_demo_fix::set_calibrate_state(int calibrate_type, int distance_index, int group)
{
	calibrate_state_manager->setCurrentIndex(calibrate_type);

	if (calibrate_type == SN3D_CALIBRATE_STATE_CAMERA && distance_index >= 0 && distance_index <= 4)
	{
		for (int i = 0; i < 5; i++)
		{
			QString str_color = "background-color:rgb(199,199,199);";
			if (camera_distance[i]->property("state").toInt() == 1)
			{
				str_color = "background-color:rgb(0,255,0);";
			}
			camera_distance[i]->setStyleSheet(str_color);
		}
		camera_distance[4 - distance_index]->setProperty("state", 1);
		camera_distance[4 - distance_index]->setStyleSheet("background-color:rgb(0,0,255);");
	}

	if (calibrate_type == SN3D_CALIBRATE_STATE_HD && distance_index >= 0 && distance_index <= 11)
	{
		for (int i = 0; i < 12; i++)
		{
			QString str_color = "background-color:rgb(199,199,199);";
			if (hd_distance[i]->property("state").toInt() == 1)
			{
				str_color = "background-color:rgb(0,255,0);";
			}
			hd_distance[i]->setStyleSheet(str_color);
		}

		hd_distance[11 - distance_index]->setStyleSheet("background-color:rgb(0,0,255);");
		hd_distance[11 - distance_index]->setProperty("state", 1);
	}

	if (calibrate_type == SN3D_CALIBRATE_STATE_WB && distance_index >= 0 && distance_index <= 11)
	{
		for (int i = 0; i < 12; i++)
		{
			wb_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");

			if (i == 5)
				wb_distance[i]->setStyleSheet("background-color:rgb(0,255,0);");
		}
		qDebug() << "distance_index=" << distance_index;
		wb_distance[11 - distance_index]->setStyleSheet("background-color:rgb(0,0,255);");

	}

}

void sdk_demo_fix::reset_calibrate_distance()
{
	for (int i = 0; i < 5; i++)
	{
		camera_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		camera_distance[i]->setProperty("state", 0);
	}
	for (int i = 0; i < 12; i++)
	{
		hd_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		hd_distance[i]->setProperty("state", 0);
	}
	for (int i = 0; i < 12; i++)
	{
		wb_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		if (i == 6)
			wb_distance[i]->setStyleSheet("background-color:rgb(0,0,255);");
	}
}
QWidget*  sdk_demo_fix::init_calibrate_distance()
{
	QWidget*  cam_widget = new  QWidget();
	QVBoxLayout* v_cam = new QVBoxLayout();
	for (int i = 0; i < 5; i++)
	{
		camera_distance[i] = new QLabel();

		camera_distance[i]->setFixedHeight(30);
		camera_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		v_cam->addWidget(camera_distance[i]);
		
	}
	v_cam->addStretch();
	cam_widget->setLayout(v_cam);

	QWidget*  hd_widget = new  QWidget();
	QVBoxLayout* v_hd = new QVBoxLayout();
	v_hd->setSpacing(2);
	for (int i = 0; i < 12; i++)
	{
		hd_distance[i] = new QLabel();
		hd_distance[i]->setFixedHeight(15);
		hd_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		v_hd->addWidget(hd_distance[i]);
	
	}
	v_hd->addStretch();
	hd_widget->setLayout(v_hd);

	QWidget*  wb_widget = new  QWidget();
	QVBoxLayout* v_wb = new QVBoxLayout();
	v_wb->setSpacing(2);
	for (int i = 0; i < 12; i++)
	{
		wb_distance[i] = new QLabel();
		wb_distance[i]->setFixedHeight(15);
		wb_distance[i]->setStyleSheet("background-color:rgb(199,199,199);");
		v_wb->addWidget(wb_distance[i]);
	
	}
	v_wb->addStretch();
	wb_widget->setLayout(v_wb);
	calibrate_state_manager = new QStackedWidget();
	calibrate_state_manager->setFixedHeight(400);
	calibrate_state_manager->addWidget(cam_widget);
	calibrate_state_manager->addWidget(hd_widget);
	calibrate_state_manager->addWidget(wb_widget);
	calibrate_state_manager->setCurrentIndex(0);

	return calibrate_state_manager;
}
void sdk_demo_fix::show_data()
{
	QString point = QString("current point=%1 whole point=%2\ncurrent mark point=%3 whole mark point=%4").arg(cur_point_count).arg(whole_point_count).arg(marker_point_count).arg(whole_marker_point_count);
	scan_point_count->setText(point);

}
int sdk_demo_fix::update_brightness()
{
	int ret = 0;
	if (handle)
	{
		int brightness = 0;
		ret = 0;// sn3d_get_brightness(handle, brightness);
		qDebug() << "ret=" << ret << "brightness=" << brightness;
		brightness_list->setCurrentIndex(brightness);
	}
	return ret;
}

void sdk_demo_fix::clear_show_data()
{
	demo_data_center::Instance()->clear_data();
	cur_point_count=0;
	whole_point_count=0;
	marker_point_count=0;
	whole_marker_point_count=0;
	show_data();
}
int sdk_demo_fix::update_scan_param()
{
	int ret = 0;
	if (handle)
	{
		/*SN3D_SCAN_PARAM param = { 0 };
		ret = sn3d_get_scan_param(handle, param);

		qDebug() << "ret=" << ret << "resolution=" << param.resolution << "flag_texture=" << param.flag_texture << "align_mode=" << param.align_mode;
		point_resolution_value->setText(QString("%1").arg(param.resolution));
		if (param.align_mode == SN3D_ALIGN_MODE_FEATURE)
			align_mode_feature->setChecked(true);
		else
			align_mode_markpoint->setChecked(true);
		
			current_texture = param.flag_texture;	 
		if (param.flag_texture == 1)
			texture->setChecked(true);
		else
			texture->setChecked(false);*/

		turntable_times_value->setText("8");
	}
	return ret;
}
void sdk_demo_fix::show_error(int err_code,bool only_show_err)
{
	QString str_err = tr("execute ok");
	switch (err_code)
	{
	case SN3D_RET_PARAM_ERROR:
		str_err = tr("param error");
		break;
	case SN3D_RET_ORDER_ERROR:
		str_err = tr("invoke order error");
		break;
	case SN3D_RET_TIME_OUT_ERROR:
		str_err = tr("invoke time out error");
		break;
	case SN3D_RET_NOT_SUPPORT_ERROR:
		str_err = tr("not support command error");
		break;
	case SN3D_RET_NO_DEVICE_ERROR:
		str_err = tr("not connect device error");
		break;
	case SN3D_RET_DEVICE_LICENSE_ERROR:
		str_err = tr("license error");
		break;
	case SN3D_RET_GPU_ERROR:
		str_err = tr("Graphics card incompatible with scanner OR the graphics driver is out-of-date! \nPlease follow the prompts and try again:\n(1) Ensure graphics card is equivalent to NVIDIA GTX series 660 or higher;\n(2) Update driver to latest version.");
		break;
	case SN3D_RET_INNER_ERROR:
		str_err = tr("SDK inner Error");
		break;
	case SN3D_RET_NOT_CALIBRATE_ERROR:
		str_err = tr("No Calibrate Data");
		break;
	case SN3D_RET_LOST_CONFIG_FILE_ERROR:
		str_err = tr("Config File Lost");
		break;
	case SN3D_RET_NO_DATA_ERROR:
		str_err = tr("No Scan Data");
		break;
	case SN3D_RET_LOST_CALIBRATE_FILE_ERROR:
		str_err = tr("Calibrate File Lost");
		break;
	default:
		break;

	}

	if (only_show_err)
	{
		if (err_code != SN3D_RET_NOERROR)
			QMessageBox::warning(NULL, tr("Warning"), str_err);
	}
	else
	{
		QMessageBox::warning(NULL, tr("Warning"), str_err);
	}
	

}

int sdk_demo_fix::turntable_scan()
{
	int turntable_times_ = 8;
	int turntable_angle_ = 360 /8 + 0.5;

	for (int turn_time_i_ = 0; turn_time_i_ < turntable_times_; ++turn_time_i_)
	{
		if (SN3D_ALIGN_TURTABLE_CODE_POINT==current_align_type)
			turntban_code_scan_control(hScanSession, turn_time_i_);
		else if (SN3D_ALIGN_MODE_MARK_POINT == current_align_type)
			turntban_ref_scan_control(hScanSession, turn_time_i_);
		else if (SN3D_ALIGN_MODE_GLOABL_MARK_POINT == current_align_type)
			turntban_ref_scan_control(hScanSession, turn_time_i_);
		//Run A Specific Angle
		std::cout << "sn3DTurnTable::GetTurnTableState === ===  " << current_align_type << std::endl;
		if (sn3DTurnTable::GetTurnTableState())
			sn3DTurnTable::Run2Coordinate(X_ROTATE, turntable_angle_, RELATIVE_ANGLE);
	}
	return 1;
}

//code scan type
//The global mark points will always used after using this function(Import Global Mark Point).
bool sdk_demo_fix::turntban_code_scan_control(
	void* hScanSession_,int times_)
{
	bool return_type_ = false;
	sn3DCore::sn3DRangeData* data = NULL;
	int value_c_ = -1;
	if (0==times_)
		value_c_ = sn3DScan::sn3d_turntable_code_Scan(hScanSession, data, true);
	else
		value_c_ = sn3DScan::sn3d_turntable_code_Scan(hScanSession, data, false);

	if (0 == value_c_)
	{
		std::cout << "turntban_scan_control === ===  " << value_c_ << std::endl;
		data->SetName(_T(""));

		char tmpStr_[512] = { '\0' };
		sprintf(tmpStr_, "res\\scan_%d", times_);
		FILE *fp_ = fopen(tmpStr_, "w");
		int point_num_ = data->GetVN();
		double rotate_[9] = { 0 };
		double trans_[3] = { 0 };
		data->GetTransformation(rotate_, trans_);
		for (int point_i_ = 0; point_i_ < point_num_; ++point_i_){

			Vector3f  &point_ = data->Vertex(point_i_); //point 
			Vector3f  &point_n_ = data->VNormal(point_i_); //normal
			double x_ = 0.0;
			double y_ = 0.0;
			double z_ = 0.0;
			x_ = point_[0] * rotate_[0] + point_[1] * rotate_[1] + point_[2] * rotate_[2] + trans_[0];
			y_ = point_[0] * rotate_[3] + point_[1] * rotate_[4] + point_[2] * rotate_[5] + trans_[1];
			z_ = point_[0] * rotate_[6] + point_[1] * rotate_[7] + point_[2] * rotate_[8] + trans_[2];
			double n_x_ = 0.0;
			double n_y_ = 0.0;
			double n_z_ = 0.0;
			n_x_ = -1 * (point_n_[0] * rotate_[0] + point_n_[1] * rotate_[1] + point_n_[2] * rotate_[2]);
			n_y_ = -1*(point_n_[0] * rotate_[3] + point_n_[1] * rotate_[4] + point_n_[2] * rotate_[5]);
			n_z_ = -1 * (point_n_[0] * rotate_[6] + point_n_[1] * rotate_[7] + point_n_[2] * rotate_[8]);
			// point Color 
			//if (data->IsEnableVColor())
			//{
			//	data->VColor(point_i_).R();
			//	data->VColor(point_i_).G();
			//	data->VColor(point_i_).B();
			//}


			fprintf(fp_, "%f %f %f %f %f %f\n", x_, y_, z_, n_x_, n_y_, n_z_);
		}
		fclose(fp_);
		m_rangeDatas.push_back(data);
	}
	else if (NULL != data)
	{
		std::cout << "turntban_scan_control === END ===  " << value_c_ << std::endl;
		delete data;
		data = NULL;
		return_type_ = false;
	}
	return return_type_;
}

//free scan
bool sdk_demo_fix::free_scan()
{
	bool result = false;
	int value_ = -1;
	sn3DCore::sn3DRangeData* m_rangeData_ = NULL;
	value_ = sn3DScan::sn3d_free_Scan(hScanSession, m_rangeDatas, m_rangeData_);
	if (0 == value_)
	{
		FILE *fl_test_ = _tfopen(_T("res\\test_.asc"), _T("w"));
		if (fl_test_ == NULL)
			return result;
		int fix_vn_ = m_rangeData_->GetVN();
		double fix_r[9] = { 0 };
		double fix_t[3] = { 0 };
		m_rangeData_->GetTransformation(fix_r, fix_t);
		for (int i = 0; i < fix_vn_; i++)
		{
			Vector3f  &point_ = m_rangeData_->Vertex(i); //point 
			Vector3f  &point_n_ = m_rangeData_->VNormal(i); //normal
			double xPoint_ = point_[0] * fix_r[0] + point_[1] * fix_r[1] + point_[2] * fix_r[2] + fix_t[0];
			double yPoint_ = point_[0] * fix_r[3] + point_[1] * fix_r[4] + point_[2] * fix_r[5] + fix_t[1];
			double zPoint_ = point_[0] * fix_r[6] + point_[1] * fix_r[7] + point_[2] * fix_r[8] + fix_t[2];
			fprintf(fl_test_, "%f %f %f \n", xPoint_, yPoint_, zPoint_);
		}
		fclose(fl_test_);
		result = true;
		m_rangeDatas.push_back(m_rangeData_);
	}
	return result;
}

//mark scan type
//The global mark points will always used after using this function(Import Global Mark Point).
bool sdk_demo_fix::turntban_ref_scan_control(
	void* hScanSession_, int times_)
{
	std::cout << "sdk_demo_fix::turntban_ref_scan_control---- " << std::endl;
	bool return_type_ = false;
	sn3DCore::sn3DRangeData* data = NULL;
	int value_c_ = -1;
	if (0 == times_)
		value_c_ = sn3DScan::sn3d_turntable_mark_Scan(hScanSession, data, m_rangeDatas, true);
	else
		value_c_ = sn3DScan::sn3d_turntable_mark_Scan(hScanSession, data, m_rangeDatas,  false);

	if (0 == value_c_)
	{
		std::cout << "turntban_scan_control === ===  " << value_c_ << std::endl;
		data->SetName(_T(""));

		char tmpStr_[512] = { '\0' };
		sprintf(tmpStr_, "res\\scan_%d", times_);
		FILE *fp_ = fopen(tmpStr_, "w");
		int point_num_ = data->GetVN();
		double rotate_[9] = { 0 };
		double trans_[3] = { 0 };
		data->GetTransformation(rotate_, trans_);
		for (int point_i_ = 0; point_i_ < point_num_; ++point_i_){

			Vector3f  &point_ = data->Vertex(point_i_);  //point 
			Vector3f  &point_n_ = data->VNormal(point_i_); //normal
			double x_ = 0.0;
			double y_ = 0.0;
			double z_ = 0.0;
			x_ = point_[0] * rotate_[0] + point_[1] * rotate_[1] + point_[2] * rotate_[2] + trans_[0];
			y_ = point_[0] * rotate_[3] + point_[1] * rotate_[4] + point_[2] * rotate_[5] + trans_[1];
			z_ = point_[0] * rotate_[6] + point_[1] * rotate_[7] + point_[2] * rotate_[8] + trans_[2];
			double n_x_ = 0.0;
			double n_y_ = 0.0;
			double n_z_ = 0.0;
			n_x_ = point_n_[0] * rotate_[0] + point_n_[1] * rotate_[1] + point_n_[2] * rotate_[2];
			n_y_ = point_n_[0] * rotate_[3] + point_n_[1] * rotate_[4] + point_n_[2] * rotate_[5];
			n_z_ = point_n_[0] * rotate_[6] + point_n_[1] * rotate_[7] + point_n_[2] * rotate_[8];

			fprintf(fp_, "%f %f %f %f %f %f\n", x_, y_, z_, n_x_, n_y_, n_z_);
		}
		fclose(fp_);
		m_rangeDatas.push_back(data);
	}
	else if (NULL != data)
	{
		delete data;
		data = NULL;
		return_type_ = false;
	}
	return return_type_;
}



bool sdk_demo_fix::load_global_mark()
{
	sn3DTargetAlign::RefPoints       gloabl_ref_pts_;
	int ref_count_ = gloabl_ref_pts_.nPoint;
	if (ref_count_)
		gloabl_ref_pts_.Free();

	char str_[200];
	ifstream file_;
	file_.open("res/Scan111.p3", ios_base::in);
	file_.getline(str_, 100);
	int count_ = 0;
	sscanf(str_, "%d rows", &count_);

	if (count_ < 1)
		return false;
	file_.getline(str_, 100);//columns
	int columns_ = 0;
	sscanf(str_, "%d columns_", &columns_);
	file_.getline(str_, 100);

	double x_;
	double y_;
	double z_;
	vector<double> coord_;
	vector<int> ids_;
	int id_ = 0;
	if (3 == columns_)
	{
		int kk_ = 0;
		while (file_.getline(str_, 200))
		{
			sscanf(str_, "%lf %lf %lf", &x_, &y_, &z_);
			coord_.push_back(x_);
			coord_.push_back(y_);
			coord_.push_back(z_);
			ids_.push_back(kk_);
			kk_++;
		}

	}
	else if (4 == columns_)
	{
		while (file_.getline(str_, 200))
		{
			sscanf(str_, "%d %lf %lf %lf", &id_, &x_, &y_, &z_);
			coord_.push_back(x_);
			coord_.push_back(y_);
			coord_.push_back(z_);
			ids_.push_back(id_);
		}
	}

	int size_ = (int)ids_.size();

	gloabl_ref_pts_.Alloc(size_);

	for (int k_ = 0; k_ < size_; k_++)
	{
		gloabl_ref_pts_.xPoints[k_] = coord_[k_ * 3 + 0];
		gloabl_ref_pts_.yPoints[k_] = coord_[k_ * 3 + 1];
		gloabl_ref_pts_.zPoints[k_] = coord_[k_ * 3 + 2];
		gloabl_ref_pts_.IDList[k_] = ids_[k_];
	}

	std::cout << "gloabl_ref_pts_-----" << gloabl_ref_pts_ .nPoint<< std::endl;

	sn3DScan::sn3d_import_global_mark_point(hScanSession, gloabl_ref_pts_);
	return true;
}

void sdk_demo_fix::on_scan_mode_change()
{
	if (current_turntable_scan == 0)
	{
		align_mode_code_point->hide();
		align_mode_markpoint->hide();
		align_mode_feature->hide();
		align_mode_global_mark_point->hide();
		align_mode_global_mark_point_check->show();
		align_mode_global_mark_point_check->setChecked(false);

	}
	else
	{
		align_mode_code_point->show();
		align_mode_markpoint->show();
		align_mode_feature->show();
		align_mode_global_mark_point->show();
		align_mode_global_mark_point_check->hide();
	}
}


void sdk_demo_fix::edit_Example()
{
	//delete 0-1000 point
	int vn_size_ = m_rangeDatas.size();
	int del_size_ = 1000;
	for (int i = 0; i <vn_size_; i++)
	{

		int vnn_ = m_rangeDatas[i]->GetVN();
		if (vnn_ < del_size_)
			del_size_ = vnn_;
		for (int j = 0; j < del_size_; j++)
		{
			m_rangeDatas[i]->VFlag(j).Deleted = 1;

		}

		m_rangeDatas[i]->UpdateFace();
		m_rangeDatas[i]->Squeeze();//delete the data 0-1000
	}
}