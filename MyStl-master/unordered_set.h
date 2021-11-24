/*
 * 以hash_table为底层支持，
 * unordered_set和unordered_multiset
 * 的实现
 */

#ifndef UNORDERED_SET_H_
#define UNORDERED_SET_H_

#include "hash_table.h"
#include <initializer_list>

namespace MyStl
{
	template <class _Value, class _HashFcn = hash<_Value>,
		class _EqualKey = equal_to<_Value>,
		class _Alloc = alloc>
	class unordered_set
	{
	private:

		typedef hashtable<_Value, _Value, _HashFcn, identity<_Value>,
			_EqualKey, _Alloc> ht;
		ht rep;	// 底层机制以hashtable完成

	public:
		typedef typename ht::key_type          key_type;
		typedef typename ht::value_type        value_type;
		typedef typename ht::hasher            hasher;
		typedef typename ht::key_equal         key_equal;

		typedef typename ht::size_type         size_type;
		typedef typename ht::difference_type   difference_type;
		typedef typename ht::const_pointer     pointer;
		typedef typename ht::const_pointer     const_pointer;
		typedef typename ht::const_reference   reference;
		typedef typename ht::const_reference   const_reference;

		typedef typename ht::const_iterator    iterator;
		typedef typename ht::const_iterator    const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:
		// 构造函数
		// 默认使用大小为100的表格。将由hash table 调整为最接近且较大之质数
		unordered_set() : rep(100, hasher(), key_equal()) {}
		explicit unordered_set(size_type n) : rep(n, hasher(), key_equal()) {}
		unordered_set(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		unordered_set(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}
		// 以下，安插动作全部使用 insert_unique()，不允许键值重复。
		template <class _InputIterator>
		unordered_set(_InputIterator f, _InputIterator l)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_unique(f, l);
		}
		template <class _InputIterator>
		unordered_set(_InputIterator f, _InputIterator l, size_type n)
			: rep(n, hasher(), key_equal()) 
		{
			rep.insert_unique(f, l);
		}
		template <class _InputIterator>
		unordered_set(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_unique(f, l);
		}
		template <class _InputIterator>
		unordered_set(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) 
		{
			rep.insert_unique(f, l);
		}

		unordered_set(const std::initializer_list<_Value>& il)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_set(const std::initializer_list<_Value>& il, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_set(const std::initializer_list<_Value>& il, size_type n, const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_set(const std::initializer_list<_Value>& il, size_type n, const hasher& hf,
			const key_equal& eql) : rep(n, hf, eql)
		{
			rep.insert_unique(il.begin(), il.end());
		}

	public:
		// 所有操作都是调用hashtable对应版本
		size_type size() const { return rep.size(); }
		size_type max_size() const { return rep.max_size(); }
		bool empty() const { return rep.empty(); }
		void swap(unordered_set& hs) { rep.swap(hs.rep); }
		friend bool operator==(const unordered_set&, const unordered_set&);

		iterator begin() const { return rep.begin(); }
		iterator end() const { return rep.end(); }

	public:
		pair<iterator, bool> insert(const value_type& obj)
		{
			pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
			return pair<iterator, bool>(p.first, p.second);
		}

		template <class _InputIterator>
		void insert(_InputIterator f, _InputIterator l) { rep.insert_unique(f, l); }

		pair<iterator, bool> insert_no_resize(const value_type& obj)
		{
			pair<typename ht::iterator, bool> p = rep.insert_unique_no_resize(obj);
			return pair<iterator, bool>(p.first, p.second);
		}

		iterator find(const key_type& key) const { return rep.find(key); }

		size_type count(const key_type& key) const { return rep.count(key); }

		pair<iterator, iterator> equal_range(const key_type& key) const
		{
			return rep.equal_range(key);
		}

		size_type erase(const key_type& key) { return rep.erase(key); }
		void erase(iterator it) { rep.erase(it); }
		void erase(iterator f, iterator l) { rep.erase(f, l); }
		void clear() { rep.clear(); }

	public:
		void resize(size_type hint) { rep.resize(hint); }
		size_type bucket_count() const { return rep.bucket_count(); }
		size_type max_bucket_count() const { return rep.max_bucket_count(); }
		size_type elems_in_bucket(size_type n) const
		{
			return rep.elems_in_bucket(n);
		}
	};

	template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
	inline bool operator==(const unordered_set<_Value, _HashFcn, _EqualKey, _Alloc>& hs1,
		const unordered_set<_Value, _HashFcn, _EqualKey, _Alloc>& hs2)
	{
		return hs1.rep == hs2.rep;
	}

	template <class _Val, class _HashFcn, class _EqualKey, class _Alloc>
	inline void swap(unordered_set<_Val, _HashFcn, _EqualKey, _Alloc>& hs1,
		unordered_set<_Val, _HashFcn, _EqualKey, _Alloc>& hs2) {
		hs1.swap(hs2);
	}


	template <class _Value, class _HashFcn = hash<_Value>,
		class _EqualKey = equal_to<_Value>,class _Alloc = alloc>
    class unordered_multiset
	{
	private:
		typedef hashtable<_Value, _Value, _HashFcn, identity<_Value>,
			_EqualKey, _Alloc> ht;
		ht rep;

	public:
		typedef typename ht::key_type key_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::const_pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::const_reference reference;
		typedef typename ht::const_reference const_reference;

		typedef typename ht::const_iterator iterator;
		typedef typename ht::const_iterator const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:
		// 默认使用大小为100的表格。将被hash table 调整为最接近且较大之质数
		unordered_multiset() : rep(100, hasher(), key_equal()) {}
		explicit unordered_multiset(size_type n) : rep(n, hasher(), key_equal()) {}
		unordered_multiset(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		unordered_multiset(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}

		// 构造函数：
		// 以下，安插动作全部使用 insert_equal()，允许键值重复。
		template <class _InputIterator>
		unordered_multiset(_InputIterator f, _InputIterator l)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_equal(f, l);
		}
		template <class _InputIterator>
		unordered_multiset(_InputIterator f, _InputIterator l, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_equal(f, l);
		}
		template <class _InputIterator>
		unordered_multiset(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf)
			: rep(n, hf, key_equal()) 
		{
			rep.insert_equal(f, l);
		}
		template <class _InputIterator>
		unordered_multiset(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) 
		{
			rep.insert_equal(f, l);
		}

		unordered_multiset(const std::initializer_list<_Value>& il)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multiset(const std::initializer_list<_Value>& il, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multiset(const std::initializer_list<_Value>& il, size_type n, const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multiset(const std::initializer_list<_Value>& il, size_type n, const hasher& hf,
			const key_equal& eql) : rep(n, hf, eql)
		{
			rep.insert_equal(il.begin(), il.end());
		}

	public:
		
		size_type size() const { return rep.size(); }
		size_type max_size() const { return rep.max_size(); }
		bool empty() const { return rep.empty(); }
		void swap(unordered_multiset& hs) { rep.swap(hs.rep); }
		friend bool operator==(const unordered_multiset&, const unordered_multiset&);

		iterator begin() const { return rep.begin(); }
		iterator end() const { return rep.end(); }

	public:
		iterator insert(const value_type& obj) { return rep.insert_equal(obj); }

		template <class _InputIterator>
		void insert(_InputIterator f, _InputIterator l) { rep.insert_equal(f, l); }

		iterator insert_no_resize(const value_type& obj)
		{
			return rep.insert_equal_no_resize(obj);
		}

		iterator find(const key_type& key) const { return rep.find(key); }

		size_type count(const key_type& key) const { return rep.count(key); }

		pair<iterator, iterator> equal_range(const key_type& key) const
		{
			return rep.equal_range(key);
		}

		size_type erase(const key_type& key) { return rep.erase(key); }
		void erase(iterator it) { rep.erase(it); }
		void erase(iterator f, iterator l) { rep.erase(f, l); }
		void clear() { rep.clear(); }

	public:
		void resize(size_type hint) { rep.resize(hint); }
		size_type bucket_count() const { return rep.bucket_count(); }
		size_type max_bucket_count() const { return rep.max_bucket_count(); }
		size_type elems_in_bucket(size_type n) const
		{
			return rep.elems_in_bucket(n);
		}
	};

	template <class _Val, class _HashFcn, class _EqualKey, class _Alloc>
	inline bool operator==(const unordered_multiset<_Val, _HashFcn, _EqualKey, _Alloc>& hs1,
		const unordered_multiset<_Val, _HashFcn, _EqualKey, _Alloc>& hs2)
	{
		return hs1.rep == hs2.rep;
	}

	template <class _Val, class _HashFcn, class _EqualKey, class _Alloc>
	inline void swap(unordered_multiset<_Val, _HashFcn, _EqualKey, _Alloc>& hs1,
		unordered_multiset<_Val, _HashFcn, _EqualKey, _Alloc>& hs2)
	{
		hs1.swap(hs2);
	}
} // end of MyStl
#endif // end of UNORDERED_SET_H_
