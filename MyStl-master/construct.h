/*
 * 定义了五个全局函数——construct(), destroy(),
 * uninitialized_copy(),uninitialized_fill(),
 * uninitialized_fill_n()中的前两个，
 * 负责对象的构建和析构
 */


#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include<new>
#include"type_traits.h"
#include"iterator.h"

namespace MyStl
{
	template <class _T1, class _T2>
	inline void construct(_T1* p, const _T2& value)
	{
		new (p) _T1(value); 	// placement new; 唤起 ctor T1(value);
	}

	// 以下是 destroy() 第一版本，接受一个指针。
	template <class _T>
	inline void destroy(_T* pointer) 
	{
		pointer->~_T();	// 唤起 dtor ~T()
	}

	// 如果元素的值类型（value type）有 non-trivial destructor
	template <class _ForwardIterator>
	inline 
		void _destroy_aux(_ForwardIterator first, _ForwardIterator last, __false_type)
	{
		for (; first < last; ++first) //逐个调用析构函数
			destroy(&*first);
	}

	// 如果元素的值类型（value type）有 trivial destructor
	template <class _ForwardIterator>
	inline 
		void _destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {} //什么也不用做

	// 判断元素的值类型（value type）是否有 trivial destructor
	template <class _ForwardIterator, class _T>
	inline void _destroy(_ForwardIterator first, _ForwardIterator last, _T*) 
	{
		//萃取_T的型别特性
		typedef typename __type_traits<_T>::has_trivial_destructor trivial_destructor; 
		_destroy_aux(first, last, trivial_destructor());
	}

	// 以下是 destroy() 第二版本，接受两个迭代器。此函式是设法找出元素的值类型，
	// 进而利用 __type_traits<> 求取最适当措施。
	template <class _ForwardIterator>
	inline void destroy(_ForwardIterator first, _ForwardIterator last)
	{
		_destroy(first, last, value_type(first));
	}

	// 以下是destroy() 第二版本针对迭代器为 char* 和 wchar_t* 的特化版
	inline void destroy(char*, char*) {}
	inline void destroy(wchar_t*, wchar_t*) {}

} //end of MyStl
#endif //end of CONSTRUCT_H_