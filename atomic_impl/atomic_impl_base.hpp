/********************************************************************
	created:		2011/02/13
	filename: 		atomic_impl_base.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_IMPL_BASE_HPP_INCLUDED
#define ATOMIC_IMPL_BASE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_defs.hpp"
#include "atomic_alignment.hpp"

namespace ATOMICS_NAMESPACE
{
	namespace detail
	{
		template <typename T> class atomic_impl_base
		{
		public:
			// default constructor
			atomic_impl_base(): var(T())
			{
				detail::alignment<T>::check(&var);
			}
			// initialization constructor
			explicit atomic_impl_base(T val): var(val)
			{
				detail::alignment<T>::check(&var);
			}
		private:
			// prevent compiler from generating copy constructor and assignment operator
			atomic_impl_base(const atomic_impl_base&);
			atomic_impl_base& operator = (const atomic_impl_base&);
		protected:
			// base type definition
			typedef atomic_impl_base<T> impl_base_type;
			// atomic variable aligned to 4 bytes boundary
			__declspec (align(4)) T var;
		};
	}
}

#endif // ATOMIC_IMPL_BASE_HPP_INCLUDED
