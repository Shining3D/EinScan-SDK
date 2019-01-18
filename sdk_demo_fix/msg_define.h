#ifndef MSG_DEFINE_H
#define MSG_DEFINE_H

#pragma warning(disable:4067)
#pragma warning(disable:4819)
#pragma warning(disable:4267)
#pragma warning(disable:4996)
#pragma warning(disable:4244)


#include <map>
#include <qvariant.h>
using namespace std;

//EinScan msg define  
#include "sn3d_pro_sdk.h"
 
#define  DEVICE_TYPE_S    0
#define  DEVICE_TYPE_PRO  1
 
 
typedef map<QString, QVariant> MapData;
typedef struct _tag_msg_data
{
	int            msg_type;
	bool           result;
	int            hint;
	MapData        map_data;
}msg_data_t;

Q_DECLARE_METATYPE(msg_data_t)
Q_DECLARE_METATYPE(unsigned char*)

#endif