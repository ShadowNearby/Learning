/*
 * 定义了五个全局函数——construct(), destroy(),
 * uninitialized_copy(),uninitialized_fill(),
 * uninitialized_fill_n()中的后三个,以及其他相关函数
 */

#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_

#include "construct.h"
#include "algorithm.h"

namespace MyStl
{
	// 以下是uninitialized_copy的实现：

	//如果是POD型别，执行以下函数
	template <class _InputIterator, class _ForwardIterator>
	inline
		_ForwardIterator _uninitialized_copy_aux(_InputIterator first, _InputIterator last,
			_ForwardIterator result, __true_type)
	{
		return MyStl::copy(first, last, result);//算法copy()
	}

	// 如果是non-POD 型别，执行流程就会转进到以下函数
	template <class _InputIterator, class _ForwardIterator>
	_ForwardIterator _uninitialized_copy_aux(_InputIterator first, _InputIterator last,
		_ForwardIterator result, __false_type)
	{
		_ForwardIterator cur = result;
		try
		{
			for (; first != last; ++first, ++cur)
				construct(&*cur, *first);	//必须一个一个元素地建构，无法批量进行
			return cur;
		}
		catch (...)
		{
			destroy(result, cur);
			throw;
		}
	}

	template <class _InputIterator, class _ForwardIterator, class _T>
	inline
		_ForwardIterator _uninitialized_copy(_InputIterator first, _InputIterator last,
			_ForwardIterator result, _T*)
	{
		typedef typename __type_traits<_T>::is_POD_type is_POD;
		//利用 is_POD() 所获得的结果，让编译程序做自变量推导。
		return _uninitialized_copy_aux(first, last, result, is_POD());

	}

	template <class _InputIterator, class _ForwardIterator>
	inline
		_ForwardIterator uninitialized_copy(_InputIterator first, _InputIterator last,
			_ForwardIterator result)
	{
		//利用 value_type() 取出 first 的 value type.
		return _uninitialized_copy(first, last, result, value_type(result));

	}

	// 以下是针对 const char* 的特化版本
	// 采用memmove()函数快速拷贝
	inline
		char* uninitialized_copy(const char* first, const char* last, char* result)
	{
		memmove(result, first, last - first);
		return result + (last - first);
	}

	// 以下是针对 const wchar_t* 的特化版本
	// 采用memmove()函数快速拷贝
	inline
		wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last - first);
	}

	// 以下是uninitialized_copy_n的实现：

	template <class _InputIterator, class _Size, class _ForwardIterator>
	pair<_InputIterator, _ForwardIterator> _uninitialized_copy_n(_InputIterator first,
		_Size count, _ForwardIterator result, input_iterator_tag)
	{
		_ForwardIterator cur = result;
		try
		{
			for (; count > 0; --count, ++first, ++cur)
				construct(&*cur, *first);
			return pair<_InputIterator, _ForwardIterator>(first, cur);
		}
		catch (...)
		{
			destroy(result, cur);
			throw;
		}
	}

	template <class _RandomAccessIterator, class _Size, class _ForwardIterator>
	inline
		pair<_RandomAccessIterator, _ForwardIterator> _uninitialized_copy_n(
			_RandomAccessIterator first, _Size count,
			_ForwardIterator result, random_access_iterator_tag)
	{
		_RandomAccessIterator last = first + count;
		return make_pair(last, uninitialized_copy(first, last, result));
	}

	template <class _InputIterator, class _Size, class _ForwardIterator>
	inline 
		pair<_InputIterator, _ForwardIterator> uninitialized_copy_n(_InputIterator first,
			_Size count, _ForwardIterator result) 
	{
		//根据迭代器型别跳转执行函数
		return _uninitialized_copy_n(first, count, result, iterator_category(first));
	}


	// 以下是uninitialized_fill的实现：

	// 如果是POD 型别，执行流程就会转进到以下函数
	template <class _ForwardIterator, class _T>
	inline 
		void _uninitialized_fill_aux(_ForwardIterator first, _ForwardIterator last,
			const _T& x, __true_type)
	{
		fill(first, last, x);//算法fill()
	}

	// 如果是non-POD 型别，执行流程就会转进到以下函数
	template <class _ForwardIterator, class _T>
	void _uninitialized_fill_aux(_ForwardIterator first, _ForwardIterator last,
			const _T& x, __false_type)
	{
		_ForwardIterator cur = first;
		try
		{
			for (; cur != last; ++cur)
				construct(&*cur, x);	// 必须一个一个元素地建构，无法批量进行
		}
		catch (...)
		{
			destroy(first, cur);
			throw;
		}
	}

	template <class _ForwardIterator, class _T, class _T1>
	inline void _uninitialized_fill(_ForwardIterator first, _ForwardIterator last,
		const _T& x, _T1*)
	{
		typedef typename __type_traits<_T1>::is_POD_type is_POD;
		_uninitialized_fill_aux(first, last, x, is_POD());

	}

	template <class _ForwardIterator, class _T>
	inline 
		void uninitialized_fill(_ForwardIterator first, _ForwardIterator last,
		const _T& x) 
	{
		_uninitialized_fill(first, last, x, value_type(first));
	}

	// 以下是uninitialized_fill_n的实现：

	// 如果是POD 型别，执行流程就会转进到以下函数
	template <class _ForwardIterator, class _Size, class _T>
	inline 
		_ForwardIterator _uninitialized_fill_n_aux(_ForwardIterator first, _Size n,
			const _T& x, __true_type) 
	{
		return MyStl::fill_n(first, n, x); //算法fill_n()
	}

	// 如果是non-POD 型别，执行流程就会转进到以下函数
	template <class _ForwardIterator, class _Size, class _T>
	_ForwardIterator _uninitialized_fill_n_aux(_ForwardIterator first, _Size n,
			const _T& x, __false_type)
	{
		_ForwardIterator cur = first;
		try
		{
			for (; n > 0; --n, ++cur)
				construct(&*cur, x);
			return cur;
		}
		catch (...)
		{
			destroy(first, cur);
			throw;
		}
	}

	template <class _ForwardIterator, class _Size, class _T, class _T1>
	inline _ForwardIterator _uninitialized_fill_n(_ForwardIterator first, _Size n,
		const _T& x, _T1*)
	{
		typedef typename __type_traits<_T1>::is_POD_type is_POD;
		return _uninitialized_fill_n_aux(first, n, x, is_POD());

	}

	template <class _ForwardIterator, class _Size, class _T>
	inline 
		_ForwardIterator uninitialized_fill_n(_ForwardIterator first, _Size n,
		const _T& x)
	{
		return _uninitialized_fill_n(first, n, x, value_type(first));
	}


	// Copies [first1, last1) into [result, result + (last1 - first1)), and
	//  copies [first2, last2) into
	//  [result, result + (last1 - first1) + (last2 - first2)).
	template <class _InputIterator1, class _InputIterator2, class _ForwardIterator>
	inline
		_ForwardIterator _uninitialized_copy_copy(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2, _ForwardIterator result)
	{
		_ForwardIterator mid = uninitialized_copy(first1, last1, result);
		try
		{
			return uninitialized_copy(first2, last2, mid);
		}
		catch (...)
		{
			destroy(result, mid);
			throw;
		}
	}

	// Fills [result, mid) with x, and copies [first, last) into
	//  [mid, mid + (last - first)).
	template <class _ForwardIterator, class _T, class _InputIterator>
	inline 
		_ForwardIterator _uninitialized_fill_copy(_ForwardIterator result, _ForwardIterator mid,
			const _T& x, _InputIterator first, _InputIterator last)
	{
		uninitialized_fill(result, mid, x);
		try
		{
			return uninitialized_copy(first, last, mid);
		}
		catch (...)
		{
			destroy(result, mid);
			throw;
		}
	}

	// Copies [first1, last1) into [first2, first2 + (last1 - first1)), and
	//  fills [first2 + (last1 - first1), last2) with x.
	template <class _InputIterator, class _ForwardIterator, class _T>
	inline 
		void _uninitialized_copy_fill(_InputIterator first1, _InputIterator last1,
			_ForwardIterator first2, _ForwardIterator last2, const _T& x)
	{
		_ForwardIterator mid2 = uninitialized_copy(first1, last1, first2);
		try
		{
			uninitialized_fill(mid2, last2, x);
		}
		catch (...)
		{
			destroy(first2, mid2);
			throw;
		}
	}
}   //end of MyStl
#endif // end of UNINITIALIZED_H_
