/*
 * 容器适配器queue，
 * 没有实现priority_queue
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "deque.h"

namespace MyStl
{
	template<class _T, class _Sequence = deque<_T> >
	class queue
	{
		friend bool operator==(const queue&, const queue&);
		friend bool operator!=(const queue&, const queue&);
		friend bool operator<(const queue&, const queue&);
		friend bool operator>(const queue&, const queue&);
		friend bool operator<=(const queue&, const queue&);
		friend bool operator>=(const queue&, const queue&);
	public:
		//没有迭代器
		typedef typename _Sequence::value_type       value_type;
		typedef typename _Sequence::size_type        size_type;
		typedef typename _Sequence::reference        reference;
		typedef typename _Sequence::const_reference  const_reference;
	protected:
		_Sequence _c;	             // 底层容器
	public:
		// 以下完全利用 _Sequence _c 的操作，完成 queue 的操作。
		bool empty() const { return _c.empty(); }
		size_type size() const { return _c.size(); }
		reference front() { return _c.front(); }
		const_reference front() const { return _c.front(); }
		reference back() { return _c.back(); }
		const_reference back() const { return _c.back(); }

		void push(const value_type& _x) { _c.push_back(_x); }
		void pop() { _c.pop_front(); }
	};

	template <class _T, class _Sequence>
	bool operator==(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return _x._c == _y._c;
	}

	template <class _T, class _Sequence>
	bool operator!=(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return !(_x == _y);
	}

	template <class _T, class _Sequence>
	bool operator<(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return _x._c < _y._c;
	}

	template <class _T, class _Sequence>
	bool operator>(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return _y < _x;
	}

	template <class _T, class _Sequence>
	bool operator<=(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return !(_y < _x);
	}

	template <class _T, class _Sequence>
	bool operator>=(const queue<_T, _Sequence>& _x, const queue<_T, _Sequence>& _y)
	{
		return !(_x > _y);
	}

}// end of MyStl
#endif // end of QUEUE_H_