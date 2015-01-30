/********************************************************************
	created:		2011/02/13
	filename: 		atomic_impl_qword.hpp
	author:			Tigran Avanesov
	description:	C++0x atomics implementation
*********************************************************************/

#ifndef ATOMIC_IMPL_QWORD_HPP_INCLUDED
#define ATOMIC_IMPL_QWORD_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "atomic_impl.hpp"

#ifdef __cplusplus_cli
# pragma managed(push, off)
#endif

namespace ATOMICS_NAMESPACE
{
	namespace detail
	{
		template <typename T> class atomic_impl<T, 8>
			: private atomic_impl_base<T>
		{
		public:
			// default constructor
			atomic_impl() {}
			// initialization constructor
			explicit atomic_impl(T val): atomic_impl_base(val) {}
			// store into atomic variable
			void store(T val, memory_order mo)
			{
				exchange(val, mo);
			}
			// load from atomic variable
			T load(memory_order) const
			{
				T val;
				_ReadWriteBarrier();
				__asm xor eax, eax;
				__asm xor edx, edx;
				__asm xor ebx, ebx;
				__asm xor ecx, ecx;
				__asm mov edi, this;
				__asm lock cmpxchg8b [edi]impl_base_type.var;
				__asm mov dword ptr val, eax;
				__asm mov dword ptr val[4], edx;
				_ReadWriteBarrier();
				return val;
			}
			// increment atomic variable
			T fetch_add(T val, memory_order mo)
			{
				T old = load(memory_order_relaxed);
				while (!compare_exchange(old, old + val, mo, memory_order_relaxed));
				return old;
			}
			// swap atomic variable's value
			T exchange(T val, memory_order mo)
			{
				T old = load(memory_order_relaxed);
				while (!compare_exchange(old, val, mo, memory_order_relaxed));
				return old;
			}
			// compare and swap atomic variable's value on success
			bool compare_exchange(T& exp, T val, memory_order, memory_order)
			{
				unsigned char res;
				_ReadWriteBarrier();
				__asm mov esi, exp;
				__asm mov edi, this;
				__asm mov eax, dword ptr [esi];
				__asm mov edx, dword ptr [esi + 4];
				__asm mov ebx, dword ptr val;
				__asm mov ecx, dword ptr val[4];
				__asm lock cmpxchg8b [edi]impl_base_type.var;
				__asm setz res;
				__asm je success;
				__asm mov dword ptr [esi], eax;
				__asm mov dword ptr [esi + 4], edx;
				__asm success:
				_ReadWriteBarrier();
				return res != 0;
			}
			// implementation is lock-free
			enum { is_lock_free = 1 };
		};
	}
}

#ifdef __cplusplus_cli
# pragma managed(pop)
#endif

#endif // ATOMIC_IMPL_QWORD_HPP_INCLUDED
