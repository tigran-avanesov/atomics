/********************************************************************
	created:		2011/02/13
	filename: 		atomic.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_HPP_INCLUDED
#define ATOMIC_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_generic.hpp"
#include "atomic_pointer.hpp"
#include "atomic_integral.hpp"

#define ATOMIC_VAR_INIT(value) (value)

#define SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(T) \
template <>	class atomic<T>: public atomic_integral<T> { \
public: \
	atomic() {} \
	atomic(T val): atomic_integral<T>(val) {} \
	T operator = (T val) volatile { \
		return atomic_integral<T>::operator = (val); \
	} \
private: \
	atomic<T>& operator = (const atomic<T>&) volatile; \
	atomic<T>(const atomic<T>&); \
};

namespace ATOMICS_NAMESPACE
{
	// define atomic integral types
	typedef atomic_integral<char> atomic_char;
	typedef atomic_integral<signed char> atomic_schar;
	typedef atomic_integral<unsigned char> atomic_uchar;
	typedef atomic_integral<short> atomic_short;
	typedef atomic_integral<unsigned short> atomic_ushort;
	typedef atomic_integral<int> atomic_int;
	typedef atomic_integral<unsigned int> atomic_uint;
	typedef atomic_integral<long> atomic_long;
	typedef atomic_integral<unsigned long> atomic_ulong;
	typedef atomic_integral<long long> atomic_llong;
	typedef atomic_integral<unsigned long long> atomic_ullong;
	typedef atomic_integral<wchar_t> atomic_wchar_t;
	typedef atomic_integral<std::size_t> atomic_size_t;
	typedef atomic_integral<std::ptrdiff_t> atomic_ptrdiff_t;

	// specialize atomic generic class for atomic integral types
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(char);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(signed char);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(unsigned char);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(short);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(unsigned short);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(int);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(unsigned int);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(long);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(unsigned long);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(long long);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(unsigned long long);
	SPECIALIZE_ATOMIC_GENERIC_FOR_INTEGRAL_TYPE(wchar_t);

	// thread memory fence
	void atomic_thread_fence(memory_order mo)
	{
		switch (mo)
		{
		case memory_order_relaxed: return;
		case memory_order_seq_cst: MemoryBarrier();
		};
		_ReadWriteBarrier();
	}

	// thread signal fence
	void atomic_signal_fence(memory_order)
	{
		_ReadWriteBarrier();
	}

	// kill dependency stub for x86
	template <typename T> T kill_dependency(T x)
	{
		return x;
	}
}

#endif // ATOMIC_HPP_INCLUDED
