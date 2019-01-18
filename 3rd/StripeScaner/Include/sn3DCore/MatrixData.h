#ifndef _MatrixData_H
#define _MatrixData_H
///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
/// @file	MatrixData.h
/// @brief	��������
///			���ļ�������һ����ά����
/// @author wuzq
/// @version 1.0
/// @date 2010-01-24
//////////////////////////////////////////////////////////////////////////////


#include <vector>
#include <assert.h>
#include <stdlib.h>

#include "sn3Dglobaldef.h"
#include "sn3DImageData.h"
namespace sn3DCore
{
	template <class  T>  
	class MatrixData     
	{    
	public:
		/// ���캯��/�������� 
		MatrixData();
		/// !!��ע����(h)����(w)��˳��
		MatrixData( uint w,uint h );
		MatrixData( uint w, uint h, const T a );
		MatrixData( uint w, uint h, const T* data);
		MatrixData(const MatrixData &rhs);

		virtual ~MatrixData();

		MatrixData & operator=( const MatrixData &rhs );
		
		inline		 T* operator[](const uint i)		{assert(i<m_h); return m_lines[i];}
		inline const T* operator[](const uint i) const	{assert(i<m_h); return m_lines[i];}
		inline T& at(uint i, uint j)                    {assert(i<m_h && j<m_w); return m_lines[i][j];}
				
		inline uint H()									{ return m_h;}
		inline uint W()									{ return m_w;}
		inline uint nrows()								{ return m_h;}
		inline uint ncols()								{ return m_w;}

		T* Buffer()										{ return m_data;};
								
		//  !!��ע����(h)����(w)��˳��
		/// ���·����ڴ�
		void Resize( uint w, uint h);		
	
		//  !!��ע����(h)����(w)��˳��
		/// Ϊ�˼����ڴ渴��ָ��data�ڴ��ɸ������ӹ�	
		void SetData(uint w, uint h, T *data);

		void Fill(const T* data);
		void Fill(const T a);

		// ������������Ե��뵽matlab���鿴
		bool Save(const char* name);
	protected:
		void CreateData();	/// �����ڴ�
		void DestroyData();	/// �ͷ��ڴ�
		
	protected:
		uint m_h;			// ��/��
		uint m_w;			// ��/��
		T **m_lines;
		T *m_data;   
	};
	///////////////////////////////////////////////////////////////////////////

	template <class T>
	MatrixData<T>::MatrixData():m_h(0),m_w(0),m_lines(NULL),m_data(NULL)		
	{ }

	template <class T>
	MatrixData<T>::MatrixData(uint w,uint h ):m_w(w),m_h(h),m_lines(NULL),m_data(NULL)
	{ 
		CreateData();
	}

	template <class T>
	MatrixData<T>::MatrixData( uint w, uint h, const T a ):m_w(w),m_h(h),m_lines(NULL),m_data(NULL)
	{ 
		CreateData();
		Fill(a);
	}

	template <class T>
	MatrixData<T>::MatrixData( uint w,uint h,const T* data):m_w(w),m_h(h),m_lines(NULL),m_data(NULL)	
	{ 
		CreateData();
		Fill(data);
	}

	template <class T>
	MatrixData<T>::MatrixData(const MatrixData &rhs):m_w(rhs.m_w),m_h(rhs.m_h),m_lines(NULL),m_data(NULL)
	{
		CreateData();
		for (uint i=0; i<m_h; i++)
			for (uint j=0; j<m_w; j++)
				m_lines[i][j]=rhs[i][j];
	}
	template <class T>
	MatrixData<T>::~MatrixData()
	{
		DestroyData();
	}

    template <class T>
    void MatrixData<T>::Resize(uint w, uint h )
    {
        DestroyData();
        m_h = h;
        m_w = w;
        CreateData();
    }
	template <class T>
	void MatrixData<T>::SetData(uint w, uint h, T *data)
	{
		DestroyData();
		m_h = h;
		m_w = w;
		m_lines = new T*[m_h];
		m_data  = data;
		for (uint i=0; i<m_h; i++)
			m_lines[i] = m_data + m_w*i;

	}

	template <class T>
	void MatrixData<T>::Fill(const T* data)
	{
		uint size = m_w*m_h;
		for (uint i=0; i<size; i++)
			m_data[i] = data[i];
	}
	template <class T>
	void MatrixData<T>::Fill(const T a)
	{
		uint size = m_w*m_h;
		for (uint i=0; i<size; i++)
			m_data[i] = a;
	}
	/// postcondition: normal assignment via copying has been performed;
	///		if matrix and rhs were different sizes, matrix
	///		has been resized to match the size of rhs
	template <class T>
	MatrixData<T>&  MatrixData<T>::operator=( const MatrixData &rhs )
	{
		if( this!= &rhs)
		{
			if( m_h!=rhs.m_h || m_w!=rhs.m_w)
				Resize(rhs.m_w, rhs.m_h);
			for (uint i=0; i<m_h; i++)
				for (uint j=0; j<m_w; j++)
					m_lines[i][j]=rhs[i][j];
		}
		return *this;
	}
    /// ���ݾ����С�����ڴ�ռ�
	template <class T>
	void  MatrixData<T>::CreateData()
	{
        // Ӧ�ñ�֤����֮ǰm_data�Ѿ��ͷŲ���Ϊ�գ������protect����û�б�Ҫ�ٴ�������
		// ��Ϊ��Ӧ��ֱ�Ӹ��ݳ�Ա���������ڴ���䡣 [2011-5-18 9:41 ChenKun]
        assert(NULL == m_data);
		assert(m_h * m_w > 0);
		m_lines = new T*[m_h];
		m_data  = new T[m_w*m_h];
		for (uint i=0; i<m_h; i++)
			m_lines[i] = m_data + m_w*i;
	}
    /// �ͷ��ڴ�ռ䣬��վ���
	template <class T>
	void  MatrixData<T>::DestroyData()
	{
		if( m_data!= NULL)
		{
			delete[] m_lines;
			delete[] m_data;
		}
		m_lines = NULL;
		m_data = NULL;
        m_h = 0;
        m_w = 0;
	}
	template <class T>
	bool  MatrixData<T>::Save(const char* name)
	{
		FILE *fp = fopen(name,"w");	assert(fp);	
		if(fp==NULL)
			return false;
		for (uint i=0; i<m_h; i++)
		{
			for (uint j=0; j<m_w; j++)
				fprintf(fp, "%f ", (float)(m_lines[i][j]));
			fprintf(fp, "\n");
		}
		fclose(fp);
		return true;
	}
// 	bool Matrix2Image(MatrixData<float> &mat, sn3DImageData<unsigned char> &img);
    inline	bool Matrix2Image(MatrixData<float> &mat, sn3DImageData<unsigned char> &img, float invalid = FLT_MAX)
 	{
		int w = mat.W();
		int h = mat.H();
		img.create(w,h,1);
		float max,min;
		max = FLT_MAX*(-1.0f);
		min = FLT_MAX;
		float *map = mat.Buffer();
		for (int i =0;i<w*h;i++)
		{
			if (FLT_MAX==map[i])
				continue;
			if (map[i]<min)
				min = map[i];
			else if (max<map[i])
				max = map[i];
		}
		if (max<=min)
			return false;
		float sub = 255/(max - min);
		for (int i=0;i<w*h;i++)
		{
			int tmp = 0;
			if (FLT_MAX!=map[i])
				tmp = (int)((map[i]-min)*sub+0.5);

			if (255<tmp)
				img.m_data[i] = 255;
			else if (tmp<0)
				img.m_data[i] = 0;
			else
				img.m_data[i] = tmp;
		}
 		return true;
 	}
    inline	bool Matrix2Image(MatrixData<unsigned char> &mat, sn3DImageData<unsigned char> &img)
 	{
 		int w = mat.W();
 		int h = mat.H();
 		img.create(w,h,1);
 		int max,min;
		max = -600;
		min = 600;
 		unsigned char *map = mat.Buffer();
 		for (int i =0;i<w*h;i++)
 		{
 			if ((int)map[i]<min)
 				min = (int)map[i];
 			else if (max<(int)map[i])
 				max = (int)map[i];
 		}
		if (max<=min)
			return false;
 		float sub = 255.0f/(max - min);
 		for (int i=0;i<w*h;i++)
 		{
 			int tmp = (int)(((int)map[i]-min)*sub+0.5);
 			if (255<tmp)
 				img.m_data[i] = 255;
 			else if (tmp<0)
 				img.m_data[i] = 0;
 			else
 				img.m_data[i] = tmp;
 		}
 		return true;
 	}
}

#endif //_MatrixData_H