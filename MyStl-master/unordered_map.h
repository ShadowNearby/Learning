/*
* 以hash_table为底层支持，
* unordered_map和unordered_multimap
* 的实现
*/

#ifndef UNORDERED_MAP_H_
#define UNORDERED_MAP_H_

#include "hash_table.h"
#include <initializer_list>

namespace MyStl
{

	template <class _Key, class _T, class _HashFcn = hash<_Key>,
		class _EqualKey = equal_to<_Key>,class _Alloc = alloc>
	class unordered_map
	{
	private:
		typedef hashtable<pair<const _Key, _T>, _Key, _HashFcn,
			select1st<pair<const _Key, _T> >, _EqualKey, _Alloc> ht;
		ht rep;	//底层机制以hashtable完成

	public:
		typedef typename ht::key_type key_type;
		typedef _T data_type;
		typedef _T mapped_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::reference reference;
		typedef typename ht::const_reference const_reference;

		typedef typename ht::iterator iterator;
		typedef typename ht::const_iterator const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:

		// 构造函数
		// 默认使用大小为100的表格。将由hashtable调整为最接近且较大之质数
		unordered_map() : rep(100, hasher(), key_equal()) {}
		explicit unordered_map(size_type n) : rep(n, hasher(), key_equal()) {}
		unordered_map(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		unordered_map(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}
		// 以下，安插动作全部使用 insert_unique()，不允许键值重复。
		template <class _InputIterator>
		unordered_map(_InputIterator f, _InputIterator l)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_unique(f, l);
		}

		template <class _InputIterator>
		unordered_map(_InputIterator f, _InputIterator l, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_unique(f, l);
		}

		template <class _InputIterator>
		unordered_map(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_unique(f, l);
		}

		template <class _InputIterator>
		unordered_map(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql)
		{
			rep.insert_unique(f, l);
		}

		unordered_map(const std::initializer_list<pair<_Key,_T>>& il)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_map(const std::initializer_list<pair<_Key, _T>>& il, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_map(const std::initializer_list<pair<_Key, _T>>& il, size_type n, const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_unique(il.begin(), il.end());
		}

		unordered_map(const std::initializer_list<pair<_Key, _T>>& il, size_type n, const hasher& hf,
			const key_equal& eql) : rep(n, hf, eql)
		{
			rep.insert_unique(il.begin(), il.end());
		}

	public:
		// 所有操作几乎都有 hash table 对应版本。转呼叫就行。
		size_type size() const { return rep.size(); }
		size_type max_size() const { return rep.max_size(); }
		bool empty() const { return rep.empty(); }
		void swap(unordered_map& hs) { rep.swap(hs.rep); }
		friend bool
			operator==(const unordered_map&, const unordered_map&);

		iterator begin() { return rep.begin(); }
		iterator end() { return rep.end(); }
		const_iterator begin() const { return rep.begin(); }
		const_iterator end() const { return rep.end(); }

	public:
		pair<iterator, bool> insert(const value_type& obj)
		{
			return rep.insert_unique(obj);
		}

		template <class _InputIterator>
		void insert(_InputIterator f, _InputIterator l) { rep.insert_unique(f, l); }

		pair<iterator, bool> insert_no_resize(const value_type& obj)
		{
			return rep.insert_unique_no_resize(obj);
		}

		iterator find(const key_type& key) { return rep.find(key); }
		const_iterator find(const key_type& key) const { return rep.find(key); }

		_T& operator[](const key_type& key) {
			return rep.find_or_insert(value_type(key, _T())).second;
		}

		size_type count(const key_type& key) const { return rep.count(key); }

		pair<iterator, iterator> equal_range(const key_type& key)
		{
			return rep.equal_range(key);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& key) const
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

	template <class _Key, class _T, class _HashFcn, class _EqualKey, class _Alloc>
	inline bool operator==(const unordered_map<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm1,
		const unordered_map<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm2)
	{
		return hm1.rep == hm2.rep;
	}

	template <class _Key, class _T, class _HashFcn, class _EqualKey, class _Alloc>
	inline void swap(unordered_map<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm1,
		unordered_map<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm2)
	{
		hm1.swap(hm2);
	}


	template <class _Key, class _T, class _HashFcn = hash<_Key>,
		class _EqualKey = equal_to<_Key>,class _Alloc = alloc>
	class unordered_multimap
	{
	private:
		typedef hashtable<pair<const _Key, _T>, _Key, _HashFcn,
			select1st<pair<const _Key, _T> >, _EqualKey, _Alloc> ht;
		ht rep;

	public:
		typedef typename ht::key_type key_type;
		typedef _T data_type;
		typedef _T mapped_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::reference reference;
		typedef typename ht::const_reference const_reference;

		typedef typename ht::iterator iterator;
		typedef typename ht::const_iterator const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:
		// 默认使用大小为100的表格。将被hash table 调整为最接近且较大之质数
		unordered_multimap() : rep(100, hasher(), key_equal()) {}
		explicit unordered_multimap(size_type n) : rep(n, hasher(), key_equal()) {}
		unordered_multimap(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		unordered_multimap(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}


		// 以下，安插动作全部使用 insert_equal()，允许键值重复。
		template <class _InputIterator>
		unordered_multimap(_InputIterator f, _InputIterator l)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_equal(f, l);
		}

		template <class _InputIterator>
		unordered_multimap(_InputIterator f, _InputIterator l, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_equal(f, l);
		}

		template <class _InputIterator>
		unordered_multimap(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf)
			: rep(n, hf, key_equal()) 
		{
			rep.insert_equal(f, l);
		}

		template <class _InputIterator>
		unordered_multimap(_InputIterator f, _InputIterator l, size_type n,
			const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql)
		{
			rep.insert_equal(f, l);
		}

		unordered_multimap(const std::initializer_list<pair<_Key, _T>>& il)
			: rep(100, hasher(), key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multimap(const std::initializer_list<pair<_Key, _T>>& il, size_type n)
			: rep(n, hasher(), key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multimap(const std::initializer_list<pair<_Key, _T>>& il, size_type n, const hasher& hf)
			: rep(n, hf, key_equal())
		{
			rep.insert_equal(il.begin(), il.end());
		}

		unordered_multimap(const std::initializer_list<pair<_Key, _T>>& il, size_type n, const hasher& hf,
			const key_equal& eql) : rep(n, hf, eql)
		{
			rep.insert_equal(il.begin(), il.end());
		}

	public:
		// 所有操作几乎都有 hash table 的对应版本，转呼叫就好。
		size_type size() const { return rep.size(); }
		size_type max_size() const { return rep.max_size(); }
		bool empty() const { return rep.empty(); }
		void swap(unordered_multimap& hs) { rep.swap(hs.rep); }
		friend bool
			operator==(const unordered_multimap&, const unordered_multimap&);

		iterator begin() { return rep.begin(); }
		iterator end() { return rep.end(); }
		const_iterator begin() const { return rep.begin(); }
		const_iterator end() const { return rep.end(); }

	public:
		iterator insert(const value_type& obj) { return rep.insert_equal(obj); }

		template <class _InputIterator>
		void insert(_InputIterator f, _InputIterator l) { rep.insert_equal(f, l); }

		iterator insert_no_resize(const value_type& obj)
		{
			return rep.insert_equal_no_resize(obj);
		}

		iterator find(const key_type& key) { return rep.find(key); }
		const_iterator find(const key_type& key) const { return rep.find(key); }

		size_type count(const key_type& key) const { return rep.count(key); }

		pair<iterator, iterator> equal_range(const key_type& key)
		{
			return rep.equal_range(key);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& key) const
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

	template <class _Key, class _T, class HF, class EqKey, class _Alloc>
	inline bool operator==(const unordered_multimap<_Key, _T, HF, EqKey, _Alloc>& hm1,
		const unordered_multimap<_Key, _T, HF, EqKey, _Alloc>& hm2)
	{
		return hm1.rep == hm2.rep;
	}

	template <class _Key, class _T, class _HashFcn, class _EqualKey, class _Alloc>
	inline void swap(unordered_multimap<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm1,
		unordered_multimap<_Key, _T, _HashFcn, _EqualKey, _Alloc>& hm2)
	{
		hm1.swap(hm2);
	}
} // end of MyStl
#endif // end of UNORDERED_MAP_H_