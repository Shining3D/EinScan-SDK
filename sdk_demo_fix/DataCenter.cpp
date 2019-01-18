#include "DataCenter.h"
#include <qdebug.h>
//#include <vld.h>

demo_data_center* demo_data_center::_instance=0;

demo_data_center::demo_data_center() :_mutx(QMutex::Recursive)
{
	memset(&_scanner_rt, 0, sizeof(_scanner_rt));
	memset(&_current_point, 0, sizeof(SN3D_CLOUD_POINT));
	memset(&_whole_point, 0, sizeof(SN3D_CLOUD_POINT));
	memset(&_mark_point, 0, sizeof(SN3D_CLOUD_POINT));
	memset(&_whole_mark_point, 0, sizeof(SN3D_CLOUD_POINT));
}
demo_data_center::~demo_data_center()
{

}
 
demo_data_center* demo_data_center::Instance()
{
	if (_instance == 0)
		_instance = new demo_data_center();

	return _instance;
}
void    demo_data_center::UnInstance()
{
	if (_instance != 0)
		delete _instance;

	_instance = 0;
}
bool demo_data_center::allocate_point_memory(SN3D_CLOUD_POINT& point)
{
	 
	if (point.vertex_count > 0)
	{
		point.vertex_data = new SN3D_POINT_DATA[point.vertex_count];
	}
	if (point.norma_count > 0)
	{
		point.norma_data = new SN3D_POINT_DATA[point.norma_count];
	}
	if (point.vertex_color_count > 0)
	{
		point.vertex_color_data = new SN3D_POINT_DATA[point.vertex_color_count];
	}

	if (point.vertex_color_data == NULL && point.norma_data == NULL && point.vertex_data == NULL)
	{
		printf("\r\n  vertex_count=%d norma_data=%d vertex_color_count=%d", point.vertex_count, point.norma_count, point.vertex_color_count);
		return false;
	}
		

	return true;

}
void demo_data_center::get_scanner_rt(SN3D_SCANNER_RT& rt)
{
	QMutexLocker lock(&_mutx);
	rt= _scanner_rt ;
}
void demo_data_center::update_scanner_rt(SN3D_SCANNER_RT& rt)
{
	QMutexLocker lock(&_mutx);
	_scanner_rt = rt;
}
void demo_data_center::update_current_cloud_point(SN3D_CLOUD_POINT& point)
{
	QMutexLocker lock(&_mutx);
	free_point_memory(_current_point);
	_current_point = point;
}
int demo_data_center::delete_point(int start0, int end0, int start1, int end1, int start2, int end2, SN3D_CLOUD_POINT& remain)
{
	QMutexLocker lock(&_mutx);
	if (start0 < 0)
		start0 = 0;

	if (start0 > (_whole_point.vertex_count-1))
		start0 = _whole_point.vertex_count-1;

	if (end0 < 0)
		end0 = 0;

	if (end0 >(_whole_point.vertex_count - 1))
		end0 = _whole_point.vertex_count - 1;

	if (start1 < 0)
		start1 = 0;
	if (start1 >(_whole_point.vertex_count - 1))
		start1 = _whole_point.vertex_count - 1;

	if (end1 < 0)
		end1 = 0;
	if (end1 >(_whole_point.vertex_count - 1))
		end1 = _whole_point.vertex_count - 1;

	if (start2 < 0)
		start2 = 0;
	if (start2 >(_whole_point.vertex_count - 1))
		start2 = _whole_point.vertex_count - 1;

	if (end2 < 0)
		end2 = 0;
	if (end2 >(_whole_point.vertex_count - 1))
		end2 = _whole_point.vertex_count - 1;

	int count0 = end0 - start0;
	int count1 = end0 - start0;
	int count2 = end0 - start0;

	if (count0 < 0) count0 = 0;
	if (count1 < 0) count1 = 0;
	if (count2 < 0) count2 = 0;

	int remain_count = 0;
	for (int i = 0; i < _whole_point.vertex_count; i++)
	{
		bool del = (i >= start0  && i <= end0) ||(i >= start1  && i <= end1) ||(i >= start2 && i <= end2);
		if (!del)
		{
			remain_count++;
		}
	}

	remain.vertex_count = remain_count;

	if (_whole_point.norma_count > 0)
	{
		remain.norma_count = remain_count;
	}

	if (_whole_point.vertex_color_count > 0)
	{
		remain.vertex_color_count = remain_count;
	}

	if (remain_count>0)
	{
		allocate_point_memory(remain);
		int j = 0;
		for (int i = 0; i < _whole_point.vertex_count; i++)
		{
			bool del = (i >= start0  && i <= end0) || (i >= start1  && i <= end1) || (i >= start2 && i <= end2);
			if (!del)
			{
				remain.vertex_data[j] = _whole_point.vertex_data[i];
				if (remain.norma_data)
					remain.norma_data[j] = _whole_point.norma_data[i];
				if (remain.vertex_color_data)
					remain.vertex_color_data[j] = _whole_point.vertex_color_data[i];

				j++;
			}
		}
	}

	free_point_memory(_whole_point);

	_whole_point = remain;

	return remain_count;
}
 
void demo_data_center::update_whole_mark_point(SN3D_CLOUD_POINT& point)
{
	QMutexLocker lock(&_mutx);
	free_point_memory(_whole_mark_point);
	_whole_mark_point = point;
}

void demo_data_center::update_current_mark_point(SN3D_CLOUD_POINT& point)
{
	QMutexLocker lock(&_mutx);
	free_point_memory(_mark_point);
	_mark_point = point;
}
void demo_data_center::update_whole_cloud_point(SN3D_CLOUD_POINT& point)
{
	QMutexLocker lock(&_mutx);
	free_point_memory(_whole_point);
	_whole_point = point;

}
void demo_data_center::clear_data()
{
	QMutexLocker lock(&_mutx);
	free_point_memory(_whole_point);
	free_point_memory(_mark_point);
	free_point_memory(_current_point);
	free_point_memory(_whole_mark_point);
}
void demo_data_center::free_point_memory(SN3D_CLOUD_POINT& point)
{
	if (point.norma_count > 0 && point.norma_data != NULL)
		delete[] point.norma_data;
	point.norma_count = 0;

	if (point.vertex_count > 0 && point.vertex_data != NULL)
		delete[] point.vertex_data;
	point.vertex_count = 0;

	if (point.vertex_color_count > 0 && point.vertex_color_data != NULL)
		delete[] point.vertex_color_data;
	point.vertex_color_count = 0;
}
int  demo_data_center::save_whole_mark_point(char* path)
{
	FILE* data_file = fopen(path, "w");
	if (data_file == NULL)
		return -1;
	{
		QMutexLocker lock(&_mutx);
		for (int i = 0; i<_whole_mark_point.vertex_count; i++)
		{
			fprintf(data_file, "%f    %f    %f\n", _whole_mark_point.vertex_data[i].x, _whole_mark_point.vertex_data[i].y, _whole_mark_point.vertex_data[i].z);
		}
	}

	fclose(data_file);

	return 0;
}
int demo_data_center::save_whole_point(char* path)
{
	FILE* data_file = fopen(path, "w");
	if (data_file == NULL)
		return -1;
	{
		QMutexLocker lock(&_mutx);
		for (int i = 0; i<_whole_point.vertex_count; i++)
		{
			fprintf(data_file, "%f    %f    %f", _whole_point.vertex_data[i].x, _whole_point.vertex_data[i].y, _whole_point.vertex_data[i].z);

			if (_whole_point.norma_data)
				fprintf(data_file, "    %f    %f    %f", _whole_point.norma_data[i].x, _whole_point.norma_data[i].y, _whole_point.norma_data[i].z);

			if (_whole_point.vertex_color_data)
				fprintf(data_file, "    %f    %f    %f", _whole_point.vertex_color_data[i].x, _whole_point.vertex_color_data[i].y, _whole_point.vertex_color_data[i].z);

			fprintf(data_file, "\n");
		}
	}

	fclose(data_file);

	return 0;
}