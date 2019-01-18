#ifndef _sn3DRgeFile_H
#define _sn3DRgeFile_H

// ==========================================================================
// File name:	sn3DRgeFile.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	RGE�ļ���ʽ�Ķ�ȡ�ʹ洢����ȡ֧��RGE_v2.0,RGE_v3.0���洢ֻ֧��RGE_v3.0
//
// Histroy:		
//	- Created : 2015/07/08  
//
// ============================================================================

#include <vector>

#include "sn3DPointSet.h"
#include "sn3DRangeData.h"

namespace sn3DCore
{
	//===========================================================================
	// ������	sn3DDataTypeRGE 
	// ������	szName	[in]�����ļ���
	//			type	[out]������ļ��������������
	// ����ֵ�� 0 �ɹ������� ʧ��
	// ���ܣ��ж�RGE�ļ��������������
	//===========================================================================
	int sn3DDataTypeRGE(const TCHAR *szName,DATA_TYPE &type);

	//===========================================================================
	// ������	sn3DReadRGE
	// ������	szName	[in]�ļ���
	//			dataObj	[out]����
	// ����ֵ�� 0 �ɹ������� ʧ��
	// ���ܣ���ȡRGE�ļ�����֪�������ͣ��ⲿ�������ݶ���
	//===========================================================================
	int sn3DReadRGE(const TCHAR* szName, sn3DDataBase *dataObj);
	
	//===========================================================================
	// ������	sn3DReadRGE
	// ������	szName	[in]�ļ���
	//			dataObj	[out]����
	// ����ֵ�� NULL ʧ�ܣ����� �ɹ�
	// ���ܣ���ȡRGE�ļ��������ڲ��������ݶ���
	//===========================================================================
	sn3DPointSet *sn3DReadRGE(const TCHAR* szName);

	//===========================================================================
	// ������	sn3DSaveRGE
	// ������	szName	[in]�ļ���
	//			dataObj	[out]����
	// ����ֵ�� 0 �ɹ������� ʧ��
	// ���ܣ����ݱ���ΪRGE�ļ���ʽ��
	//===========================================================================
	int sn3DSaveRGE(const TCHAR* szName, sn3DDataBase *dataObj);

	int sn3DSaveRange_v2(const TCHAR* szName, sn3DRangeData *range);
	
	// ֻ�����ļ������־�����Ϣ����־��ֻ�ܱ��ļ�����
	int sn3DSaveRefPointRGE(const TCHAR* szName,sn3DRangeData *range);
	// ����RGE�ļ��еı任������Ϣ
	int sn3DSaveTransformationRGE(const TCHAR* szName,sn3DRangeData *range);
	//===========================================================================
	// ������	sn3DSavePLY
	// ������	szName	[in]�ļ���
	//			dataObj	[out]����
	// ����ֵ�� 0 �ɹ������� ʧ��
	// ���ܣ����ݱ���ΪPLY�ļ���ʽ��
	//===========================================================================
	int sn3DSavePLY(const TCHAR* szName, sn3DDataBase *dataObj);
}

#endif // _sn3DRgeFile.h