/*
 * 标准配置器，空间利用率不佳，
 * 只是简单封装了::operator new 和
 * ::operator delete，不建议使用
 */
#ifndef DEFALLOC_H_
#define DEFALLOC_H_

#include<iostream>
#include<new>
#include<climits>
namespace MyStl
{

	template<typename _T>
	inline _T* allocate(ptrdiff_t size, _T*) //全局空间配置函数
	{
		set_new_handler(0);
		_T* _tmp = static_cast<_T*>(_T*)(::operator new(size_t(size * sizeof(_T))));
		if (0 == _tmp)
		{
			cerr << "out of memory!" << endl;
			exit(1);
		}
		return _tmp;
	}

	template<typename _T>
	inline void deallocate(_T* _buffer) //全局空间释放函数
	{
		::operator delete(_buffer);
	}

	template<typename _T>
	class allocator
	{
	public:
		typedef _T value_type;
		typedef _T* pointer;
		typedef const _T* const_pointer;
		typedef _T& reference;
		typedef const _T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		pointer allocate(difference_type _n)
		{
			return ::allocate((difference_type)_n, (pointer)0);
		}

		void deallocate(pointer _p)
		{
			::deallocate(_p);
		}

		pointer address(reference _x)
		{
			return (pointer)&_x;
		}

		const_pointer const_address(const_reference _x)
		{
			return (const_pointer)&_x;
		}

		size_type init_page_size()
		{
			return max((size_type)(1), (size_type)(4096 / sizeof(_T)));
		}

		size_type max_size()
		{
			return (size_type)(UINT_MAX / sizeof(_T));
		}

	};

	template<>
	class allocator<void>
	{
	public:
		typedef void* pointer;
	};
} //end of MyStl
#endif //end of DEFALLOC_H_