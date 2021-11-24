/*
 * 基础迭代器的实现，
 * 没有实现反向迭代器
 * 以及插入迭代器等
 * 迭代器适配器
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include<cstddef> 

namespace MyStl
{
	// 五种迭代器类型
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class _T, class _Distance>
	struct input_iterator
	{
		typedef input_iterator_tag  iterator_category;
		typedef _T                  value_type;
		typedef _Distance           difference_type;
		typedef _T*                 pointer;
		typedef _T&                 reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class _T, class _Distance>
	struct forward_iterator
	{
		typedef forward_iterator_tag iterator_category;
		typedef _T                    value_type;
		typedef _Distance             difference_type;
		typedef _T*                   pointer;
		typedef _T&                   reference;
	};


	template <class _T, class _Distance>
	struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag iterator_category;
		typedef _T                          value_type;
		typedef _Distance                   difference_type;
		typedef _T*                         pointer;
		typedef _T&                         reference;
	};

	template <class _T, class _Distance>
	struct random_access_iterator
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _T                          value_type;
		typedef _Distance                   difference_type;
		typedef _T*                         pointer;
		typedef _T&                         reference;
	};

	//自行开发的迭代器最好继承自下面这个标准迭代器
	template <class _Category, class _T, class _Distance = ptrdiff_t,
		class _Pointer = _T*, class _Reference = _T&>
	struct iterator 
	{
		typedef _Category   iterator_category;
		typedef _T          value_type;
		typedef _Distance   difference_type;
		typedef _Pointer    pointer;
		typedef _Reference  reference;
	};

	template <class _Iterator>
	struct iterator_traits 
	{
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type        value_type;
		typedef typename _Iterator::difference_type   difference_type;
		typedef typename _Iterator::pointer           pointer;
		typedef typename _Iterator::reference         reference;
	};

	// 针对原生指针而设计的traits偏特化版。
	template <class _T>
	struct iterator_traits<_T*> 
	{
		//原生指针的迭代器型别是random_access_iterator_tag
		typedef random_access_iterator_tag  iterator_category; 
		typedef _T                          value_type;
		typedef ptrdiff_t                   difference_type;
		typedef _T*                         pointer;
		typedef _T&                         reference;
	};

	// 针对原生top-level const指针设计的traits偏特化版。
	template <class _T>
	struct iterator_traits<const _T*>
	{
		typedef random_access_iterator_tag  iterator_category;
		typedef _T                          value_type; //注意value_type是_T
		typedef ptrdiff_t                   difference_type;
		typedef const _T*                   pointer;
		typedef const _T&                   reference;
	};

	//取得某个迭代器的类型（category）
	template <class _Iterator>
	inline
		typename iterator_traits<_Iterator>::iterator_category iterator_category(const _Iterator&)
	{
		typedef typename iterator_traits<_Iterator>::iterator_category category;
		return category();
	}

	// 取得某个迭代器的distance_type（指针）
	template <class _Iterator>
	inline 
		typename iterator_traits<_Iterator>::difference_type* distance_type(const _Iterator&) 
	{
		return static_cast<typename iterator_traits<_Iterator>::difference_type*>(0);
	}

	// 取得某个迭代器的value_type（指针）
	template <class _Iterator>
	inline 
		typename iterator_traits<_Iterator>::value_type* value_type(const _Iterator&) 
	{
		return static_cast<typename iterator_traits<_Iterator>::value_type*>(0);
	}


	// 以下是整组distance函式
	template <class _InputIterator>
	inline 
		typename iterator_traits<_InputIterator>::difference_type _distance(_InputIterator first, 
			_InputIterator last, input_iterator_tag) 
	{
		typename iterator_traits<_InputIterator>::difference_type n = 0;
		while (first != last) 
		{
			++first; ++n;
		}
		return n;
	}

	template <class _RandomAccessIterator>
	inline 
		typename iterator_traits<_RandomAccessIterator>::difference_type _distance(_RandomAccessIterator first,
			_RandomAccessIterator last, random_access_iterator_tag) 
	{
		return last - first;
	}

	template <class _InputIterator>
	inline 
		typename iterator_traits<_InputIterator>::difference_type distance(_InputIterator first, 
			_InputIterator last) 
	{
		typedef typename iterator_traits<_InputIterator>::iterator_category category;
		return _distance(first, last, category());
	}



	// 以下是整组 advance 函式
	template <class _InputIterator, class _Distance>
	inline void _advance(_InputIterator& i, _Distance n, input_iterator_tag) 
	{
		while (n--) ++i;
	}

	template <class BidirectionalIterator, class _Distance>
	inline void _advance(BidirectionalIterator& i, _Distance n,
		bidirectional_iterator_tag)
	{
		if (n >= 0)
			while (n--) ++i;
		else
			while (n++) --i;
	}

	template <class _RandomAccessIterator, class _Distance>
	inline void _advance(_RandomAccessIterator& i, _Distance n,
		random_access_iterator_tag) 
	{
		i += n;
	}

	template <class _InputIterator, class _Distance>
	inline void advance(_InputIterator& i, _Distance n)
	{
		_advance(i, n, iterator_category(i));
	}
} //end of MyStl
#endif // end of ITERATOR_H_
