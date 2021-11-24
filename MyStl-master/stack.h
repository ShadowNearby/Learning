/*
 * 容器适配器stack
 */

#ifndef STACK_H_
#define STACK_H_

#include "deque.h"

namespace MyStl
{
	template <class _T, class _Sequence = deque<_T>>
	class stack
	{
		friend bool operator== (const stack&, const stack&);
		friend bool operator!= (const stack&, const stack&);
		friend bool operator< (const stack&, const stack&);
		friend bool operator> (const stack&, const stack&);
		friend bool operator<= (const stack&, const stack&);
		friend bool operator>=(const stack&, const stack&);
	public:
		typedef typename _Sequence::value_type        value_type;
		typedef typename _Sequence::size_type         size_type;
		typedef typename _Sequence::reference         reference;
		typedef typename _Sequence::const_reference   const_reference;
	protected:
		_Sequence c;	// 底层容器
	public:
		// 以下完全利用 Sequence c 的操作，完成 stack 的操作。
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		// deque 是两头可进出，stack 是末端进，末端出（所以后进者先出）。
		void push(const value_type& x) { c.push_back(x); }
		void pop() { c.pop_back(); }
	};  // end of stack

	template <typename _T, typename _Sequence>
	bool operator==(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return _x._c == _y._c;
	}

	template <typename _T, typename _Sequence>
	bool operator!=(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return !(_x == _y)；
	}

	template <typename _T, typename _Sequence>
	bool operator<(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return _x._c < _y._c;
	}

	template <typename _T, typename _Sequence>
	bool operator>(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return _y < _x;
	}

	template <typename _T, typename _Sequence>
	bool operator<=(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return !(_y < _x);
	}

	template <typename _T, typename _Sequence>
	bool operator>=(const stack<_T, _Sequence>& _x, const stack<_T, _Sequence>& _y)
	{
		return !(_x < _y);
	}

} // end of MyStl
#endif // end of STACK_H_
