#pragma once

#ifndef _YE_VECTOR_WRAPPER_H_
#define _YE_VECTOR_WRAPPER_H_

#include "DXAPI.h"
#include "VectorWrapper.h"

template <typename T>
class DX_API YEVectorWrapper
{
public:

	YEVectorWrapper()
	{
		m_vectorWrapper = VectorWrapper<T>();
	};

	virtual ~YEVectorWrapper() {};

	void addElement(T element)
	{
		m_vectorWrapper.push_back(element);
	}

	void clearElements()
	{
		m_vectorWrapper._list.clear();
	}

	void removeElementAt(size_t index)
	{
		if (index < m_vectorWrapper._list.size())
		{
			m_vectorWrapper._list.erase(m_vectorWrapper._list.begin() + index);
		}
	}

	VectorWrapper<T>* getVector()
	{
		return &m_vectorWrapper;
	}

private:
	VectorWrapper<T> m_vectorWrapper;
};

#endif