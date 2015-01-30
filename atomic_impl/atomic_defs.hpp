/********************************************************************
	created:		2011/02/13
	filename: 		atomic_defs.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_DEFS_HPP_INCLUDED
#define ATOMIC_DEFS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <limits>

#define ATOMIC_CHAR_LOCK_FREE 1
#define ATOMIC_CHAR16_T_LOCK_FREE 1
#define ATOMIC_CHAR32_T_LOCK_FREE 1
#define ATOMIC_WCHAR_T_LOCK_FREE 1
#define ATOMIC_SHORT_LOCK_FREE 1
#define ATOMIC_INT_LOCK_FREE 1
#define ATOMIC_LONG_LOCK_FREE 1

#if ULLONG_MAX <= 0xFFFFFFFFFFFFFFFF
# define ATOMIC_LLONG_LOCK_FREE 1
#endif

#define ATOMICS_NAMESPACE std

#if !defined(_MSC_VER) || !defined(_X86_)
# error "Unsupported platform, C++0x atomics library supports only x86-32 on Microsoft Visual Studio"
#endif

namespace ATOMICS_NAMESPACE
{
	// memory order enumeration definition
	typedef enum memory_order
	{
		memory_order_relaxed, memory_order_consume, memory_order_acquire,
		memory_order_release, memory_order_acq_rel, memory_order_seq_cst
	} memory_order;
}

#endif // ATOMIC_DEFS_HPP_INCLUDED
