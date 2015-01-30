/********************************************************************
	created:		2011/02/13
	filename: 		atomic_integral.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_GENERIC_HPP_INCLUDED
#define ATOMIC_GENERIC_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_base.hpp"

namespace ATOMICS_NAMESPACE
{
	// generic atomic implementation
	template <typename T> class atomic
		: public atomic_base<T>
	{
	public:
		atomic() {}
		atomic(T val): atomic_base<T>(val) {}
		T operator = (T val) volatile
		{
			return atomic_base<T>::operator = (val);
		}
	private:
		// prevent compiler from generating copy constructor and assignment operator
		atomic<T>& operator = (const atomic<T>&) volatile;
		atomic<T>(const atomic<T>&);
	};
}

#endif // ATOMIC_GENERIC_HPP_INCLUDED
