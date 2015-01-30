/********************************************************************
	created:		2011/02/13
	filename: 		atomic_integral.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_INTEGRAL_HPP_INCLUDED
#define ATOMIC_INTEGRAL_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_base.hpp"

namespace ATOMICS_NAMESPACE
{
	// atomic implementation for integral types
	template <typename T> class atomic_integral
		: public atomic_base<T>
	{
	public:
		atomic_integral() {}
		atomic_integral(T val): atomic_base<T>(val) {}
		T fetch_add(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->fetch_add(val, mo);
		}
		T fetch_sub(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->fetch_add(~val + 1, mo);
		}
		T fetch_and(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			T old = impl_ptr()->load(memory_order_relaxed);
			while (!impl_ptr()->compare_exchange(old, old & val, mo, memory_order_relaxed));
			return old;
		}
		T fetch_or(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			T old = impl_ptr()->load(memory_order_relaxed);
			while (!impl_ptr()->compare_exchange(old, old | val, mo, memory_order_relaxed));
			return old;
		}
		T fetch_xor(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			T old = impl_ptr()->load(memory_order_relaxed);
			while (!impl_ptr()->compare_exchange(old, old ^ val, mo, memory_order_relaxed));
			return old;
		}
		T operator = (T val) volatile
		{
			return atomic_base<T>::operator = (val);
		}
		T operator ++(int) volatile
		{
			return fetch_add(1);
		}
		T operator --(int) volatile
		{
			return fetch_sub(1);
		}
		T operator ++() volatile
		{
			return fetch_add(1) + 1;
		}
		T operator --() volatile
		{
			return fetch_sub(1) - 1;
		}
		T operator &= (T rhl) volatile
		{
			return fetch_and(rhl);
		}
		T operator |= (T rhl) volatile
		{
			return fetch_or(rhl);
		}
		T operator ^= (T rhl) volatile
		{
			return fetch_xor(rhl);
		}
	private:
		// prevent compiler from generating copy constructor and assignment operator
		atomic_integral<T>& operator = (const atomic_integral<T>&) volatile;
		atomic_integral<T>(const atomic_integral<T>&);
	};
}

#endif // ATOMIC_INTEGRAL_HPP_INCLUDED
