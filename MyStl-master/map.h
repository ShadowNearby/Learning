/*
 * 关联容器map
 * 键值不允许重复
 */

#ifndef MAP_H_
#define MAP_H_

#include "rb_tree.h"
#include <initializer_list>

namespace MyStl
{

	template <class _Key, class _T, class _Compare = less<_Key>, class _Alloc = alloc>
	class map 
	{
	public:
		typedef _Key                 key_type;	    // 键值型别
		typedef _T                   data_type;		// 真值型别
		typedef _T                   mapped_type;	// map独有,等同于真值型别
		typedef pair<const _Key, _T> value_type;	// 元素型别（键值/真值）
		typedef _Compare             key_compare;	// 键值比较函数

		// 以下定义一个 functor，其作用就是唤起元素比较函数。
		class value_compare
			: public binary_function<value_type, value_type, bool>
		{
			friend class map<_Key, _T, _Compare, _Alloc>;
		protected:
			_Compare comp;
			value_compare(_Compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const 
			{
				return comp(x.first, y.first);
			}
		};

	private:
		// 以map元素型别（一个pair）的第一型别，做为RB-tree节点的键值型别。
		typedef rb_tree<key_type, value_type, select1st<value_type>, key_compare, _Alloc> rep_type;
		rep_type t;  // 以红黑树（RB-tree）表现 map
	public:
		typedef typename rep_type::pointer                  pointer;
		typedef typename rep_type::const_pointer            const_pointer;
		typedef typename rep_type::reference                reference;
		typedef typename rep_type::const_reference          const_reference;
		typedef typename rep_type::iterator                 iterator;  //与set的iterator不同
		typedef typename rep_type::const_iterator           const_iterator;
		typedef typename rep_type::size_type                size_type;
		typedef typename rep_type::difference_type          difference_type;

		// 构造函数
		// map一定使用 insert_unique() 而不使用 insert_equal()。
		// multimap 才使用 insert_equal()。

		map() : t(_Compare()) {}
		explicit map(const _Compare& comp) : t(comp) {}

		template <class _InputIterator>
		map(_InputIterator first, _InputIterator last)
			: t(_Compare())
		{
			t.insert_unique(first, last);
		}

		template <class _InputIterator>
		map(_InputIterator first, _InputIterator last, const _Compare& comp) : t(comp)
		{
			t.insert_unique(first, last);
		}

		map(const std::initializer_list<pair<_Key, _T>>& il) : t(_Compare())
		{
			t.insert_unique(il.begin(), il.end());
		}

		map(const std::initializer_list<pair<_Key, _T>>& il, const _Compare comp) : t(comp)
		{
			t.insert_unique(il.begin(), il.end());
		}

		map(const map<_Key, _T, _Compare, _Alloc>& x) : t(x.t) {}
		map<_Key, _T, _Compare, _Alloc>& operator=(const map<_Key, _T, _Compare, _Alloc>& x)
		{
			t = x.t;
			return *this;
		}

		//接口函数：
		key_compare key_comp() const { return t.key_comp(); }
		value_compare value_comp() const { return value_compare(t.key_comp()); }
		iterator begin() { return t.begin(); }
		const_iterator begin() const { return t.begin(); }
		iterator end() { return t.end(); }
		const_iterator end() const { return t.end(); }
		bool empty() const { return t.empty(); }
		size_type size() const { return t.size(); }
		size_type max_size() const { return t.max_size(); }
		_T& operator[](const key_type& k) //根据键值在map中查找，如果找到，返回真值的引用
			                              //未找到，插入该键值，真值默认初始化，之后可以被修改
		{
			return (*((insert(value_type(k, _T()))).first)).second;
		}
		void swap(map<_Key, _T, _Compare, _Alloc>& x) { t.swap(x.t); }

		// insert()返回一个pair，bool参数标示插入成功与否，如成功，第一参数返回插入位置
		pair<iterator, bool> insert(const value_type& x) { return t.insert_unique(x); }
		iterator insert(iterator position, const value_type& x)
		{
			return t.insert_unique(position, x);
		}
		template <class _InputIterator>
		void insert(_InputIterator first, _InputIterator last) {
			t.insert_unique(first, last);
		}


		void erase(iterator position) { t.erase(position); }
		size_type erase(const key_type& x) { return t.erase(x); }
		void erase(iterator first, iterator last) { t.erase(first, last); }
		void clear() { t.clear(); }

		// map operations:

		iterator find(const key_type& x) { return t.find(x); }
		const_iterator find(const key_type& x) const { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
		const_iterator lower_bound(const key_type& x) const {
			return t.lower_bound(x);
		}
		iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
		const_iterator upper_bound(const key_type& x) const {
			return t.upper_bound(x);
		}

		pair<iterator, iterator> equal_range(const key_type& x) {
			return t.equal_range(x);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
			return t.equal_range(x);
		}
		friend bool operator==(const map&, const map&);
		friend bool operator<(const map&, const map&);
	};

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline bool operator==(const map<_Key, _T, _Compare, _Alloc>& x,
		const map<_Key, _T, _Compare, _Alloc>& y) {
		return x.t == y.t;
	}

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline bool operator<(const map<_Key, _T, _Compare, _Alloc>& x,
		const map<_Key, _T, _Compare, _Alloc>& y) {
		return x.t < y.t;
	}

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline void swap(map<_Key, _T, _Compare, _Alloc>& x,
		map<_Key, _T, _Compare, _Alloc>& y) {
		x.swap(y);
	}
}// end of MyStl

#endif // end of MAP_H_
