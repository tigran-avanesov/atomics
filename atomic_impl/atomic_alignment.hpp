/********************************************************************
	created:		2011/02/17
	filename: 		atomic_alignment.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_ALIGNMENT_HPP_INCLUDED
#define ATOMIC_ALIGNMENT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cassert>

namespace ATOMICS_NAMESPACE
{
	namespace detail
	{
		// alignment assertion template class
		template <typename T, bool perform = sizeof(T*) <= sizeof(__int64)> struct alignment
		{
			enum
			{
				// calculate required boundary for specified type at compile-time
				required = sizeof(T) == 8 ? 4 : sizeof(T) == 4 ? 4 : sizeof(T) == 2 ? 2 : 1
			};
			static void check(const T* const ptr)
			{
				// check specified pointer alignment
				assert((reinterpret_cast<__int64>(ptr) & (required - 1)) == 0);
			}
		};
		// check cannot be performed (size does not fit), generate stub instead
		template <typename T> struct alignment<T, false>
		{
			static void check(const T* const ptr) {}
		};
	}
}

#endif // ATOMIC_ALIGNMENT_HPP_INCLUDED
