/********************************************************************
	created:		2011/02/17
	filename: 		atomic_flag.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_FLAG_HPP_INCLUDED
#define ATOMIC_FLAG_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_defs.hpp"
#include "atomic_base.hpp"

#define ATOMIC_FLAG_INIT (ATOMICS_NAMESPACE::atomic_flag::flag_init_clear())

namespace ATOMICS_NAMESPACE
{
	class atomic_flag
		: private atomic_base<unsigned char>
	{
	public:
		// initialize clear state flag type
		struct flag_init_clear {};
		// default initialization (cleared)
		atomic_flag() {}
		// clear initialization (added to support ATOMIC_FLAG_INIT)
		atomic_flag(flag_init_clear) {}

		bool test_and_set(memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->exchange(1, mo) == 1;
		}
		void clear(memory_order mo = memory_order_seq_cst) volatile
		{
			return impl_ptr()->store(0, mo);
		}
	private:
		// prevent compiler from generating copy constructor and assignment operator
		atomic_flag(const atomic_flag&);
		atomic_flag& operator=(const atomic_flag&) volatile;
	};
}

#endif // ATOMIC_FLAG_HPP_INCLUDED
