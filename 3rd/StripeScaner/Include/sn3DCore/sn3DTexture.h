#ifndef _sn3DTexture_H
#define _sn3DTexture_H

///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
/// @file	sn3DTexture.h
/// @brief	纹理数据
///			
/// @author 胡国军
/// @version 1.0
/// @date 2011-08-29
//////////////////////////////////////////////////////////////////////////////

#include "sn3Dglobaldef.h"
#include "sn3DImageData.h"
namespace sn3DCore
{
	class sn3DTexture
	{
	public:
		sn3DTexture(){};
		~sn3DTexture(){};
		inline sn3DImageData<byte> *GetImageData();
		inline void SetImageData(sn3DImageData<byte> *data);
		

	protected:
		sn3DImageData<byte> m_data;

	};


	inline sn3DImageData<byte> * sn3DTexture::GetImageData()
	{
		return &m_data;
	}

	inline void sn3DTexture::SetImageData(sn3DImageData<byte> *data)
	{
		m_data.create(data->W(),data->H(),data->Channel());
		memcpy(m_data.m_data,data->m_data,data->W()*data->H()*data->Channel());
	}
}

#endif