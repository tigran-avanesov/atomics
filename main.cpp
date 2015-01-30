#pragma pack(1)
#include <iostream>
#include "atomic"


struct X
{
	long a;
	long b;
};

struct Y
{
	long a;
	long b;
	long c;
};

struct V
{
	char a;
	std::atomic_int b;
};

int main()
{
	V v;
	std::atomic_int a;
	a = 10;
	std::atomic<int> b;
	b = 10;
	std::atomic<short> c;
	c = 10;
	std::atomic<int*> ptr = 0;
	ptr = 0;

	std::atomic<int> ee;
	ee = 0;
	ee.fetch_and(10);
	std::atomic<X> q;

	X x = X();
	q = x;
	q.load();
	q.compare_exchange_strong(x, X(), std::memory_order_acquire);
	q.compare_exchange_weak(x, X(), std::memory_order_acquire);
	q.compare_exchange_strong(x, X(), std::memory_order_acquire, std::memory_order_acquire);
	q.compare_exchange_weak(x, X(), std::memory_order_acquire, std::memory_order_acquire);

	std::atomic<Y> w;
	Y y = Y();
	w.store(y);
	w.load();

	w.compare_exchange_strong(y, Y(), std::memory_order_acquire);
	w.compare_exchange_weak(y, Y(), std::memory_order_acquire);
	w.compare_exchange_strong(y, Y(), std::memory_order_acquire, std::memory_order_acquire);
	w.compare_exchange_weak(y, Y(), std::memory_order_acquire, std::memory_order_acquire);

	std::atomic<short*> e;
	e.exchange(0);
	e.store(0);
	e.fetch_add(1);
	e.fetch_sub(1);
	short* t;
	e.compare_exchange_weak(t, 0);
	e.compare_exchange_strong(t, 0);
}
