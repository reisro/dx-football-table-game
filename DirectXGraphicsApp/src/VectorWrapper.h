#pragma once

#ifndef _VECTOR_WRAPPER_H_
#define _VECTOR_WRAPPER_H_

#include <vector>

template <typename T>
class VectorWrapper
{
public:
	VectorWrapper()
	{
		_list = std::vector<T>();
	}

	virtual ~VectorWrapper()
	{
		_list.clear();
	}

	void push_back(T element)
	{
		_list.push_back(element);
	}

	std::vector<T> GetElements()
	{
		return _list;
	}

	std::vector<T> _list;
};

#endif // _YE_VECTOR_WRAPPER_H_