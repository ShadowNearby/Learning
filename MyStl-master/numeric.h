/*
 * 数值算法
 */

#ifndef NUMERIC_H_
#define NUMERIC_H_

#include "iterator.h"
#include "functional.h"


namespace MyStl
{
	// 版本一
	template <class _InputIterator, class _T>
	_T accumulate(_InputIterator first, _InputIterator last, _T init)
	{
		for (; first != last; ++first)
			init = init + *first; 	// 将每个元素值累加到初值 init 身上
		return init;
	}

	// 版本二：接受一个二元谓词，替代默认加法操作
	template <class _InputIterator, class _T, class _BinaryOperation>
	_T accumulate(_InputIterator first, _InputIterator last, _T init,
		_BinaryOperation binary_op)
	{
		for (; first != last; ++first)
			init = binary_op(init, *first);	//  对每一个元素执行二元操作
		return init;
	}

	// 版本一
	template <class _InputIterator1, class _InputIterator2, class _T>
	_T inner_product(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _T init)
	{
		// 以第一序列之元素个数为据，将两个序列都走一遍。
		// 第二序列长度不小于第一序列，以下类似
		for (; first1 != last1; ++first1, ++first2)
			init = init + (*first1 * *first2); // 执行两个序列的一般内积
		return init;
	}

	// 版本二
	template <class _InputIterator1, class _InputIterator2, class _T,
		class _BinaryOperation1, class _BinaryOperation2>
		_T inner_product(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _T init, _BinaryOperation1 binary_op1,
			_BinaryOperation2 binary_op2)
	{
		// 以第一序列之元素个数为据，将两个序列都走一遍。
		for (; first1 != last1; ++first1, ++first2)
			// 以外界提供的仿函式来取代第一版本中的 operator* 和 operator+。
			// op2 作用于两元素间，op1 用于 op2 之结果与 init 之间。 
			init = binary_op1(init, binary_op2(*first1, *first2));
		return init;
	}

	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator _partial_sum(_InputIterator first, _InputIterator last,
		_OutputIterator result, _T*)
	{
		_T value = *first;
		while (++first != last)
		{
			value = value + *first;	 	// 前n个元素的总和
			*++result = value;			// 指定给目的端
		}
		return ++result;
	}

	// 版本一
	template <class _InputIterator, class _OutputIterator>
	_OutputIterator partial_sum(_InputIterator first, _InputIterator last,
		_OutputIterator result)
	{
		if (first == last) return result;
		*result = *first;
		return _partial_sum(first, last, result, value_type(first));
	}

	template <class _InputIterator, class _OutputIterator, class _T,
		class _BinaryOperation>
		_OutputIterator _partial_sum(_InputIterator first, _InputIterator last,
			_OutputIterator result, _T*,
			_BinaryOperation binary_op) 
	{
		_T value = *first;
		while (++first != last) {
			value = binary_op(value, *first);	// 前n个元素的总计
			*++result = value;					// 指定给目的端
		}
		return ++result;
	}

	// 版本二
	template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
	_OutputIterator partial_sum(_InputIterator first, _InputIterator last,
		_OutputIterator result, _BinaryOperation binary_op) {
		if (first == last) return result;
		*result = *first;
		return _partial_sum(first, last, result, value_type(first), binary_op);
	}

	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator _adjacent_difference(_InputIterator first, _InputIterator last,
		_OutputIterator result, _T*)
	{
		_T value = *first;
		while (++first != last)
		{		// 走过整个范围
			_T tmp = *first;
			*++result = tmp - value;	// 将相邻两元素的差额（后-前），指派给目的端
			value = tmp;
		}
		return ++result;
	}

	// 版本一
	template <class _InputIterator, class _OutputIterator>
	_OutputIterator adjacent_difference(_InputIterator first, _InputIterator last,
		_OutputIterator result) 
	{
		if (first == last) return result;
		*result = *first;	// 首先记录第一个元素
		return _adjacent_difference(first, last, result, value_type(first));
	}

	template <class _InputIterator, class _OutputIterator, class _T,
		class _BinaryOperation>
		_OutputIterator _adjacent_difference(_InputIterator first, _InputIterator last,
			_OutputIterator result, _T*,
			_BinaryOperation binary_op) {
		_T value = *first;
		while (++first != last)
		{		// 走过整个范围
			_T tmp = *first;
			*++result = binary_op(tmp, value); // 将相邻两元素的运算结果，指派给目的端
			value = tmp;
		}
		return ++result;
	}

	// 版本二
	template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
	_OutputIterator adjacent_difference(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		_BinaryOperation binary_op)
	{
		if (first == last) return result;
		*result = *first;	// 首先记录第一个元素
		return _adjacent_difference(first, last, result, value_type(first),
			binary_op);
	}

	// 版本二，幂次方。如果指定为乘法运算，则当n >= 0 时传回 x^n。
	// 注意，"multiplication" 必须满足结合律（associative），
	// 但不需满足交换律（commutative）。
	template <class _T, class _Integer, class _MonoidOperation>
	_T power(_T x, _Integer n, _MonoidOperation op)
	{
		if (n == 0)
			return identity_element(op);// 取出「证同元素」identity element.
		else 
		{
			while ((n & 1) == 0)
			{
				n >>= 1;
				x = op(x, x);
			}

			_T result = x;
			n >>= 1;
			while (n != 0)
			{
				x = op(x, x);
				if ((n & 1) != 0)
					result = op(result, x);
				n >>= 1;
			}
			return result;
		}
	}

	// 版本一，乘幂。
	template <class _T, class _Integer>
	inline _T power(_T x, _Integer n)
	{
		return power(x, n, multiplies<_T>());
	}

	// 函式意义：在 [first,last) 范围内填入value, value+1, value+2...
	// 产生连续数
	template <class _ForwardIterator, class _T>
	void iota(_ForwardIterator first, _ForwardIterator last, _T value) 
	{
		while (first != last) *first++ = value++;
	}
} //end of MyStl


#endif //end of NUMERIC_H_
