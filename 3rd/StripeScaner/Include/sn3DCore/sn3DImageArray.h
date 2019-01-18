#ifndef _sn3DImageArray_H
#define _sn3DImageArray_H

#include <vector>
#include "sn3DImageData.h"

//////////////////////////////////////////////////////////////////////////////
//
//	类：sn3DImageArray
//
//		保存多幅图片数据
//
//////////////////////////////////////////////////////////////////////////////
namespace sn3DCore
{

	//=======================================================================
	//
	// class declare
	//

	template<class T>
	class sn3DImageArray
	{
	public:
		sn3DImageArray(){};
		~sn3DImageArray();

		int GetSize();

		void PushBack(sn3DImageData<T> *img);
		bool DeleteAt(int i);
		void DeleteAll();

		void SetData(int i, T *pData);

		sn3DImageData<T> *operator[](int i);

	public:
		std::vector<sn3DImageData<T> *> m_array;
	};

	//=======================================================================
	//
	// class implement
	//

	template<class T>
	inline sn3DImageArray<T>::~sn3DImageArray()
	{
		DeleteAll();
	}

	template<class T>
	inline int sn3DImageArray<T>::GetSize()
	{
		return (int)( m_array.size() );
	}

	template<class T>
	inline void sn3DImageArray<T>::PushBack(sn3DImageData<T> *img)
	{
		m_array.push_back(img);
	}

	template<class T>
	inline bool sn3DImageArray<T>::DeleteAt(int i)
	{
		std::vector<sn3DImageData<T> *>::iterator it;
		int id=0;
		for(it=m_array.begin(); it!=m_array.end(); it++)
		{
			if(id==i)
			{
				delete (*this)[i];
				m_array.erase(it);
				return true;
			}
			id++;
		}
		return true;
	}

	template<class T>
	inline void sn3DImageArray<T>::DeleteAll()
	{
		for( int i=0; i<(int)(m_array.size()); i++ )
		{
			delete (*this)[i];
		}
		m_array.clear();
	}

	template<class T>
	inline sn3DImageData<T> *sn3DImageArray<T>::operator[](int i)
	{
		return m_array[i];
	}

	template<class T>
	inline void sn3DImageArray<T>::SetData(int i, T *pData)
	{
		m_array[i]->m_data = pData;
	}
}// namespace



#endif