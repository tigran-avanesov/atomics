/********************************************************************
	created:		2011/02/17
	filename: 		atomic_free_functions.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_FREE_FUNCTIONS_HPP_INCLUDED
#define ATOMIC_FREE_FUNCTIONS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_flag.hpp"
#include "atomic_base.hpp"

namespace ATOMICS_NAMESPACE
{
	// general operations on atomic types
	template <typename T> void atomic_init(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type val)
	{
		return atomic->store(val, memory_order_relaxed);
	}
	template <typename T> bool atomic_is_lock_free(
		const volatile atomic_base<T>* atomic)
	{
		return atomic->is_lock_free();
	}
	template <typename T> void atomic_store(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type val)
	{
		return atomic->store(val);
	}
	template <typename T> void atomic_store_explicit(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type val, memory_order mo)
	{
		return atomic->store(val, mo);
	}
	template <typename T> T atomic_load(
		const volatile atomic_base<T>* atomic)
	{
		return atomic->load();
	}
	template <typename T> T atomic_load_explicit(
		const volatile atomic_base<T>* atomic, memory_order mo)
	{
		return atomic->load(mo);
	}
	template <typename T> bool atomic_exchange(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type val)
	{
		return atomic->exchange(val);
	}
	template <typename T> bool atomic_exchange_explicit(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type val, memory_order mo)
	{
		return atomic->exchange(val, mo);
	}
	template <typename T> bool atomic_compare_exchange_weak(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type* exp,
		typename atomic_base<T>::value_type val)
	{
		return atomic->compare_exchange_weak(*exp, val);
	}
	template <typename T> bool atomic_compare_exchange_strong(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type* exp,
		typename atomic_base<T>::value_type val)
	{
		return atomic->compare_exchange_strong(*exp, val);
	}
	template <typename T> bool atomic_compare_exchange_weak_explicit(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type* exp,
		typename atomic_base<T>::value_type val,
		memory_order success, memory_order failure)
	{
		return atomic->compare_exchange_weak(*exp, val, success, failure);
	}
	template <typename T> bool atomic_compare_exchange_strong_explicit(
		volatile atomic_base<T>* atomic,
		typename atomic_base<T>::value_type* exp,
		typename atomic_base<T>::value_type val,
		memory_order success, memory_order failure)
	{
		return atomic->compare_exchange_strong(*exp, val, success, failure);
	}

	// templated operations on atomic types
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_add(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val)
	{
		return atomic->fetch_add(val);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_add_explicit(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val, memory_order mo)
	{
		return atomic->fetch_add(val, mo);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_sub(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val)
	{
		return atomic->fetch_sub(val);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_sub_explicit(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val, memory_order mo)
	{
		return atomic->fetch_sub(val, mo);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_and(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val)
	{
		return atomic->fetch_and(val);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_and_explicit(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val, memory_order mo)
	{
		return atomic->fetch_and(val, mo);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_or(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val)
	{
		return atomic->fetch_or(val);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_or_explicit(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val, memory_order mo)
	{
		return atomic->fetch_or(val, mo);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_xor(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val)
	{
		return atomic->fetch_xor(val);
	}
	template <typename T> typename atomic_integral<T>::value_type atomic_fetch_xor_explicit(
		volatile atomic_integral<T>* atomic,
		typename atomic_integral<T>::value_type val, memory_order mo)
	{
		return atomic->fetch_xor(val, mo);
	}

	// templated atomic operations on pointers
	template <typename T> typename atomic<T*>::value_type atomic_fetch_add(
		volatile atomic<T*>* atomic, std::ptrdiff_t diff)
	{
		return atomic->fetch_add(diff);
	}
	template <typename T> typename atomic<T*>::value_type atomic_fetch_add_explicit(
		volatile atomic<T*>* atomic, std::ptrdiff_t diff, memory_order mo)
	{
		return atomic->fetch_add(diff, mo);
	}
	template <typename T> typename atomic<T*>::value_type atomic_fetch_sub(
		volatile atomic<T*>* atomic, std::ptrdiff_t diff)
	{
		return atomic->fetch_sub(diff);
	}
	template <typename T> typename atomic<T*>::value_type atomic_fetch_sub_explicit(
		volatile atomic<T*>* atomic, std::ptrdiff_t diff, memory_order mo)
	{
		return atomic->fetch_sub(diff, mo);
	}

	// atomic flag free operations
	bool atomic_flag_test_and_set(volatile atomic_flag* atomic)
	{
		return atomic->test_and_set();
	}
	bool atomic_flag_test_and_set_explicit(volatile atomic_flag* atomic, memory_order mo)
	{
		return atomic->test_and_set(mo);
	}
	void atomic_flag_clear(volatile atomic_flag* atomic)
	{
		return atomic->clear();
	}
	void atomic_flag_clear_explicit(volatile atomic_flag* atomic, memory_order mo)
	{
		return atomic->clear(mo);
	}
}

#endif // ATOMIC_FREE_FUNCTIONS_HPP_INCLUDED
