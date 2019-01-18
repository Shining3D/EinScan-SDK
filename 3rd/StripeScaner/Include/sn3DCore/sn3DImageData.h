#ifndef _sn3DImageData_H
#define _sn3DImageData_H

// ==========================================================================
// File name:	sn3DImageData.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	保存图像数据的类模板。
//
// Histroy:		
//	- Created : 2010/01/24  
//
// ============================================================================

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#include <string.h>

namespace sn3DCore
{

	template<class T>
	class sn3DImageData
	{
	public:
		// 构造函数 析构函数
		sn3DImageData();
		sn3DImageData(int w, int h, int channel=1);
		sn3DImageData(int w, int h, int channel, T* data );
		~sn3DImageData();

		// 产生数据
		void create(int w, int h, int channel=1 );

		// 获取数据，c表示通道
		inline T& pos(int i, int j, int c=0);

		// 获取数据指针，调用data(0,0)表示获取整个数据
		inline T* data(int i, int j);
		inline T* data();

		// 数据填充，初始化使用
		void fill( T v);
		inline int& H()		{return	m_h;};
		inline int& W()		{return m_w;};
		inline int& Channel(){return m_channel;};
		inline bool IsEmpty(){return m_data==NULL;}

		void SetName(const char * szName);
		const char *GetName();
	public:
		T *m_data;              // 保存图像数据指针
		int m_w;				// 图像宽
		int m_h;				// 图像高
		int m_channel;			// 图像通道，每个像素所占的字节数
		char m_name[MAX_PATH];
	};

	//=======================================================================
	// 模板实现

	template<class T>
	inline sn3DImageData<T>::sn3DImageData():m_w(0),m_h(0),m_channel(0),m_data(NULL)
	{
		m_name[0]='\0';
	}

	template<class T>
	inline sn3DImageData<T>::sn3DImageData(int w, int h, int channel ):m_data(NULL)
	{
		m_name[0]='\0';
		create( w, h, channel );
	}
	template<class T>
	inline sn3DImageData<T>::sn3DImageData(int w, int h, int channel, T* data )
	{
		m_w = w;
		m_h = h;
		m_channel = channel;
		m_data = data;
	}

	template<class T>
	inline sn3DImageData<T>::~sn3DImageData()
	{
		if (m_data)
		{
			delete[] m_data;
			m_data = NULL;
		}
	}

	template<class T>
	inline void sn3DImageData<T>::create(int w, int h, int channel )
	{
		if( m_data )
			delete[] m_data;
		m_w = w;
		m_h = h;
		m_channel = channel;
		m_data = new T[m_w*m_h*m_channel];
	}
	
	template<class T>
	inline T& sn3DImageData<T>::pos(int i, int j, int c )
	{
		return m_data[i*m_w*m_channel+j*m_channel+c];
	}

	template<class T>
	inline T* sn3DImageData<T>::data()
	{
		return m_data ;
	}
	
	template<class T>
	inline T* sn3DImageData<T>::data(int i, int j)
	{
		return m_data + (i*m_w + j)*m_channel;
	}

	template<class T>
	inline void sn3DImageData<T>::fill( T v)
	{
		int s=m_w*m_h*m_channel;
		for (int i=0; i<s; i++)
			m_data[i] = v;
	}
	template<class T>
	inline void sn3DImageData<T>::SetName(const char * szName)
	{
		strcpy_s(m_name,szName);
	}
	template<class T>
	inline const char * sn3DImageData<T>::GetName()
	{
		return m_name;
	}
	
	// 全局函数，彩色图像转为灰度图像，彩色图像像素字节顺序是BGR
	inline void ToGray(sn3DImageData<unsigned char> &rgbImg, sn3DImageData<unsigned char> &grayImg)
	{
		int w = rgbImg.W();
		int h = rgbImg.H();

		grayImg.create(w,h);
		grayImg.SetName(rgbImg.GetName());

		unsigned char* p = rgbImg.data();
		unsigned char* d = grayImg.data();
		for(int y=0; y<h; y++)
		{
			for(int x=0; x<w; x++)
			{
				float t = *(p)*0.114f + *(p+1)*0.587f + *(p+2)*0.299f;
				if( t > 255)		t = 255;
				else if( t < 0 )	t = 0;

				*d = (unsigned char)t;
				d=d+1;	p=p+3;
			}
		}
	}

    // reverse the image data by row
    inline bool ReverseByRow(sn3DImageData<unsigned char> &imageData)
    {
        if (imageData.data()==NULL)
        {
            return false;
        }

        int w = imageData.W();
        int h = imageData.H();
        int c = imageData.Channel();

        unsigned char *tempbuffer = new unsigned char[w*c];
        // 按行内存拷贝交换
        for (int i = 0; i < h/2; i++)
        {
            memset(tempbuffer, 0, w*c);
            unsigned char *src, *dst, *tmp;
            src = imageData.data() + i*w*c;
            tmp = tempbuffer;
            dst = imageData.data() + (h-1-i)*w*c;
            memcpy(tmp, src, w*c);
            memcpy(src, dst, w*c);
            memcpy(dst, tmp, w*c);
        }

        delete []tempbuffer;

        return true;
    }

    // change the BGR order into RGB order
    inline bool ChangeColorOrder(sn3DImageData<unsigned char> &imageData)
    {
        if (imageData.data()==NULL || imageData.Channel() < 3)
        {
            return false;
        }

        int w = imageData.W();
        int h = imageData.H();

        unsigned char temp;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                unsigned char *pixeldata = imageData.data(i,j);
                unsigned char *b = pixeldata + 0;
                unsigned char *r = pixeldata + 2;

                temp = *b;
                *b = *r;
                *r = temp;
            }
        }

        temp = NULL;

        return true;
    }

	
}// namespace

#endif