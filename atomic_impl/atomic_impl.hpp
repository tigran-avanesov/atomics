/********************************************************************
	created:		2011/02/13
	filename: 		atomic_impl.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_IMPL_HPP_INCLUDED
#define ATOMIC_IMPL_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <intrin.h>
#include <windows.h>
#include <memory.h>

#include "atomic_impl_base.hpp"

namespace ATOMICS_NAMESPACE
{
	namespace detail
	{
		template <typename T, int size = sizeof(T)> class atomic_impl
			: private atomic_impl_base<T>
		{
		public:
			// default constructor
			atomic_impl()
			{
				InitializeCriticalSection(&mutex);
			}
			// initialization constructor
			explicit atomic_impl(T val): atomic_impl_base(val)
			{
				InitializeCriticalSection(&mutex);
			}
			// destructor
			~atomic_impl()
			{
				DeleteCriticalSection(&mutex);
			}
			// store into atomic variable
			void store(T val, memory_order)
			{
				internal_mutex_lock();
				std::memcpy(&var, &val, sizeof(T));
				internal_mutex_unlock();
			}
			// load from atomic variable
			T load(memory_order) const
			{
				internal_mutex_lock();
				T val;
				std::memcpy(&val, &var, sizeof(T));
				internal_mutex_unlock();
				return val;
			}
			// swap atomic variable's value
			T exchange(T val, memory_order)
			{
				internal_mutex_lock();
				T old;
				std::memcpy(&old, &var, sizeof(T));
				std::memcpy(&var, &val, sizeof(T));
				internal_mutex_unlock();
				return old;
			}
			// compare and swap atomic variable's value on success
			bool compare_exchange(T& exp, T val, memory_order, memory_order)
			{
				internal_mutex_lock();
				if (std::memcmp(&var, &exp, sizeof(T)) == 0)
				{
					std::memcpy(&var, &val, sizeof(T));
					internal_mutex_unlock();
					return true;
				}
				std::memcpy(&exp, &var, sizeof(T));
				internal_mutex_unlock();
				return false;
			}
			// implementation is lock-based
			enum { is_lock_free = 0 };
		private:
			// enter critical section
			void internal_mutex_lock() const
			{
				EnterCriticalSection(&mutex);
			}
			// leave critical section
			void internal_mutex_unlock() const
			{
				LeaveCriticalSection(&mutex);
			}
			mutable CRITICAL_SECTION mutex;
		};
	}
}

#endif // ATOMIC_IMPL_HPP_INCLUDED
