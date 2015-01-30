/********************************************************************
	created:		2011/02/13
	filename: 		atomic_pointer.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_POINTER_HPP_INCLUDED
#define ATOMIC_POINTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_generic.hpp"
#include "atomic_base.hpp"

namespace ATOMICS_NAMESPACE
{
	// atomic specialization for pointers
	template <typename T> class atomic<T*>
		: public atomic_base<T*>
	{
	public:
		atomic() {}
		atomic(T* val): atomic_base<T*>(val) {}
		T* fetch_add(std::ptrdiff_t diff, memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->fetch_add(static_cast<T*>(0) + diff, mo);
		}
		T* fetch_sub(std::ptrdiff_t diff, memory_order mo = memory_order_seq_cst) volatile
		{
			return fetch_add(~diff + 1, mo);
		}
		T* operator = (T* val) volatile
		{
			return atomic_base<T*>::operator = (val);
		}
		T* operator ++(int) volatile
		{
			return fetch_add(1);
		}
		T* operator --(int) volatile
		{
			return fetch_sub(1);
		}
		T* operator ++() volatile
		{
			return fetch_add(1) + 1;
		}
		T* operator --() volatile
		{
			return fetch_sub(1) - 1;
		}
	private:
		// prevent compiler from generating copy constructor and assignment operator
		atomic<T*>& operator = (const atomic<T*>&) volatile;
		atomic<T*>(const atomic<T*>&);
	};
}

#endif // ATOMIC_POINTER_HPP_INCLUDED
