/*
 * 简单的hash function，
 * 针对字符串做了处理，
 * 整数型别忠实地返回原值
 * 必要时可自定义
 */

#ifndef HASH_FUNC_H_
#define HASH_FUNC_H_

#include <cstddef>

namespace MyStl
{
	template <class _Key> struct hash { };

	inline size_t _stl_hash_string(const char* s)
	{
		unsigned long h = 0;
		for (; *s; ++s)
			h = 5 * h + *s;
		return size_t(h);
	}

	template<>
	struct hash<char*>
	{
		size_t operator()(const char* s) const { return _stl_hash_string(s); }
	};

	template<>
	struct hash<const char*>
	{
		size_t operator()(const char* s) const { return _stl_hash_string(s); }
	};

	template<>
	struct hash<char> 
	{
		size_t operator()(char x) const { return size_t(x); }
	};

	template<>
	struct hash<unsigned char> 
	{
		size_t operator()(unsigned char x) const { return size_t(x); }
	};

	template<>
	struct hash<signed char>
	{
		size_t operator()(unsigned char x) const { return size_t(x); }
	};

	template<>
	struct hash<short>
	{
		size_t operator()(short x) const { return size_t(x); }
	};

	template<>
	struct hash<unsigned short>
	{
		size_t operator()(unsigned short x) const { return size_t(x); }
	};

	template<>
	struct hash<int> 
	{
		size_t operator()(int x) const { return size_t(x); }
	};

	template<>
	struct hash<unsigned int> 
	{
		size_t operator()(unsigned int x) const { return size_t(x); }
	};

	template<>
	struct hash<long> 
	{
		size_t operator()(long x) const { return size_t(x); }
	};

	template<>
	struct hash<unsigned long> 
	{
		size_t operator()(unsigned long x) const { return size_t(x); }
	};

}//end of MyStl

#endif //end of HASH_FUNC_H_
