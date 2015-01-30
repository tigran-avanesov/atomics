/********************************************************************
	created:		2011/02/17
	filename: 		atomic_base.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_BASE_HPP_INCLUDED
#define ATOMIC_BASE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_impl_byte.hpp"
#include "atomic_impl_word.hpp"
#include "atomic_impl_dword.hpp"
#include "atomic_impl_qword.hpp"

namespace ATOMICS_NAMESPACE
{
	// generic atomic implementation
	template <typename T> class atomic_base
	{
	public:
		typedef T value_type;

		atomic_base() {}
		explicit atomic_base(T val): impl(val) {}

		T load(memory_order mo = memory_order_seq_cst) const volatile
		{
			return impl_ptr()->load(mo);
		}
		void store(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->store(val, mo);
		}
		T exchange(T val, memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->exchange(val, mo);
		}
		bool compare_exchange_weak(T& exp, T val,
			memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->compare_exchange(exp, val, mo, mo);
		}
		bool compare_exchange_weak(T& exp, T val,
			memory_order success, memory_order failure) volatile
		{
			return impl_ptr()->compare_exchange(exp, val, success, failure);
		}
		bool compare_exchange_strong(T& exp, T val,
			memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->compare_exchange(exp, val, mo, mo);
		}
		bool compare_exchange_strong(T& exp, T val,
			memory_order success, memory_order failure) volatile
		{
			return impl_ptr()->compare_exchange(exp, val, success, failure);
		}
		bool is_lock_free() const volatile
		{
			return atomic_impl<T>::is_lock_free != 0;
		}
		T operator = (T val) volatile
		{
			store(val);
			return val;
		}
		operator T() const volatile
		{
			return load();
		}
	protected:
		const detail::atomic_impl<T>* impl_ptr() const volatile
		{
			// get rid of volatile
			return const_cast<const detail::atomic_impl<T>*>(&impl);
		}
		detail::atomic_impl<T>* impl_ptr() volatile
		{
			// get rid of volatile
			return const_cast<detail::atomic_impl<T>*>(&impl);
		}
	private:
		detail::atomic_impl<T> impl;
	};
}

#endif // ATOMIC_BASE_HPP_INCLUDED
