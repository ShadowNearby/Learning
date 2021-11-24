/*
 * 基本算法
 */
#ifndef ALGOBASE_H_
#define ALGOBASE_H_

#include "pair.h"
#include "type_traits.h"
#include "iterator.h"
#include <string>
#include <climits>
#include <cstdlib>
#include <cstddef>
#include <new>
#include <iostream>

namespace MyStl
{
	// iter_swap() 是「有必要运用迭代器之 value type」的一个好例子。
	// 是的，它必须知道迭代器的 value type，才能够据此宣告一个对象，用来
	// 暂时放置迭代器所指的对象。
	template <class _ForwardIterator1, class _ForwardIterator2, class _T>
	inline void _iter_swap(_ForwardIterator1 a, _ForwardIterator2 b, _T*) {
		_T tmp = *a;
		*a = *b;
		*b = tmp;
	}
	//交换两个迭代器所指的对象
	template <class _ForwardIterator1, class _ForwardIterator2>
	inline void iter_swap(_ForwardIterator1 a, _ForwardIterator2 b) 
	{
		
		_iter_swap(a, b, value_type(a));;
	}

	//交换两元素值
	template <class _T>
	inline void swap(_T& a, _T& b)
	{
		_T tmp = a;
		a = b;
		b = tmp;
	}

	//取两对象中较小者/较大者
	//相等时统一取前者
	template <class _T>
	inline const _T& min(const _T& a, const _T& b)
	{
		return b < a ? b : a;
	}
	template <class _T>
	inline const _T& max(const _T& a, const _T& b)
	{
		return  a < b ? b : a;
	}
	template <class _T, class _Compare>
	inline const _T& min(const _T& a, const _T& b, _Compare comp)
	{
		return comp(b, a) ? b : a;	// 由 comp 决定「大小比较」标准
	}
	template <class _T, class _Compare>
	inline const _T& max(const _T& a, const _T& b, _Compare comp)
	{
		return comp(a, b) ? b : a;	// 由 comp 决定「大小比较」标准
	}

	//以下是copy的实现：

	//针对input_iterator、forward_iterator、bidirectional_iterator
	template <class _InputIterator, class _OutputIterator>
	inline
		_OutputIterator _copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, input_iterator_tag)
	{
		//比较迭代器决定循环是否继续、速度慢
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	}
	
	template <class _RandomAccessIterator, class _OutputIterator, class _Distance>
	inline
		_OutputIterator _copy_d(_RandomAccessIterator first, _RandomAccessIterator last, 
			_OutputIterator result, _Distance*)
	{
		//以迭代器距离n决定循环是否继续执行，速度快
		for (_Distance n = last - first; n > 0; --n, ++result, ++first)
			*result = *first;
		return result;
	}
	//针对random_access_iterator
    //调用上面函数
	template <class _RandomAccessIterator, class _OutputIterator>
	inline 
		_OutputIterator _copy(_RandomAccessIterator first, _RandomAccessIterator last,
			_OutputIterator result, random_access_iterator_tag)
	{
		return _copy_d(first, last, result, distance_type(first));
	}
	//泛化版_copy_dispatch
	template <class _InputIterator, class _OutputIterator>
	struct _copy_dispatch
	{
		_OutputIterator operator()(_InputIterator first, _InputIterator last,
			_OutputIterator result) 
		{
			return _copy(first, last, result, iterator_category(first));
		}
	};
	//特化版本一：指针所指对象有 平凡赋值运算符
	template <class _T>
	inline 
		_T* _copy_t(const _T* first, const _T* last, _T* result, __true_type)
	{
		memmove(result, first, sizeof(_T) * (last - first));
		return result + (last - first);
	}
	//特化版本二：指针所指对象有 非平凡赋值运算符
	template <class _T>
	inline 
		_T* _copy_t(const _T* first, const _T* last, _T* result, __false_type)
	{
		return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	template <class _T>
	struct _copy_dispatch<_T*, _T*>
	{
		_T* operator()(_T* first, _T* last, _T* result) 
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};

	template <class _T>
	struct _copy_dispatch<const _T*, _T*>
	{
		_T* operator()(const _T* first, const _T* last, _T* result)
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};


	// copy 函式运用了 function overloading, type traits, partial 
	// specialization, 无所不用其极地改善效率。
	//泛化接口：
	template <class _InputIterator, class _OutputIterator>
	inline 
		_OutputIterator copy(_InputIterator first, _InputIterator last,
		_OutputIterator result)
	{
		return _copy_dispatch<_InputIterator, _OutputIterator>()(first, last, result);
	}
	//特化接口：调用memmove()函数实现copy
	inline 
		char* copy(const char* first, const char* last, char* result) 
	{
		memmove(result, first, last - first);
		return result + (last - first);
	}
	//特化接口：调用memmove()函数实现copy
	inline
		wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last - first);
	}

	//以下是copy_backward的实现：
	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	inline _BidirectionalIterator2 _copy_backward(_BidirectionalIterator1 first,
		_BidirectionalIterator1 last,
		_BidirectionalIterator2 result) {
		while (first != last) *--result = *--last;
		return result;
	}

	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	struct _copy_backward_dispatch
	{
		_BidirectionalIterator2 operator()(_BidirectionalIterator1 first,
			_BidirectionalIterator1 last,
			_BidirectionalIterator2 result) {
			return _copy_backward(first, last, result);
		}
	};

	template <class _T>
	inline 
		_T* _copy_backward_t(const _T* first, const _T* last, _T* result,
		__true_type)
	{
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(_T) * N);
		return result - N;
	}

	template <class _T>
	inline
		_T* _copy_backward_t(const _T* first, const _T* last, _T* result,
		__false_type)
	{
		return _copy_backward(first, last, result);
	}

	template <class _T>
	struct _copy_backward_dispatch<_T*, _T*>
	{
		_T* operator()(_T* first, _T* last, _T* result)
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	template <class _T>
	struct _copy_backward_dispatch<const _T*, _T*>
	{
		_T* operator()(const _T* first, const _T* last, _T* result) 
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//copy_backward接口：
	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	inline _BidirectionalIterator2 copy_backward(_BidirectionalIterator1 first,
		_BidirectionalIterator1 last,
		_BidirectionalIterator2 result)
	{
		return _copy_backward_dispatch<_BidirectionalIterator1,
			_BidirectionalIterator2>()(first, last, result);
	}

	//以下是copy_n的实现：
	template <class _InputIterator, class _Size, class _OutputIterator>
	pair<_InputIterator, _OutputIterator> _copy_n(_InputIterator first, _Size count,
		_OutputIterator result,
		input_iterator_tag)
	{
		for (; count > 0; --count, ++first, ++result)
			*result = *first;
		return pair<_InputIterator, _OutputIterator>(first, result);
	}

	template <class _RandomAccessIterator, class _Size, class _OutputIterator>
	inline pair<_RandomAccessIterator, _OutputIterator>
		_copy_n(_RandomAccessIterator first, _Size count,
			_OutputIterator result,
			random_access_iterator_tag)
	{
		_RandomAccessIterator last = first + count;
		return pair<_RandomAccessIterator, _OutputIterator>
			(last, copy(first, last, result));
	}

	//copy_n接口：
	//从 first 开始复制 count 个元素到 result 以后的空间。
	template <class _InputIterator, class _Size, class _OutputIterator>
	inline pair<_InputIterator, _OutputIterator>
		copy_n(_InputIterator first, _Size count,
			_OutputIterator result)
	{
		return _copy_n(first, count, result, iterator_category(first));
	}

	//区间内元素改填新值
	template <class _ForwardIterator, class _T>
	void fill(_ForwardIterator first, _ForwardIterator last, const _T& value)
	{
		for (; first != last; ++first)	//迭代走过整个范围
			*first = value;
	}

	//区间内前n个元素改填新值，返回最后一个被改填元素的下一元素の迭代器
	template <class _OutputIterator, class _Size, class _T>
	_OutputIterator fill_n(_OutputIterator first, _Size n, const _T& value) 
	{
		for (; n > 0; --n, ++first)		// 经过n个元素
			*first = value;	// 注意，assignment 是覆写（overwrite）而不是安插（insert）
		return first;
	}

	//平行比较两序列，返回一对迭代器，指向两序列中第一次不匹配位置
	// 以下，如果序列一走完，就结束。
	// 以下，如果序列一和序列二的对应元素相等，就结束。
	// 显然，序列二的元素个数必须不少于序列一的元素个数，否则结果无可预期。
	template <class _InputIterator1, class _InputIterator2>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 first1,
		_InputIterator1 last1, _InputIterator2 first2) 
	{
		while (first1 != last1 && *first1 == *first2) 
		{
			++first1;
			++first2;
		}
		return pair<_InputIterator1, _InputIterator2>(first1, first2);
	}

	template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _BinaryPredicate binary_pred)
	{
		while (first1 != last1 && binary_pred(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return pair<_InputIterator1, _InputIterator2>(first1, first2);
	}


	//区间相等函数：
	//只保证在所比较区间内元素相等，序列二数量可以比序列一多
	//要判定两个序列是否完全相等，需要先判定其size()是否一样
	template <class _InputIterator1, class _InputIterator2>
	inline 
		bool equal(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2) 
	{
		// 以下，将序列一走过一遍。序列二亦步亦趋。
		// 假定序列二元素不少于序列一元素个数
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)		// 只要对应元素不相等，
				return false;			// 就结束并传回 false。
		return true;				   // 至此，全部相等，传回true。
	}

	template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
	inline 
		bool equal(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _BinaryPredicate binary_pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!binary_pred(*first1, *first2))
				return false;
		return true;
	}

	//两列序列以字典序比较，第一列序列小于第二列序列，返回true，大于等于都返回false
	template <class _InputIterator1, class _InputIterator2>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2)
	{
		// 以下，任何一个序列到达尾端，就结束。否则两序列就相应元素一一进行比对。
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)	// 第一序列元素值小于第二序列的相应元素值
				return true;
			if (*first2 < *first1) // 第二序列元素值小于第一序列的相应元素值
				return false;
			// 如果不符合以上两条件，表示两值相等，那就进行下一组相应元素值的比对。
		}
		// 进行到这里，如果第一序列到达尾端而第二序列尚有余额，那么第一序列小于第二序列。
		return first1 == last1 && first2 != last2;
	}

	template <class _InputIterator1, class _InputIterator2, class _Compare>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_Compare comp) 
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}
    //针对原生指针unsigned char*的特化
	inline
		bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, 
			const unsigned char* first2, const unsigned char* last2)
	{
		const size_t len1 = last1 - first1; 	// 第一序列长度
		const size_t len2 = last2 - first2; 	// 第二序列长度
		// 先比较相同长度的一截。memcmp() 速度极快。
		const int result = memcmp(first1, first2, min(len1, len2));
		// 如果不相上下，则长度较长者被视为比较大。
		return result != 0 ? result < 0 : len1 < len2;
	}
	inline 
		bool lexicographical_compare(const char* first1, const char* last1,
		const char* first2, const char* last2)
	{
		// 转型为 const signed char*
		return lexicographical_compare((const signed char*)first1,
			(const signed char*)last1,
			(const signed char*)first2,
			(const signed char*)last2);
	}
	//如果第一个范围按字典顺序小于第二个范围，则此函数返回一个负数
	//如果第一个范围按字典顺序大于第二个范围，则返回正数
	//如果两个范围在字典上都不大于另一个范围，则返回零
	template <class _InputIterator1, class _InputIterator2>
	int lexicographical_compare_3way(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2) 
		{
			if (*first1 < *first2) return -1;
			if (*first2 < *first1) return 1;
			++first1; ++first2;
		}
		if (first2 == last2) 
		{
			return !(first1 == last1);
		}
		else 
		{
			return -1;
		}
	}

	inline int
		lexicographical_compare_3way(const unsigned char* first1,
			const unsigned char* last1,
			const unsigned char* first2,
			const unsigned char* last2)
	{
		const ptrdiff_t len1 = last1 - first1;
		const ptrdiff_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return result != 0 ? result : (len1 == len2 ? 0 : (len1 < len2 ? -1 : 1));
	}

	inline int lexicographical_compare_3way(const char* first1, const char* last1,
		const char* first2, const char* last2)
	{
		return lexicographical_compare_3way(
			(const signed char*)first1,
			(const signed char*)last1,
			(const signed char*)first2,
			(const signed char*)last2);
	}
} //end of MyStl
#endif //end of ALGOBASE_H_

